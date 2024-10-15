#ifndef __STUMPLESS_COMMON_H
#define __STUMPLESS_COMMON_H

// Common function declaration for error handling
void raise_error(enum stumpless_error_id id, const char *message, int code, const char *code_type);

#endif /* __STUMPLESS_COMMON_H */
