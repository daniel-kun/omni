
namespace OmniPrototype
{
    class Example
    {
        /*
        This demo code should be created in this prototype:
        [x] OmBlockStatement
        [x] OmVariableDeclarationExpression
        [x] OmBoolLiteralExpression
        [x] OmIntLiteralExpression
        [x] OmVariableUseExpression
        [x] OmBinaryOperatorExpression: For +, && and <
        [ ] OmIfElseStatement
        [ ] OmReturnStatement
        */
        private bool ExampleFunc()
        {
            var variable1 = true;
            var variable2 = 20;
            var variable3 = variable2 + 30;
            if (variable1 && variable2 < variable3)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }
}
