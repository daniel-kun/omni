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
                ext.OpSelectionControl.Text = binOpExpr.Operator;
                UpdateOperandPositions(binOpExpr.Operator, ext.LeftOpPanel, ext.RightOpPanel);
            };
            ext.Grid = new Grid();
            for (int i = 0; i < 3; ++i)
            {
                ext.Grid.RowDefinitions.Add(new RowDefinition()
                {
                    Height = GridLength.Auto
                });
            }
            for (int i = 0; i < 5; ++i)
            {
                ext.Grid.ColumnDefinitions.Add(new ColumnDefinition()
                {
                    Width = GridLength.Auto
                });
            }

            ext.LeftOpPanel = new WrapPanel()
            {
                HorizontalAlignment = HorizontalAlignment.Center
            };
            ext.RightOpPanel = new WrapPanel()
            {
                HorizontalAlignment = HorizontalAlignment.Center
            };
            ext.OpSelectionControl = new OperatorSelectionControl()
            {
                Text = binOpExpr.Operator
            };
            ext.OpSelectionControl.TextChanged += (sender, eventArgs) =>
            {
                binOpExpr.Operator = ext.OpSelectionControl.Text;
            };
            Grid.SetRow(ext.OpSelectionControl, 1);
            Grid.SetColumn(ext.OpSelectionControl, 2);
            UpdateOperandPositions(binOpExpr.Operator, ext.LeftOpPanel, ext.RightOpPanel);
            var leftParens = new TextStretchBlock()
            {
                Text = "("
            };
            Grid.SetRow(leftParens, 0);
            Grid.SetRowSpan(leftParens, 3);
            Grid.SetColumn(leftParens, 0);
            var rightParens = new TextStretchBlock()
            {
                Text = ")"
            };
            Grid.SetRow(rightParens, 0);
            Grid.SetRowSpan(rightParens, 3);
            Grid.SetColumn(rightParens, 4);
            ext.Grid.Children.Add(leftParens);
            ext.Grid.Children.Add(ext.LeftOpPanel);
            ext.Grid.Children.Add(ext.OpSelectionControl);
            ext.Grid.Children.Add(ext.RightOpPanel);
            ext.Grid.Children.Add(rightParens);

            OmMetaUiControlCreator.ApplyControlsToLayout (ext.Grid, ext.LeftOpPanel,
                ExpressionInputControl.CreateInputOrControls(theContext, binOpExpr, binOpExpr.LeftOperand, OmType.Void, (theInput) =>
                {
                    ext.LeftOperandControl = theInput;
                    ext.LeftOperandControl.ExpressionCreated += (ExpressionInputControl theSender, OmStatement theLeftExpression) =>
                    {
                        binOpExpr.LeftOperand = theLeftExpression as OmExpression;
                    };
                }));
            OmMetaUiControlCreator.ApplyControlsToLayout(ext.Grid, ext.RightOpPanel,
                ExpressionInputControl.CreateInputOrControls(theContext, binOpExpr, binOpExpr.RightOperand, OmType.Void, (theInput) =>
                {
                    ext.RightOperandControl = theInput;
                    ext.RightOperandControl.ExpressionCreated += (ExpressionInputControl theSender, OmStatement theRightExpression) =>
                    {
                        binOpExpr.RightOperand = theRightExpression as OmExpression;
                    };
                }));
            //            var metaUiExt = theStatement.GetMeta(theContext).GetExtension("omni.ui") as OmMetaUiExtension;
//            OmMetaUiControlCreator.ApplyControlsToLayout(theGrid, firstLinePanel, metaUiExt.CreateControls(theContext, theStatement));

            /*
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
                                ext.LeftOperandControl.ExpressionCreated += (ExpressionInputControl theSender, OmStatement theLeftExpression) =>
                                {
                                    binOpExpr.LeftOperand = theLeftExpression as OmExpression;
                                };
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
                                ext.RightOperandControl.ExpressionCreated += (ExpressionInputControl theSender, OmStatement theRightExpression) =>
                                {
                                    binOpExpr.RightOperand = theRightExpression as OmExpression;
                                };
                            });
                    }
                    else if (theName == "operator")
                    {
                        var opSelCtrl = new OperatorSelectionControl()
                        {
                            Text = binOpExpr.Operator
                        };
                        return MakeSingleControlList(opSelCtrl);
                     }
                    else
                    {
                        throw new Exception(string.Format("In OmVariableDeclarationExpressionMetaUiExtension: Unknown text placeholder {0}", theName));
                    }

                });
            return creator.CreateControlsFromTemplate2(theContext,  GetTemplate(theContext));
            */
            yield return new List<FrameworkElement> { ext.Grid };
        }

        private void UpdateOperandPositions(string theOperator, WrapPanel theLeftPanel, WrapPanel theRightPanel)
        {
            if (theOperator == "/")
            {
                Grid.SetRow(theLeftPanel, 0);
                Grid.SetColumn(theLeftPanel, 2);
                
                Grid.SetRow(theRightPanel, 2);
                Grid.SetColumn(theRightPanel, 2);
            }
            else
            {
                Grid.SetRow(theLeftPanel, 1);
                Grid.SetColumn(theLeftPanel, 1);
                
                Grid.SetRow(theRightPanel, 1);
                Grid.SetColumn(theRightPanel, 3);
            }
        }

        public override OmEntityExtension CreateExtension()
        {
            return new OmBinaryOperatorExpressionUiExtension();
        }
    }
}
