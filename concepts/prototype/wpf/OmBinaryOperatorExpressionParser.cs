using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OmniPrototype
{
    public class OmBinaryOperatorExpressionParser : OmEntityParser
    {
        public IEnumerable<OmEntityFactory> TryParse(OmScope theScope, OmType theTargetType, string theInput)
        {
            if (theInput.IndexOfAny("+-*/".ToCharArray()) == 0 && theInput.Length == 1)
            {
                yield return new OmBinaryOperatorExpressionFactory (theInput);
            }
        }
    }
}
