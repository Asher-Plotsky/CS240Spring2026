#include <stdio.h>
//This code works in SEGGER which the project is intended for but not in CLion
int main(void)
{
    int arr[] = {1, 2, 3, 4, 5};
    int rotate = 3;
    int newValue = 8;
    int byte = 4;
    int newArray[sizeof(arr)/sizeof(arr[0]) + 1];
    int size = sizeof(arr)/sizeof(arr[0]);
    int newSize = sizeof(arr)/sizeof(arr[0]) + 1;
    asm volatile (
        "mov r4, %[arr]\n\t"
        "mov r5, %[newArray]\n\t"
        "mov r6, %[rotate]\n\t"
        "mov r7, %[newValue]\n\t"
        "mov r8, %[byte]\n\t"
        "mov r9, %[newSize]\n\t"
        "mov r11, %[size]\n\t"
        "ldr r10, =0x20001000\n\t"
        "sub r9, r9, #1\n\t"

        "Rotate: \n\t"
        "cmp r6, #0\n\t"
        "beq Add\n\t"
        "sub r6, r6, #1\n\t"
        "add r12, r4, #0\n\t"
        "add r4, r4, r8\n\t"
        ""

        "b Rotate"

        "Add: \n\t"
        "mul r9, r9, r8\n\t"
        "add r9, r5, r9\n\t"
        "str r7, [r9]\n\t"

        "End: \n\t"
        "mov %[newArray], r5\n\t"

        : [arr] "=r" (arr), [newArray] "=r" (newArray), [newValue] "=r" (newValue)
        : [newSize] "r" (newSize), [byte] "r" (byte), [rotate] "r" (rotate), [size] "r" (size)
        : "r4", "r5", "r6", "r7", "r8", "r9", "r10", "r11", "r12"
    );
    for (int i = 0; i < newSize; i++){
        printf("%d", newArray[i]);
        if (i+1 != newSize){
            printf(", ");
        }
    }
    printf("\n");
    asm volatile (
        ""
    );

    return 0;
}
