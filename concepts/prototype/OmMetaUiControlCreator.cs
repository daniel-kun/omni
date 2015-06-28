using System;
using System.Collections.Generic;
using System.Globalization;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Linq;

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

        private static Brush ColorFromText(string theText)
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

        private static int StringIndexOfNotAny (string theText, string theAny, int theStartIndex)
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

        private static IEnumerable<string> SplitAtBrackets(string theText)
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

        private static IEnumerable<List<FrameworkElement>> Merge(List<FrameworkElement> theCurrentLine, IEnumerable<List<FrameworkElement>> theControls)
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

        public IEnumerable <List <FrameworkElement>> CreateControlsFromTemplate (OmContext theContext, OmEntity theEntity, string theTemplate)
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
                yield return WrapWithHosts(controls, theContext, theEntity);
                foreach (var newLine in newLineControls)
                {
                    yield return WrapWithHosts(newLine, theContext, theEntity);
                }
            }
        }

        private List<FrameworkElement> WrapWithHosts(List<FrameworkElement> controls, OmContext theContext, OmEntity theEntity)
        {
            if (theEntity != null)
            {
                return new List<FrameworkElement>(controls.Select(control => new ExpressionControlSelectionHost()
                {
                    Content = control,
                    Entity = theEntity
                }));
            }
            else
            {
                return controls;
            }
        }

        private static void CreateStaticTextControls (List<FrameworkElement> theControls,string theStaticText, bool theIsBeforePlaceholder)
        {
            foreach(var text in SplitAtBrackets(theStaticText)) {
                if (text.Contains("(") || text.Contains(")"))
                {
                    theControls.Add(new TextStretchBlock()
                    {
                        Text = text,
                        Foreground = Brushes.Blue
                    });
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
