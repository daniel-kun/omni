
using System.Collections.Generic;
namespace OmniPrototype
{
    public class OmEntity
    {
        public OmEntity()
        {
            Components = new Dictionary<string, OmEntity> ();
        }

        public delegate void ChangeHandler(OmEntity theSender);

        public event ChangeHandler NameChanged;
        public event ChangeHandler ParentChanged;
        public event ChangeHandler Changed;

        public delegate void ComponentHandler(OmEntity theSender, string theKey, OmEntity theChild);
        public event ComponentHandler ComponentAdded;
        public event ComponentHandler ComponentRemoved;

        public OmMeta GetMetaStatic(OmContext thContext)
        {
            return null;
        }

        public virtual OmMeta GetMeta(OmContext theContext)
        {
            return null;
        }

        public string Name
        {
            get
            {
                return mName;
            }
            set
            {
                mName = value;
                EmitChangeEvent(NameChanged);
            }
        }

        public Dictionary <string, OmEntity> Components
        {
            get;
            private set;
        }

        public OmEntity Parent
        {
            get
            {
                return mParent;
            }
            private set
            {
                mParent = value;
                EmitChangeEvent(ParentChanged);
            }
        }

        public void AddComponent(string theKey, OmEntity theEntity)
        {
            Components[theKey] = theEntity;
            theEntity.Parent = this;
            EmitComponentEvent(ComponentAdded, theKey, theEntity);
        }

        private void RemoveComponent(string theKey)
        {
            var entity = Components[theKey];
            entity.Parent = null;
            Components.Remove(theKey);
            EmitComponentEvent(ComponentRemoved, theKey, entity);
        }

        private string mName = string.Empty;
        private OmEntity mParent = null;

        protected void EmitComponentEvent(ComponentHandler theHandler, string theKey, OmEntity theComponent)
        {
            var handler = theHandler;
            if (handler != null)
            {
                handler (this, theKey, theComponent);
            }
            var changedHandler = Changed;
            if (changedHandler != null)
            {
                changedHandler(this);
            }
        }

        protected void EmitChanged ()
        {
            EmitChangeEvent (Changed);
        }

        protected void EmitChangeEvent(ChangeHandler theHandler)
        {
            var handler = theHandler;
            if (handler != null)
            {
                handler(this);
            }
            var changedHandler = Changed;
            if (changedHandler != null)
            {
                changedHandler(this);
            }
        }

        public OmEntityExtension GetExtension (OmContext theContext, string theName)
        {
            if (!mExtensions.ContainsKey(theContext))
            {
                mExtensions.Add(theContext, new Dictionary<string, OmEntityExtension>());
            }
            if (mExtensions[theContext].ContainsKey(theName))
            {
                return mExtensions[theContext][theName];
            }
            else
            {
                var result = GetMeta(theContext).GetExtension(theName).CreateExtension();
                mExtensions[theContext][theName] = result;
                return result;
            }
            
        }

        private Dictionary<OmContext, Dictionary <string, OmEntityExtension>> mExtensions = new Dictionary<OmContext, Dictionary <string, OmEntityExtension>>();

    }

}
