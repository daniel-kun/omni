using System;
using System.Collections.Generic;
using System.Globalization;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;

namespace OmniPrototype
{
    public class OmMetaUiControlCreator
    {
        public delegate FrameworkElement ComponentPlaceholderRequestedHandler(WrapPanel thePanel, ref int thePlaceholderIndex, string thePlaceholderName);
        public delegate IEnumerable <List <FrameworkElement>> ComponentPlaceholderRequestedHandler2(string thePlaceholderName);

        public OmMetaUiControlCreator (
            ComponentPlaceholderRequestedHandler theExpressionPlaceholderRequested)
        {
            mExpressionPlaceholderRequested = theExpressionPlaceholderRequested;
        }

        public OmMetaUiControlCreator(
           ComponentPlaceholderRequestedHandler2 theExpressionPlaceholderRequested)
        {
            mExpressionPlaceholderRequested2 = theExpressionPlaceholderRequested;
        }

        public static Brush ColorFromText(string theText)
        {
            // When the text only consists of some kind of brackets and whitespace:
            if (theText.Trim("{}()[] \t\r\n".ToCharArray()).Length == 0)
            {
                return Brushes.Red;
            }
            else
            {
                return Brushes.Blue;
            }
        }

        public static int StringIndexOfNotAny (string theText, string theAny, int theStartIndex)
        {
            for (int i = theStartIndex; i < theText.Length; ++i)
            {
                if (theAny.IndexOf(theText[i]) < 0)
                {
                    return i;
                }
            }
            return -1;
        }

        public static IEnumerable <string> SplitAtBrackets (string theText)
        {
            // variable
            // (variable
            // (
            // = (<input>)
            /*
            foreach (var c in theText)
            {
                yield return c.ToString ();
            }
            */
            const string match = "{}[]() \t\r\n"; // "{}()[] \t\r\n"
            int startIdx = 0;
            int endIdx = 0;
            do
            {
                endIdx = StringIndexOfNotAny(theText, match, startIdx);
                if (endIdx == startIdx)
                {
                    endIdx = theText.IndexOfAny(match.ToCharArray(), startIdx);
                }
                if (endIdx == -1)
                {
                    endIdx = theText.Length;
                }
                yield return theText.Substring(startIdx, endIdx - startIdx);
                startIdx = endIdx;
            } while (endIdx < theText.Length);
        }

