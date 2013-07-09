#include <iostream>
#include <string>

extern "C" { // Declarations for functions defined in .ll-code
void template_basic ();
}

int main_ (int argc, char * argv[])
{
    template_basic ();

    std::cout << "Finished!" << std::endl;
    std::string line;
    std::getline (std::cin, line);
    std::getline (std::cin, line);

    return 0;
}