using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace OmniPrototype
{
    /// <summary>
    /// Interaction logic for ExpressionControlSelectionHost.xaml
    /// </summary>
    public partial class ExpressionControlSelectionHost : UserControl
    {
        public ExpressionControlSelectionHost()
        {
            InitializeComponent();
            IsKeyboardFocusWithinChanged += ExpressionControlSelectionHost_IsKeyboardFocusWithinChanged;
        }

        private void ExpressionControlSelectionHost_IsKeyboardFocusWithinChanged(object sender, DependencyPropertyChangedEventArgs e)
        {
            if (UiExtension != null)
            {
                if ((bool) e.NewValue)
                {
                    foreach (var child in VisualTreeUtils.AllVisualChildren(this))
                    {
                        if (child is ExpressionControlSelectionHost && ((ExpressionControlSelectionHost)child).IsKeyboardFocusWithin)
                        {
                            return;
                        }
                    }
                }
                UiExtension.IsSelected = (bool) e.NewValue;
            }
        }

        public OmEntityUiExtension UiExtension
        {
            get
            {
                return mUiExtension;
            }
            set
            {
                if (mUiExtension != null)
                {
                    mUiExtension.SelectionChanged -= mUiExtension_SelectionChanged;
                }
                mUiExtension = value;
                if (mUiExtension != null)
                {
                    mUiExtension.SelectionChanged += mUiExtension_SelectionChanged;
                }
            }
        }

        private void mUiExtension_SelectionChanged(OmEntityUiExtension obj)
        {
            IsSelected = obj.IsSelected;
        }

        public bool IsSelected
        {
            get
            {
                return (bool)GetValue(IsSelectedProperty);
            }
            set
            {
                SetValue(IsSelectedProperty, value);
            }
        }

        // Using a DependencyProperty as the backing store for IsSelected.  This enables animation, styling, binding, etc...
        public static readonly DependencyProperty IsSelectedProperty =
            DependencyProperty.Register("IsSelected", typeof(bool), typeof(ExpressionControlSelectionHost), new PropertyMetadata(false));
        private OmEntityUiExtension mUiExtension;

        
    }
}
