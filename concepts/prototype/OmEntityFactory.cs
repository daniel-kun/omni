
namespace OmniPrototype
{
    public interface OmEntityFactory
    {
        OmEntity Create (OmScope theParentScope);

        string Preview
        {
            get;
        }
    }
}
