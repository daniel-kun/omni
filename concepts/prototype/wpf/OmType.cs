using System.Collections.Generic;

namespace OmniPrototype
{
    public class OmType
    {
        public string Name
        {
            get;
            private set;
        }

        public OmType Super
        {
            get;
            set;
        }

        public static OmType FindFundamental (string theType)
        {
            foreach (var type in Fundamentals())
            {
                if (type.Name == theType)
                {
                    return type;
                }
            }
            return null;
        }

        public static List<OmType> Fundamentals()
        {
            return new List<OmType>
            {
                Void,
                Int,
                Bool,
                String
            };
        }

        public static readonly OmType Void = new OmType() { Name = "void" };
        public static readonly OmType Int = new OmType() { Name = "int", Super = OmType.Void };
        public static readonly OmType Bool = new OmType() { Name = "bool", Super = OmType.Void };
        public static readonly OmType String = new OmType() { Name = "string", Super = OmType.Void };
    
    }
}
