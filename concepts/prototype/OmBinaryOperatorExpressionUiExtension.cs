using System.Windows.Controls;

namespace OmniPrototype
{
    public class OmBinaryOperatorExpressionUiExtension : OmEntityUiExtension
    {
        public ExpressionInputControl LeftOperandControl
        {
            get;
            set;
        }

        public ExpressionInputControl RightOperandControl
        {
            get;
            set;
        }

        public ComboBox OperatorSelector
        {
            get;
            set;
        }
    }
}
