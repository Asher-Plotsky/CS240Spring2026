#include <stdio.h>

int main(void) {
    int power_log[] = {65, 340, 82, 305, 315, 190, 77, 420};   // Power log contains your dataset of power readings.
    int len = sizeof(power_log)/sizeof(power_log[0]);   // Number of readings in the log.
    int total = 0;           // Sum of "high" readings encountered when scanning the power logs.
    int count = 0;         // Number of "high" readings encountered when scanning the power logs.
    int avg = 0;             // Mean avg. of "high" readings encountered when scanning the power logs.
    int lowcount = 0;   // Number of "low" readings encountered when scanning the power logs.

    asm volatile (

          //PLACE

          //YOUR

          //CODE

          //HERE


        : [total] "=r" (total), [count] "=r" (count), [lowcount] "=r" (lowcount)   // This part can be changed if you want.
        : [arr] "r" (power_log), [len] "r" (len)
        : "r4", "r5", "r6", "r7", "r8", "r9", "r10"  // Registers used. Can be changed as well.
    );

    if (count > 0)
        avg = total / count;

    printf("Average of high-power readings = %d mW\n", avg);
    printf("%d low-power readings dumped into RAM at 0x20001000:\n",lowcount);
    return 0;
}
