using System;
using System.Collections.Generic;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;

namespace OmniPrototype
{
    public class OmVariableDeclarationExpressionMetaUiExtension : OmMetaUiExtension
    {
        public OmVariableDeclarationExpressionMetaUiExtension() : base ("variable_declaration_expression")
        {
        }

        public override OmEntityExtension CreateExtension ()
        {
            return new OmVariableDeclarationUiExtension();
        }

        /**
        @return First list entry is the in-place list of controls, the rest are new-line controls.
        **/
        public override IEnumerable<List<FrameworkElement>> CreateControls2(OmContext theContext, OmStatement theExpression)
        {
            var ext = theExpression.GetExtension(theContext, "omni.ui") as OmVariableDeclarationUiExtension;
            var varDecl = theExpression as OmVariableDeclarationExpression;

            Action applyName = () =>
            {
                if (ext.NameInput.Text != varDecl.Name)
                {
                    ext.NameInput.Text = varDecl.Name;
                }
            };

            varDecl.NameChanged += (OmEntity theSender) =>
            {
                applyName();
            };

            /*
            varDecl.InitializationExpressionChanged += (OmEntity theSender) =>
            {

                ext.InitializationExpressionInput.ReplaceWithExpression(theContext, theLinesPanel, thePanel, ref index, varDecl.InitializationExpression);
            };
            */

            FrameworkElement focusElement = null;
            var creator = new OmMetaUiControlCreator(
                (WrapPanel theP, ref int thePlaceholderIndex, string theName) =>
                {
                    if (theName == "name")
                    {
                        ext.NameInput = new TextBox()
                        {
                            Text = varDecl.Name,
                            MinWidth = 40,
                            Foreground = Brushes.DarkRed
                        };
                        ext.NameInput.TextChanged += (object sender, TextChangedEventArgs e) =>
                        {
                            varDecl.Name = ext.NameInput.Text;
                        };
                        focusElement = ext.NameInput;
                        return ext.NameInput;
                    }
                    else if (theName == "initexpr")
                    {
                        ExpressionInputControl.CreateInputOrControls(
                            theContext,
                            varDecl, 
                            varDecl.InitializationExpression,
                            OmType.Void,
                            (ExpressionInputControl theInput) =>
                            {
                                ext.InitializationExpressionInput = theInput;
                                theInput.ExpressionCreated += (ExpressionInputControl theSender, OmStatement theNewExpression) =>
                                {
                                    varDecl.InitializationExpression = theNewExpression as OmExpression;
                                }; 
                            });
                        return ext.InitializationExpressionInput;
                    }
                    else
                    {
                        throw new Exception(string.Format("In OmVariableDeclarationExpressionMetaUiExtension: Unknown text placeholder {0}", theName));
                    }

                });
            return creator.CreateControlsFromTemplate2(theContext, GetTemplate(theContext));
        }

        public override FrameworkElement CreateControls(OmContext theContext, StackPanel theLinesPanel, WrapPanel thePanel, ref int theIndex, OmStatement theExpression)
        {
            var ext = theExpression.GetExtension(theContext, "omni.ui") as OmVariableDeclarationUiExtension;
            var varDecl = theExpression as OmVariableDeclarationExpression;

            Action applyName = () =>
            {
                if (ext.NameInput.Text != varDecl.Name)
                {
                    ext.NameInput.Text = varDecl.Name;
                }
            };

            varDecl.NameChanged += (OmEntity theSender) =>
            {
                applyName();
            };

            int index = theIndex;
            varDecl.InitializationExpressionChanged += (OmEntity theSender) => 
            {
                ext.InitializationExpressionInput.ReplaceWithExpression (theContext, theLinesPanel, thePanel, ref index, varDecl.InitializationExpression);
            };

            FrameworkElement focusElement = null;
            var creator = new OmMetaUiControlCreator (
                (WrapPanel theP, ref int thePlaceholderIndex, string theName) =>
                {
                    if (theName == "name")
                    {
                        ext.NameInput = new TextBox () {
                            Text = varDecl.Name,
                            MinWidth = 40,
                            Foreground = Brushes.DarkRed
                        };
                        ext.NameInput.TextChanged += (object sender, TextChangedEventArgs e) =>
                        {
                            varDecl.Name = ext.NameInput.Text;
                        };
                        focusElement = ext.NameInput;
                        return ext.NameInput;
                    } else if (theName == "initexpr") {
                        ext.InitializationExpressionInput = new ExpressionInputControl(theContext, theExpression as OmScope, OmType.Void);
                        if (varDecl.InitializationExpression != null)
                        {
                            ext.InitializationExpressionInput.ReplaceWithExpression(theContext, theLinesPanel, theP, ref thePlaceholderIndex, varDecl.InitializationExpression);
                        }
                        ext.InitializationExpressionInput.ExpressionCreated += (ExpressionInputControl theSender, OmStatement theNewExpression) =>
                        {
                            varDecl.InitializationExpression = theNewExpression as OmExpression;
                        };
                        return ext.InitializationExpressionInput;
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
