#include "vuln.h"
#include <string.h>
#include <stdio.h>
#include <stdint.h>

// 1. A Global Volatile "Sink"
// The compiler cannot optimize writes to this variable because
// it assumes 'SINK' might be read by the outside world (OS, threads).
volatile int SINK;

void vulnerable_function(const uint8_t *data, size_t size) {
    char buffer[12]; 

    if (size > 0 && data[0] == 'B') {
        
        // 2. The Vulnerability
        // Logic error: We accept sizes up to 20, but buffer is only 12.
        if (size > 20) return;

        // CRASH HAPPENS HERE
        // When size is 13-20, this overwrites the stack return address/canary.
        memcpy(buffer, data, size);

        // 3. The Anchor (The Fix)
        // We force the compiler to believe 'buffer' is useful by 
        // reading from it and writing to the Global Sink.
        // To execute this line, the compiler MUST execute the memcpy above.
        SINK = buffer[size - 1]; 
    }
}