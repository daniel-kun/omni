
namespace OmniPrototype
{
    public class OmBoolLiteralExpression : OmExpression
    {
        public event ChangeHandler ValueChanged;

        public OmBoolLiteralExpression ()
        {
            Type = OmType.Bool;
            ValueChanged += (OmEntity theSender) =>
            {
                EmitChanged ();
            };
        }

        public bool Value
        {
            get {
                return mValue;
            }
            set {
                mValue = value;
                EmitChangeEvent (ValueChanged);
            }
        }

        private bool mValue = false;

        public static new OmMeta GetMetaStatic (OmContext theContext)
        {
            return theContext.BoolLiteralExpressionMeta;
        }

        public override OmMeta GetMeta(OmContext theContext)
        {
            return theContext.BoolLiteralExpressionMeta;
        }

    }
}
