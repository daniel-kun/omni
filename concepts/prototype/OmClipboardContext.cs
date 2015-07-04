using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OmniPrototype
{
    public class OmClipboardContext : OmContext
    {
        public enum ClipboardAction {
            Cut,
            Copy
        };

        public ClipboardAction Action
        {
            get;
            set;
        }
    }
}
