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

        public override IEnumerable<List<FrameworkElement>> CreateControls2 (OmContext theContext, OmStatement theExpression)
        {
            var ext = theExpression.GetExtension(theContext, "omni.ui") as OmBinaryOperatorExpressionUiExtension;
            var binOpExpr = theExpression as OmBinaryOperatorExpression;

            binOpExpr.LeftOperandChanged += (OmEntity theSender) =>
            {
                ext.LeftOperandControl.ReplaceWithExpression2(theContext, binOpExpr.LeftOperand);
            };
            binOpExpr.RightOperandChanged += (OmEntity theSender) =>
            {
                ext.RightOperandControl.ReplaceWithExpression2(theContext, binOpExpr.RightOperand);
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

        public override FrameworkElement CreateControls(OmContext theContext, StackPanel theLinesPanel, WrapPanel thePanel, ref int theIndex, OmStatement theExpression)
        {
            var ext = theExpression.GetExtension(theContext, "omni.ui") as OmBinaryOperatorExpressionUiExtension;
            var binOpExpr = theExpression as OmBinaryOperatorExpression;

            applyOperand applyLeftOperand = (WrapPanel theInnerPanel, ref int theDefaultPosition) =>
            {
                return ext.LeftOperandControl.ReplaceWithExpression(theContext, theLinesPanel, theInnerPanel, ref theDefaultPosition, binOpExpr.LeftOperand);
            };
            int idx = theIndex;
            binOpExpr.LeftOperandChanged += (OmEntity theSender) =>
            {
                applyLeftOperand(thePanel, ref idx);
            };

            applyOperand applyRightOperand = (WrapPanel theInnerPanel, ref int theDefaultPosition) =>
            {
                return ext.RightOperandControl.ReplaceWithExpression(theContext, theLinesPanel, theInnerPanel, ref theDefaultPosition, binOpExpr.RightOperand);
            };
            idx = theIndex;
            binOpExpr.RightOperandChanged += (OmEntity theSender) =>
            {
                applyRightOperand(thePanel, ref idx);
            };

            Action applyOperator = () =>
            {
                ext.OperatorSelector.SelectedValue = binOpExpr.Operator;
            };
            binOpExpr.OperatorChanged += (OmEntity theSender) =>
            {
                applyOperator();
            };
            FrameworkElement focusElement = null;

            var creator = new OmMetaUiControlCreator(
                (WrapPanel theP, ref int thePlaceholderIndex, string theName) =>
                {
                    if (theName == "left")
                    {
                        ext.LeftOperandControl = new ExpressionInputControl(theContext, binOpExpr, OmType.Void);
                        focusElement = ext.LeftOperandControl;
                        return applyLeftOperand(theP, ref thePlaceholderIndex);
                    }
                    else if (theName == "right")
                    {
                        ext.RightOperandControl = new ExpressionInputControl(theContext, binOpExpr, OmType.Void);
                        return applyRightOperand(theP, ref thePlaceholderIndex);
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
                        applyOperator();
                        ext.OperatorSelector.SelectionChanged += (object sender, SelectionChangedEventArgs e) =>
                        {
                            if (e.AddedItems.Count == 1 && e.AddedItems [0] is string)
                            {
                                binOpExpr.Operator = (string)e.AddedItems[0];
                            }
                        };
                        grid.Children.Add(ext.OperatorSelector);
                        return grid;
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
            return new OmBinaryOperatorExpressionUiExtension();
        }
    }
}
