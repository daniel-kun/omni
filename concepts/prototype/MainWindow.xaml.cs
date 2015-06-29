using System.Collections.Generic;
using System.Reflection;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;

namespace OmniPrototype
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            // Very dirty hack to override the global system parameter "SPI_GETKEYBOARDCUES" (aka "Always show underlined hotkeys").
            // This enabled elements to show dashed focus rectangles even when received focus by code or per mouse click:
            typeof(KeyboardNavigation).GetProperty("AlwaysShowFocusVisual", BindingFlags.NonPublic | BindingFlags.Static).SetValue(null, true, null);
            InitializeComponent();
            PreviewKeyDown += MainWindow_PreviewKeyDown;
            PreviewKeyUp += MainWindow_PreviewKeyUp;

            mContext2.Templates = new Dictionary<string, string>()
            {
                {"binary_operator_expression", "(<operator> <left> <right>)"},
                {"block", "<statement>"},
                {"bool_literal_expression", "<value>"},
                {"int_literal_expression", "<value>"},
                {"variable_declaration_expression", "(let [name] <initexpr>)"},
                {"variable_use_expression", "<variable>"},
{"if_statement",
@"(cond (<condition>)
    (<body>)"},
            };

            /*
            var block = new OmBlockStatement ();
            var variable1 = new OmVariableDeclarationExpression()
            {
                InitializationExpression = new OmIntLiteralExpression()
                {
                    Value = 10
                },
                Name = "foobar"
            };
            block.AddComponent ("1", variable1);
            block.AddComponent("2", new OmVariableUseExpression()
            {
                Variable = variable1
            });
            block.AddComponent("2", new OmIntLiteralExpression()
            {
                Value = 1337
            });
            CreateRootControl(mLinesPanel1, mContext1, block);
            CreateRootControl(mLinesPanel2, mContext2, block);
            */

             var rootBlock = new OmBlockStatement ();
            CreateRootControl(mLinesPanel1, mContext1, rootBlock);
            CreateRootControl(mLinesPanel2, mContext2, rootBlock);

             var varDecl = new OmVariableDeclarationExpression ()
             {
             };
             varDecl.Name = "var1";
             rootBlock.AddComponent("1", varDecl);
             var initExpr = new OmBoolLiteralExpression() {
                 Value = true
             };
             varDecl.InitializationExpression = initExpr;

             var varDecl2 = new OmVariableDeclarationExpression ()
             {
             };
             rootBlock.AddComponent("2", varDecl2);
             varDecl2.Name = "var2";
             var initExpr2 = new OmIntLiteralExpression () {
                 Value = 123456
             };
             varDecl2.InitializationExpression = initExpr2;

             var varDecl3 = new OmVariableDeclarationExpression()
             {
                 Name = "var3"
             };
             rootBlock.AddComponent("3", varDecl3);
             varDecl3.InitializationExpression = new OmBinaryOperatorExpression()
             {
                 LeftOperand = new OmVariableUseExpression()
                 {
                     Variable = varDecl2
                 },
                 Operator = "+",
                 RightOperand = new OmIntLiteralExpression()
                 {
                     Value = 20
                 }
             };
             rootBlock.AddComponent("4",
                 new OmIfStatement () {
                     Condition = new OmBoolLiteralExpression () { Value = true },
                     Body = new OmBinaryOperatorExpression()
                     {
                         LeftOperand = new OmIntLiteralExpression()
                         {
                             Value = 30
                         },
                         Operator = "+",
                         RightOperand = new OmIntLiteralExpression()
                         {
                             Value = 20
                         }
                     }});
        }

        private void MainWindow_PreviewKeyDown(object sender, KeyEventArgs e)
        {
            // Very hacky way to let navigational direction key pass on to known controls that might "need" them
            // (e.g. a TextBox that uses left/right keys), but use it for navigation if the focused control does not "need" them:
            bool isSelectionHost = FocusManager.GetFocusedElement (this) is ExpressionControlSelectionHost;

            bool handled = true;
            switch (e.Key) {
                case Key.Up:
                    NavigateUp ();
                    break;
                case Key.Down:
                    NavigateDown ();
                    break;
                case Key.Left:
                    if (!isSelectionHost) {
                        handled = false;
                    } else {
                        NavigateLeft ();
                    }
                    break;
                case Key.Right:
                    if (!isSelectionHost) {
                        handled = false;
                    } else {
                        NavigateRight ();
                    }
                    break;
                default:
                    handled = false;
                    break;
            }
            if (handled) {
                e.Handled = true;
            }
        }

        private void NavigateRight()
        {
            // TODO
        }

        private void NavigateLeft()
        {
            // TODO
        }

        private void NavigateDown()
        {
            // TODO
        }

        private void NavigateUp()
        {
            // TODO
        }

        private void MainWindow_PreviewKeyUp(object sender, KeyEventArgs e)
        {
            bool handled = true;
            switch (e.Key) {
                case Key.Escape:
                    NavigateToControlParent();
                    break;
                default:
                    handled = false;
                    break;
            }
            if (handled) {
                e.Handled = true;
            }
        }

        private void NavigateToControlParent()
        {
            FrameworkElement focusedElement = FocusManager.GetFocusedElement(this) as FrameworkElement;
            
            var newFocus = VisualTreeUtils.FindVisualParent<ExpressionControlSelectionHost>(focusedElement);
            if (newFocus != null)
            {
                newFocus.Focus();
                FocusManager.SetFocusedElement(newFocus, newFocus);
            }
        }

        private static void CreateRootControl(Grid theGrid, OmContext theContext, OmStatement theStatement)
        {
            var metaUiExt = theStatement.GetMeta(theContext).GetExtension("omni.ui") as OmMetaUiExtension;
            var firstLinePanel = new WrapPanel();
            theGrid.RowDefinitions.Add(new RowDefinition()
            {
                Height = GridLength.Auto
            });
            Grid.SetRow(firstLinePanel, theGrid.RowDefinitions.Count - 1);
            theGrid.Children.Add(firstLinePanel);
            OmMetaUiControlCreator.ApplyControlsToLayout(
                theGrid,
                firstLinePanel,
                metaUiExt.CreateControls(theContext, theStatement));
        }

        private OmContext mContext1 = new OmContext();
        private OmContext mContext2 = new OmContext();
    }
}
