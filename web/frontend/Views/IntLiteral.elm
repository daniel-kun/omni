module Views.IntLiteral exposing (Model, view)

import Html exposing (..)

type alias Model = Int

view : Model -> Html msg

view model =
    span [] [ text (toString model) ]

