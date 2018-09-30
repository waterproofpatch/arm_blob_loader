#include <stdio.h>

// some other function
int some_other_function();

// some global
int g_a;

/**
 * @brief entry point to this PIC blob, takes one int arg.
 * @param arg: integer argument.
 * @return: integer argument.
 */
int my_start(int arg)
{
    g_a = 0x1337;
    return some_other_function();
}

/**
 * @brief some other function to do stuff.
 * @return some integer argument.
 */
int some_other_function()
{
    return g_a + 1;
}
