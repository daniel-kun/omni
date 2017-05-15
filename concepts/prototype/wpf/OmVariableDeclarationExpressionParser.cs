using System.Collections.Generic;

namespace OmniPrototype
{
    public class OmVariableDeclarationExpressionParser : OmEntityParser
    {
        public IEnumerable<OmEntityFactory> TryParse(OmScope theScope, OmType theTargetType, string theInput)
        {
            if ("variable".Contains(theInput))
            {
                yield return new OmVariableDeclarationExpressionFactory ();
            }
        }
    }
}
