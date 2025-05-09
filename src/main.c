#include<stdio.h>
#include<stdint.h>

int main(){
    asm volatile("mov r1,#3");
    printf("Hello There\n");
    printf("Bye!\n");
}