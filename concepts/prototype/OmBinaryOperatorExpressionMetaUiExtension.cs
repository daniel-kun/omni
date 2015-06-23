using System;
using System.Collections.Generic;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;

namespace OmniPrototype
{
    public class OmBinaryOperatorExpressionMetaUiExtension : OmMetaUiExtension
    {
        public OmBinaryOperatorExpressionMetaUiExtension() : base ("binary_operator_expression")
        {
        }

        private delegate FrameworkElement applyOperand(WrapPanel thePanel, ref int theIndex);

        public override IEnumerable<List<FrameworkElement>> CreateControls (OmContext theContext, OmStatement theExpression)
        {
            var ext = theExpression.GetExtension(theContext, "omni.ui") as OmBinaryOperatorExpressionUiExtension;
            var binOpExpr = theExpression as OmBinaryOperatorExpression;

            binOpExpr.LeftOperandChanged += (OmEntity theSender) =>
            {
                ext.LeftOperandControl.ReplaceWithExpression(theContext, binOpExpr.LeftOperand);
            };
            binOpExpr.RightOperandChanged += (OmEntity theSender) =>
            {
                ext.RightOperandControl.ReplaceWithExpression(theContext, binOpExpr.RightOperand);
            };
            binOpExpr.OperatorChanged += (OmEntity theSender) =>
            {
                ext.OperatorSelector.SelectedValue = binOpExpr.Operator;
            };

            var creator = new OmMetaUiControlCreator(
                (string theName) =>
                {
                    if (theName == "left")
                    {
                        return ExpressionInputControl.CreateInputOrControls(
                            theContext,
                            theExpression,
                            binOpExpr.LeftOperand,
                            OmType.Void,
                            (theInput) =>
                            {
                                ext.LeftOperandControl = theInput;
                            });
                    }
                    else if (theName == "right")
                    {
                        return ExpressionInputControl.CreateInputOrControls(
                            theContext,
                            theExpression,
                            binOpExpr.RightOperand,
                            OmType.Void,
                            (theInput) =>
                            {
                                ext.RightOperandControl = theInput;
                            });
                    }
                    else if (theName == "operator")
                    {
                        var grid = new Grid();
                        var fakeCombo = new ComboBox();
                        fakeCombo.Items.Add("&&");
                        fakeCombo.SelectedIndex = 0;
                        fakeCombo.Visibility = Visibility.Hidden;
                        fakeCombo.Style = (Style)fakeCombo.FindResource(ToolBar.ComboBoxStyleKey);

                        grid.Children.Add(fakeCombo);

                        ext.OperatorSelector = new ComboBox()
                        {
                            Background = Brushes.White,
                        };
                        ext.OperatorSelector.Style = (Style)ext.OperatorSelector.FindResource(ToolBar.ComboBoxStyleKey);
                        string[] operators = new string[] {
                            "+", "-", "*", "/",
                            "and", "or"
                        };
                        foreach (var op in operators)
                        {
                            ext.OperatorSelector.Items.Add(op);
                        }
                        ext.OperatorSelector.HorizontalAlignment = HorizontalAlignment.Stretch;
                        ext.OperatorSelector.SelectedValue = binOpExpr.Operator;
                        ext.OperatorSelector.SelectionChanged += (object sender, SelectionChangedEventArgs e) =>
                        {
                            if (e.AddedItems.Count == 1 && e.AddedItems[0] is string)
                            {
                                binOpExpr.Operator = (string)e.AddedItems[0];
                            }
                        };
                        grid.Children.Add(ext.OperatorSelector);
                        return MakeSingleControlList (grid);
                    }
                    else
                    {
                        throw new Exception(string.Format("In OmVariableDeclarationExpressionMetaUiExtension: Unknown text placeholder {0}", theName));
                    }

                });
            return creator.CreateControlsFromTemplate2(theContext,  GetTemplate(theContext));
        }

        public override OmEntityExtension CreateExtension()
        {
            return new OmBinaryOperatorExpressionUiExtension();
        }
    }
}
