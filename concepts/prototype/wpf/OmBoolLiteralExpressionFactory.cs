
namespace OmniPrototype
{
    public class OmBoolLiteralExpressionFactory : OmEntityFactory
    {
        public OmBoolLiteralExpressionFactory (bool theValue)
        {
            Value = theValue;
        }

        public OmEntity Create (OmScope theParentScope)
        {
            return new OmBoolLiteralExpression()
            {
                Value = Value
            };
        }

        public bool Value
        {
            get;
            private set;
        }


        public string Preview
        {
            get
            {
                if (Value)
                {
                    return "true";
                }
                else
                {
                    return "false";
                }
            }
        }
    }
}
