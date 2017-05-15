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

        public virtual void ApplyUiDefaults(OmContext theContext, OmEntity theEntity)
        {
        }

        /**
        @return First list entry is the in-place list of controls, the rest are new-line controls.
        **/
        public abstract IEnumerable<List<FrameworkElement>> CreateControls(OmContext theContext, OmStatement theExpression);

        public string InternalName
        {
            get;
            private set;
        }

        protected static IEnumerable<List<FrameworkElement>> MakeSingleControlList(FrameworkElement theControl)
        {
            return new List<List<FrameworkElement>> { new List<FrameworkElement> { theControl } };
        }
    }
}
