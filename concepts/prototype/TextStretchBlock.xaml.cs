using System;
using System.Collections.Generic;
using System.Globalization;
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
    /// Interaction logic for TextStretchBlock.xaml
    /// </summary>
    public partial class TextStretchBlock : UserControl
    {
        public TextStretchBlock()
        {
            Margin = new Thickness(3);
        }

        private FormattedText CreateFormattedText()
        {
            var typeFaceEnum = FontFamily.GetTypefaces().GetEnumerator();
            typeFaceEnum.MoveNext();
            return new FormattedText(
                Text,
                CultureInfo.CurrentCulture,
                FlowDirection,
                typeFaceEnum.Current,
                FontSize,
                Foreground);
        }

        protected override Size MeasureOverride(Size constraint)
        {
            var geometry = CreateFormattedText().BuildGeometry(new Point(0, 0));
            if (constraint.Height == 0)
            {
                return new Size(0, 0);
            }
            else if (double.IsInfinity(geometry.Bounds.Width) || double.IsInfinity(geometry.Bounds.Height))
            {
                return new Size(0, 0);
            }
            else if (double.IsInfinity(constraint.Height))
            {
                return new Size(geometry.Bounds.Width, geometry.Bounds.Height);
            }
            else
            {
                return new Size(geometry.Bounds.Width, constraint.Height);
            }
        }

        protected override void OnRender(DrawingContext drawingContext)
        {
            base.OnRender(drawingContext);
            var geometry = CreateFormattedText().BuildGeometry(new Point(0, 0));
            if (geometry.Bounds.Width != 0 &&
                geometry.Bounds.Height != 0 &&
                !double.IsInfinity(geometry.Bounds.Width) &&
                !double.IsInfinity(geometry.Bounds.Height))
            {
                var transforms = new TransformGroup();
                transforms.Children.Add(new TranslateTransform(-geometry.Bounds.Left, -geometry.Bounds.Top));
                transforms.Children.Add(new ScaleTransform(ActualWidth / geometry.Bounds.Width, ActualHeight / geometry.Bounds.Height));
                geometry.Transform = transforms;

                drawingContext.DrawGeometry(Brushes.Black, new Pen(Brushes.Black, 0.18), geometry);
            }
        }

        public static readonly DependencyProperty TextProperty = DependencyProperty.Register(
            "Text",
            typeof(string),
            typeof(TextStretchBlock),
            new FrameworkPropertyMetadata()
            {
                AffectsMeasure = true,
                AffectsRender = true,
                PropertyChangedCallback = TextPropertyChanged
            });

        private static void TextPropertyChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            var self = (TextStretchBlock)d;
            self.InvalidateMeasure();
        }

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
    }
}
