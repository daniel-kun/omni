using System;
using System.Collections.Generic;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;

namespace OmniPrototype
{
    public class OmVariableUseExpressionMetaUiExtension : OmMetaUiExtension
    {
        public OmVariableUseExpressionMetaUiExtension() : base ("variable_use_expression")
        {
        }

        public override OmEntityExtension CreateExtension()
        {
            return new OmVariableUseExpressionUiExtension();
        }

        public override IEnumerable<List<FrameworkElement>> CreateControls(OmContext theContext, OmStatement theExpression)
        {
            var varUseExpr = theExpression as OmVariableUseExpression;
            var uiExt = varUseExpr.GetExtension (theContext, "omni.ui") as OmVariableUseExpressionUiExtension;
            var creator = new OmMetaUiControlCreator(
                (string thePlaceholderName) =>
                {
                    if (thePlaceholderName == "variable")
                    {
                        uiExt.VariableNameLabel = new TextBlock();
                        uiExt.Variable = varUseExpr.Variable;
                        varUseExpr.VariableChanged += (OmEntity theSender) =>
                        {
                            uiExt.Variable = varUseExpr.Variable;
                        };
                        return MakeSingleControlList(uiExt.VariableNameLabel);
                    }
                    else
                    {
                        throw new Exception(string.Format("Unknown placeholder name {0} for OmVariableUseExpression", thePlaceholderName));
                    }
                });
            return creator.CreateControlsFromTemplate(theContext, GetTemplate(theContext));
        }

    }
}
