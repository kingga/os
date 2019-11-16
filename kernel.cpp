#ifdef __cplusplus
extern "C" {
#endif

#include "src/Console.h"

void kernel_main()
{
    // Console *console = new Console();
    // TODO: Test this.
    Console console;
    console.write("Welcome to my first operating system!");

    // console->write("Welcome to my first operating system!");
    for (;;);
}

#ifdef __cplusplus
}
#endif
