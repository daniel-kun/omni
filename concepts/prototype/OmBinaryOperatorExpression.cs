
namespace OmniPrototype
{
    public class OmBinaryOperatorExpression : OmExpression
    {
        public event ChangeHandler LeftOperandChanged;

        private OmExpression mLeftOperand;

        public OmExpression LeftOperand
        {
            get
            {
                return mLeftOperand;
            }
            set
            {
                mLeftOperand = value;
                EmitChangeEvent (LeftOperandChanged);
            }
        }

        public event ChangeHandler RightOperandChanged;

        private OmExpression mRightOperand;
        private string mOperator;

        public OmExpression RightOperand
        {
            get
            {
                return mRightOperand;
            }
            set
            {
                mRightOperand = value;
                EmitChangeEvent(RightOperandChanged);
            }
        }

        public string Operator
        {
            get
            {
                return mOperator;
            }
            set
            {
                mOperator = value;
                EmitChangeEvent(OperatorChanged);
            }
        }

        public event ChangeHandler OperatorChanged;

        public static new OmMeta GetMetaStatic (OmContext theContext)
        {
            return theContext.BinaryOperatorExpressionMeta;
        }

        public override OmMeta GetMeta(OmContext theContext)
        {
            return theContext.BinaryOperatorExpressionMeta;
        }

    }
}
