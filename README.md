# Machine-Code
Experimenting with parsing and executing raw machine code on macOS ARM64

---

## Generation

`generator/generator.c` contains a number of functions which can be used to generate machine code instructions. The operations currently supported are:
- `NOP`
- `RET`
- `SVC 0x80`
- `MOV`
- `ADR`
- `ADD`
- `SUB`
- `MUL`
- `DIV`
- `MSUB`
- `CMP`
- `B`
- `B.COND`
- `CBZ`
- `STRB`
- `LDRB`

The functions can be called in `main` and printed with `print_binary` and `print_hex`. The generator can then be run with `gen`.

---

## Execution

Execution has two phases; `parser.c`, which assembles a file into a `u_int32_t` array, and `runner.c`, which executes the program on JIT-allocated memory. This process can be shortcut with `run`, which takes a path from `/bin/` to a file.

Binary files are stored in `bin`, with the following subfolders:
- `/cmd/`: basic command examples
- `/flow/`: control flow examples
  - `/cond/`: conditional jumps
- `/io/`: I/O examples
  - `/conv/`: type conversions for numeric printing
- `/math/`: mathematical operations
  - `/calc/`: CLI calculator prototypes