        public FrameworkElement CreateControlsFromTemplate(OmContext theContext, StackPanel theLinesPanel, WrapPanel thePanel, ref int thePosition, string theTemplate)
        {
            string[] lines = theTemplate.Split(new string[] { "\r\n" }, System.StringSplitOptions.None);
            var panel = thePanel;
            for (int i = 0; i < lines.Length; ++ i)
            {
                var line = lines[i];
                int idx = theLinesPanel.Children.IndexOf(thePanel);
                var lineRest = line;
                while (lineRest.Length > 0)
                {
                    int freeInputIndex = lineRest.IndexOf("[");
                    int expressionTypeIndex = lineRest.IndexOf("<");
                    if (freeInputIndex >= 0 && (freeInputIndex < expressionTypeIndex || expressionTypeIndex < 0))
                    {
                        // First the free input placeholder
                        string staticText = lineRest.Substring(0, freeInputIndex);
                        if (staticText.Length > 0)
                        {
                            //mGrid.ColumnDefinitions.Add(new ColumnDefinition() { Width = new GridLength(1.0, GridUnitType.Auto) });
                            foreach (var text in SplitAtBrackets(staticText))
                            {
                                var tb = new TextBlock()
                                {
                                    Text = text,
                                    VerticalAlignment = VerticalAlignment.Center,
                                    Foreground = ColorFromText(text),
                                    Margin = new Thickness(0)
                                };
                                panel.Children.Insert(thePosition++, tb);
                            }
                        }
                        lineRest = lineRest.Substring(freeInputIndex + 1);
                        int freeInputIndexEnd = lineRest.IndexOf("]");
                        if (freeInputIndexEnd < 0)
                        {
                            throw new Exception("Unterminated [");
                        }
                        string freeInputName = lineRest.Substring(0, freeInputIndexEnd);
                        panel.Children.Insert(thePosition++, mExpressionPlaceholderRequested(panel, ref thePosition, freeInputName));
                        lineRest = lineRest.Substring(freeInputIndexEnd + 1);
                    }
                    else if (expressionTypeIndex >= 0)
                    {
                        // First the free expression placeholder
                        string staticText = lineRest.Substring(0, expressionTypeIndex);
                        lineRest = lineRest.Substring(expressionTypeIndex + 1);
                        int expressionTypeIndexEnd = lineRest.IndexOf(">");
                        if (expressionTypeIndexEnd < 0)
                        {
                            throw new Exception("Unterminated <");
                        }
                        if (staticText.Length > 0)
                        {
                            foreach (var text in SplitAtBrackets(staticText))
                            {
                                var tb = new TextBlock()
                                {
                                    Text = text,
                                    VerticalAlignment = VerticalAlignment.Center,
                                    Foreground = ColorFromText(text),
                                    Margin = new Thickness(0)
                                };
                                panel.Children.Insert(thePosition++, tb);
                            }
                        }
                        var componentName = lineRest.Substring(0, expressionTypeIndexEnd);
                        var newChild = mExpressionPlaceholderRequested(panel, ref thePosition, componentName);
                        if (newChild != null)
                        {
                            panel.Children.Insert(thePosition++, newChild);
                        }
                        lineRest = lineRest.Substring(expressionTypeIndexEnd + 1);
                    }
                    else
                    {
                        // No placeholders any more
                        foreach (var text in SplitAtBrackets(lineRest))
                        {
                            var tb = new TextBlock()
                            {
                                Text = text,
                                VerticalAlignment = VerticalAlignment.Center,
                                Foreground = ColorFromText(text),
                                Margin = new Thickness(0)
                            };
                            panel.Children.Insert(thePosition++, tb);
                        }
                        lineRest = string.Empty;
                    }
                }
                if (lines.Length > 1)
                {
                    var newPanel = new WrapPanel();
                    theLinesPanel.Children.Insert(theLinesPanel.Children.IndexOf(panel) + 1, newPanel);
                    panel = newPanel;
                    thePosition = 0;
                }
            }
            return null;
        }

        private static IEnumerable <List <FrameworkElement>> Merge(List<FrameworkElement> theCurrentLine, IEnumerable<List<FrameworkElement>> theControls)
        {
            var controls = new List <List<FrameworkElement>> (theControls);
            bool isInline = true;
            foreach (var line in theControls)
            {
                if (isInline)
                {
                    isInline = false;
                    theCurrentLine.AddRange(line);
                }
                else
                {
                    yield return line;
                }
            }
        }

        public IEnumerable <List <FrameworkElement>> CreateControlsFromTemplate2 (OmContext theContext, string theTemplate)
        {
            string[] lines = theTemplate.Split(new string[] { "\r\n" }, System.StringSplitOptions.None);
            foreach (var line in lines)
            {
                var controls = new List<FrameworkElement>();
                var newLineControls = new List <List<FrameworkElement>>();
                var lineRest = line;
                bool isBeforePlaceholder = true;
                while (lineRest.Length > 0)
                {
                    int freeInputIndex = lineRest.IndexOf("[");
                    int expressionTypeIndex = lineRest.IndexOf("<");
                    if (freeInputIndex >= 0 && (freeInputIndex < expressionTypeIndex || expressionTypeIndex < 0))
                    {
                        // First the free input placeholder
                        string staticText = lineRest.Substring(0, freeInputIndex);
                        if (staticText.Length > 0)
                        {
                            //mGrid.ColumnDefinitions.Add(new ColumnDefinition() { Width = new GridLength(1.0, GridUnitType.Auto) });
                            CreateStaticTextControls(controls, staticText, isBeforePlaceholder);
                        }
                        lineRest = lineRest.Substring(freeInputIndex + 1);
                        int freeInputIndexEnd = lineRest.IndexOf("]");
                        if (freeInputIndexEnd < 0)
                        {
                            throw new Exception("Unterminated [");
                        }
                        string freeInputName = lineRest.Substring(0, freeInputIndexEnd);
                        newLineControls.AddRange(Merge(controls, mExpressionPlaceholderRequested2(freeInputName)));
                        isBeforePlaceholder = false;
                        lineRest = lineRest.Substring(freeInputIndexEnd + 1);
                    }
                    else if (expressionTypeIndex >= 0)
                    {
                        // First the free expression placeholder
                        string staticText = lineRest.Substring(0, expressionTypeIndex);
                        lineRest = lineRest.Substring(expressionTypeIndex + 1);
                        int expressionTypeIndexEnd = lineRest.IndexOf(">");
                        if (expressionTypeIndexEnd < 0)
                        {
                            throw new Exception("Unterminated <");
                        }
                        if (staticText.Length > 0)
                        {
                            CreateStaticTextControls(controls, staticText, isBeforePlaceholder);
                        }
                        var componentName = lineRest.Substring(0, expressionTypeIndexEnd);
                        newLineControls.AddRange(Merge(controls, mExpressionPlaceholderRequested2(componentName)));
                        isBeforePlaceholder = false;
                        lineRest = lineRest.Substring(expressionTypeIndexEnd + 1);
                    }
                    else
                    {
                        // No placeholders any more
                        CreateStaticTextControls(controls, lineRest, isBeforePlaceholder);
                        lineRest = string.Empty;
                    }
                }
                yield return controls;
                foreach (var newLine in newLineControls)
                {
                    yield return newLine;
                }
            }
        }

