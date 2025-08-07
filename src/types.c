#include "types.h"

const BOOL starts_with(const char *prefix, const char *str)
{
    return strncmp(prefix, str, strlen(prefix)) == 0;
}