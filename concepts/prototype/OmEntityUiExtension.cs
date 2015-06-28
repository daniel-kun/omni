
using System;
namespace OmniPrototype
{
    public class OmEntityUiExtension : OmEntityExtension
    {
        public OmContext CreatedInContext
        {
            get;
            set;
        }

        public event Action <OmEntityUiExtension> SelectionChanged;

        private bool mIsSelected;

        public bool IsSelected
        {
            get
            {
                return mIsSelected;
            }
            set
            {
                mIsSelected = value;
                EmitSelectionChanged();
            }
        }

        private void EmitSelectionChanged()
        {
            var handler = SelectionChanged;
            if (handler != null) {
                handler(this);
            }
        }
    }
}
