#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include "parser.h"

int main() {
    u_int32_t* machine_code = parse("bin/math.s");
    size_t MC_SIZE = sizeof(u_int32_t)*current_size;

    // Allocate memory page
    void *mem = mmap(NULL, MC_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON | MAP_JIT, -1, 0);

    // Copy bytes to the executable memory space
    memcpy(mem, machine_code, MC_SIZE);

    //clear instruction cache
    __builtin___clear_cache(mem, (char *)mem + MC_SIZE);

    //change allocated memory to have Execute permissions
    if (mprotect(mem, MC_SIZE, PROT_READ | PROT_EXEC) != 0) perror("mprotect");

    // Cast memory address to a function pointer and execute it
    int (*func)(void) = mem;
    int r = func();
    printf("Return code: %d\n", r);

    free(machine_code);
    return 0;
}