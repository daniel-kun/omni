#include <QApplication>
#include <omni/forge/mainwindow.hpp>
#include "sandbox.hpp"

/*

statement
    - block
    - if_statement
    - return_statement
    - while_statemnt
    + expression
        + modifying_expression
            - function_call_expression
            - variable_assignment_expression
        + pure_expression
            - binary_operator_expression
            + cast_expression
                - bitcast_expression
            - literal_expression
            - variable_declaration_expression
            - variable_expression

*/

int main (int argc, char * argv[])
{
    QApplication app (argc, argv);
    omni::forge::sandbox mainWindow;
    mainWindow.show ();

    return app.exec ();
}
