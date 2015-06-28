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
        public static T FindVisualParent<T>(FrameworkElement theElement) where T : FrameworkElement
        {
            if (theElement.Parent is T) {
                return (T) theElement.Parent;
            }
            else if (theElement.Parent is FrameworkElement)
            {
                return FindVisualParent<T>((FrameworkElement) theElement.Parent);
            }
            else
            {
                return null;
            }
        }

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

        public static IEnumerable<DependencyObject> AllVisualChildrenWhere(DependencyObject theParent, Func <DependencyObject, bool> thePredicate)
        {
            for (int i = 0; i < VisualTreeHelper.GetChildrenCount(theParent); ++i)
            {
                var child = VisualTreeHelper.GetChild(theParent, i);
                if (!thePredicate (child))
                {
                    break;
                }
                yield return child;
                foreach (var subChild in AllVisualChildrenWhere(child, thePredicate))
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

        public static IEnumerable<DependencyObject> AllVisualChildrenWithMeWhere(DependencyObject theParent, Func<DependencyObject, bool> thePredicate)
        {
            yield return theParent;
            for (int i = 0; i < VisualTreeHelper.GetChildrenCount(theParent); ++i)
            {
                var child = VisualTreeHelper.GetChild(theParent, i);
                if (!thePredicate(child))
                {
                    break;
                }
                foreach (var subChild in AllVisualChildrenWithMeWhere(child, thePredicate))
                {
                    yield return subChild;
                }
            }
        }

    }
}
