module IntLiteralView exposing (dummy)

import Html exposing (..)

dummy intLiteral =
    span [] [ text (toString intLiteral.value) ]

