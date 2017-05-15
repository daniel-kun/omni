using System.Windows.Controls;

namespace OmniPrototype
{
    public class OmVariableDeclarationUiExtension : OmEntityUiExtension
    {
        public TextBox NameInput
        {
            get;
            set;
        }

        public ExpressionInputControl InitializationExpressionInput
        {
            get;
            set;
        }
    }
}
