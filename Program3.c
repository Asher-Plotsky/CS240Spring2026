//This code works in SEGGER which the project is intended for but not in CLion
#include <stdio.h>

int main(void) {
    int power_log[] = {65, 340, 82, 305, 315, 190, 77, 420};   // Power log contains your dataset of power readings.
    int len = sizeof(power_log)/sizeof(power_log[0]);   // Number of readings in the log.
    int total = 0;           // Sum of "high" readings encountered when scanning the power logs.
    int count = 0;         // Number of "high" readings encountered when scanning the power logs.
    int avg = 0;             // Mean avg. of "high" readings encountered when scanning the power logs.
    int lowcount = 0;   // Number of "low" readings encountered when scanning the power logs.
    asm volatile (
        "mov r4, %[arr]            \n\t"
        "mov r5, %[len]            \n\t"
        "mov r6, #0                \n\t"
        "mov r7, %[total]          \n\t"
        "mov r8, %[count]          \n\t"
        "mov r9, %[lowcount]       \n\t"
        "ldr r10, =0x20001000      \n\t"

        "loop:                     \n\t"
        "cmp r6, r5                \n\t"
        "bge end                   \n\t"
        "ldr r11, [r4, r6, LSL #2] \n\t"
        "cmp r11, #300             \n\t"
        "blt cont                  \n\t"
        "add r7, r7, r11           \n\t"
        "add r8, r8, #1            \n\t"
        "b endloop                 \n\t"

        "cont:                     \n\t"
        "str r11, [r10], #4        \n\t"
        "add r9, r9, #1            \n\t"

        "endloop:                  \n\t"
        "add r6, r6, #2            \n\t"
        "b loop                    \n\t"

        "end:                      \n\t"
        "mov %[total], r7          \n\t"
        "mov %[count], r8          \n\t"
        "mov %[lowcount], r9       \n\t"

        : [total] "=r" (total), [count] "=r" (count), [lowcount] "=r" (lowcount)   // This part can be changed if you want.
        : [arr] "r" (power_log), [len] "r" (len)
        : "r4", "r5", "r6", "r7", "r8", "r9", "r10", "r11"  // Registers used. Can be changed as well.
    );
    if (count > 0)
        avg = total / count;

    printf("Average of high-power readings = %d mW\n", avg);
    printf("%d low-power readings dumped into RAM at 0x20001000:\n",lowcount);

    return 0;
}
