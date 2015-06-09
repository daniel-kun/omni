using System.Windows.Controls;

namespace OmniPrototype
{
    public class OmVariableDeclarationUiExtension : OmEntityExtension
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
