
namespace OmniPrototype
{
    public class OmVariableUseExpression : OmExpression
    {
        public event ChangeHandler VariableChanged;

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
                    mVariable.TypeChanged -= VariableTypeChanged;
                }
                mVariable = value;
                EmitChangeEvent(VariableChanged);
                if (mVariable != null)
                {
                    mVariable.TypeChanged += VariableTypeChanged;
                    mVariable.NameChanged += VariableNameChanged;
                    Name = mVariable.Name;
                }
            }
        }

        private void VariableNameChanged (OmEntity theSender)
        {
            var variable = theSender as OmVariableDeclarationExpression;
            if (variable != null)
            {
                Name = variable.Name;
            }
            else
            {
                Name = null;
            }
        }

        private OmVariableDeclarationExpression mVariable;

        private void VariableTypeChanged(OmEntity theSender)
        {
            var variable = theSender as OmVariableDeclarationExpression;
            if (variable != null)
            {
                Type = variable.Type;
            }
            else
            {
                Type = OmType.Void;
            }
        }

        public new OmMeta GetMetaStatic (OmContext theContext)
        {
            return theContext.VariableUseExpressionMeta;
        }

        public override OmMeta GetMeta(OmContext theContext)
        {
            return theContext.VariableUseExpressionMeta;
        }

    }

}
