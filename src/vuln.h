#ifndef VULN_H
#define VULN_H
#include <stddef.h>
#include <stdint.h>

void vulnerable_function(const uint8_t *data, size_t size);

#endif