0x100000C1 # ADR x1, message with 24-bit offset

0xD2800020 # MOV x0, #1 ; 1 = stdout
0xD28001C2 # MOV x2, #14 ; length of string 
0xD2800090 # MOV x16, #4 ; set up syscall for 'write'
0xD4001001 # svc #0x80 ; syscall
0xD65F03C0 # return

0x6C6C6548 0x77202C6F 0x646C726F 0x00000A21 # 'Hell' 'o, w' 'orld' '!\n'