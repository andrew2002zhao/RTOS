//#pragma once
//
//#include "stdlib.h"
//#include "stdarg.h"
//#include "usr_mem.h"
//#include "stdio.h"
//#include "string.h"
//struct TEST_HARNESS;
//
//typedef struct TEST_HARNESS{
//    int passed_cases;
//    int failed_cases;
//    char logs[10000000];
//} test_harness;
//
//void run_test(test_harness * p_test_harness, char * test_name, int test_number, int test_result);
//void log_results(test_harness * p_test_harness);
//
//int int_verify_equal(int actual, int expected);
//int int_verify_not_equal(int actual, int expected);
//
//int ptr_verify_equal(void * actual, void * expected);
//int ptr_verify_not_equal(int actual, int expected);
//
////declare tests under here
//void test_get_node_size();
//
//int test_partition_free_node_1();
//int test_partition_free_node_2();
//int test_partition_free_node_3();
//
//int test_allocate_node_1();
//int test_allocate_node_2();
//int test_allocate_node_3();
//int test_allocate_node_4();
//
//int test_usr_k_mem_alloc_1();
//int test_usr_k_mem_alloc_2();
//int test_usr_k_mem_alloc_3();
//int test_usr_k_mem_alloc_4();
