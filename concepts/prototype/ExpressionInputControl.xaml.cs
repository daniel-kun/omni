using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Diagnostics;
using System.Timers;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Data;
using System.Windows.Input;

namespace OmniPrototype
{
    /// <summary>
    /// Interaction logic for ExpressionInputControl.xaml
    /// </summary>
    public partial class ExpressionInputControl : UserControl
    {

        public delegate void ExpressionCreatedHandler(ExpressionInputControl theSender, OmStatement theExpression);

        public event ExpressionCreatedHandler ExpressionCreated;

        public delegate void ContinuationInputCreatedHandler (ExpressionInputControl theSender);

        public event ContinuationInputCreatedHandler ContinuationInputCreated;

        public ExpressionInputControl (OmContext theContext, OmScope theScope, OmType theType)
        {
            if (theContext == null || theScope == null || theType == null)
            {
                throw new Exception("ExpressionInputControl invalid parameters");
            }
            Context = theContext;
            Scope = theScope;
            TargetType = theType;
            InitializeComponent();

            var listItemFactory = new FrameworkElementFactory(typeof(TextBlock));
            listItemFactory.SetBinding(TextBlock.TextProperty, new Binding("Preview"));
            mPopupList = new ListBox()
            {
                ItemTemplate = new DataTemplate(typeof(OmEntityFactory))
                {
                    VisualTree = listItemFactory
                }
            };
            mPopupList.SelectionChanged += popupList_SelectionChanged;
            mPopup = new Popup()
            {
                Width = 200,
                Height = 300,
                PlacementTarget = mGrid,
                Placement = PlacementMode.Bottom,
                MaxHeight = 150,
                Child = mPopupList
            };
            
            mText.TextChanged += mText_TextChanged;
        }

        private void popupList_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (e.AddedItems != null && e.AddedItems.Count > 0 && e.AddedItems[0] is OmEntityFactory)
            {
                mPopup.IsOpen = false;
                SetExpression ((OmEntityFactory)e.AddedItems[0]);
            }
        }

        private void SetExpression (OmEntityFactory theFactory)
        {
            var newStatement = theFactory.Create(Scope) as OmStatement;
            var uiMetaExt = newStatement.GetMeta(Context).GetExtension("omni.ui") as OmMetaUiExtension;
            var uiExt = newStatement.GetExtension(Context, "omni.ui") as OmEntityUiExtension;
            uiExt.CreatedInContext = Context;
            uiMetaExt.ApplyUiDefaults(Context, newStatement);
            Expression = newStatement;
        }

        protected override void OnLostKeyboardFocus(KeyboardFocusChangedEventArgs e)
        {
            base.OnLostKeyboardFocus(e);
            mPopup.IsOpen = false;
        }

        protected override void OnPreviewKeyDown(KeyEventArgs e)
        {
            base.OnPreviewKeyDown(e);
            if (e.Key == Key.Down)
            {
                if ((mPopupList.SelectedIndex < mPopupList.Items.Count - 1) || (mPopupList.SelectedIndex == -1 && mPopupList.Items.Count > 0))
                {
                    mPopupList.SelectionChanged -= popupList_SelectionChanged;
                    mPopupList.SelectedIndex = mPopupList.SelectedIndex + 1;
                    mPopupList.SelectionChanged += popupList_SelectionChanged;
                }

            }
            else if (e.Key == Key.Up)
            {
                if (mPopupList.SelectedIndex > 0)
                {
                    mPopupList.SelectionChanged -= popupList_SelectionChanged;
                    mPopupList.SelectedIndex = mPopupList.SelectedIndex - 1;
                    mPopupList.SelectionChanged += popupList_SelectionChanged;
                }
            }
            else if (e.Key == Key.Enter || e.Key == Key.Return)
            {
                if (mPopupList.SelectedItem is OmEntityFactory)
                {
                    mPopup.IsOpen = false;
                    var factory = (OmEntityFactory)mPopupList.SelectedItem;
                    SetExpression(factory);
                }
            }
        }

        public OmStatement Expression
        {
            get
            {
                return mExpression;
            }
            private set
            {
                mExpression = value;
                var handler = ExpressionCreated;
                if (handler != null)
                {
                    handler(this, value);
                }
                // And now dissolve into the void
                var panel = Parent as Panel;
                if (panel != null)
                {
                    panel.Children.Remove(this);
                }
            }
        }

        public OmContext Context
        {
            get;
            private set;
        }

        public OmScope Scope
        {
            get;
            private set;
        }

        public OmType TargetType
        {
            get;
            private set;
        }

        public void mText_TextChanged(object sender, TextChangedEventArgs e)
        {
            var possibleExpressions = Scope.TryParse (Context, TargetType, mText.Text);
            var list = new ObservableCollection<OmEntityFactory>(possibleExpressions);
            mPopupList.ItemsSource = list;
            mPopup.IsOpen = list.Count > 0;
        }

        private Action<ExpressionInputControl> mInitializationRoutine;

        public static IEnumerable<List <FrameworkElement>> CreateInputOrControls (OmContext                      theContext,
                                                                                  OmScope                        theScope,
                                                                                  OmStatement                    theStatement,
                                                                                  OmType                         theTargetType,
                                                                                  Action<ExpressionInputControl> theInitializeInput)
        {
            if (theStatement == null)
            {
                // Yay, create a cool input control now:
                var input = new ExpressionInputControl(theContext, theScope, theTargetType);
                input.mInitializationRoutine = theInitializeInput;
                input.mInitializationRoutine (input);
                yield return new List <FrameworkElement> () { input };
            }
            else
            {
                var childUiExt = theStatement.GetMeta(theContext).GetExtension("omni.ui") as OmMetaUiExtension;
                foreach (var controls in childUiExt.CreateControls (theContext, theStatement))
                {
                    yield return controls;
                }
            }
        }

