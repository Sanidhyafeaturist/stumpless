/* SPDX-License-Identifier: Apache-2.0 */

/*
 * Copyright 2018-2024 Joel E. Anderson
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

/** @file
 * Error codes and functions for detecting and assessing them.
 */

#ifndef __STUMPLESS_ERROR_H
#define __STUMPLESS_ERROR_H

#include <stdbool.h>
#include <stdio.h>
#include <stumpless/config.h>
#include <stumpless/generator.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A macro to implement error id enum and error string array.
 */
#define STUMPLESS_FOREACH_ERROR(ERROR) \
  /** A provided network address was not valid. \
    This might be a formatting issue or indicate a DNS lookup failure. */ \
  ERROR(STUMPLESS_ADDRESS_FAILURE, 0) \
  /** A required function parameter was NULL or empty. */ \
  ERROR(STUMPLESS_ARGUMENT_EMPTY, 1) \
  /** A provided argument was too big, e.g., it cannot fit into the target buffer. */ \
  ERROR(STUMPLESS_ARGUMENT_TOO_BIG, 2) \
  /** A duplicate of an already existing element was detected in an entry. \
    @since release v1.6.0. */ \
  ERROR(STUMPLESS_DUPLICATE_ELEMENT, 3) \
  /** No element with the specified characteristics was found. \
    @since release v1.6.0. */ \
  ERROR(STUMPLESS_ELEMENT_NOT_FOUND, 4) \
  /** Could not open a file. */ \
  ERROR(STUMPLESS_FILE_OPEN_FAILURE, 5) \
  /** Could not write to a file. */ \
  ERROR(STUMPLESS_FILE_WRITE_FAILURE, 6) \
  /** A provided index was not in a valid range. */ \
  ERROR(STUMPLESS_INDEX_OUT_OF_BOUNDS, 7) \
  /** A provided facility code did not conform to RFC 5424. */ \
  ERROR(STUMPLESS_INVALID_FACILITY, 8) \
  /** A target or entry ID was not valid. */ \
  ERROR(STUMPLESS_INVALID_ID, 9) \
  /** A provided severity code did not conform to RFC 5424. \
    @since release v1.6.0. */ \
  ERROR(STUMPLESS_INVALID_SEVERITY, 10) \
  /** A memory allocation or reallocation failed. */ \
  ERROR(STUMPLESS_MEMORY_ALLOCATION_FAILURE, 11) \
  /** The given layer 3 protocol is not supported by this implementation. */ \
  ERROR(STUMPLESS_NETWORK_PROTOCOL_UNSUPPORTED, 12) \
  /** No param with the specified characteristics was found. \
    @since release v1.6.0. */ \
  ERROR(STUMPLESS_PARAM_NOT_FOUND, 13) \
  /** Could not bind to a socket. */ \
  ERROR(STUMPLESS_SOCKET_BIND_FAILURE, 14) \
  /** Could not connect to a socket. */ \
  ERROR(STUMPLESS_SOCKET_CONNECT_FAILURE, 15) \
  /** Could not create a socket. */ \
  ERROR(STUMPLESS_SOCKET_FAILURE, 16) \
  /** Could not send to a socket. */ \
  ERROR(STUMPLESS_SOCKET_SEND_FAILURE, 17) \
  /** Could not write to a stream. */ \
  ERROR(STUMPLESS_STREAM_WRITE_FAILURE, 18) \
  /** The requested operation is not valid on the given target type. */ \
  ERROR(STUMPLESS_TARGET_INCOMPATIBLE, 19) \
  /** The target type provided is unsupported by this implementation. */ \
  ERROR(STUMPLESS_TARGET_UNSUPPORTED, 20) \
  /** The given layer 4 protocol is not supported by this implementation. */ \
  ERROR(STUMPLESS_TRANSPORT_PROTOCOL_UNSUPPORTED, 21) \
  /** Could not close the Windows Event Log. */ \
  ERROR(STUMPLESS_WINDOWS_EVENT_LOG_CLOSE_FAILURE, 22) \
  /** Could not open the Windows Event Log. */ \
  ERROR(STUMPLESS_WINDOWS_EVENT_LOG_OPEN_FAILURE, 23) \
  /** A provided encoding does not conform to the standard. */ \
  ERROR(STUMPLESS_INVALID_ENCODING, 24) \
  /** The current hostname could not be retrieved. */ \
  ERROR(STUMPLESS_GETHOSTNAME_FAILURE, 25) \
  /** A call to a function target's log function failed. \
    @since release v2.1.0 */ \
  ERROR(STUMPLESS_FUNCTION_TARGET_FAILURE, 26) \
  /** A call to a systemd journald function failed. \
    @since release v2.1.0 */ \
  ERROR(STUMPLESS_JOURNALD_FAILURE, 27) \
  /** A general failure of a Windows API call. Details on what call failed and \
    why are provided in the error details. \
    @since release v2.1.0 */ \
  ERROR(STUMPLESS_WINDOWS_FAILURE, 28) \
  /** The format of the given string is incorrect. \
    @since release v2.2.0 */ \
  ERROR(STUMPLESS_INVALID_PARAM_STRING, 29) \
  /** SQLite3 was busy and could not complete the request. \
    @since release v2.2.0 */ \
  ERROR(STUMPLESS_SQLITE3_BUSY, 30) \
  /** A custom callback to a SQLite3 target failed. \
    @since release v2.2.0 */ \
  ERROR(STUMPLESS_SQLITE3_CALLBACK_FAILURE, 31) \
  /** SQLite3 encountered a failure. \
    @since release v2.2.0 */ \
  ERROR(STUMPLESS_SQLITE3_FAILURE, 32) \
  /** The network connection requested has been closed. \
    @since release v2.2.0 */ \
  ERROR(STUMPLESS_NETWORK_CLOSED, 33)

