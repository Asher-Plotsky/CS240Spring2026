#include <stdio.h>
//This code works in SEGGER which the project is intended for but not in CLion
int main(void)
{
    int arr[] = {1, 2, 3, 4, 5};
    int rotate = 3;
    int newValue = 8;
    int counter = 0;
    int newArray[sizeof(arr)/sizeof(arr[0]) + 1];
    int newSize = sizeof(arr)/sizeof(arr[0]) + 1;
    asm volatile (
        "mov r4, %[arr]\n\t"
        "mov r5, %[newArray]\n\t"
        "mov r6, %[rotate]\n\t"
        "mov r7, %[newValue]\n\t"
        "mov r8, %[counter]\n\t"
        "mov r9, %[newSize]\n\t"
        "ldr r10, =0x20001000\n\t"

        "Rotate: \n\t"
        "cmp r6, #0\n\t"
        "beq Add\n\t"

        "Add: \n\t"
        "cmp r9, #0\n\t"
        "beq End\n\t"
        ""

        "End: \n\t"
        "mov %[newArray], r5\n\t"

        : [arr] "=r" (arr), [newArray] "=r" (newArray), [newValue] "=r" (newValue)
        : [newSize] "r" (newSize), [counter] "r" (counter), [rotate] "r" (rotate)
        : "r4", "r5", "r6", "r7", "r8", "r9", "r10"
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
