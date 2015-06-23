using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;

namespace OmniPrototype
{
    public class OmVariableUseExpressionMetaUiExtension : OmMetaUiExtension
    {
        public OmVariableUseExpressionMetaUiExtension() : base ("variable_use_expression")
        {
        }

        public override OmEntityExtension CreateExtension()
        {
            return new OmVariableUseExpressionUiExtension();
        }
    }
}
