#include "unit_test.h"
#include <iostream>

static bool TEST_CASE_RESULT = true;
static int TEST_CASE_NUM = 0;


void REQUIRE_EQUAL(const char* func, int file_line, bool is_equal, bool is_suc) {
    TEST_CASE_NUM++;
    if (!is_equal) {
        TEST_CASE_RESULT = false;
        std::cout << "\033[0;1;31m" /*"\033[31m"*/ << func << ": failed, file line: " <<  file_line << "\033[0m" << std::endl;
    }
    else {
        std::cout << "\033[32m" /*"\033[31m"*/ << func << ": pass, file line: " <<  file_line << "\033[0m" << std::endl;
    }
}

void TEST_CASES_INIT() {
    TEST_CASE_RESULT = true;
    TEST_CASE_NUM = 0;
}

void TEST_CASES_RESULT() {
    if (!TEST_CASE_NUM) {
        std::cout << "\033[32m" << "No test case!" << "\033[0m" << std::endl;
    }
    else if (TEST_CASE_RESULT) {
        std::cout << "\033[32m" << "There " << TEST_CASE_NUM << " test cases are passed " << "\033[0m" << std::endl;
    }
}