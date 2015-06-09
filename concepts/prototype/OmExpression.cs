
namespace OmniPrototype
{
    public class OmExpression : OmStatement
    {
        public event ChangeHandler TypeChanged;

        public OmType Type
        {
            get
            {
                return mType;
            }
            set
            {
                mType = value;
                EmitChangeEvent(TypeChanged);
            }
        }

        private OmType mType;

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
