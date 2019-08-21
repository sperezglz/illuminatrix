#ifndef INTERRUPTS_H
#define INTERRUPTS_H

struct idt_register {
    uint16_t limit:16;
    uint32_t base:32;
};

struct idt_desc {
    uint32_t offset15_0:16;
    uint32_t seg_sel:16;
    uint32_t rsvd:8;
    uint32_t type:4;
    uint32_t s:1;
    uint32_t dpl:2;
    uint32_t p:1;
    uint32_t offset31_16:16;
};

void load_idt(void);

#endif
