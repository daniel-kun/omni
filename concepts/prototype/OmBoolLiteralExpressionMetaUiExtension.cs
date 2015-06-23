namespace OmniPrototype {
    using System;
    using System.Collections.Generic;
    using System.Windows;
    using System.Windows.Controls;

    public class OmBoolLiteralExpressionMetaUiExtension : OmMetaUiExtension
    {
        
        public OmBoolLiteralExpressionMetaUiExtension () : base ("bool_literal_expression")
        {
        }

        public override OmEntityExtension CreateExtension()
        {
            return new OmBoolLiteralExpressionUiExtension ();
        }

        public override IEnumerable<List<FrameworkElement>> CreateControls (OmContext theContext, OmStatement theExpression)
        {
            var ext = theExpression.GetExtension(theContext, "omni.ui") as OmBoolLiteralExpressionUiExtension;
            var literalExpr = theExpression as OmBoolLiteralExpression;

            Action applyValue = () =>
            {
                ext.ValueInput.Text = literalExpr.Value.ToString().ToLower();
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
                        if (literalExpr.Value)
                        {
                            ext.ValueInput.Text = "true";
                        }
                        else
                        {
                            ext.ValueInput.Text = "false";
                        }
                        ext.ValueInput.TextChanged += (object sender, TextChangedEventArgs e) =>
                        {
                            bool value;
                            if (bool.TryParse(ext.ValueInput.Text, out value))
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
            return creator.CreateControlsFromTemplate2 (theContext, GetTemplate(theContext));
        }

    }
}
