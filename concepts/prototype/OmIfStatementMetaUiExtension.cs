using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;

namespace OmniPrototype {
    public class OmIfStatementMetaUiExtension : OmMetaUiExtension {

        public OmIfStatementMetaUiExtension () : base ("if_statement")
        {
        }

        public override FrameworkElement CreateControls (
            OmContext theContext,
            StackPanel theLinesPanel,
            WrapPanel thePanel,
            ref int theIndex,
            OmStatement theExpression)
        {
            var ifStatement = theExpression as OmIfStatement;
            var ext = ifStatement.GetExtension(theContext, "omni.ui") as OmIfStatementUiExtension;
            Action <OmExpression> applyCondition = (theConditionExpression) =>
            {
                //int dummy = 0;
                //ext.ConditionInput.ReplaceWithExpression (theContext, theLinesPanel, thePanel, ref dummy, theConditionExpression);
            };

            var creator = new OmMetaUiControlCreator (
                (WrapPanel theInnerPanel, ref int thePlaceholderIndex, string thePlaceholderName) => {
                    if (thePlaceholderName == "condition") {
                        var result = new ExpressionInputControl (theContext, theExpression, OmType.Bool);
                        int index = thePlaceholderIndex;
                        result.ExpressionCreated += (ExpressionInputControl theSender, OmStatement theConditionExpression) =>
                        {
                            int localIndex = index;
                            result.ReplaceWithExpression(theContext, theLinesPanel, theInnerPanel, ref localIndex, theConditionExpression);
                        };
                        return result;
                    } else if (thePlaceholderName == "body") {
                        return new ExpressionInputControl (theContext, theExpression, OmType.Void);
                    } else if (thePlaceholderName == "else-body") {
                        return new ExpressionInputControl (theContext, theExpression, OmType.Void);
                    } else {
                        return null;
                    }
                });
            creator.CreateControlsFromTemplate (theContext, theLinesPanel, thePanel, ref theIndex, GetTemplate (theContext));
            return null;
        }

        public override OmEntityExtension CreateExtension()
        {
            return new OmIfStatementUiExtension ();
        }
    }
}
