using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OmniPrototype
{
    public class OmBinaryOperatorExpressionFactory : OmEntityFactory
    {
        public OmBinaryOperatorExpressionFactory(string theOperator)
        {
            Operator = theOperator;
        }

        public string Operator
        {
            get;
            private set;
        }

        public OmEntity Create(OmScope theParentScope)
        {
            return new OmBinaryOperatorExpression()
            {
                Operator = Operator
            };
        }

        public string Preview
        {
            get
            {
                return "<left> " + Operator + " <right>";
            }
        }
    }
}
