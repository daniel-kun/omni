
namespace OmniPrototype
{
    public class OmIfStatement : OmStatement
    {
        public event ChangeHandler ConditionChanged;
        public event ChangeHandler BodyChanged;

        public OmExpression Condition
        {
            get
            {
                return mCondition;
            }
            set
            {
                mCondition = value;
                EmitChangeEvent(ConditionChanged);
            }
        }

        public OmStatement Body
        {
            get
            {
                return mBody;
            }
            set
            {
                mBody = value;
                EmitChangeEvent(BodyChanged);
            }
        }

        private OmExpression mCondition;
        private OmStatement mBody;

        public new OmMeta GetMetaStatic (OmContext theContext)
        {
            return theContext.IfStatementMeta;
        }

        public override OmMeta GetMeta(OmContext theContext)
        {
            return theContext.IfStatementMeta;
        }

    }
}
