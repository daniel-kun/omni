using System;
using System.Windows;
using System.Windows.Controls;

namespace OmniPrototype
{
    public class OmIntLiteralxpressionMetaUiExtension : OmMetaUiExtension
    {
        public OmIntLiteralxpressionMetaUiExtension () : base ("int_literal_expression")
        {
        }

        public override OmEntityExtension CreateExtension()
        {
            return new OmIntLiteralExpressionUiExtension();
        }


        public override FrameworkElement CreateControls(OmContext theContext, StackPanel theLinesPanel, WrapPanel thePanel, ref int theIndex, OmStatement theExpression)
        {

            var ext = theExpression.GetExtension(theContext, "omni.ui") as OmIntLiteralExpressionUiExtension;
            var literalExpr = theExpression as OmIntLiteralExpression;

            Action applyValue = () =>
            {
                ext.ValueInput.Text = literalExpr.Value.ToString();
            };

            literalExpr.ValueChanged += (OmEntity theSender) =>
            {
                applyValue();
            };

            FrameworkElement focusElement = null;
            var creator = new OmMetaUiControlCreator(
                (WrapPanel theP, ref int thePlaceholderIndex, string theName) =>
                {
                    if (theName == "value")
                    {
                        ext.ValueInput = new TextBox();
                        ext.ValueInput.Text = literalExpr.Value.ToString ();
                        ext.ValueInput.TextChanged += (object sender,TextChangedEventArgs e) =>
                        {
                            int value;
                            if (int.TryParse (ext.ValueInput.Text, out value)) {
                                literalExpr.Value = value;
                            }
                        };
                        return ext.ValueInput;
                    }
                    else
                    {
                        throw new Exception(string.Format("In OmVariableDeclarationExpressionMetaUiExtension: Unknown text placeholder {0}", theName));
                    }

                });
            creator.CreateControlsFromTemplate (theContext, theLinesPanel, thePanel, ref theIndex, GetTemplate (theContext));
            return focusElement;
        }
    }
}
