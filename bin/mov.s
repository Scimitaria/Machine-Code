0xD2800020 #MOVZ x0, #1
# 1101 0010 1000 0000 0000 0000 0010 0000
# 1      - 64-bit
# 10     - MOVZ opcode
# 100101 - move wide - immediately load value and zero out other bits
# 00     - left shift 0 bits
# 0000000000000001 - value to load
# 00000  - destination register

0xD65F03C0 #return