        /// Specifies whether, when an expression has been selected for this input, a new ExpressionInputControl should be created and displayed
        /// next to or beneath the old one. Used for e.g. block statements, parameter lists and any other kinds of lists of elements.
        public enum Continuation
        {
            None,
            RightTo,
            Beneath
        }

        public void ReplaceWithExpression(OmContext theContext, OmStatement theExpression, Continuation theContinuation = Continuation.None)
        {
            var parent = Parent;
            FrameworkElement self = this;
            if (parent is ExpressionControlSelectionHost)
            {
                self = (FrameworkElement)parent;
                parent = self.Parent;
            }
            if (!(parent is WrapPanel))
            {
                throw new Exception("Can not use ReplaceWithExpression2 if Parent is not a WrapPanel");
            }
            var panel = (Panel)parent;
            int oldIndex = panel.Children.IndexOf(self);
            if (oldIndex < 0)
            {
                throw new Exception ("Can not use ReplaceWithExpression2 if this ExpressionInputControl is not part of the Parent panel");
            }
            panel.Children.RemoveAt(oldIndex);
            //int selfIndex = oldIndex++;
            if (! (panel.Parent is Grid))
            {
                throw new Exception("Can not use ReplaceWithExpression2 if Parent.Parent is not a Grid");
            }
            var linesPanel = (Grid)panel.Parent;
            int oldLinesIndex = linesPanel.Children.IndexOf(panel);
            if (oldLinesIndex < 0)
            {
                throw new Exception("Can not use ReplaceWithExpression2 if the parent WrapPanel is not part of it's parent Grid");
            }
            
            var childMetaUiExt = theExpression.GetMeta(theContext).GetExtension("omni.ui") as OmMetaUiExtension;
            bool isFirstInline = true;
            var controls = childMetaUiExt.CreateControls (theContext, theExpression);
            var childUiExt = theExpression.GetExtension(theContext, "omni.ui") as OmEntityUiExtension;
            bool isFirstFocusable = true;
            foreach (var line in controls)
            {
                if (! isFirstInline)
                {
                    panel = new WrapPanel();
                    linesPanel.RowDefinitions.Add(new RowDefinition()
                    {
                        Height = GridLength.Auto
                    });
                    foreach (UIElement child in linesPanel.Children)
                    {
                        int row = Grid.GetRow(child);
                        if (row > oldLinesIndex)
                        {
                            Grid.SetRow(child, row);
                        }
                    }
                    Grid.SetRow(panel, ++oldLinesIndex);
                    linesPanel.RowDefinitions.Add(new RowDefinition()
                    {
                        Height = GridLength.Auto
                    });
                    linesPanel.Children.Add(panel);
                    oldIndex = 0;
                }
                isFirstInline = false;
                foreach (var control in line) {
                    panel.Children.Insert (oldIndex++, control);
                    isFirstFocusable = FocusIfFirstFocusableControl(theContext, childUiExt, isFirstFocusable, control);
                }
            }
            
            CreateContinuation(theContinuation, linesPanel, oldLinesIndex);
        }

        private bool FocusIfFirstFocusableControl(OmContext theContext, OmEntityUiExtension childUiExt, bool isFirstFocusable, FrameworkElement control)
        {
            if (childUiExt.CreatedInContext == theContext)
            {
                var c = ResolveControl(control);
                if (isFirstFocusable && c != null)
                {
                    if (c.IsTabStop && c.Focusable)
                    {
                        isFirstFocusable = false;
                        Dispatcher.Invoke(new Action(() =>
                        {
                            c.Focus();
                        }), System.Windows.Threading.DispatcherPriority.ApplicationIdle);
                    }
                }
            }
            return isFirstFocusable;
        }

        private Control ResolveControl(FrameworkElement control)
        {
            if (control is ExpressionControlSelectionHost && ((ExpressionControlSelectionHost) control).Content is FrameworkElement)
            {
                control = (FrameworkElement) ((ExpressionControlSelectionHost)control).Content;
            }
            if (control is Control)
            {
                var c = (Control)control;
                if (c.Focusable && c.IsTabStop)
                {
                    return c;
                }
            }
            return null;
        }

        private void CreateContinuation (Continuation theContinuation, Grid linesPanel, int oldLinesIndex)
        {
            switch (theContinuation)
            {
                case Continuation.Beneath:
                    var continuationInput = new ExpressionInputControl(Context, Scope, TargetType);
                    continuationInput.mInitializationRoutine = mInitializationRoutine;
                    continuationInput.ExpressionCreated = ExpressionCreated;
                    continuationInput.ContinuationInputCreated = ContinuationInputCreated;
                    var newPanel = new WrapPanel();
                    foreach (UIElement child in linesPanel.Children)
                    {
                        int row = Grid.GetRow(child);
                        if (row > oldLinesIndex)
                        {
                            Grid.SetRow(child, row);
                        }
                    }
                    linesPanel.RowDefinitions.Add(new RowDefinition()
                    {
                        Height = GridLength.Auto
                    });
                    Grid.SetRow(newPanel, ++oldLinesIndex);
                    newPanel.Children.Add(continuationInput);
                    linesPanel.Children.Add(newPanel);
                    if (continuationInput.mInitializationRoutine != null)
                    {
                        continuationInput.mInitializationRoutine(continuationInput);
                    }
                    var handler = ContinuationInputCreated;
                    if (handler != null)
                    {
                        handler(continuationInput);
                    }
                    break;
                case Continuation.RightTo:
                    // TODO
                    break;
            }
        }

        private OmStatement mExpression = null;


        public Popup mPopup
        {
            get;
            set;
        }

        public ListBox mPopupList
        {
            get;
            set;
        }
    }
}
