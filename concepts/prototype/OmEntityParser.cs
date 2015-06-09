using System.Collections.Generic;

namespace OmniPrototype
{
    public interface OmEntityParser
    {
        IEnumerable <OmEntityFactory> TryParse(OmScope theScope, OmType theTargetType, string theInput);
    }
}
