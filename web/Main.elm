import Html exposing (..)
import Html.Attributes exposing (..)
import Html.Events exposing (..)
import MainModel exposing (..)
import Http 
import Json.Decode exposing (list, string, int, field, Decoder, map2, map3)
import Json.Encode
import Material
import Material.Scheme
import InputPlaceholderView
import IntLiteralView

main =
    Html.program { init = init, update = update, view = view, subscriptions = subscriptions }

-- INIT

init : (Model, Cmd Msg)

init =
    (Model "" Material.model [] [], Cmd.none)

-- UPDATE

update msg model =
    case msg of
        Mdl mdlMsg ->
            Material.update Mdl mdlMsg model
        FetchSuggestion text ->
            ({ model | dummy = "Fetching: " ++ text }, buildFetchSuggestionHttpRequest text)
        ProvideSuggestion (Ok val) ->
            ({ model | dummy = "OK!", activeSuggestions = val}, Cmd.none)
        ProvideSuggestion (Err err) ->
            ({ model | dummy = "ERROR: " ++ (toString err)}, Cmd.none)
        AcceptSuggestion item ->
            ({ model | dummy = "Accepted: " ++ item.suggestion }, buildCreateElementHttpRequest item)
        ElementCreated (Ok element) ->
            case omniElementFromCreateElementResponse element of
                Ok newElement ->
                    ({ model | activeSuggestions = [], elements = model.elements ++ [newElement] }, Cmd.none)
                Err errorMessage ->
                    ({ model | dummy = "Error: " ++ errorMessage }, Cmd.none)
        ElementCreated (Err err) ->
            ({ model | dummy = "HTTP Error: " ++ (toString err)}, Cmd.none)

-- VIEW

viewSuggestionResponseItem item =
    a [onClick (AcceptSuggestion item)] [ text item.suggestion ]

viewSuggestionResponseItems items =
    case items of
        [] ->
            []
        [a] ->
            [viewSuggestionResponseItem a]
        a::rest ->
            viewSuggestionResponseItem a :: viewSuggestionResponseItems rest

viewOmniElements elements =
    case elements of
        [] ->
            []
        [IntLiteral v] ->
            [p [] [ text (toString v) ]]
        IntLiteral v::rest ->
            p [] [ text (toString v) ] :: viewOmniElements rest

view : Model -> Html Msg

view model =
    div [] 
    ((viewOmniElements model.elements) ++
    [
        InputPlaceholderView.view Mdl model.mdl,
        p [] [ text model.dummy ]
    ] ++ 
    (viewSuggestionResponseItems model.activeSuggestions)) |> Material.Scheme.top

-- SUBSCRIPTIONS

subscriptions : Model -> Sub Msg
subscriptions model =
    Sub.none

-- LOGIC

buildFetchSuggestionHttpRequest text =
    let
        url = "http://localhost:5000/api/suggestion"

        request = Http.post url (Http.jsonBody (Json.Encode.object [("text", Json.Encode.string text)])) (Json.Decode.field "results" (Json.Decode.list (map3 SuggestionResponseItem (field "suggestion" string) (field "orderNo" int) (field "createUrl" string))))
    in
        Http.send ProvideSuggestion request

buildCreateElementHttpRequest suggestionResponseItem =
    let
        url = suggestionResponseItem.createUrl

        request = Http.get url (map2 CreateElementResponse (field "elementType" string) (field "elementValue" string))
    in
        Http.send ElementCreated request

omniElementFromCreateElementResponse response =
    case response.elementType of
        "int-literal" ->
            case String.toInt response.elementValue of
                Ok val ->
                    Ok (IntLiteral val)
                Err _ ->
                    Err ("Could not convert " ++ response.elementValue ++ " to int.")
        _ ->
            Err ("Unknown elementType " ++ response.elementType)

