module MainModel exposing (Model, Msg (..), OmniElement (..), SuggestionResponseItem, CreateElementResponse)

import Material
import Http
import Views.IntLiteral

type alias Model = { dummy: String, mdl: Material.Model, activeSuggestions: (List SuggestionResponseItem), elements: (List OmniElement) }

type alias SuggestionResponseItem = { suggestion: String, orderno: Int, createUrl: String }

type alias CreateElementResponse = { elementType: String, elementValue: String }

type Msg =
    Mdl (Material.Msg Msg) |
    FetchSuggestion String |
    ProvideSuggestion (Result Http.Error (List SuggestionResponseItem)) |
    AcceptSuggestion SuggestionResponseItem |
    ElementCreated (Result Http.Error CreateElementResponse)

type OmniElement =
    IntLiteral Views.IntLiteral.Model

