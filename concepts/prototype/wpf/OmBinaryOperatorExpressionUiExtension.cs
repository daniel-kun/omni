using System.Windows.Controls;

namespace OmniPrototype
{
    public class OmBinaryOperatorExpressionUiExtension : OmEntityUiExtension
    {
        public Grid Grid
        {
            get;
            set;
        }

        public WrapPanel LeftOpPanel
        {
            get;
            set;
        }

        public WrapPanel RightOpPanel
        {
            get;
            set;
        }

        public OperatorSelectionControl OpSelectionControl
        {
            get;
            set;
        }

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

    }
}
