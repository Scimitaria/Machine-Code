0xD10083FF # SUB SP,SP,#32 ; 16 bytes i/o

## PRINT PROMPT ##
0x100003E1  # ADR prompt ; 124-bit offset
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
0xAA1F03E1   # MOV x1,SP  ; pointer to input buffer
0xD2800002   # MOV x2,#0  ; x2 = accumulator
0xD2800003   # MOV x3,#0  ; x3 = index

## ATOI PARSE LOOP ##
0xEB13007F   # CMP x3,x19
0x5400018A   # B.GE 12 ; parse done
0x38636824   # LDRB W4, [x1,x3]
0x7100C09F   # CMP W4,#'0'
0x5400012B   # B.LT 9  ; parse done
0x7100E49F   # CMP  W4, #'9'
0x540000EC   # B.GT 7  ; parse done
0x5100C084   # SUB w4,w4,#'0'
0xD2800145   # MOV x5,#10
0xDB0200A2   # MUL x2,x2,x5
0x8B040042   # ADD x2,x2,x4
0x91000463   # ADD x3,x3,#1
0x17FFFFF4   # B -12 ; start of parse loop

## ADD 1 AND RETURN ##
0x91000442 # ADD x2,x2,#1
0xAA0203E0 # MOV x0,x2

0x8B2003FF # ADD SP,SP,#32
0xD65F03C0 # RET

0x0000203E  # prompt: '> '