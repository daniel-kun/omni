using System;
using System.Collections.Generic;
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

        /// TODO: Make CreateControls return a List<List<FrameworkElement>> (and a focus FrameworkElement) instead of letting it populate theLinesPanel and thePanel itself.
        /// Additionally, a Flag is required whether the controls should be inserted in-place or into a new line.
        /// That way, the parameters theLinesPanel, thePanel and theIndex can be removed.
        public abstract FrameworkElement CreateControls(OmContext theContext, StackPanel theLinesPanel, WrapPanel thePanel, ref int theIndex, OmStatement theExpression);

        /**
        @return First list entry is the in-place list of controls, the rest are new-line controls.
        **/
        public virtual IEnumerable<List<FrameworkElement>> CreateControls2(OmContext theContext, OmStatement theExpression)
        {
            return new List<List<FrameworkElement>>();
        }

        public string InternalName
        {
            get;
            private set;
        }
    }
}
