0xD10043FF   # SUB  SP, SP, #16   ; reserve 16 bytes of writable stack space

0xD2800000   # MOV  X0, #0        ; stdin
0x910003E1   # ADD  X1, SP        ; buffer = stack pointer
0xD2800102   # MOV  X2, #8        ; read up to 8 bytes
0xD2800070   # MOV  X16, #3       ; syscall: read
0xD4001001   # SVC  #0x80

0x394003E3   # LDRB W3,[SP]
0x7100AC7F   # CMP W3,#'+'
0x54000060   # B.EQ 3 ; skip RET
0x910043FF   # ADD  SP, SP, #16   ; restore stack before return
0xD65F03C0   # RET
0xD28001C0   # MOV  X0,14
0x910043FF   # ADD  SP, SP, #16   ; restore stack before return
0xD65F03C0   # RET