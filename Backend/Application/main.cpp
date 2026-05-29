#include <signal.h>
#include <stdio.h>
#include "Backend.hpp"

static Backend *spBackend = nullptr;

/* ************************************************************************* */

/**
 * @brief 
 * @param sig 
 */
static void Signal_Handler(int sig)
{
    (void) sig;
    spBackend->stop();
}

/* ************************************************************************* */

/**
 * @brief 
 */
int main(int, char **)
{
    // Catch signals for a grace shutdown.
    signal(SIGINT,  Signal_Handler);
    signal(SIGTERM, Signal_Handler);

    printf("[INFO] MotorTester Backend starting...\n");

    // Allocate memory for the backend instance. 
    spBackend = new Backend();
    // Call the running and wait until the end of processing.
    return spBackend->start();
}