
namespace OmniPrototype
{
    public class OmExpression : OmStatement
    {
        public override OmType Type
        {
            get
            {
                return mType;
            }
            set
            {
                mType = value;
                EmitTypeChangedEvent ();
            }
        }

        public new OmMeta GetMetaStatic (OmContext theContext)
        {
            return null;
        }

        public override OmMeta GetMeta(OmContext theContext)
        {
            return null;
        }

    }

}
