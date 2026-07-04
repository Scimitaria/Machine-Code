# Until loop

0xD2800780 # MOV x0,#60
0xD28008A1 # MOV x1,#69

# B.LT -2 goes here
0x91000400 # ADD x0,x0,#1
0xEB01001F 0x54FFFFCB # B.LT x0,x1,-2

# B.EQ goes here
0xD65F03C0 # RET