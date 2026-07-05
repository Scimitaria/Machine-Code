0xD10083FF # SUB SP,SP,#32 ; 16 bytes i/o

### READ NUM1 INTO x17 ###
## PRINT PROMPT ##
0x10000AE1  # ADR prompt ; 348-bit offset
0xD2800020  # MOV x0, #1 ; 1 = stdout
0xD2800042  # MOV x2, #2 ; length of string 
0xD2800090  # MOV x16,#4 ; set up syscall for 'write'
0xD4001001  # svc #0x80  ; syscall

## GET INPUT ##
0xD2800000   # MOV  x0, #0        ; stdin
0x910003E1   # ADD  x1, SP        ; buffer = stack pointer
0xD2800102   # MOV  x2, #8        ; read up to 8 bytes
0xD2800070   # MOV  x16,#3        ; syscall: read
0xD4001001   # SVC  #0x80
0xAA0003F3   # MOV  x19,x0        ; x19 = # of bytes read

## ATOI SETUP ##
0x910003E1   # ADD x1,SP    ; buffer = stack pointer
0xD2800002   # MOV x2,#0    ; x2 = accumulator ; val goes here
0xD2800003   # MOV x3,#0    ; x3 = index ; counts through bytes

## ATOI PARSE LOOP ##
0xEB13007F   # CMP x3,x19
0x5400018A   # B.GE 12 ; parse done ; exit loop when all bytes read
0x38636824   # LDRB W4, [x1,x3]
0x7100C09F   # CMP W4,#'0'
0x5400012B   # B.LT 9  ; parse done
0x7100E49F   # CMP  W4, #'9'
0x540000EC   # B.GT 7  ; parse done
0x5100C084   # SUB w4,w4,#'0'
0xD2800145   # MOV x5,#10
0x9B057C42   # MUL x2,x2,x5
0x8B040042   # ADD x2,x2,x4
0x91000463   # ADD x3,x3,#1 ; i++
0x17FFFFF4   # B -12 ; start of parse loop

0xAA0203F1 # MOV x17,x2

### READ NUM2 INTO x18 ###
## PRINT PROMPT ##
0x10000761  # ADR prompt ; 236-bit offset
0xD2800020  # MOV x0, #1 ; 1 = stdout
0xD2800042  # MOV x2, #2 ; length of string 
0xD2800090  # MOV x16, #4 ; set up syscall for 'write'
0xD4001001  # svc #0x80 ; syscall

## GET INPUT ##
0xD2800000   # MOV  x0, #0        ; stdin
0x910003E1   # ADD  x1, SP        ; buffer = stack pointer
0xD2800102   # MOV  x2, #8        ; read up to 8 bytes
0xD2800070   # MOV  x16,#3        ; syscall: read
0xD4001001   # SVC  #0x80
0xAA0003F3   # MOV  x19,x0        ; x19 = # of bytes read

## ATOI SETUP ##
0x910003E1   # ADD x1,SP    ; buffer = stack pointer
0xD2800002   # MOV x2,#0    ; x2 = accumulator ; val goes here
0xD2800003   # MOV x3,#0    ; x3 = index ; counts through bytes

## ATOI PARSE LOOP ##
0xEB13007F   # CMP x3,x19
0x5400018A   # B.GE 12 ; parse done ; exit loop when all bytes read
0x38636824   # LDRB W4, [x1,x3]
0x7100C09F   # CMP W4,#'0'
0x5400012B   # B.LT 9  ; parse done
0x7100E49F   # CMP  W4, #'9'
0x540000EC   # B.GT 7  ; parse done
0x5100C084   # SUB w4,w4,#'0'
0xD2800145   # MOV x5,#10
0x9B057C42   # MUL x2,x2,x5
0x8B040042   # ADD x2,x2,x4
0x91000463   # ADD x3,x3,#1 ; i++
0x17FFFFF4   # B -12 ; start of parse loop

0xAA0203F2 # MOV x18,x2

## ADD ##
0x8B120222 # ADD x2,x17,x18

## ITOA SETUP ##
0x91007FE6 # ADD x6,SP,#31 ; x6 = pointer to stack buffer
0xD2800007 # MOV x7,#0 ; x7 = digit count
0xD2800148 # MOV x8,#10 ; divisor
0xB50000C2 # CBNZ X2, 6 ; start of ITOA loop
0x52800604 # MOV w4,#'0' ; result is 0
0x390000C4 # STRB w4,[x6]
0xD10004C6 # SUB x6,x6,#1
0xD2800027 # MOV x7,#1
0x1400000A # B 10 ; post-ITOA

## ITOA LOOP ##
0xB4000122 # CBZ x2,9 ; post-ITOA
0x9AC80849 # DIV x9,x2,x8 ; x9 = x2/10
0x9B08892A # MSUB x10,x9,x8,x2 ; x10 = remainder
0x1100C14A # ADD w10,w10,#'0'
0x390000CA # STRB w10,[x6]
0xD10004C6 # SUB x6,x6,#1
0x910004E7 # ADD x7,x7,#1
0xAA0903E2 # MOV x2,x9
0x17FFFFF8 # B -8 ; start of ITOA loop

## POST-ITOA ##
0x910004C6 # ADD x6,x6,#1 ; x6 = first digit of result
0x52800145 # MOV w5,#10 ; add trailing newline
0x382768C5 # STRB W5, [X6, X7]
0x910004E7 # ADD x7,x7,#1 ; include newline in length

## PRINT ##
0xAA0603E1 # MOV x1,x6
0xD2800020 # MOV x0,#1  ; stdout
0xAA0703E2 # MOV x2,x7
0xD2800090 # MOV x16,#4 ; write
0xD4001001 # SVC #0x80

## EXIT ##
0xD2800000  # MOV x0,#0 
0xD2800030  # MOV x16,#1     ; syscall: exit
0xD4001001  # SVC #0x80      ; syscall

## TEXT ##
0x0000203E  # prompt: '> '