#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include "parser.h"

// Example raw machine bytes for an ARM64 function that simply returns
//u_int32_t machine_code[] = { 0xD65F03C0 };

int main() {
    u_int32_t* machine_code = parse("bin/ret.s");

    // Allocate memory page
    void *mem = mmap(NULL, sizeof(*machine_code), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON | MAP_JIT, -1, 0);

    // Copy bytes to the executable memory space
    memcpy(mem, machine_code, sizeof(*machine_code));
    //clear instruction cache
    __builtin___clear_cache(mem, (char *)mem + sizeof(*machine_code));

    //change allocated memory to have Execute permissions
    if (mprotect(mem, sizeof(machine_code), PROT_READ | PROT_EXEC) != 0) perror("mprotect");

    // Cast memory address to a function pointer and execute it
    void (*func)(void) = mem;
    func();

    printf("Machine code executed successfully!\n");
    free(machine_code);
    return 0;
}