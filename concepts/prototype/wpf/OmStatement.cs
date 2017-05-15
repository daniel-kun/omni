
using System;
namespace OmniPrototype
{
    public class OmStatement : OmScope
    {
        public event ChangeHandler TypeChanged;

        public virtual OmType Type
        {
            get
            {
                return mType;
            }
            set
            {
                throw new Exception ("Can not change type of a statement, it's always void");
            }
        }

        protected OmType mType;

        protected void EmitTypeChangedEvent ()
        {
            EmitChangeEvent(TypeChanged);
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