/**
 * An (enum) identifier of the types of errors that might be encountered.
 *
 * Note that the same error may be encountered in different contexts with a
 * different ultimate cause. To completely diagnose a problem, you will need
 * to look at more than just the error id.
 *
 * See STUMPLESS_FOREACH_ERROR() and STUMPLESS_GENERATE_ENUM() for how this
 * enumeration is generated.
 */
enum stumpless_error_id {
  STUMPLESS_FOREACH_ERROR(STUMPLESS_GENERATE_ENUM)
};

/**
 * Severity levels for errors.
 */
enum stumpless_severity {
  STUMPLESS_SEVERITY_DEBUG = 0,
  STUMPLESS_SEVERITY_INFO,
  STUMPLESS_SEVERITY_WARNING,
  STUMPLESS_SEVERITY_ERROR,
  STUMPLESS_SEVERITY_CRITICAL,
  STUMPLESS_SEVERITY_UNKNOWN = -1
};

/** 
 * Information describing an error encountered by the library. 
 */
struct stumpless_error {
  enum stumpless_error_id id; /**< Error family */
  const char *message; /**< Specific details of the failure */
  int code; /**< An error code possibly providing more information */
  const char *code_type; /**< A description of the error code */
  enum stumpless_severity severity; /**< Severity level of the error */
};

/**
 * Retrieves the error encountered by the last library call.
 *
 * The returned error struct is only valid until the next call to a stumpless
 * function. After this, it should not be referred to, and if the error of any
 * subsequent call is needed another call to stumpless_get_error must be made.
 *
 * Note that the id is the only field of the error that is guaranteed to be set.
 * Other members may or may not be set, depending on the context of the error.
 *
 * If the code_type is NULL, then the code is not valid and should be ignored.
 *
 * This function does _not_ clear or update the per-thread error code for
 * stumpless, as it is involved in the error handling process itself.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe. No synchronization primitives are used as the
 * returned pointer is specific to the thread of execution. As a result, the
 * result should not be shared between threads.
 *
 * **Async Signal Safety: AS-Safe**
 * This function is safe to call from signal handlers. If you do so, note that
 * if it is called before a stumpless library function in the handler itself
 * the result will not be meaningful.
 *
 * **Async Cancel Safety: AC-Safe**
 * This function is safe to call from threads that may be asynchronously
 * cancelled.
 *
 * @return A stumpless_error struct describing the error encountered by the last
 * function call. If no error was encountered, the id will be set to
 * STUMPLESS_NO_ERROR.
 */
struct stumpless_error stumpless_get_error(void);

/**
 * Clears the error state for this library.
 *
 * After this function is called, the next call to stumpless_get_error() will
 * return an error id of STUMPLESS_NO_ERROR.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe. No synchronization primitives are used as the
 * per-thread error code is updated for the thread of execution.
 *
 * **Async Signal Safety: AS-Safe**
 * This function is safe to call from signal handlers. If you do so, note that
 * if it is called before a stumpless library function in the handler itself
 * the result will not be meaningful.
 *
 * **Async Cancel Safety: AC-Safe**
 * This function is safe to call from threads that may be asynchronously
 * cancelled.
 */
void stumpless_clear_error(void);

#ifdef __cplusplus
}
#endif

#endif /* __STUMPLESS_ERROR_H */
