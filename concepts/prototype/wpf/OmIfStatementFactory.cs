using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OmniPrototype {
    public class OmIfStatementFactory : OmEntityFactory {
        public OmEntity Create(OmScope theParentScope)
        {
            return new OmIfStatement ();
        }

        public string Preview {
            get {
                return "if (...)";
            }
        }
    }
}