        public partial class TextStretchBlock2 : UserControl
        {
            public TextStretchBlock2()
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
                typeof(TextStretchBlock2),
                new FrameworkPropertyMetadata()
                {
                    AffectsMeasure = true,
                    AffectsRender = true,
                    PropertyChangedCallback = TextPropertyChanged
                });

            private static void TextPropertyChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
            {
                var self = (TextStretchBlock2)d;
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

        private static void CreateStaticTextControls (List<FrameworkElement> theControls,string theStaticText, bool theIsBeforePlaceholder)
        {
            foreach(var text in SplitAtBrackets(theStaticText)) {
                /*
                var viewBox = new Viewbox()
                {
                    Child = new TextBlock()
                    {
                        Text = text,
                        Foreground = ColorFromText(text),
                        Background = Brushes.Bisque,
                        Margin = new Thickness(0)
                    },
                    StretchDirection = StretchDirection.Both,
                    VerticalAlignment = VerticalAlignment.Top,
                    HorizontalAlignment = HorizontalAlignment.Left
                };
                */
                // TODO Render text myself.... ;-(
                /*var userControl = new UserControl () {
                    Content = viewBox,
                    VerticalAlignment = VerticalAlignment.Stretch,
                    HorizontalAlignment = HorizontalAlignment.Left,
                    VerticalContentAlignment = VerticalAlignment.Top,
                    HorizontalContentAlignment = HorizontalAlignment.Left,
                    Background = Brushes.Beige
                };
                userControl.SizeChanged += (object sender, SizeChangedEventArgs e) =>
                {
                    viewBox.Width = userControl.ActualWidth;
                    viewBox.Height = userControl.ActualHeight;
                };
                */
                if (text.Contains("(") || text.Contains(")"))
                {
                    theControls.Add(new TextStretchBlock2 () { Text = text });
                }
                else
                {
                    theControls.Add(new TextBlock()
                    {
                        Text = text
                    });
                }
            }
        }

        public static void ApplyControlsToLayout (Grid theGrid, WrapPanel thePanel, IEnumerable <List <FrameworkElement>> theControls)
        {
            bool isFirstInline = true;
            WrapPanel currentLinePanel = thePanel;
            foreach (var controlLine in theControls)
            {
                if (! isFirstInline) {
                    currentLinePanel = new WrapPanel();
                    theGrid.RowDefinitions.Add(new RowDefinition()
                    {
                        Height = GridLength.Auto
                    });
                    Grid.SetRow(currentLinePanel, theGrid.RowDefinitions.Count - 1);
                    theGrid.Children.Add(currentLinePanel);
                }
                isFirstInline = false;
                foreach (var control in controlLine)
                {
                    currentLinePanel.Children.Add(control);
                }
            }
        }

        private ComponentPlaceholderRequestedHandler mExpressionPlaceholderRequested;
        private ComponentPlaceholderRequestedHandler2 mExpressionPlaceholderRequested2;
    }
}
