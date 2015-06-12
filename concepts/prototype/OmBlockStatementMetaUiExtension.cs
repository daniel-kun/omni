using System;
using System.Diagnostics;
using System.Windows;
using System.Windows.Controls;

namespace OmniPrototype {

    public class OmBlockStatementMetaUiExtension : OmMetaUiExtension
    {
        public OmBlockStatementMetaUiExtension () : base ("block")
        {
        }

        public override FrameworkElement CreateControls(OmContext theContext, StackPanel theLinesPanel, WrapPanel thePanel, ref int theIndex, OmStatement theExpression)
        {
            // thePanel is ignored, because blocks create new lines
            var block = theExpression as OmBlockStatement;

            var wrapPanel = new WrapPanel();
            theLinesPanel.Children.Add(wrapPanel);
            var ext = block.GetExtension(theContext, "omni.ui") as OmBlockStatementUiExtension;
            int idx = theIndex;
            block.ComponentAdded += (OmEntity theSender, string theKey, OmEntity theChild) => {
                var newWrapPanel = new WrapPanel();
                int ignore = 0;
                theLinesPanel.Children.Insert(theLinesPanel.Children.Count - 1, newWrapPanel);
                ext.AddExpressionControl.ReplaceWithExpression(theContext, theLinesPanel, newWrapPanel, ref ignore, theChild as OmStatement);
            };

            FrameworkElement focusElement = null;
            var creator = new OmMetaUiControlCreator (
                (WrapPanel theP, ref int thePlaceholderIndex, string theName) =>
                {
                    if (theName == "statement")
                    {
                        ext.AddExpressionControl = new ExpressionInputControl(theContext, block, OmType.Void);
                        theLinesPanel.Children.Add(ext.AddExpressionControl);
                        Debug.Assert (ext.AddExpressionControl.Parent != null);
                        focusElement = ext.AddExpressionControl;
                        ext.AddExpressionControl.ExpressionCreated += ExpressionCreatedFromInput;
                        return null;
                    }
                    else
                    {
                        throw new Exception(string.Format("In OmVariableDeclarationExpressionMetaUiExtension: Unknown text placeholder {0}", theName));
                    }

                });
            creator.CreateControlsFromTemplate(theContext, theLinesPanel, wrapPanel, ref theIndex, GetTemplate (theContext));
            return focusElement;
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
