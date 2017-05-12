module InputPlaceholderView exposing (view)

import MainModel exposing (Model, Msg)
import IntLiteralView
import Material.Textfield as Textfield
import Material.Options as Options

view msg mdl =
        Textfield.render msg [0] mdl
            [ Textfield.label "Code here!",
              Options.onInput (\text -> MainModel.FetchSuggestion text)]
            []

