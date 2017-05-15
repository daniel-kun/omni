using System.Collections.Generic;

namespace OmniPrototype
{
    public class OmBoolLiteralExpressionParser : OmEntityParser
    {
        public IEnumerable<OmEntityFactory> TryParse(OmScope theScope, OmType theTargetType, string theInput)
        {
            if ( "true".Contains(theInput))
            {
                yield return new OmBoolLiteralExpressionFactory(true);
            }
            if ("false".Contains(theInput))
            {
                yield return new OmBoolLiteralExpressionFactory(false);
            }
        }
    }
}
