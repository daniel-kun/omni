using System.Collections.Generic;

namespace OmniPrototype
{
    public class OmMeta
    {
        public OmMeta(string theName, OmEntityParser theParser)
        {
            Name = theName;
            Parser = theParser;
        }

        public string Name
        {
            get;
            private set;
        }

        public OmEntityParser Parser
        {
            get;
            private set;
        }

        public OmMetaExtension GetExtension(string theName)
        {
            return mExtensions[theName];
        }

        public void SetExtension(string theName, OmMetaExtension theExtension)
        {
            mExtensions[theName] = theExtension;
        }

        private Dictionary<string, OmMetaExtension> mExtensions = new Dictionary<string, OmMetaExtension>();

    }
}
