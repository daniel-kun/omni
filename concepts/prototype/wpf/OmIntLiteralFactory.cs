using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OmniPrototype
{
    public class OmIntLiteralFactory : OmEntityFactory
    {
        public OmIntLiteralFactory(int theValue)
        {
            Value = theValue;
        }

        public int Value
        {
            get;
            private set;
        }

        public OmEntity Create(OmScope theParentScope)
        {
            return new OmIntLiteralExpression()
            {
                Value = Value
            };
        }

        public string Preview
        {
            get
            {
                return Value.ToString();
            }
        }
    }
}
