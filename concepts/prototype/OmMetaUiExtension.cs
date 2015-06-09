using System.Windows;
using System.Windows.Controls;

namespace OmniPrototype
{
    public abstract class OmMetaUiExtension : OmMetaExtension
    {
        protected OmMetaUiExtension (string theInternalName)
        {
            InternalName = theInternalName;
        }

        public string GetTemplate(OmContext theContext)
        {
            return theContext.Templates[InternalName];
        }

        public abstract FrameworkElement CreateControls(OmContext theContext, StackPanel theLinesPanel, WrapPanel thePanel, ref int theIndex, OmStatement theExpression);

        public string InternalName
        {
            get;
            private set;
        }
    }
}
