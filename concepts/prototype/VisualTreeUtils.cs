using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Media;

namespace OmniPrototype
{
    public static class VisualTreeUtils
    {
        public static IEnumerable<DependencyObject> AllVisualChildren(DependencyObject theParent)
        {
            for (int i = 0; i < VisualTreeHelper.GetChildrenCount(theParent); ++i)
            {
                var child = VisualTreeHelper.GetChild(theParent, i);
                yield return child;
                foreach (var subChild in AllVisualChildren(child))
                {
                    yield return subChild;
                }
            }
        }

        public static IEnumerable<DependencyObject> AllVisualChildrenWithMe(DependencyObject theParent)
        {
            yield return theParent;
            for (int i = 0; i < VisualTreeHelper.GetChildrenCount(theParent); ++i)
            {
                var child = VisualTreeHelper.GetChild(theParent, i);
                foreach (var subChild in AllVisualChildrenWithMe(child))
                {
                    yield return subChild;
                }
            }
        }
    }
}
