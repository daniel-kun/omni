using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Reflection;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Linq;
using System.Windows.Media;

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

            mContextLispStyle.Templates = new Dictionary<string, string>()
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

             var rootBlock = new OmBlockStatement ();
            CreateRootControl(mLinesPanel1, mContextCStyle, rootBlock);
            CreateRootControl(mLinesPanel2, mContextLispStyle, rootBlock);

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

        private void SetClipboardStatement (OmStatement theStatement, OmClipboardContext.ClipboardAction theAction)
        {
            mClipboardPanel.Children.Clear();
            mContextClipboard.Action = theAction;
            CreateRootControl(mClipboardPanel, mContextClipboard, theStatement);
        }

        private static bool IsClipboardAction(bool theIsSelectionHost, Key thePressedKey, Key theClipboardKey)
        {
            return theIsSelectionHost && thePressedKey == theClipboardKey && ((Keyboard.Modifiers & ModifierKeys.Control) == ModifierKeys.Control);
        }

        private void MainWindow_PreviewKeyDown(object sender, KeyEventArgs e)

        {
            // Very hacky way to let navigational direction key pass on to known controls that might "need" them
            // (e.g. a TextBox that uses left/right keys), but use it for navigation if the focused control does not "need" them:
            var focusedElement = FocusManager.GetFocusedElement(this) as FrameworkElement;
            if (focusedElement != null)
            {
                bool isSelectionHost = focusedElement is ExpressionControlSelectionHost;
                bool handled = true;
                if (IsClipboardAction (isSelectionHost, e.Key, Key.X))
                {
                    var selectionHost = (ExpressionControlSelectionHost)focusedElement;
                    SetClipboardStatement(selectionHost.Entity as OmStatement, OmClipboardContext.ClipboardAction.Cut);
                    //.Foreground = Brushes.LightGray;
                }
                else if (IsClipboardAction(isSelectionHost, e.Key, Key.C))
                {
                    var selectionHost = (ExpressionControlSelectionHost)focusedElement;
                    SetClipboardStatement(selectionHost.Entity as OmStatement, OmClipboardContext.ClipboardAction.Copy);
                    //.Foreground = Brushes.LightGray;
                } else {
                    switch (e.Key)
                    {
                        case Key.Up:
                            NavigateUp(focusedElement);
                            break;
                        case Key.Down:
                            NavigateDown(focusedElement);
                            break;
                        case Key.Left:
                            if (!isSelectionHost)
                            {
                                handled = false;
                            }
                            else
                            {
                                NavigateLeft(focusedElement);
                            }
                            break;
                        case Key.Right:
                            if (!isSelectionHost)
                            {
                                handled = false;
                            }
                            else
                            {
                                NavigateRight(focusedElement);
                            }
                            break;
                        default:
                            handled = false;
                            break;
                    }
                }
                if (handled) {
                    e.Handled = true;
                }
            }
        }

        private void NavigateRight(FrameworkElement theElement)
        {
            NavigateHorizontal(theElement, i => ++i);
        }

        private static void NavigateHorizontal(FrameworkElement theElement, Func<int, int> step)
        {
            // 1. Find parent layout (panel)
            // 2. Navigate to the left until a selection-host for a different expression is found
            // 3. if at the beginning:
            // 4. Find a higher parent layout
            // continue with 1
            var startSelectionHost = theElement as ExpressionControlSelectionHost;
            Tuple<Panel, FrameworkElement> current = new Tuple<Panel, FrameworkElement>(null, theElement);
            // Note: Currently does not work with Grids, only with layouts where the order of the Children equals the horizontal order of the controls
            while ((current = VisualTreeUtils.FindVisualParentAndDirectChild<Panel>(current.Item1 == null ? current.Item2 : current.Item1)) != null)
            {
                var panel = current.Item1;
                var child = current.Item2;
                int idx = panel.Children.IndexOf(child);
                Debug.Assert(idx >= 0);
                for (int i = idx; i >= 0 && i < panel.Children.Count; i = step(i))
                {
                    if (startSelectionHost != null)
                    {
                        if (panel.Children[i] is ExpressionControlSelectionHost)
                        {
                            var selectionHost = (ExpressionControlSelectionHost)panel.Children[i];
                            if (selectionHost.Entity != startSelectionHost.Entity)
                            {
                                DependencyObject firstFocusable = null;

                                foreach (var elemen in VisualTreeUtils.AllVisualChildren(selectionHost).Where(element => element is Control && ((Control)element).IsTabStop))
                                {
                                    firstFocusable = elemen;
                                    break;
                                }
                                if (firstFocusable != null)
                                {
                                    selectionHost.Focus();
                                    return;
                                }
                            }
                        }
                    }
                }
            }
        }

        private void NavigateLeft(FrameworkElement theElement)
        {
            NavigateHorizontal(theElement, i => --i);
        }

        private void NavigateDown(FrameworkElement theElement)
        {
            // 1. Store visual coordinates of the source element
            // 2. Find parent Grid Panel
            // 3. Find and sort children on the row above
            // 4. iterate sorted children (selection hosts) from left to right
            // 5. select the child that is nearest to the source element's border
            Func<FrameworkElement, Rect> getBounds = elem => new Rect(elem.PointToScreen(new Point(0, 0)), elem.PointToScreen(new Point(elem.ActualWidth, elem.ActualHeight)));
            Rect originalRect = getBounds (theElement);
            Tuple <Grid, FrameworkElement> gridTuple = VisualTreeUtils.FindVisualParentAndDirectChild<Grid>(theElement);
            var grid = gridTuple.Item1;
            var container = gridTuple.Item2;
            var nextRowChildren = new List<FrameworkElement>();
            int containerRow = Grid.GetRow(container);
            int currentRow = int.MaxValue;
            foreach (FrameworkElement child in grid.Children)
            {
                int childRow = Grid.GetRow(child);
                if (childRow > containerRow && childRow <= currentRow)
                {
                    if (childRow < currentRow)
                    {
                        currentRow = childRow;
                        nextRowChildren.Clear();
                    }
                    nextRowChildren.Add(child);
                }
            }
            if (nextRowChildren.Count > 0)
            {
                nextRowChildren.Sort((left, right) =>
                    Grid.GetColumn(left).CompareTo (Grid.GetColumn(right))
                );
                foreach (var child in nextRowChildren)
                {
                    bool found = false;
                    foreach (var selectionHost in VisualTreeUtils.AllVisualChildrenWithMe(child))
                    {
                        if (selectionHost is ExpressionControlSelectionHost)
                        {
                            found = true;
                            ((Control)selectionHost).Focus();
                        }
                    }
                    if (found)
                    {
                        break;
                    }
                }
            }
        }

        private void NavigateUp(FrameworkElement theElement)
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

        private OmContext mContextCStyle = new OmContext();
        private OmContext mContextLispStyle = new OmContext();
        private OmClipboardContext mContextClipboard = new OmClipboardContext ();
    }
}
