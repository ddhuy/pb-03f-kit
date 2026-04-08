int main(void)
{
    /* Initialize the system. */
    SystemInit();

    /* Initialize the application. */
    AppInit();

    /* Start the scheduler. */
    vTaskStartScheduler();

    /* We should never get here as control is now taken by the scheduler. */
    for (;;);
}