using System.Collections.Generic;

namespace OmniPrototype
{
    public class OmContext
    {
        public OmContext()
        {
            VariableDeclarationExpressionMeta.  SetExtension("omni.ui", new OmVariableDeclarationExpressionMetaUiExtension());
            BoolLiteralExpressionMeta.          SetExtension("omni.ui", new OmBoolLiteralExpressionMetaUiExtension());
            BlockStatementMeta.                 SetExtension("omni.ui", new OmBlockStatementMetaUiExtension());
            IntLiteralExpressionMeta.           SetExtension("omni.ui", new OmIntLiteralxpressionMetaUiExtension());
            VariableUseExpressionMeta.          SetExtension("omni.ui", new OmVariableUseExpressionMetaUiExtension());
            BinaryOperatorExpressionMeta.       SetExtension("omni.ui", new OmBinaryOperatorExpressionMetaUiExtension());
            IfStatementMeta.                    SetExtension("omni.ui", new OmIfStatementMetaUiExtension ());
        }

        public readonly OmMeta VariableDeclarationExpressionMeta = new OmMeta ("variable_declaration_expression", new OmVariableDeclarationExpressionParser ());
        public readonly OmMeta BoolLiteralExpressionMeta         = new OmMeta ("bool_literal_expression", new OmBoolLiteralExpressionParser ());
        public readonly OmMeta BlockStatementMeta                = new OmMeta ("block", null);
        public readonly OmMeta IntLiteralExpressionMeta          = new OmMeta ("int_literal_expression", null);
        public readonly OmMeta VariableUseExpressionMeta         = new OmMeta ("variable_use_expression", new OmVariableUseExpressionParser ());
        public readonly OmMeta BinaryOperatorExpressionMeta      = new OmMeta ("binary_operator_expression", null);
        public readonly OmMeta IfStatementMeta                   = new OmMeta ("if_statement", new OmIfStatementParser ());

        public Dictionary<string, string> Templates = new Dictionary<string, string>()
        {
            {"binary_operator_expression", "<left> <operator> <right>"},
            {"block", "<statement>"},
            {"bool_literal_expression", "<value>"},
            {"int_literal_expression", "<value>"},
            {"variable_declaration_expression", "variable [name]=<initexpr>"},
            {"variable_use_expression", "<variable>"},
            {"if_statement",
@"if (<condition>) {
    <body>
} else {
    <else-body>
}"},
        };

        public IEnumerable <OmMeta> GetEntityMetas ()
        {
            yield return VariableDeclarationExpressionMeta;
            yield return BoolLiteralExpressionMeta;
            yield return BlockStatementMeta;
            yield return IntLiteralExpressionMeta;
            yield return VariableUseExpressionMeta;
            yield return BinaryOperatorExpressionMeta;
            yield return IfStatementMeta;
        }
    }

}
