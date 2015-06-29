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
    public partial class OperatorSelectionControl : UserControl
    {
        public OperatorSelectionControl()
        {
            InitializeComponent();
            mText.SetBinding(TextBlock.TextProperty, new Binding("Text")
            {
                Source = this
            });
            MouseUp += (object sender, MouseButtonEventArgs e) => {
                Focus ();
            };
        }

        public event EventHandler<EventArgs> TextChanged;

        public string Text
        {
            get
            {
                return (string)GetValue(TextProperty);
            }
            set
            {
                SetValue(TextProperty, value);
            }
        }

        // Using a DependencyProperty as the backing store for Text.  This enables animation, styling, binding, etc...
        public static readonly DependencyProperty TextProperty =
            DependencyProperty.Register("Text", typeof(string), typeof(OperatorSelectionControl), new PropertyMetadata(string.Empty, TextChangedCallback));


        private static void TextChangedCallback(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            var c = (OperatorSelectionControl)d;
            c.EmitTextChanged();
        }

        private void EmitTextChanged()
        {
            var handler = TextChanged;
            if (handler != null)
            {
                handler(this, new EventArgs());
            }
        }

        protected override void OnPreviewKeyDown(KeyEventArgs e)
        {
            switch (e.Key)
            {
                case Key.Add:
                    Text = "+";
                    break;
                case Key.Subtract:
                    Text = "-";
                    break;
                case Key.Multiply:
                    Text = "*";
                    break;
                case Key.Divide:
                    Text = "/";
                    break;
            }
        }
    }
}
