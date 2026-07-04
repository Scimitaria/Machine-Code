0xD2800540 # MOV x0,#42
0xD28008A1 # MOV x1,#69

0xEB01001F # CMP x0,x1
0x54000041 # B.NE 2 ; jump if x0 and x1 are not equal

0xD65F03C0 # RET

# B.NE 2 lands here
0xD28008A0 # MOV x0,#69
0xD65F03C0 # RET