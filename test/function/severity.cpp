// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2019-2024 Joel E. Anderson
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

#include <gtest/gtest.h>
#include <stumpless.h>
#include "test/helper/assert.hpp"

namespace {

class SeverityTest : public ::testing::Test {
};

// Test getting severity string for each valid severity
TEST(GetSeverityString, EachValidSeverity) {
    const char* result;

    #define CHECK_SEVERITY(STRING, ENUM) \
        result = stumpless_get_severity_string(ENUM); \
        EXPECT_STREQ(result, STRING);
    
    STUMPLESS_FOREACH_SEVERITY(CHECK_SEVERITY);
}

// Test for invalid severity string
TEST(GetSeverityString, NoSuchSeverity) {
    int severity_count = 0;
    const char* result;

    #define COUNT_SEVERITY(STRING, ENUM) ++severity_count;
    STUMPLESS_FOREACH_SEVERITY(COUNT_SEVERITY);

    stumpless_severity wrong_severity = static_cast<stumpless_severity>(severity_count + 1);
    result = stumpless_get_severity_string(wrong_severity);
    EXPECT_STREQ(result, "NO_SUCH_SEVERITY");
}

// Test getting severity enum for each valid severity
TEST(GetSeverityEnum, EachValidSeverity) {
    int result;

    #define CHECK_SEVERITY_ENUM(STRING, ENUM) \
        result = stumpless_get_severity_enum(STRING); \
        EXPECT_EQ(result, ENUM);
    
    STUMPLESS_FOREACH_SEVERITY(CHECK_SEVERITY_ENUM);
}

// Test getting severity enum with lowercase valid severity
TEST(GetSeverityEnum, LowercaseValidSeverity) {
    int result;

    result = stumpless_get_severity_enum("emerg");
    EXPECT_EQ(result, STUMPLESS_SEVERITY_EMERG);

    result = stumpless_get_severity_enum("alert");
    EXPECT_EQ(result, STUMPLESS_SEVERITY_ALERT);

    result = stumpless_get_severity_enum("crit");
    EXPECT_EQ(result, STUMPLESS_SEVERITY_CRIT);

    result = stumpless_get_severity_enum("err");
    EXPECT_EQ(result, STUMPLESS_SEVERITY_ERR);

    result = stumpless_get_severity_enum("warning");
    EXPECT_EQ(result, STUMPLESS_SEVERITY_WARNING);

    result = stumpless_get_severity_enum("notice");
    EXPECT_EQ(result, STUMPLESS_SEVERITY_NOTICE);

    result = stumpless_get_severity_enum("info");
    EXPECT_EQ(result, STUMPLESS_SEVERITY_INFO);

    result = stumpless_get_severity_enum("debug");
    EXPECT_EQ(result, STUMPLESS_SEVERITY_DEBUG);

    // Deprecated checks
    result = stumpless_get_severity_enum("panic");
    EXPECT_EQ(result, STUMPLESS_SEVERITY_EMERG);

    result = stumpless_get_severity_enum("error");
    EXPECT_EQ(result, STUMPLESS_SEVERITY_ERR);

    result = stumpless_get_severity_enum("warn");
    EXPECT_EQ(result, STUMPLESS_SEVERITY_WARNING);
}

// Test for an invalid severity string
TEST(GetSeverityEnum, NoSuchSeverity) {
    int result = stumpless_get_severity_enum("an_invalid_severity");
    EXPECT_EQ(result, -1);
}

// Test for getting severity enum from buffer for an invalid severity string
TEST(GetSeverityEnumFromBuffer, NoSuchSeverity) {
    int result = stumpless_get_severity_enum_from_buffer("an_invalid_severity", 10);
    EXPECT_EQ(result, -1);
}

// Test for incomplete severity strings
TEST(GetSeverityEnumFromBuffer, IncompleteSeverity) {
    int result;

    result = stumpless_get_severity_enum("war");
    EXPECT_EQ(result, -1);

    result = stumpless_get_severity_enum("not");
    EXPECT_EQ(result, -1);
}

// Test for overextended severity strings
TEST(GetSeverityEnumFromBuffer, OverextendedSeverity) {
    int result;

    result = stumpless_get_severity_enum("warnings are neat");
    EXPECT_EQ(result, -1);

    result = stumpless_get_severity_enum("notices are bad");
    EXPECT_EQ(result, -1);

    result = stumpless_get_severity_enum("panic you should not");
    EXPECT_EQ(result, -1);
}

} // namespace
