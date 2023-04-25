#ifndef __UNIT_TEST_H
#define __UNIT_TEST_H

void REQUIRE_EQUAL(const char* func, int file_line, bool is_equal, bool is_suc);
#define REQUIRE(x) REQUIRE_EQUAL(__FUNCTION__, __LINE__, x, false);
#define REQUIRE_EX(x) REQUIRE_EQUAL(__FUNCTION__, __LINE__, x, true);
void TEST_CASES_INIT();
void TEST_CASES_RESULT();

#endif