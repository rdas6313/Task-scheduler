#include<stdio.h>
#include<stdint.h>
#define KB 1024
#define RAM_START 0x20000000
#define RAM_SIZE (4 * KB)
#define RAM_END (RAM_START + RAM_SIZE)
#define MAIN_STACK RAM_END


void Reset_handler(void);
void initialise_monitor_handles();
int main();

void Nmi_handler(void) __attribute__((weak,alias("Default_handler")));
void Hardfault_handler(void);
void Mem_manage_fault_handler(void) __attribute__((weak,alias("Default_handler")));
void Busfault_handler(void) __attribute__((weak,alias("Default_handler")));
void Usagefault_handler(void) __attribute__((weak,alias("Default_handler")));
void Svc_handler(void) __attribute__((weak,alias("Default_handler")));
void Pendsv_handler(void) __attribute__((weak,alias("Default_handler")));
void Systick_handler(void) __attribute__((weak,alias("Default_handler")));


extern uint32_t __data_start__;
extern uint32_t __data_end__;
extern uint32_t __ldata__;

__attribute__((section(".vector_table")))
uintptr_t vector_table[] = {
    MAIN_STACK,
    (uintptr_t)Reset_handler,
    (uintptr_t)Nmi_handler,
    (uintptr_t)Hardfault_handler,
    (uintptr_t)Mem_manage_fault_handler,
    (uintptr_t)Busfault_handler,
    (uintptr_t)Usagefault_handler,
    0,0,0,0,
    (uintptr_t)Svc_handler,
    0,0,
    (uintptr_t)Pendsv_handler,
    (uintptr_t)Systick_handler
};


void Default_handler(void){
    printf("default_handler\n");
}

void Hardfault_handler(void){
    printf("HardFault handler\n");
}


void Reset_handler(void){

    uint8_t* mem_data = (uint8_t*)&__data_start__;
    uint8_t* mem_data_end = (uint8_t*)&__data_end__;
    uint8_t* flash_data = (uint8_t*)&__ldata__;

    while(mem_data < mem_data_end){
        *mem_data = *flash_data;
        mem_data++;
        flash_data++;
    }



    initialise_monitor_handles();
    //int x = 10;
    asm volatile("mov r0,#05");
    main();
    while(1);
}


