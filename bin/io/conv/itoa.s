0xD2800505 # MOV x5,#40
0x910008A6 # ADD x6,x5,#2  ; adding confirms numeric ; print this

0xD10083FF # SUB SP,SP,#32 ; reserve stack space

0x910053E9 # ADD x9,SP,#20 ; x9 = pointer ; high end of buffer down
0x52800148 # MOV W8,#10
0x39000128 # STRB W8,[x9]  ; buffer[20] = '\n'
0xD1000529 # SUB x9,x9,#1
0xD2800143 # MOV x3,#10    ; divisor

# Conversion loop #
0x9AC308C7 # UDIV x7,x6,x3    ; x7 = x6/10
0x9B0398E8 # MSUB x8,x7,x3,x6 ; x8 = x6 - (x7*10) -> remainder
0x1100C108 # ADD w8,w8,#'0'   ; convert char to ASCII
0x39000128 # STRB w8,[x9]
0xD1000529 # SUB x9,x9,#1
0xAA0703E6 # MOV x6,x7
0xB5FFFF46 # CBNZ x6,#-6 ; jump to start of loop

0x91000529 # ADD x9,x9,#1   ; x9 points to first digit
0x910057EA # ADD x10,SP,#21 ; one past newline
0xCB090142 # SUB x2,x10,x9  ; x2 = length of digits + newline

0xAA0903E1 # MOV x1,x9  ; pointer to strind
0xD2800020 # MOV x0,#1  ; stdout
0xD2800090 # MOV x16,#4 ; write
0xD4001001 # SVC #0x80

0x910083FF # ADD SP,SP,#32 ; restore stack
0xD65F03C0 # RET
