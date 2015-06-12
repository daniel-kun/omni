using System.Collections.Generic;
using System.Windows;

namespace OmniPrototype
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();

            mContext2.Templates = new Dictionary<string, string>()
            {
                {"binary_operator_expression", "(<operator> <left> <right>)"},
                {"block", "<statement>"},
                {"bool_literal_expression", "<value>"},
                {"int_literal_expression", "<value>"},
                {"variable_declaration_expression", "(let [name] <initexpr>)"},
                {"variable_use_expression", "<variable>"},
{"if_statement",
@"(cond (<condition>)
    (<body>)
    (<else-body>)"},
            };


            var rootBlock = new OmBlockStatement ();
            int index = 0;
            var metaUiExt = OmBlockStatement.GetMetaStatic(mContext).GetExtension("omni.ui") as OmMetaUiExtension;
            metaUiExt.CreateControls(mContext, mLinesPanel1, null, ref index, rootBlock);

            index = 0;
            var metaUiExt2 = OmBlockStatement.GetMetaStatic(mContext2).GetExtension("omni.ui") as OmMetaUiExtension;
            metaUiExt2.CreateControls(mContext2, mLinesPanel2, null, ref index, rootBlock);

            var varDecl = new OmVariableDeclarationExpression ()
            {
            };
            varDecl.Name = "var1";
            rootBlock.AddComponent("1", varDecl);
            var initExpr = new OmBoolLiteralExpression() {
                Value = true
            };
            varDecl.InitializationExpression = initExpr;

            var varDecl2 = new OmVariableDeclarationExpression ()
            {
            };
            rootBlock.AddComponent("2", varDecl2);
            varDecl2.Name = "var2";
            var initExpr2 = new OmIntLiteralExpression () {
                Value = 123456
            };
            varDecl2.InitializationExpression = initExpr2;

            var varDecl3 = new OmVariableDeclarationExpression()
            {
                Name = "var3"
            };
            rootBlock.AddComponent("3", varDecl3);
            varDecl3.InitializationExpression = new OmBinaryOperatorExpression()
            {
                LeftOperand = new OmVariableUseExpression()
                {
                    Variable = varDecl2
                },
                Operator = "+",
                RightOperand = new OmIntLiteralExpression()
                {
                    Value = 20
                }
            };
            rootBlock.AddComponent("4",
                new OmIfStatement () {
                    Condition = new OmBoolLiteralExpression () { Value = true },
                    Body = new OmBinaryOperatorExpression()
                    {
                        LeftOperand = new OmIntLiteralExpression()
                        {
                            Value = 30
                        },
                        Operator = "+",
                        RightOperand = new OmIntLiteralExpression()
                        {
                            Value = 20
                        }
                    }});
        }

        private OmContext mContext = new OmContext();
        private OmContext mContext2 = new OmContext();
    }
}
