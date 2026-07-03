0xD2800540 # MOV x0,#42
0x14000002 # B 2

# B -2 lands here
0xD65F03C0 # RET

# B 2 lands here
0xD28008A0 # MOV x0,#69
0x17FFFFFE # B -2 ; jump 0x8 bytes back
0xD65F03C0 # RET