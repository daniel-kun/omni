using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OmniPrototype
{
    public class OmIntLiteralParser : OmEntityParser
    {
        public IEnumerable<OmEntityFactory> TryParse(OmScope theScope, OmType theTargetType, string theInput)
        {
            int value;
            if (int.TryParse(theInput, out value))
            {
                yield return new OmIntLiteralFactory(value);
            }
        }
    }
}
