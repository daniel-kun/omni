using System.Collections.Generic;

namespace OmniPrototype
{
    public class OmVariableUseExpressionParser : OmEntityParser
    {
        public IEnumerable<OmEntityFactory> TryParse(OmScope theScope, OmType theTargetType, string theInput)
        {
            foreach (var childExpression in theScope.Components)
            {
                if (childExpression.Value is OmVariableDeclarationExpression)
                {
                    var varDecl = (OmVariableDeclarationExpression)childExpression.Value;
                    if (varDecl.Name.Contains(theInput))
                    {
                        yield return new OmVariableUseExpressionFactory(varDecl);
                    }
                }
            }
            if (theScope.Parent is OmScope) {
                foreach (var factory in TryParse((OmScope) theScope.Parent, theTargetType, theInput))
                {
                    yield return factory;
                }
            }
        }
    }
}
