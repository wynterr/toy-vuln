#include "vuln.h"
#include <string.h>
#include <stdio.h>

void vulnerable_function(const uint8_t *data, size_t size) {
    volatile char buffer[12]; 

    if (size > 0 && data[0] == 'B') {
        if (size > 20) {
             return; 
        }
        
        // Because 'buffer' is volatile, the compiler is forced 
        // to perform this write, which will trigger the crash.
        // Cast to (void*) to silence "discard qualifiers" warning if needed
        memcpy((void*)buffer, data, size);
    }
}