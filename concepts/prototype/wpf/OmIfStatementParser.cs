using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OmniPrototype {
    public class OmIfStatementParser : OmEntityParser {

        public IEnumerable<OmEntityFactory> TryParse(OmScope theScope,OmType theTargetType,string theInput)
        {
            if ("if".Contains(theInput))
            {
                yield return new OmIfStatementFactory ();
            }
        }
    }
}
