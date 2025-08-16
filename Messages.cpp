#include "Messages.h"

namespace test
{
    Messages::Messages()
    {
        std::cout << "ConstructedMessages\n";
    }
    void Messages::SaySomething1()
    {
        std::cout << "SaySomething1\n"; 
    }

    void Messages::SaySomething2()
    {
        std::cout << "SaySomething2\n";
    }
}