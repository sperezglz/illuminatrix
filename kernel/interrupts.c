#include <stdint.h>
#include "interrupts.h"

#define VECTORS 255

struct idt_desc idt[VECTORS];
struct idt_register idtr;

void load_idt(void)
{
    extern void isr_0(void);
    extern void isr_1(void);
    extern void isr_10(void);
    extern void isr_11(void);

    uint32_t base = (uint32_t)isr_0;
    uint32_t size_no_error = ((uint32_t)isr_1) - ((uint32_t)isr_0);
    uint32_t size_w_error = ((uint32_t)isr_11) - ((uint32_t)isr_10);
    uint32_t offset = base;
    int i;

    for(i = 0; i <= 32 ; i++) {
        if (i != 8 && i < 10 && i > 14 &&  i != 17) {
            offset += size_no_error;
            idt[i].type = 0xE; //32 bit interrupt gate
            idt[i].p = 1;
            idt[i].s = 0;
            idt[i].seg_sel = 0x8; //Segment selector
            idt[i].offset15_0 = (uint16_t)(offset);
            idt[i].offset31_16 = (uint16_t)(offset >> 16);
        } else {
            offset += size_w_error;
            idt[i].type = 0xE; //32 bit interrupt gate
            idt[i].p = 1;
            idt[i].s = 0;
            idt[i].seg_sel = 0x8; //Segment selector
            idt[i].offset15_0 = (uint16_t)(offset);
            idt[i].offset31_16 = (uint16_t)(offset >> 16);
        }
    }


    // prepare idtr
    idtr.limit = (VECTORS * sizeof(struct idt_desc)) - 1;
    idtr.base = (uint32_t)idt;

    // load idt
    __asm__ volatile(
                     "lidtl %0 \n\t"
                     :: "m" (idtr)
                     );
}

void common_handler_error_code(uint32_t vector, uint32_t edi, uint32_t esi, uint32_t ebp,
    uint32_t esp, uint32_t ebx, uint32_t edx, uint32_t ecx, uint32_t eax, uint32_t error,
    uint32_t eip, uint32_t cs, uint32_t eflags)
{

halt: goto halt;

}

void common_handler(uint32_t vector, uint32_t edi, uint32_t esi, uint32_t ebp,
    uint32_t esp, uint32_t ebx, uint32_t edx, uint32_t ecx, uint32_t eax,
    uint32_t eip, uint32_t cs, uint32_t eflags)
{

halt: goto halt;

}
