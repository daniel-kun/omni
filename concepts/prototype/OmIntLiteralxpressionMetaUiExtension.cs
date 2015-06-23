using System;
using System.Collections.Generic;
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


        public override IEnumerable<List<FrameworkElement>> CreateControls2(OmContext theContext, OmStatement theExpression)
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

            var creator = new OmMetaUiControlCreator(
                (string theName) =>
                {
                    if (theName == "value")
                    {
                        ext.ValueInput = new TextBox();
                        ext.ValueInput.Text = literalExpr.Value.ToString();
                        ext.ValueInput.TextChanged += (object sender, TextChangedEventArgs e) =>
                        {
                            int value;
                            if (int.TryParse(ext.ValueInput.Text, out value))
                            {
                                literalExpr.Value = value;
                            }
                        };
                        return MakeSingleControlList (ext.ValueInput);
                    }
                    else
                    {
                        throw new Exception(string.Format("In OmVariableDeclarationExpressionMetaUiExtension: Unknown text placeholder {0}", theName));
                    }

                });
            return creator.CreateControlsFromTemplate2(theContext, GetTemplate(theContext));
        }
    }
}
