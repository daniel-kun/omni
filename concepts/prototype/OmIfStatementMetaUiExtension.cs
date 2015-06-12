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
            var creator = new OmMetaUiControlCreator (
                (WrapPanel theInnerPanel, ref int thePlaceholderIndex, string thePlaceholderName) => {
                    if (thePlaceholderName == "condition") {
                        return new ExpressionInputControl (theContext, theExpression, OmType.Bool);
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
