0xD10043FF   # SUB  SP, SP, #16   ; reserve 16 bytes of writable stack space

0xD2800000   # MOV  X0, #0        ; stdin
0x910003E1   # ADD  X1, SP        ; buffer = stack pointer
0xD2800102   # MOV  X2, #8        ; read up to 8 bytes
0xD2800070   # MOV  X16, #3       ; syscall: read
0xD4001001   # SVC  #0x80

0xD2800020   # MOV  X0, #1        ; stdout
0x910003E1   # ADD  X1, SP        ; buffer = stack pointer
0xD2800102   # MOV  X2, #8        ; write up to 8 bytes
0xD2800090   # MOV  X16, #4       ; syscall: write
0xD4001001   # SVC  #0x80

0x910043FF   # ADD  SP, SP, #16   ; restore stack before return
0xD65F03C0   # RET