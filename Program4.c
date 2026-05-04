#include <stdio.h>
//This code works in SEGGER which the project is intended for but not in CLion
int extendReverse(void)
{
    int arr[] = {1, 2, 3, 4, 5};
    int newValue = 6;

    int size = sizeof(arr) / sizeof(arr[0]);
    int reverseArray[size];
    int reverseSize = size - 1;
    int newArray[size + 1];
    int newSize = sizeof(newArray) / sizeof(newArray[0]);
    for (int i = 0; i < size; i++)
    {
        printf("%d", arr[i]);
        if (i + 1 != size)
        {
            printf(", ");
        }
    }

    asm volatile (
        "add r4, %[arr], #0\n\t"
        "add r5, %[newArray], #0\n\t"
        "add r3, %[newValue], #0\n\t"
        "sub r2, %[size], #0\n\t"
        "sub r10, %[reverseArray], #0\n\t"
        "mov r11, %[reverseSize]\n\t"

        "lsl r11, r11, #2\n\t"
        "add r10, r10, r11\n\t"
        "Copy: \n\t"
        "ldr r8, [r4]\n\t"
        "str r8, [r5]\n\t"
        "str r8, [r10]\n\t"
        "adds r4, r4, #4\n\t"
        "adds r5, r5, #4\n\t"
        "sub r10, r10, #4\n\t"
        "sub r2, r2, #1\n\t"
        "cmp r2, #0\n\t"
        "bne Copy \n\t"

        "str r3, [r5]\n\t"

        :
        :[arr] "r" (arr), [newArray] "r" (newArray), [newValue] "r" (newValue), [size] "r" (size), [reverseArray] "r" (
            reverseArray), [reverseSize] "r" (reverseSize)
        : "r4", "r5", "r3", "r2", "r8", "r10", "r11", "memory"
    );
    printf("\nExtended Array: \n");
    for (int i = 0; i < newSize; i++)
    {
        printf("%d", newArray[i]);
        if (i + 1 != newSize)
        {
            printf(", ");
        }
    }
    printf("\nReverse Array: \n");
    for (int i = 0; i < size; i++)
    {
        printf("%d", reverseArray[i]);
        if (i + 1 != size)
        {
            printf(", ");
        }
    }
    printf("\n");
    return 0;
}
int multiply(void)
{
    printf("Part 2: \n");
    int arr[] = {1, 2, 3, 4, 5};
    int size = sizeof(arr)/sizeof(arr[0]);
    for (int i = 0; i < size - 1; i++){
        printf("%d, ", arr[i]);
    }
    printf("%d\n", arr[size - 1]);
    int sum = 0;
    int bitCheck = 0;

    asm volatile (
        "mov r4, %[arr]\n\t"
        "mov r5, #1\n\t"
        "mov r2, %[size]\n\t"
        "add r8, r5, #3\n\t"
        "eor r9, r9, r9\n\t"

        "nop\n\t"
        "Loop: \n\t"
        "cmp r2, #0\n\t"
        "beq End\n\t"
        "mul r5, r5, r8\n\t"
        "ldr r6, [r4]\n\t"
        "adds r9, r9, r6\n\t"
        "adds r6, r6, r5\n\t"
        "str r6, [r4]\n\t"
        "adds r4, r4, r8\n\t"
        "udiv r5, r5, r8\n\t"
        "adds r5, r5, #1\n\t"
        "subs r2, #1\n\t"
        "b Loop\n\t"

        "End: \n\t"
        "mov r4, %[arr]\n\t"
        "ldr r6, [r4]\n\t"
        "and r0, r6, #1\n\t"
        "orr r0, r0, r5\n\t"
        "eor r0, r0, r8\n\t"
        "lsl r0, r0, #1\n\t"
        "lsr r0, r0, #1\n\t"
        "asr r0, r0, #1\n\t"
        "tst r0, #1\n\t"
        "mvn r1, r0\n\t"
        "mov %[sum], r9\n\t"
        "orr %[bitCheck], r0, r0\n\t"

        : [sum] "=r" (sum), [bitCheck] "=r" (bitCheck)
        : [arr] "r" (arr), [size] "r" (size)
        : "r0", "r1", "r4", "r5", "r6", "r2", "r8", "r9", "memory"
    );
    printf("Multiply By 5:\n");
    for (int i = 0; i < size - 1; i++){
        printf("%d, ", arr[i]);
    }
    printf("%d\n", arr[size - 1]);
    printf("Sum of original array: %d\n", sum);
    printf("Bit check value: %d\n", bitCheck);
    return 0;
}
int main(void)
{
    extendReverse();
    multiply();
    return 0;
}