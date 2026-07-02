0xD2800000 #MOV x0, #0 ; exit code 0
0xD2800030 # MOV x16, #1 ; set up syscall for 'exit'
0xD4001001 # svc #0x80 ; syscall