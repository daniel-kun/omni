using System.Collections.Generic;

namespace OmniPrototype
{
    public class OmScope : OmEntity
    {
        public OmExpression Entities
        {
            get;
            set;
        }

        public new OmMeta GetMetaStatic (OmContext theContext)
        {
            return null;
        }

        public override OmMeta GetMeta(OmContext theContext)
        {
            return null;
        }

        public OmType FindType (string typeName)
        {
            return OmType.FindFundamental(typeName);
        }

        public IEnumerable <OmEntityFactory> TryParse (OmContext theContext, OmType theTargetType, string theInput)
        {
            var result = new List<OmEntityFactory>();
            foreach (var meta in theContext.GetEntityMetas())
            {
                if (meta.Parser != null)
                {
                    result.AddRange (meta.Parser.TryParse(this, theTargetType, theInput));
                }
            }
            return result;
        }
    }

}
