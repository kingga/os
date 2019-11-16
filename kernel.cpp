#include "src/Console.h"

void kernel_main()
{
    Console *console = new Console();

    console->write("Welcome to my first operating system!");
    for (;;);
}
