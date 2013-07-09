#include <cstdio>

/**
This template implements a few basic features:

in string_equals:
+ functions
+ arguments
+ while()
+ dereferencing pointers
+ comparing dereferenced values with each other
+ if ()
+ incrementing pointers
+ comparing dereferenced values with constants
+ return

in main:
+ system calls
+ static array fields of constant size
+ initialized local variables
+ uninitialized local variables
- for()
- decrement a variable by a constant
- `greater than'-comparison
- decrementation
- if () else
- modulo
- multiplication
- in-place adding values
- do...while
- switch
- calling a function
**/

bool string_equals (char const * str1, char const * str2)  // #1 functions, #2 arguments
{
    while (* str1 != '\0' && * str2 != '\0') { // #2 while
        if (* str1 != * str2) { // #3 if ()
            return false; // #4 return
        }
        ++ str1;
        ++ str2;
    };
    return * str1 == '\0' && * str2 == '\0';
}

void template_basic ()
{
    std::printf ("Type \"exit\" to quit.\n");
    char inputBuffer [256];
    do { // #5 do...while
        const unsigned int facultyStart = 5;
        int faculty = facultyStart;

        for (int i = facultyStart - 1; i > 0; -- i) {
            if ((i % 2) != 0) {
                faculty *= i;
            } else {
                faculty += i;
            }
            // Just for the fun of it, do some random calculations with faculty based on i:
            switch (i) {
            case 1:
                faculty += i * 2;
                break;
            case 2:
                faculty -= i * 3;
                break;
            case 3:
                faculty *= i + 4;
                break;
            }
        }

        std::printf ("Faculty: %d\n", faculty);
        std::scanf ("%s", inputBuffer);
    } while (! string_equals (inputBuffer, "exit"));
}