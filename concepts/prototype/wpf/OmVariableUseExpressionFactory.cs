
namespace OmniPrototype
{
    public class OmVariableUseExpressionFactory : OmEntityFactory
    {
        public OmVariableUseExpressionFactory (OmVariableDeclarationExpression theVariable)
        {
            Variable = theVariable;
        }

        public OmEntity Create(OmScope theParentScope)
        {
            return new OmVariableUseExpression()
            {
                Variable = Variable
            };
        }

        public OmVariableDeclarationExpression Variable
        {
            get;
            private set;
        }


        public string Preview
        {
            get
            {
                return Variable.Name;
            }
        }
    }
}
