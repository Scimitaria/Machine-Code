/*
# # # # # # # # # # # # #
# Important registers:  #
# X17 - first number    #
# X18 - second number   #
# W3  - operation       #
# X2  - result          #
# # # # # # # # # # # # #
*/

.global _main
.align 4

_main:
    load_num1:
        prompt_num1:
            MOV X0,1
            ADR X1,prompt
            MOV X2,2
            MOV X16,4
            SVC 0X80

        read_num1:
            MOV X0,0
            ADD X1,SP,XZR
            MOV X2,8
            MOV X16,3
            SVC 0X80
            MOV X19,X0

        num1_atoi_setup:
            ADD X1,SP,XZR
            MOV X2,0
            MOV X3,0
        
        num1_atoi_loop:
            CMP X3,X19
            B.GE num1_parse_done
            LDRB W4,[X1,X3]
            CMP W4,'0'
            B.LT num1_parse_done
            CMP W4,'9'
            B.GT num1_parse_done
            SUB W4,W4,'0'
            MOV X5,10
            MUL X2,X2,X5
            ADD X2,X2,X4
            ADD X3,X3,1
            B num1_atoi_loop

        num1_parse_done:
            MOV X17,X2

    load_num2:
        prompt_num2:
            MOV X0,1
            ADR X1,prompt
            MOV X2,2
            MOV X16,4
            SVC 0X80

        read_num2:
            MOV X0,0
            ADD X1,SP,XZR
            MOV X2,8
            MOV X16,3
            SVC 0X80
            MOV X19,X0

        num2_atoi_setup:
            ADD X1,SP,XZR
            MOV X2,0
            MOV X3,0
        
        num2_atoi_loop:
            CMP X3,X19
            B.GE num2_parse_done
            LDRB W4,[X1,X3]
            CMP W4,'0'
            B.LT num2_parse_done
            CMP W4,'9'
            B.GT num2_parse_done
            SUB W4,W4,'0'
            MOV X5,10
            MUL X2,X2,X5
            ADD X2,X2,X4
            ADD X3,X3,1
            B num2_atoi_loop

        num2_parse_done:
            MOV X18,X2

    load_op:
        prompt_op:
            MOV X0,1
            ADR X1,prompt
            MOV X2,2
            MOV X16,4
            SVC 0X80

        read_op:
            MOV X0,0
            ADD X1,SP,XZR
            MOV X2,8
            MOV X16,3
            SVC 0X80
            MOV X19,X0
            LDRB W3,[SP]
        
    math:
        o_add:
            CMP W3,'+'
            B.NE o_sub
            ADD x2,x17,x18
            B print
        o_sub:
            CMP W3,'-'
            B.NE o_mul
            SUB x2,x17,x18
            B print
        o_mul:
            CMP W3,'*'
            B.NE o_div
            MUL x2,x17,x18
            B print
        o_div:
            CMP W3,'/'
            B.NE exit
            UDIV x2,x17,x18
            B print

    print:
        itoa_setup:
            ADD x6,SP,31
            MOV x7,0
            MOV x8,10
            CBNZ x2,itoa_loop
            MOV W4,'0'
            STRB W4,[x6]
            SUB x6,x6,1
            MOV x7,1
            B itoa_done
        
        itoa_loop:
            CBZ x2,itoa_done
            UDIV x9,x2,x8
            MSUB x10,x9,x8,x2
            ADD W10,W10,'0'
            STRB W10,[x6]
            SUB x6,x6,1
            ADD x7,x7,1
            MOV x2,x9
            B itoa_loop

        itoa_done:
            ADD x6,x6,1
            MOV W5,10
            STRB W5,[X6,X7]
            ADD x7,x7,1
        
        print_res:
            MOV x1,x6
            MOV x0,1
            MOV x2,x7
            MOV x16,4
            SVC 0x80

        B load_num1

    exit:
        ADD SP,SP,16
        MOV x0,0
        MOV x16,1
        SVC 0x80

prompt:
    .asciz "> "
