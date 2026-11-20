//# # # # # # # # # # # # #
//# Important registers:  #
//# X20 - first number    #
//# X21 - second number   #
//# W3  - operation       #
//# X2  - result          #
//# # # # # # # # # # # # #

.global _main
.align 4

_main:
    load_nums:  
        BL load_num
        MOV X20,X2
        BL load_num
        MOV X21,X2

    load_op:
        prompt_op:
            MOV X0,1
            ADR X1,prompt
            MOV X2,2
            MOV X16,4
            SVC 0X80

        read_op:
            SUB SP,SP,16
            MOV X0,0
            MOV X1,SP
            MOV X2,8
            MOV X16,3
            SVC 0X80
            MOV X19,X0
            LDRB W3,[SP]
        
    math:
        o_add:
            CMP W3,'+'
            B.NE o_sub
            ADD X2,X20,X21
            B print
        o_sub:
            CMP W3,'-'
            B.NE o_mul
            SUB X2,X20,X21
            B print
        o_mul:
            CMP W3,'*'
            B.NE o_div
            MUL X2,X20,X21
            B print
        o_div:
            CMP W3,'/'
            B.NE eXit
            UDIV X2,X20,X21
            B print

    print:
        itoa_setup:
            ADD X6,SP,31
            MOV X7,0
            MOV X8,10
            CBNZ X2,itoa_loop
            MOV W4,'0'
            STRB W4,[X6]
            SUB X6,X6,1
            MOV X7,1
            B itoa_done
        
        itoa_loop:
            CBZ X2,itoa_done
            UDIV X9,X2,X8
            MSUB X10,X9,X8,X2
            ADD W10,W10,'0'
            STRB W10,[X6]
            SUB X6,X6,1
            ADD X7,X7,1
            MOV X2,X9
            B itoa_loop

        itoa_done:
            ADD X6,X6,1
            MOV W5,10
            STRB W5,[X6,X7]
            ADD X7,X7,1
        
        print_res:
            MOV X1,X6
            MOV X0,1
            MOV X2,X7
            MOV X16,4
            SVC 0X80

        B load_nums

    eXit:
        ADD SP,SP,16
        MOV X0,0
        MOV X16,1
        SVC 0X80

    load_num:
        prompt_num:
            MOV X0,1
            ADR X1,prompt
            MOV X2,2
            MOV X16,4
            SVC 0X80

        read_num:
            SUB SP,SP,32
            MOV X0,0
            MOV X1,SP
            MOV X2,31
            MOV X16,3
            SVC 0X80
            MOV X19,X0

        atoi_setup:
            MOV X1,SP
            MOV X2,0
            MOV X3,0
        
        atoi_loop:
            CMP X3,X19
            B.GE parse_done
            LDRB W4,[X1,X3]
            CMP W4,'0'
            B.LT parse_done
            CMP W4,'9'
            B.GT parse_done
            SUB W4,W4,'0'
            MOV X5,10
            MUL X2,X2,X5
            ADD X2,X2,X4
            ADD X3,X3,1
            B atoi_loop

        parse_done:
            ADD SP,SP,32
            RET

prompt:
    .asciz "> "
