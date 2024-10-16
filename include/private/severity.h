/* SPDX-License-Identifier: Apache-2.0 */

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

#ifndef __STUMPLESS_PRIVATE_SEVERITY_H
#  define __STUMPLESS_PRIVATE_SEVERITY_H

// In include/private/private_header.h
#include "../../src/error.c" // Adjust the path based on the directory structure

/**
 * Gets the value of the severity from the given prival. This will be equivalent
 * to the STUMPLESS_SEVERITY_*_VALUE constant for the severity.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe.
 *
 * **Async Signal Safety: AS-Safe**
 * This function is safe to call from signal handlers.
 *
 * **Async Cancel Safety: AC-Safe**
 * This function is safe to call from threads that may be asynchronously
 * cancelled.
 *
 * @param prival The prival to extract the severity from.
 *
 * @return the severity of the prival, as an integer.
 */
int
get_severity( int prival );

/**
 * Checks if the given severity is invalid. If it is invalid, it raises an error.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe.
 *
 * **Async Signal Safety: AS-Safe**
 * This function is safe to call from signal handlers.
 *
 * **Async Cancel Safety: AC-Safe**
 * This function is safe to call from threads that may be asynchronously
 * cancelled.
 *
 * @param severity The severity value to check.
 *
 * @return 1 if the severity is invalid, 0 if it is valid.
 */
int
severity_is_invalid( int severity ) {
  if( severity < 0 || severity > 7 ) {
    raise_error( STUMPLESS_INVALID_SEVERITY );  // Raise an error if invalid
    return 1;
  }

  return 0;
}

#endif /* __STUMPLESS_PRIVATE_SEVERITY_H */
