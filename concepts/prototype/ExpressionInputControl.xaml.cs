using System;
using System.Collections.ObjectModel;
using System.Diagnostics;
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
                var factory = (OmEntityFactory)e.AddedItems[0];
                Expression = factory.Create (Scope) as OmStatement;
            }
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
                    Expression = factory.Create(Scope) as OmStatement;
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
                var panel = Parent as StackPanel;
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
            /*
            if (expressions.Count == 1)
            {
                Expression = expressions[0].Create (Scope) as OmExpression;
            }
            */
        }

        public FrameworkElement ReplaceWithExpression (OmContext theContext, StackPanel theLinesPanel, WrapPanel thePanel, ref int theDefaultPos, OmStatement theExpression)
        {
            if (theExpression == null)
            {
                return this;
            }
            var childUiExt = theExpression.GetMeta(theContext).GetExtension("omni.ui") as OmMetaUiExtension;
            WrapPanel p = Parent as WrapPanel;
            if (p == null)
            {
                p = thePanel;
            }
            int pos = thePanel.Children.IndexOf(this);
            if (pos < 0)
            {
                pos = theDefaultPos;
            }
            else
            {
                thePanel.Children.RemoveAt(pos);
            }
            Debug.Assert(thePanel.Children.IndexOf(this) == -1);
            bool wasFocused = IsKeyboardFocusWithin;
            FrameworkElement focus = childUiExt.CreateControls(theContext, theLinesPanel, thePanel, ref pos, theExpression);
            if (wasFocused && focus != null)
            {
                focus.Focus();
            }
            theDefaultPos = pos;
            return null;
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
