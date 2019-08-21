

.macro ISR_ERROR_CODE handler, vector
.global i_vector_\vector
i_vector_\vector:
        pushal
        mov $(\vector), %eax
        pushl, %eax
        call \handler
        addl $4, %esp
        popal
        addl $4, %esp
        iretl


.macro ISR handler, vector
.global i_vector_\vector
i_vector_\vector:
        pushal
        mov $(\vector), %eax
        pushl, %eax
        call \handler
        addl $4, %esp
        popal
        iretl
        nop           //Just two keep the two routines aligned to the same size. It makes arithmetic easier ;)
        nop
        nop



.global interrupt_vectors
interrupt_vectors:
ISR                 fault_handler, 0
ISR                 fault_handler, 1 
ISR                 fault_handler, 2
ISR                 fault_handler, 3
ISR                 fault_handler, 4
ISR                 fault_handler, 5
ISR                 fault_handler, 6
ISR                 fault_handler, 7
ISR_ERROR_CODE      fault_handler, 8
ISR                 fault_handler, 9
ISR_ERROR_CODE      fault_handler, 10
ISR_ERROR_CODE      fault_handler, 11
ISR_ERROR_CODE      fault_handler, 12
ISR_ERROR_CODE      fault_handler, 13
ISR_ERROR_CODE      fault_handler, 14
ISR                 fault_handler, 15
ISR                 fault_handler, 16
ISR_ERROR_CODE      fault_handler, 17
ISR                 fault_handler, 18
ISR                 fault_handler, 19
ISR                 fault_handler, 20
ISR                 fault_handler, 21
ISR                 fault_handler, 22
ISR                 fault_handler, 23
ISR                 fault_handler, 24
ISR                 fault_handler, 25
ISR                 fault_handler, 26
ISR                 fault_handler, 27
ISR                 fault_handler, 28
ISR                 fault_handler, 29
ISR                 fault_handler, 30
ISR                 fault_handler, 31 

.global idt
idt:
.space 256*8, 0x0



.macro FILL_IDT_ENTRY 

.global setup_idt
setup_idt:
     mov $i_vector_0, %eax
     mov $i_vector_1, %ebx
     subl %eax, %ebx
     mov $idt, %ecx
     movw %ax, (%ecx)
     movw $SEGMENT_SELECTOR ,[%ecx+2]
     movw $MASK, [%ecx+4]
     shrl $16, %eax
     movw %ax,[%ecx+6]

     shr $16,%eax




     addl %ebx,%ecx



