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
        }

        protected override void OnPreviewLostKeyboardFocus(KeyboardFocusChangedEventArgs e)
        {
            base.OnPreviewLostKeyboardFocus(e);
            UpdateIsSelected(e);
        }

        private void UpdateIsSelected(KeyboardFocusChangedEventArgs e)
        {
            if (Entity != null)
            {
                Func <DependencyObject, bool> noSelectionHost = (child) =>
                {
                    return !(child is ExpressionControlSelectionHost);
                };
                Entity.WithAllExpressions <OmEntityUiExtension> ("omni.ui", extension =>
                    extension.IsSelected = VisualTreeUtils.AllVisualChildrenWithMeWhere(this, noSelectionHost).Where(child => child == e.NewFocus).Count() > 0);
            }
        }

        protected override void OnPreviewGotKeyboardFocus(KeyboardFocusChangedEventArgs e)
        {
            base.OnPreviewGotKeyboardFocus(e);
            UpdateIsSelected(e);
        }

        public OmEntity Entity
        {
            get
            {
                return mEntity;
            }
            set
            {
                if (mEntity != null)
                {
                    mEntity.WithAllExpressions<OmEntityUiExtension>("omni.ui", extension =>
                        extension.SelectionChanged -= mUiExtension_SelectionChanged);
                }
                mEntity = value;
                if (mEntity != null)
                {
                    mEntity.WithAllExpressions<OmEntityUiExtension>("omni.ui", extension =>
                        extension.SelectionChanged += mUiExtension_SelectionChanged);
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
        private OmEntity mEntity;

        
    }
}
