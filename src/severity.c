// SPDX-License-Identifier: Apache-2.0
/*
 * Copyright 2018-2022 Joel E. Anderson
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stddef.h>
#include <string.h>
#include "stumpless/severity.h"
#include "private/severity.h"
#include "private/strhelper.h"
#include "../../src/error.c"

static char *severity_enum_to_string[] = {
  STUMPLESS_FOREACH_SEVERITY( GENERATE_STRING )
};

const char *
stumpless_get_severity_string( enum stumpless_severity severity ) {
  // Clear any existing errors
  stumpless_clear_error();

  if ( !severity_is_invalid( severity ) ) {
    return severity_enum_to_string[severity];
  }

  // Set an error for invalid severity
  stumpless_set_error( STUMPLESS_INVALID_SEVERITY,
                       "Invalid severity value: %d", severity );
  return "NO_SUCH_SEVERITY";
}

enum stumpless_severity
stumpless_get_severity_enum( const char *severity_string ) {
  // Clear any existing errors
  stumpless_clear_error();

  enum stumpless_severity severity = stumpless_get_severity_enum_from_buffer(
                                        severity_string, strlen(severity_string));

  if ( severity == -1 ) {
    // Set an error if the severity is invalid
    stumpless_set_error( STUMPLESS_INVALID_SEVERITY,
                         "Invalid severity string: %s", severity_string );
  }

  return severity;
}

enum stumpless_severity
stumpless_get_severity_enum_from_buffer( const char *severity_buffer, size_t severity_buffer_length ) {
  // Clear any existing errors
  stumpless_clear_error();

  size_t severity_bound;
  size_t i;
  const int str_offset = 19; // to omit "STUMPLESS_SEVERITY_"

  severity_bound = sizeof( severity_enum_to_string ) /
                   sizeof( severity_enum_to_string[0] );

  for( i = 0; i < severity_bound; i++ ) {
    if( strncasecmp_custom( severity_buffer, severity_enum_to_string[i] + str_offset, severity_buffer_length ) == 0 ) {
      return i;
    }
  }

  if( strncasecmp_custom( severity_buffer, "PANIC", severity_buffer_length ) == 0 ) {
    return STUMPLESS_SEVERITY_EMERG_VALUE;
  }

  if( strncasecmp_custom( severity_buffer, "ERROR", severity_buffer_length ) == 0 ) {
    return STUMPLESS_SEVERITY_ERR_VALUE;
  }

  if( strncasecmp_custom( severity_buffer, "WARN", severity_buffer_length ) == 0 ) {
    return STUMPLESS_SEVERITY_WARNING_VALUE;
  }

  // If no valid severity is found, set an error and return -1
  stumpless_set_error( STUMPLESS_INVALID_SEVERITY,
                       "Invalid severity buffer: %.*s",
                       (int) severity_buffer_length, severity_buffer );
  return -1;
}

/* private functions */

int
get_severity( int prival ) {
  return prival & 0x7;
}

int
severity_is_invalid( int severity ) {
  return severity < 0 || severity > 7;
}
