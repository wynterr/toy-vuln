#include "vuln.h"
#include <string.h>
#include <stdio.h>

void vulnerable_function(const uint8_t *data, size_t size) {
    char buffer[12]; // Small buffer

    // BUG: logic error. We check for size > 20, but we memcpy 'size' bytes.
    // If input is 15 bytes, it passes the check but overflows the 12-byte buffer.
    if (size > 0 && data[0] == 'B') {
        if (size > 20) {
             return; // "Safety" check
        }
        // VULNERABILITY: Stack Buffer Overflow (13-20 bytes will crash)
        memcpy(buffer, data, size);
    }
}