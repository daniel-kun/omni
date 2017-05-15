
namespace OmniPrototype
{
    public class OmVariableDeclarationExpression : OmExpression
    {
        public event ChangeHandler InitializationExpressionChanged;

        public OmExpression InitializationExpression
        {
            get
            {
                return mInitializationExpression;
            }
            set
            {
                if (mInitializationExpression != null)
                {
                    mInitializationExpression.TypeChanged -= InitializationExpressionTypeChanged;
                }
                mInitializationExpression = value;
                if (mInitializationExpression != null)
                {
                    mInitializationExpression.TypeChanged += InitializationExpressionTypeChanged;
                }
                Type = mInitializationExpression.Type;
                EmitChangeEvent(InitializationExpressionChanged);
            }

        }

        private void InitializationExpressionTypeChanged(OmEntity theSender)
        {
            var expr = theSender as OmExpression;
            if (expr != null)
            {
                Type = expr.Type;
            }
        }

        private OmExpression mInitializationExpression;

        public new OmMeta GetMetaStatic (OmContext theContext)
        {
            return theContext.VariableDeclarationExpressionMeta;
        }

        public override OmMeta GetMeta(OmContext theContext)
        {
            return theContext.VariableDeclarationExpressionMeta;
        }

    }

}
