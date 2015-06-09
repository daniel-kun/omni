using System;
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

        public override FrameworkElement CreateControls(OmContext theContext, StackPanel theLinesPanel, WrapPanel thePanel, ref int theIndex, OmStatement theExpression)
        {
            var ext = theExpression.GetExtension(theContext, "omni.ui") as OmVariableUseExpressionUiExtension;
            var varUseExpr = theExpression as OmVariableUseExpression;

            Action applyName = () =>
            {
                ext.VariableNameLabel.Text = varUseExpr.Name;
            };

            varUseExpr.NameChanged += (OmEntity theSender) =>
            {
                applyName();
            };

            FrameworkElement focusElement = null;
            var creator = new OmMetaUiControlCreator(
                (WrapPanel theP, ref int thePlaceholderIndex, string theName) =>
                {
                    if (theName == "variable")
                    {
                        ext.VariableNameLabel = new TextBlock ()
                        {
                            VerticalAlignment = VerticalAlignment.Center,
                            Padding = new Thickness (3,0,3,0),
                            Margin = new Thickness (2,0,2,0),
                            Foreground = Brushes.DarkRed
                        };
                        applyName();
                        focusElement = ext.VariableNameLabel;
                        return ext.VariableNameLabel;
                    }
                    else
                    {
                        throw new Exception(string.Format("In OmVariableDeclarationExpressionMetaUiExtension: Unknown text placeholder {0}", theName));
                    }

                });
            creator.CreateControlsFromTemplate(theContext, theLinesPanel, thePanel, ref theIndex, GetTemplate (theContext));
            return focusElement;
        }

        public override OmEntityExtension CreateExtension()
        {
            return new OmVariableUseExpressionUiExtension();
        }
    }
}
