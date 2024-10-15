#ifndef __STUMPLESS_COMMON_H
#define __STUMPLESS_COMMON_H

#include "error.h"


void
raise_error( enum stumpless_error_id id,
             const char *message,
             int code,
             const char *code_type ) {
  last_error.id = id;
  last_error.message = message;
  last_error.code = code;
  last_error.code_type = code_type;
  error_valid = true;
}


#endif /* __STUMPLESS_COMMON_H */
