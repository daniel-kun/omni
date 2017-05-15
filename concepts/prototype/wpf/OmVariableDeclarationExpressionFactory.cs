
namespace OmniPrototype
{
    public class OmVariableDeclarationExpressionFactory : OmEntityFactory
    {
        public OmEntity Create (OmScope theParentScope)
        {
            return new OmVariableDeclarationExpression();
        }



        public string Preview
        {
            get
            {
                return "variable...";
            }
        }
    }
}
