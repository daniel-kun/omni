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

        public override void ApplyUiDefaults(OmContext theContext, OmEntity theEntity)
        {
            var ifStatement = (OmIfStatement)theEntity;
            ifStatement.Body = new OmBlockStatement();
        }

        public override IEnumerable<List<FrameworkElement>> CreateControls2(OmContext theContext, OmStatement theExpression)
        {
            var ifStatement = theExpression as OmIfStatement;
            var ext = ifStatement.GetExtension(theContext, "omni.ui") as OmIfStatementUiExtension;

            ifStatement.BodyChanged += (theIfStatement) => {
                ext.BodyInput.ReplaceWithExpression2 (theContext, ifStatement.Body, ExpressionInputControl.Continuation.Beneath);
            };
            ifStatement.ConditionChanged += (theIfStatement) => {
                ext.ConditionInput.ReplaceWithExpression2 (theContext, ifStatement.Condition);
            };

            var creator = new OmMetaUiControlCreator(
                (string thePlaceholderName) =>
                {
                    if (thePlaceholderName == "condition")
                    {
                        return ExpressionInputControl.CreateInputOrControls(
                            theContext,
                            theExpression,
                            ifStatement.Condition,
                            OmType.Bool,
                            (theInput) =>
                            {
                                ext.ConditionInput = theInput;
                                ext.ConditionInput.ExpressionCreated += (ExpressionInputControl theSender, OmStatement theConditionExpression) =>
                                {
                                    ifStatement.Condition = theConditionExpression as OmExpression;
                                };
                            });
                    }
                    else if (thePlaceholderName == "body")
                    {
                        var linesPanel = new Grid ();
                        linesPanel.RowDefinitions.Add(new RowDefinition()
                        {
                            Height = GridLength.Auto
                        });
                        var panel = new WrapPanel ();
                        Grid.SetRow(panel, 0);
                        linesPanel.Children.Add(panel);
                        OmMetaUiControlCreator.ApplyControlsToLayout (
                            linesPanel,
                            panel,
                            ExpressionInputControl.CreateInputOrControls(
                                theContext,
                                theExpression,
                                ifStatement.Body,
                                OmType.Void,
                                (theInput) =>
                                {
                                    ext.BodyInput = theInput;
                                    ext.BodyInput.ExpressionCreated += (ExpressionInputControl theSender, OmStatement theBodyStatement) =>
                                    {
                                        ifStatement.Body = theBodyStatement;
                                    };
                                }));
                        return MakeSingleControlList (linesPanel);
                    }
                        /*
                    else if (thePlaceholderName == "else-body")
                    {
                        return ExpressionInputControl.CreateInputOrControls(
                            theContext,
                            theExpression,
                            ifStatement.else,
                            OmType.Void,
                            (theInput) =>
                            {
                                theInput.ExpressionCreated += (ExpressionInputControl theSender, OmStatement theBodyStatement) =>
                                {
                                    ifStatement.Body = theBodyStatement;
                                    theInput.ReplaceWithExpression2(theContext, theBodyStatement);
                                };
                            });
                    }
                        */
                    else
                    {
                        throw new Exception(string.Format("In OmVariableDeclarationExpressionMetaUiExtension: Unknown text placeholder {0}", thePlaceholderName));
                    }
                });
            return creator.CreateControlsFromTemplate2(theContext, GetTemplate(theContext));
        }

        public override OmEntityExtension CreateExtension()
        {
            return new OmIfStatementUiExtension ();
        }
    }
}
