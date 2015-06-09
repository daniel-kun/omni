
namespace OmniPrototype
{
    public class OmIntLiteralExpression : OmExpression
    {
        public OmIntLiteralExpression()
        {
            ValueChanged += (OmEntity theSender) => 
            {
                EmitChanged ();
            };
        }

        public event ChangeHandler ValueChanged;
        private int mValue;

        public int Value
        {
            get
            {
                return mValue;
            }
            set
            {
                mValue = value;
                EmitChangeEvent(ValueChanged);
            }
        }

        public static new OmMeta GetMetaStatic(OmContext theContext)
        {
            return theContext.IntLiteralExpressionMeta;
        }

        public override OmMeta GetMeta(OmContext theContext)
        {
            return theContext.IntLiteralExpressionMeta;
        }
    }
}
