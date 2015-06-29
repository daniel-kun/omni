using System.Windows.Controls;

namespace OmniPrototype
{
    public class OmVariableUseExpressionUiExtension : OmEntityUiExtension
    {
        private OmVariableDeclarationExpression mVariable;
        public OmVariableDeclarationExpression Variable
        {
            get
            {
                return mVariable;
            }
            set
            {
                if (mVariable != null)
                {
                    mVariable.NameChanged -= VariableNameChanged;
                }
                mVariable = value;
                if (mVariable != null)
                {
                    mVariable.NameChanged += VariableNameChanged;
                }
                VariableNameChanged(null);
            }
        }

        private void VariableNameChanged(OmEntity theSender)
        {
            if (Variable != null)
            {
                VariableNameLabel.Text = Variable.Name;
            }
            else
            {
                VariableNameLabel.Text = string.Empty;
            }
        }

        public TextBlock VariableNameLabel
        {
            get;
            set;
        }
    }
}
