using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Windows;
using System.Windows.Controls;

namespace OmniPrototype {

    public class OmBlockStatementMetaUiExtension : OmMetaUiExtension
    {
        public OmBlockStatementMetaUiExtension () : base ("block")
        {
        }

        public override IEnumerable <List <FrameworkElement>> CreateControls(OmContext theContext, OmStatement theExpression)
        {
            // thePanel is ignored, because blocks create new lines
            var block = theExpression as OmBlockStatement;
            var ext = block.GetExtension(theContext, "omni.ui") as OmBlockStatementUiExtension;
            block.ComponentAdded += (OmEntity theSender, string theKey, OmEntity theChild) =>
            {
                ext.AddExpressionControl.ReplaceWithExpression(theContext, theChild as OmStatement, ExpressionInputControl.Continuation.Beneath);
            };

            var creator = new OmMetaUiControlCreator(
                (string theName) =>
                {
                    if (theName == "statement")
                    {
                        var controlList = new List <List <FrameworkElement>> ();
                        foreach (var statement in block.Components) {
                            controlList.AddRange(ExpressionInputControl.CreateInputOrControls(theContext, block, statement.Value as OmStatement, OmType.Void, (theInput) =>
                            {
                            }));
                        }
                        ext.AddExpressionControl = new ExpressionInputControl(theContext, block, OmType.Void);
                        ext.AddExpressionControl.ExpressionCreated += (ExpressionInputControl theSender, OmStatement theNewExpression) =>
                        {
                            block.AddComponent ((block.Components.Count + 1).ToString (), theNewExpression);
                        };
                        ext.AddExpressionControl.ContinuationInputCreated += (ExpressionInputControl theSender) => {
                            ext.AddExpressionControl = theSender;
                        };
                        controlList.Add(new List<FrameworkElement> { ext.AddExpressionControl });
                        return controlList;
                    }
                    else
                    {
                        throw new Exception(string.Format("In OmVariableDeclarationExpressionMetaUiExtension: Unknown text placeholder {0}", theName));
                    }

                });
            return creator.CreateControlsFromTemplate2(theContext, GetTemplate(theContext));
        }

        private void ExpressionCreatedFromInput (ExpressionInputControl theSender, OmStatement theNewExpression)
        {
            var block = theSender.Scope as OmBlockStatement;
            block.AddComponent((block.Components.Count + 1).ToString (), theNewExpression);
            var newInput = new ExpressionInputControl (theSender.Context, block, OmType.Void);
            var ext = block.GetExtension(theSender.Context, "omni.ui") as OmBlockStatementUiExtension;
            ext.AddExpressionControl = newInput;
            var linesPanel = theSender.Parent as StackPanel;
            linesPanel.Children.Add(newInput);
            Debug.Assert (newInput.Parent != null);
            newInput.ExpressionCreated += ExpressionCreatedFromInput;
        }

        public override OmEntityExtension CreateExtension()
        {
            return new OmBlockStatementUiExtension ();
        }
    }
}
