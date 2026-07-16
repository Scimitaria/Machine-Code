0xd2800020 #     mov     x0, #0x1                ; =1
0x10000e61 #     adr     x1, 0x1d0 <prompt>
0xd2800042 #     mov     x2, #0x2                ; =2
0xd2800090 #     mov     x16, #0x4               ; =4
0xd4001001 #     svc     #0x80

0xd2800000 #     mov     x0, #0x0                ; =0
0x8b3f63e1 #     add     x1, sp, xzr
0xd2800102 #     mov     x2, #0x8                ; =8
0xd2800070 #     mov     x16, #0x3               ; =3
0xd4001001 #     svc     #0x80
0xaa0003f3 #     mov     x19, x0

0x8b3f63e1 #     add     x1, sp, xzr
0xd2800002 #     mov     x2, #0x0                ; =0
0xd2800003 #     mov     x3, #0x0                ; =0

0xeb13007f #     cmp     x3, x19
0x5400018a #     b.ge    0x6c <num1_parse_done>
0x38636824 #     ldrb    w4, [x1, x3]
0x7100c09f #     cmp     w4, #0x30
0x5400012b #     b.lt    0x6c <num1_parse_done>
0x7100e49f #     cmp     w4, #0x39
0x540000ec #     b.gt    0x6c <num1_parse_done>
0x5100c084 #     sub     w4, w4, #0x30
0xd2800145 #     mov     x5, #0xa                ; =10
0x9b057c42 #     mul     x2, x2, x5
0x8b040042 #     add     x2, x2, x4
0x91000463 #     add     x3, x3, #0x1
0x17fffff4 #     b       0x38 <num1_atoi_loop>

0xaa0203f4 #     mov     x20, x2

0xd2800020 #     mov     x0, #0x1                ; =1
0x10000ae1 #     adr     x1, 0x1d0 <prompt>
0xd2800042 #     mov     x2, #0x2                ; =2
0xd2800090 #     mov     x16, #0x4               ; =4
0xd4001001 #     svc     #0x80

0xd2800000 #     mov     x0, #0x0                ; =0
0x8b3f63e1 #     add     x1, sp, xzr
0xd2800102 #     mov     x2, #0x8                ; =8
0xd2800070 #     mov     x16, #0x3               ; =3
0xd4001001 #     svc     #0x80
0xaa0003f3 #     mov     x19, x0

0x8b3f63e1 #     add     x1, sp, xzr
0xd2800002 #     mov     x2, #0x0                ; =0
0xd2800003 #     mov     x3, #0x0                ; =0

0xeb13007f #     cmp     x3, x19
0x5400018a #     b.ge    0xdc <num2_parse_done>
0x38636824 #     ldrb    w4, [x1, x3]
0x7100c09f #     cmp     w4, #0x30
0x5400012b #     b.lt    0xdc <num2_parse_done>
0x7100e49f #     cmp     w4, #0x39
0x540000ec #     b.gt    0xdc <num2_parse_done>
0x5100c084 #     sub     w4, w4, #0x30
0xd2800145 #     mov     x5, #0xa                ; =10
0x9b057c42 #     mul     x2, x2, x5
0x8b040042 #     add     x2, x2, x4
0x91000463 #     add     x3, x3, #0x1
0x17fffff4 #     b       0xa8 <num2_atoi_loop>

0xaa0203f5 #     mov     x21, x2

0xd2800020 #     mov     x0, #0x1                ; =1
0x10000761 #     adr     x1, 0x1d0 <prompt>
0xd2800042 #     mov     x2, #0x2                ; =2
0xd2800090 #     mov     x16, #0x4               ; =4
0xd4001001 #     svc     #0x80

0xd2800000 #     mov     x0, #0x0                ; =0
0x8b3f63e1 #     add     x1, sp, xzr
0xd2800102 #     mov     x2, #0x8                ; =8
0xd2800070 #     mov     x16, #0x3               ; =3
0xd4001001 #     svc     #0x80
0xaa0003f3 #     mov     x19, x0
0x394003e3 #     ldrb    w3, [sp]

0x7100ac7f #     cmp     w3, #0x2b
0x54000061 #     b.ne    0x120 <o_sub>
0x8b150282 #     add     x2, x20, x21
0x1400000d #     b       0x150 <print>

0x7100b47f #     cmp     w3, #0x2d
0x54000061 #     b.ne    0x130 <o_mul>
0xcb150282 #     sub     x2, x20, x21
0x14000009 #     b       0x150 <print>

0x7100a87f #     cmp     w3, #0x2a
0x54000061 #     b.ne    0x140 <o_div>
0x9b157e82 #     mul     x2, x20, x21
0x14000005 #     b       0x150 <print>

0x7100bc7f #     cmp     w3, #0x2f
0x540003e1 #     b.ne    0x1c0 <exit>
0x9ad50a82 #     udiv    x2, x20, x21
0x14000001 #     b       0x150 <print>

0x91007fe6 #     add     x6, sp, #0x1f
0xd2800007 #     mov     x7, #0x0                ; =0
0xd2800148 #     mov     x8, #0xa                ; =10
0xb50000c2 #     cbnz    x2, 0x174 <itoa_loop>
0x52800604 #     mov     w4, #0x30               ; =48
0x390000c4 #     strb    w4, [x6]
0xd10004c6 #     sub     x6, x6, #0x1
0xd2800027 #     mov     x7, #0x1                ; =1
0x1400000a #     b       0x198 <itoa_done>

0xb4000122 #     cbz     x2, 0x198 <itoa_done>
0x9ac80849 #     udiv    x9, x2, x8
0x9b08892a #     msub    x10, x9, x8, x2
0x1100c14a #     add     w10, w10, #0x30
0x390000ca #     strb    w10, [x6]
0xd10004c6 #     sub     x6, x6, #0x1
0x910004e7 #     add     x7, x7, #0x1
0xaa0903e2 #     mov     x2, x9
0x17fffff8 #     b       0x174 <itoa_loop>

0x910004c6 #     add     x6, x6, #0x1
0x52800145 #     mov     w5, #0xa                ; =10
0x382768c5 #     strb    w5, [x6, x7]
0x910004e7 #     add     x7, x7, #0x1

0xaa0603e1 #     mov     x1, x6
0xd2800020 #     mov     x0, #0x1                ; =1
0xaa0703e2 #     mov     x2, x7
0xd2800090 #     mov     x16, #0x4               ; =4
0xd4001001 #     svc     #0x80
0x17ffff91 #     b       0x0 <prompt_num1>

0x910043ff #     add     sp, sp, #0x10
0xd2800000 #     mov     x0, #0x0                ; =0
0xd2800030 #     mov     x16, #0x1               ; =1
0xd4001001 #     svc     #0x80

0x203e # '> '