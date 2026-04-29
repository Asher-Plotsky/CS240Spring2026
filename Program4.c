#include <stdio.h>
//This code works in SEGGER which the project is intended for but not in CLion
int main(void)
{
    //region First Section
    int arr[] = {1, 2, 3, 4, 5};
    int newValue = 6;

    int size = sizeof(arr)/sizeof(arr[0]);
    int reverseArray[size];
    int reverseSize = size - 1;
    int newArray[size + 1];
    int newSize = sizeof(newArray)/sizeof(newArray[0]);
    for (int i = 0; i < size; i++){
        printf("%d", arr[i]);
        if (i+1 != size){
            printf(", ");
        }
    }

    asm volatile (
        "mov r4, %[arr]\n\t"
        "mov r5, %[newArray]\n\t"
        "mov r6, %[newValue]\n\t"
        "mov r7, %[size]\n\t"
        "mov r10, %[reverseArray]\n\t"
        "mov r11, %[reverseSize]\n\t"
        "mov r9, #4\n\t"

        "mul r11, r11, r9\n\t"
        "add r10, r10, r11\n\t"
        "Copy: \n\t"
        "ldr r8, [r4]\n\t"
        "str r8, [r5]\n\t"
        "str r8, [r10]\n\t"
        "add r4, r4, r9\n\t"
        "add r5, r5, r9\n\t"
        "sub r10, r10, r9\n\t"
        "sub r7, r7, #1\n\t"
        "cmp r7, #0\n\t"
        "bne Copy \n\t"

        "str r6, [r5]\n\t"

        :
        :[arr] "r" (arr), [newArray] "r" (newArray), [newValue] "r" (newValue), [size] "r" (size), [reverseArray] "r" (reverseArray), [reverseSize] "r" (reverseSize)
        : "r4", "r5", "r6", "r7", "r8", "r9", "r10", "r11", "memory"
    );
    printf("\nExtended Array: \n");
    for (int i = 0; i < newSize; i++){
        printf("%d", newArray[i]);
        if (i+1 != newSize){
            printf(", ");
        }
    }
    printf("\nReverse Array: \n");
    for (int i = 0; i < size; i++){
        printf("%d", reverseArray[i]);
        if (i+1 != size){
            printf(", ");
        }
    }
    printf("\n");
    //endregion
    //region Second Section

    asm volatile (
        ""

        :
        :
        :
    );

    //endregion
    return 0;
}
