
namespace OmniPrototype {
    public class OmBlockStatement : OmStatement
    {
        public static new OmMeta GetMetaStatic (OmContext theContext)
        {
            return theContext.BlockStatementMeta;
        }

        public override OmMeta GetMeta(OmContext theContext)
        {
            return theContext.BlockStatementMeta;
        }

    }
}
