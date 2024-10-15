#ifndef __STUMPLESS_COMMON_H
#define __STUMPLESS_COMMON_H

#include "error.h"


// Common function declaration for error handling
void raise_error(enum stumpless_error_id id, const char *message, int code, const char *code_type) {

    // Check for null message or code_type and handle it gracefully
    if (!message) {
        message = "Unknown error occurred.";
    }
    if (!code_type) {
        code_type = "Unknown code type.";
    }

    // Log the error details
    fprintf(stderr, "Error ID: %d\n", id);
    fprintf(stderr, "Message: %s\n", message);
    fprintf(stderr, "Code: %d\n", code);
    fprintf(stderr, "Code Type: %s\n", code_type);
}

#endif /* __STUMPLESS_COMMON_H */
