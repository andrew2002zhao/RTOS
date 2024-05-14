//
///* Run with "gcc -m32 -o output usr_tst.c usr_mem.c" */
//#include "usr_tst.h"
//
//void test_set_node_size();
//void test_coalesce_1();
//void test_get_node_size();
//void test_coalesce_2();
//void test_coalesce_3();
//
//void test_usr_k_mem_dealloc_1();
//void test_usr_k_mem_dealloc_2();
//void test_usr_k_mem_dealloc_3();
//void test_usr_k_mem_dealloc_4();
//void test_usr_k_mem_dealloc_5();
//void test_usr_k_mem_dealloc_6();
//int test_partition_free_node_1();
//int test_partition_free_node_2();
//int test_partition_free_node_3();
//
//int test_usr_k_mem_count_extfrag(size_t size);
//void test_get_node_ST();
//void test_set_node_free();
//void test_set_node_taken();
//void test_is_head_sentinel();
//void test_is_tail_sentinel();
//void test_set_node_sentinel_head();
//void test_set_node_sentinel_tail();
//void test_get_node_p_next();
//void test_set_node_p_next();
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
//
//test_harness * p_test_harness;
//
//int main(int argc, char * argv []) {
//    //do not touch
//    // test_harness initialization
//    p_test_harness = malloc(sizeof(test_harness));
//    p_test_harness -> passed_cases = 0;
//    p_test_harness -> failed_cases = 0;
//    //do not touch
//
//
//    //run tests
//    test_get_node_size();
//    test_set_node_size();
//    test_coalesce_1();
//    test_coalesce_2();
//    test_coalesce_3();
//
//    test_usr_k_mem_dealloc_1();
//    test_usr_k_mem_dealloc_2();
//    test_usr_k_mem_dealloc_3();
//    test_usr_k_mem_dealloc_4();
//    test_usr_k_mem_dealloc_5();
//    test_usr_k_mem_dealloc_6();
//    test_partition_free_node_1();
//    test_partition_free_node_2();
//    test_partition_free_node_3();
//
//    test_usr_k_mem_count_extfrag();
//    test_get_node_ST();
//    test_set_node_free();
//    test_set_node_taken();
//    test_is_head_sentinel();
//    test_is_tail_sentinel();
//    test_set_node_sentinel_head();
//    test_set_node_sentinel_tail();
//    test_get_node_p_next();
//    test_set_node_p_next();
//
//    test_allocate_node_1();
//    test_allocate_node_2();
//    test_allocate_node_3();
//    test_allocate_node_4();
//
//    test_usr_k_mem_alloc_1();
//    test_usr_k_mem_alloc_2();
//    test_usr_k_mem_alloc_3();
//    test_usr_k_mem_alloc_4();
//    //do not touch
//    //log results
//    log_results(p_test_harness);
//    //// results
//    //freep_test_harness);
//    //do not touch
//}
///*
// *===========================================================================
// *                             UNIT TESTS
// *===========================================================================
// */
///* Example Test Suite */
///*
//INIT TESTS
//*/
//// Call it once
//
///*
//SET/GET TESTS
//*/
//void test_get_node_size() {
//    /*
//    1. pass arbitrary node, return segment size
//    2. pass corrupted node, return error
//
//    //returns node size (bytes)
//    */
//
//    /* Test Case 1*/
//    //initialize test parameters
//    m_node * test_node = malloc(sizeof(m_node));
//    test_node -> size = 12;
//    //initialize expected data
//    int expected = 12;
//    //run function to get actual results
//    int actual = get_node_size(test_node);
//    //log results
//    run_test(
//        p_test_harness,
//        "get_node_size",
//        1,
//        //verify results
//        int_verify_equal(
//            actual, //actual
//            expected //expected
//        )
//    );
//
//    //clean test
//    free(test_node);
//    // //freeexpected);
//    // //freeactual);
//    //end of test
//
//
//    /* Test Case 2*/
//
//    //initialize test parameters
//    test_node = malloc(sizeof(m_node));
//    test_node -> size = 12;
//    //initialize expected data
//    expected = 11;
//    //run function to get actual results
//    actual = get_node_size(test_node);
//    //log results
//    run_test(
//        p_test_harness,
//        "get_node_size",
//        2,
//        //verify results
//        int_verify_not_equal(
//            actual, //actual
//            expected //expected
//        )
//    );
//
//    //clean test
//    free(test_node);
//    // //freeexpected);
//    // //freeactual);
//    //end of test
//}
//
//void test_set_node_size(){
//    /*
//    1. pass arbitrary node, set node size
//    2. pass already set size node, set new node size
//    3. pass arbitrary node, set to min, max size
//    4. pass courrupted node address, return error
//    5. set to negative number
//
//    //sets node size (bytes)
//    */
//    /* Test Case 1*/
//    m_node * test_node = malloc(sizeof(m_node));
//    set_node_size(test_node, 16);
//
//    int expected = 16;
//    int actual = test_node->size;
//
//    run_test(
//        p_test_harness,
//        "set_node_size",
//        1,
//        int_verify_equal(actual, expected)
//    );
//    free(test_node);
//    //end of test
//
//    /* Test Case 2*/
//    test_node = malloc(sizeof(m_node));
//    set_node_size(test_node, 4);
//
//    expected = 4;
//    actual = test_node->size;
//
//    run_test(
//        p_test_harness,
//        "set_node_size",
//        2,
//        int_verify_equal(actual, expected)
//    );
//    free(test_node);
//
//    test_node = malloc(sizeof(m_node));
//    set_node_size(test_node, 40000000);
//
//    expected = 40000000;
//    actual = test_node->size;
//
//    run_test(
//        p_test_harness,
//        "set_node_size",
//        2,
//        int_verify_equal(actual, expected)
//    );
//    free(test_node);
//    //end of test
//
//    /* Test Case 3*/
//    test_node = malloc(sizeof(m_node));
//    set_node_size(test_node, 12);
//    set_node_size(test_node, 16);
//
//    expected = 16;
//    actual = test_node->size;
//
//    run_test(
//        p_test_harness,
//        "set_node_size",
//        3,
//        int_verify_equal(actual, expected)
//    );
//    free(test_node);
//    //end of test
//
//    /* Test Case 4*/
//    // test_node = malloc(sizeof(m_node));
//    // test_node = nullptr;
//    // set_node_size(test_node,5);
//
//    // expected = nullptr;
//    // actual = test_node->size;
//
//    // run_test(
//    //     p_test_harness,
//    //     "set_node_size",
//    //     4,
//    //     int_verify_equal(actual, expected)
//    // );
//    // free(test_node);
//    //end of test
//
//    /* Test Case 5*/
//    test_node = malloc(sizeof(m_node));
//    set_node_size(test_node, 12);
//    set_node_size(test_node, -1);
//
//    expected = 12;
//    actual = test_node->size;
//
//    run_test(
//        p_test_harness,
//        "set_node_size",
//        4,
//        int_verify_equal(actual, expected)
//    );
//    free(test_node);
//    //end of test
//}
//
//void test_get_node_ST(){
//  /*
//  1. Pass a free node, return 0
//  2. Pass a taken node, return 1
//  3. Pass the same free/taken node x times, return 0 or 1
//  4. Pass undefined node (corrupted address), return error
//
//  //returns taken status (0 free, 1 taken)
//  */
//
//    /* Test Case 1*/
//    m_node * test_node = malloc(sizeof(m_node));
//    test_node -> control = 1;
//
//    int expected = get_node_taken(test_node);
//    int actual = 1;
//
//    run_test(
//        p_test_harness,
//        "get_node_taken",
//        1,
//        int_verify_equal(actual, expected)
//    );
//    free(test_node);
//    //end of test
//
//    /* Test Case 2*/
//    test_node = malloc(sizeof(m_node));
//    test_node -> control = 0;
//
//    expected = get_node_taken(test_node);
//    actual = 0;
//
//    run_test(
//        p_test_harness,
//        "get_node_taken",
//        2,
//        int_verify_equal(actual, expected)
//    );
//    free(test_node);
//    //end of test
//
//    /* Test Case 3*/
//    test_node = malloc(sizeof(m_node));
//    test_node -> control = 0;
//
//    expected = get_node_free(test_node);
//    actual = 1;
//
//    run_test(
//        p_test_harness,
//        "get_node_free",
//        3,
//        int_verify_equal(actual, expected)
//    );
//    free(test_node);
//    //end of test
//
//    /* Test Case 4*/
//    test_node = malloc(sizeof(m_node));
//    test_node -> control = 1;
//
//    expected = get_node_free(test_node);
//    actual = 0;
//
//    run_test(
//        p_test_harness,
//        "get_node_free",
//        4,
//        int_verify_equal(actual, expected)
//    );
//    free(test_node);
//    //end of test
//
//}
//
//void test_set_node_free(){
//  /*
//  1. Pass an allocated node, sets node to free (0)
//  2. Pass a free node, return error
//  3. Pass an undefined node (corrupted address), return error
//  4. Pass the same node just passed, return error (can't set to free 2x)
//
//  //set node free
//  */
//    /* Test Case 1*/
//    m_node * test_node = malloc(sizeof(m_node));
//    test_node -> control = 1;
//    set_node_free(test_node);
//
//    int expected = test_node -> control;
//    int actual = 0;
//
//    run_test(
//        p_test_harness,
//        "set_node_free",
//        1,
//        int_verify_equal(actual, expected)
//    );
//    free(test_node);
//    //end of test
//
//    /* Test Case 2*/
//    test_node = malloc(sizeof(m_node));
//    test_node -> control = 0;
//    set_node_free(test_node);
//
//    expected = test_node -> control;
//    actual = 0;
//
//    run_test(
//        p_test_harness,
//        "set_node_free",
//        2,
//        int_verify_equal(actual, expected)
//    );
//    free(test_node);
//    //end of test
//}
//
//void test_set_node_taken(){
///*
//  1. Pass a free node, sets node to taken
//  2. Pass a taken node, returns error
//  3. Pass an undefined node (corrupted address), returns error
//  4. Pass a node just passed, return error(can't set to taken 2x)
//
//  //sets node taken
//*/
//    /* Test Case 1*/
//    m_node * test_node = malloc(sizeof(m_node));
//    test_node -> control = 1;
//    set_node_taken(test_node);
//
//    int expected = test_node -> control;
//    int actual = 1;
//
//    run_test(
//        p_test_harness,
//        "set_node_taken",
//        1,
//        int_verify_equal(actual, expected)
//    );
//    free(test_node);
//    //end of test
//
//    /* Test Case 2*/
//    test_node = malloc(sizeof(m_node));
//    test_node -> control = 0;
//    set_node_taken(test_node);
//
//    expected = test_node -> control;
//    actual = 1;
//
//    run_test(
//        p_test_harness,
//        "set_node_taken",
//        2,
//        int_verify_equal(actual, expected)
//    );
//    free(test_node);
//    //end of test
//
//}
//
//void test_is_head_sentinel(){
///*
//  1. pass sentinel head, returns true
//  2. pass sentinel tail, returns false
//  3. pass arbitrary node, returns false
//  4. pass corrupted node, returns error
//
//  //returns if node is head sentinel
//*/
//    /* Test Case 1*/
//    m_node * test_node = malloc(sizeof(m_node));
//    test_node -> control = 2;
//
//    int expected = is_head_sentinel(test_node);
//    int actual = 1;
//
//    run_test(
//        p_test_harness,
//        "is_head_sentinel",
//        1,
//        int_verify_equal(actual, expected)
//    );
//    free(test_node);
//    //end of test
//
//    /* Test Case 2*/
//    test_node = malloc(sizeof(m_node));
//    test_node -> control = 4;
//
//    expected = is_head_sentinel(test_node);
//    actual = 0;
//
//    run_test(
//        p_test_harness,
//        "is_head_sentinel",
//        2,
//        int_verify_equal(actual, expected)
//    );
//    free(test_node);
//    //end of test
//
//    /* Test Case 3*/
//    test_node = malloc(sizeof(m_node));
//    test_node -> control = 0;
//
//    expected = is_head_sentinel(test_node);
//    actual = 0;
//
//    run_test(
//        p_test_harness,
//        "is_head_sentinel",
//        3,
//        int_verify_equal(actual, expected)
//    );
//    free(test_node);
//    //end of test
//
//    /* Test Case 4*/
//    test_node = malloc(sizeof(m_node));
//    test_node -> control = 6;
//
//    expected = is_head_sentinel(test_node);
//    actual = 0;
//
//    run_test(
//        p_test_harness,
//        "is_head_sentinel",
//        4,
//        int_verify_equal(actual, expected)
//    );
//    free(test_node);
//    //end of test
//}
//
//void test_is_tail_sentinel(){
///*
//  1. pass sentinel head, returns false
//  2. pass sentinel tail, returns true
//  3. pass arbitrary node, returns false
//  4. pass corrupted node, returns error
//
//  //returns if node is tail sentinel
//*/
//    /* Test Case 1*/
//    m_node * test_node = malloc(sizeof(m_node));
//    test_node -> control = 2;
//
//    int expected = is_tail_sentinel(test_node);
//    int actual = 0;
//
//    run_test(
//        p_test_harness,
//        "is_tail_sentinel",
//        1,
//        int_verify_equal(actual, expected)
//    );
//    free(test_node);
//    //end of test
//
//    /* Test Case 2*/
//    test_node = malloc(sizeof(m_node));
//    test_node -> control = 4;
//
//    expected = is_tail_sentinel(test_node);
//    actual = 1;
//
//    run_test(
//        p_test_harness,
//        "is_tail_sentinel",
//        2,
//        int_verify_equal(actual, expected)
//    );
//    free(test_node);
//    //end of test
//
//    /* Test Case 3*/
//    test_node = malloc(sizeof(m_node));
//    test_node -> control = 0;
//
//    expected = is_tail_sentinel(test_node);
//    actual = 0;
//
//    run_test(
//        p_test_harness,
//        "is_tail_sentinel",
//        3,
//        int_verify_equal(actual, expected)
//    );
//    free(test_node);
//    //end of test
//
//     /* Test Case 4*/
//    test_node = malloc(sizeof(m_node));
//    test_node -> control = 6;
//
//    expected = is_tail_sentinel(test_node);
//    actual = 0;
//
//    run_test(
//        p_test_harness,
//        "is_tail_sentinel",
//        4,
//        int_verify_equal(actual, expected)
//    );
//    free(test_node);
//    //end of test
//}
//
//void test_set_node_sentinel_head(){
///*
//  1. pass arbitrary node, set node to sentinel head
//  2. pass sentinel head node, return error
//  3. pass sentinel tail node, set node to sentinel head
//  4. pass corrupted node address, return error
//
//  //changes passed node to head sentinel node
//*/
//    /* Test Case 1*/
//    m_node * test_node = malloc(sizeof(m_node));
//    test_node -> control = 0;
//    set_node_sentinel_head(test_node);
//
//    int expected = 2;
//    int actual = test_node -> control;
//
//    run_test(
//        p_test_harness,
//        "set_node_sentinel_head",
//        1,
//        int_verify_equal(actual, expected)
//    );
//    free(test_node);
//    //end of test
//
//    /* Test Case 2*/
//    test_node = malloc(sizeof(m_node));
//    test_node -> control = 6;
//    set_node_sentinel_head(test_node);
//
//    expected = 6;
//    actual = test_node -> control;
//
//    run_test(
//        p_test_harness,
//        "set_node_sentinel_head",
//        2,
//        int_verify_equal(actual, expected)
//    );
//    free(test_node);
//    //end of test
//
//    /* Test Case 3*/
//    test_node = malloc(sizeof(m_node));
//    test_node -> control = 4;
//    set_node_sentinel_head(test_node);
//
//    expected = 6;
//    actual = test_node -> control;
//
//    run_test(
//        p_test_harness,
//        "set_node_sentinel_head",
//        3,
//        int_verify_equal(actual, expected)
//    );
//    free(test_node);
//    //end of test
//
//    /* Test Case 3*/
//    test_node = malloc(sizeof(m_node));
//    test_node -> control = 2;
//    set_node_sentinel_head(test_node);
//
//    expected = 2;
//    actual = test_node -> control;
//
//    run_test(
//        p_test_harness,
//        "set_node_sentinel_head",
//        4,
//        int_verify_equal(actual, expected)
//    );
//    free(test_node);
//    //end of test
//}
//
//void test_set_node_sentinel_tail(){
///*
//  1. pass arbitrary node, set node to sentinel tail
//  2. pass sentinel tail node, return error
//  3. pass sentinel head node, set node to sentinel tail
//  4. pass corrupted node address, return error
//
//  //changes passed node to tail sentinel node
//*/
//    /* Test Case 1*/
//    m_node * test_node = malloc(sizeof(m_node));
//    test_node -> control = 0;
//    set_node_sentinel_tail(test_node);
//
//    int expected = 4;
//    int actual = test_node -> control;
//
//    run_test(
//        p_test_harness,
//        "set_node_sentinel_tail",
//        1,
//        int_verify_equal(actual, expected)
//    );
//    free(test_node);
//    //end of test
//
//    /* Test Case 2*/
//    test_node = malloc(sizeof(m_node));
//    test_node -> control = 6;
//    set_node_sentinel_tail(test_node);
//
//    expected = 6;
//    actual = test_node -> control;
//
//    run_test(
//        p_test_harness,
//        "set_node_sentinel_tail",
//        2,
//        int_verify_equal(actual, expected)
//    );
//    free(test_node);
//    //end of test
//
//    /* Test Case 3*/
//    test_node = malloc(sizeof(m_node));
//    test_node -> control = 4;
//    set_node_sentinel_tail(test_node);
//
//    expected = 4;
//    actual = test_node -> control;
//
//    run_test(
//        p_test_harness,
//        "set_node_sentinel_tail",
//        3,
//        int_verify_equal(actual, expected)
//    );
//    free(test_node);
//    //end of test
//
//    /* Test Case 3*/
//    test_node = malloc(sizeof(m_node));
//    test_node -> control = 2;
//    set_node_sentinel_tail(test_node);
//
//    expected = 6;
//    actual = test_node -> control;
//
//    run_test(
//        p_test_harness,
//        "set_node_sentinel_tail",
//        3,
//        int_verify_equal(actual, expected)
//    );
//    free(test_node);
//    //end of test
//}
//
//void test_get_node_p_next(){
///*
//  1. pass arbitrary node, return next node
//  2. pass sentinal tail node, should check if sentinel in all cases, no error
//  3. pass corrupted node address, return error
//
//  //returns next node address
//*/
//    /* Test Case 1*/
//    m_node * test_node = malloc(sizeof(m_node));
//    m_node * next_node = malloc(sizeof(m_node));
//    test_node -> p_next = next_node;
//
//    m_node * expected = next_node;
//    m_node * actual = get_node_p_next(test_node);
//
//    run_test(
//        p_test_harness,
//        "get_node_p_next",
//        1,
//        ptr_verify_equal(actual, expected)
//    );
//    free(test_node);
//    //freenext_node);
//    //end of test
//
//    /* Test Case 2*/
//    test_node = malloc(sizeof(m_node));
//    test_node -> control = 4;
//
//    test_node -> p_next = nullptr;
//
//    expected = nullptr;
//    actual = get_node_p_next(test_node);
//
//    run_test(
//        p_test_harness,
//        "get_node_p_next",
//        2,
//        ptr_verify_equal(actual, expected)
//    );
//    free(test_node);
//    //end of test
//
//
//    /* Test Case 3*/
//    // m_node * test_node = malloc(sizeof(m_node));
//    // m_node * next_node = nullptr;
//    // set_node_p_next(test_node, next_node);
//
//    // m_node * expected = next_node;
//    // m_node * actual = test_node->p_next;
//
//    // run_test(
//    //     p_test_harness,
//    //     "set_node_size",
//    //     3,
//    //     ptr_verify_equal_equal(actual, expected)
//    // );
//    // free(test_node);
//
//    // m_node * next_node = malloc(sizeof(m_node));
//    // m_node * test_node = nullptr;
//
//    // int actual = set_node_p_next(test_node, next_node);
//    // int expected = -1;
//
//    // run_test(
//    //     p_test_harness,
//    //     "set_node_size",
//    //     3,
//    //     int_verify_not_equal(actual, expected)
//    // );
//    // free(test_node);
//    // //end of test
//
//}
//
//int test_usr_k_mem_count_extfrag(size_t size){
//    /* Test Case 1 - Test with multiple Free/Taken with multiple sizes*/
//    size_t sizeToTest = 20;
//    printf("SIZEEE %d\n", sizeToTest);
//    //initialize test parameters
//    head_sentinel = malloc(sizeof(m_node));
//    tail_sentinel = malloc(sizeof(m_node));
//    m_node * node1 = malloc(sizeof(m_node));
//    m_node * node2 = malloc(sizeof(m_node));
//    m_node * node3 = malloc(sizeof(m_node));
//    m_node * node4 = malloc(sizeof(m_node));
//    m_node * node5 = malloc(sizeof(m_node));
//    m_node * node6 = malloc(sizeof(m_node));
//
//    // Setting up each node
//    head_sentinel->control = 3;
//    head_sentinel->p_next = node1;
//    node1->size = sizeToTest - 4;
//    node1->control = 0;
//    node1->p_next = node2;
//    node2->size = sizeToTest + 4;
//    node2->control = 0;
//    node2->p_next = node3;
//    node3->size = sizeToTest - 12;
//    node3->control = 1;
//    node3->p_next = node4;
//    node4->size = sizeToTest + 40;
//    node4->control = 0;
//    node4->p_next = node5;
//    node5->size = sizeToTest - 20;
//    node5->control = 0;
//    node5->p_next = node6;
//    node6->size = sizeToTest;
//    node6->control = 0;
//    node6->p_next = tail_sentinel;
//    tail_sentinel->p_next = NULL;
//    tail_sentinel->control = 5;
//
//    //initialize expected data
//    int expected = 2;
//    //run function to get actual results
//    int actual = usr_k_mem_count_extfrag(sizeToTest);
//    printf("HEREEEEE  %d", actual);
//    //log results
//    run_test(
//        p_test_harness,
//        "mem_count_extfrag",
//        1,
//        //verify results
//        int_verify_equal(
//            actual, //actual
//            expected //expected
//        )
//    );
//    //end of test
//
//
//    // Test Case 2 - Test by passing in a size of 0
//    sizeToTest = 0;
//
//    //initialize expected data
//    expected = 0;
//    //run function to get actual results
//    actual = usr_k_mem_count_extfrag(sizeToTest);
//    printf("HEREEEEE  %d", actual);
//    //log results
//    run_test(
//        p_test_harness,
//        "mem_count_extfrag",
//        2,
//        //verify results
//        int_verify_equal(
//            actual, //actual
//            expected //expected
//        )
//    );
//    //end of test
//
//
//    // Test Case 3 - Make all Nodes taken so no free ext frag nodes
//    node1->control = 1;
//    node2->control = 1;
//    node3->control = 1;
//    node4->control = 1;
//    node5->control = 1;
//    node6->control = 1;
//
//    //initialize expected data
//    expected = 0;
//    //run function to get actual results
//    actual = usr_k_mem_count_extfrag(sizeToTest);
//    printf("HEREEEEE  %d", actual);
//    //log results
//    run_test(
//        p_test_harness,
//        "mem_count_extfrag",
//        3,
//        //verify results
//        int_verify_equal(
//            actual, //actual
//            expected //expected
//        )
//    );
//    //end of test
//
//
//    //clean test
//    free(head_sentinel);
//    free(tail_sentinel);
//    free(node1);
//    free(node2);
//    free(node3);
//    free(node4);
//    free(node5);
//    free(node6);
//    //end of test
//}
//
//void test_set_node_p_next(){
///*
//  1. pass arbitrary node, set next node to passed node
//  2. sentinel node
//  3. pass corrupted node addres/next node address, return error
//
//
//  //set next node address
//*/
//    /* Test Case 1*/
//    m_node * test_node = malloc(sizeof(m_node));
//    m_node * next_node = malloc(sizeof(m_node));
//    set_node_p_next(test_node, next_node);
//
//    m_node * expected = next_node;
//    m_node * actual = test_node->p_next;
//
//    run_test(
//        p_test_harness,
//        "set_node_p_next",
//        1,
//        ptr_verify_equal(actual, expected)
//    );
//    free(test_node);
//    //freenext_node);
//    //end of test
//
//    /* Test Case 2*/
//    test_node = malloc(sizeof(m_node));
//    next_node = malloc(sizeof(m_node));
//    test_node -> control = 4;
//    set_node_p_next(test_node, next_node);
//
//    expected = next_node;
//    actual = test_node->p_next;
//
//    run_test(
//        p_test_harness,
//        "set_node_p_next",
//        2,
//        ptr_verify_equal(actual, expected)
//    );
//    // free
//    // int expected_1 = 4;
//    // int actual_1 = next_node->control;
//
//    // run_test(
//    //     p_test_harness,
//    //     "set_node_p_next",
//    //     3,
//    //     int_verify_equal(actual_1, expected_1)
//    // );
//    // free(test_node);
//    //freenext_node);
//
//}
//
////integration tests
//
////partition free_node tests
//int test_partition_free_node_1() {
//
//    /* Test Case 1*/
//
//    //1 node
//    /*
//
//    A
//
//    Partition A and expect that
//
//    A -> (A' new node)
//
//    */
//
//    //initialize test parameters
//    m_node * test_node = malloc(sizeof(m_node) + 1000);
//    test_node -> size = 1000;
//    test_node -> control = 1;
//    test_node -> p_next = nullptr;
//
//    int requested_size = 200;
//    //call function
//    partition_free_node(test_node, requested_size);
//
//
//    int actual_size = test_node -> size;
//    int expected_size = 200;
//
//    //log results
//    run_test(
//        p_test_harness,
//        "partition_free_node partitioned node size",
//        1,
//        //verify results
//        int_verify_equal(
//            actual_size, //actual
//            expected_size //expected
//        )
//    );
//
//    m_node * actual_p_next =(m_node *) test_node -> p_next;
//    void* expected_p_next = test_node + 212;
//    run_test(
//        p_test_harness,
//        "partition_free_node next node address",
//        1,
//        //verify results
//		ptr_verify_equal(
//            actual_p_next, //actual
//            expected_p_next //expected
//        )
//    );
//    int actual_new_node_size = actual_p_next -> size;
//    int expected_new_node_size = 788;
//    printf("size: %d \n", actual_p_next -> size );
//    run_test(
//        p_test_harness,
//        "partition_free_node next node size",
//        1,
//        //verify results
//		ptr_verify_equal(
//            actual_p_next, //actual
//            expected_p_next //expected
//        )
//    );
//
//    m_node * actual_p_next_p_next = (m_node *) actual_p_next -> p_next;
//    void* expected_p_next_p_next = nullptr;
//    run_test(
//        p_test_harness,
//        "partition_free_node next node next address",
//        1,
//        //verify results
//		ptr_verify_equal(
//            actual_p_next, //actual
//            expected_p_next //expected
//        )
//    );
//
//    //clean test
//    free(test_node);
//    //end of test
//
//}
//
//int test_partition_free_node_2() {
//
//    /* Test Case 2*/
//
//    //2 nodes in sequence
//
//    /*
//
//    A -> B
//
//    Partition A and expect that
//
//    A -> (A' new node) -> B
//
//    */
//
//    //initialize test parameters
//    m_node * test_node = malloc(sizeof(m_node) + 1000);
//    test_node -> size = 1000;
//    test_node -> control = 1;
//    test_node -> p_next = nullptr;
//
//    m_node * test_node_2 =  malloc(sizeof(m_node) + 48);
//    test_node_2 -> size = 48;
//    test_node_2 -> control = 1;
//    test_node_2 -> p_next = nullptr;
//
//    test_node -> p_next = test_node_2;
//
//    int requested_size = 200;
//    //call function
//    partition_free_node(test_node, requested_size);
//
//
//    int actual_size = test_node -> size;
//    int expected_size = 200;
//
//    //log results
//    run_test(
//        p_test_harness,
//        "partition_free_node partitioned node size",
//        2,
//        //verify results
//        int_verify_equal(
//            actual_size, //actual
//            expected_size //expected
//        )
//    );
//
//    m_node * actual_p_next =(m_node *) test_node -> p_next;
//    void* expected_p_next = test_node + 212;
//    run_test(
//        p_test_harness,
//        "partition_free_node next node address",
//        2,
//        //verify results
//		ptr_verify_equal(
//            actual_p_next, //actual
//            expected_p_next //expected
//        )
//    );
//    int actual_new_node_size = actual_p_next -> size;
//    int expected_new_node_size = 788;
//    run_test(
//        p_test_harness,
//        "partition_free_node next node size",
//        2,
//        //verify results
//		ptr_verify_equal(
//            actual_p_next, //actual
//            expected_p_next //expected
//        )
//    );
//
//    m_node * actual_p_next_p_next = (m_node *) actual_p_next -> p_next;
//    void* expected_p_next_p_next = test_node_2;
//    run_test(
//        p_test_harness,
//        "partition_free_node next node next address",
//        2,
//        //verify results
//		ptr_verify_equal(
//            actual_p_next, //actual
//            expected_p_next //expected
//        )
//    );
//
//    //clean test
//    free(test_node);
//    free(test_node_2);
//    //end of test
//
//}
//
//int test_partition_free_node_3() {
//
//
//
//    /* Test Case 3*/
//
//    //2 nodes in sequence
//
//    /*
//
//    A -> B
//
//    Partition B and expect that
//
//    A -> B -> B' (new node)
//
//    */
//
//    //initialize test parameters
//    m_node * test_node = malloc(sizeof(m_node) + 48);
//    test_node -> size = 48;
//    test_node -> control = 1;
//    test_node -> p_next = nullptr;
//
//    m_node * test_node_2 =  malloc(sizeof(m_node) + 1000);
//    test_node_2 -> size = 1000;
//    test_node_2 -> control = 1;
//    test_node_2 -> p_next = nullptr;
//
//    test_node -> p_next = test_node_2;
//
//    int requested_size = 200;
//    //call function
//    partition_free_node(test_node_2, requested_size);
//
//
//    int actual_size = test_node_2 -> size;
//    int expected_size = 200;
//
//    //log results
//    run_test(
//        p_test_harness,
//        "partition_free_node partitioned node size",
//        3,
//        //verify results
//        int_verify_equal(
//            actual_size, //actual
//            expected_size //expected
//        )
//    );
//
//    m_node * actual_p_next =(m_node *) test_node_2 -> p_next;
//    void* expected_p_next = test_node_2 + 212;
//    run_test(
//        p_test_harness,
//        "partition_free_node next node address",
//        3,
//        //verify results
//		ptr_verify_equal(
//            actual_p_next, //actual
//            expected_p_next //expected
//        )
//    );
//    int actual_new_node_size = actual_p_next -> size;
//    int expected_new_node_size = 788;
//    run_test(
//        p_test_harness,
//        "partition_free_node next node size",
//        3,
//        //verify results
//		ptr_verify_equal(
//            actual_p_next, //actual
//            expected_p_next //expected
//        )
//    );
//
//    m_node * actual_p_next_p_next = (m_node *) actual_p_next -> p_next;
//    void* expected_p_next_p_next = nullptr;
//    run_test(
//        p_test_harness,
//        "partition_free_node next node next address",
//        3,
//        //verify results
//		ptr_verify_equal(
//            actual_p_next, //actual
//            expected_p_next //expected
//        )
//    );
//
//    m_node * test_node_next_actual = test_node -> p_next;
//    m_node * test_node_next_expected = test_node_2;
//    run_test(
//        p_test_harness,
//        "partition_free_node next node next address",
//        3,
//        //verify results
//		ptr_verify_equal(
//            actual_p_next, //actual
//            expected_p_next //expected
//        )
//    );
//    //clean test
//    free(test_node);
//    free(test_node_2);
//    //end of test
//
//}
//
//
//
////allocate node
//int test_allocate_node_1(){
//
//    //create a partition with exact size
//
//
//    //initialize test parameters
//    m_node * test_node = malloc(sizeof(m_node));
//    test_node -> size = 12;
//    test_node -> p_next = nullptr;
//    test_node -> control = 0;
//    //initialize expected data
//    int requested_size = 12;
//
//    int actual_error_code = allocate_node(test_node, requested_size);
//    int expected_error_code = 0;
//
//    //log results
//    run_test(
//        p_test_harness,
//        "get_node_size error code",
//        1,
//        //verify results
//        int_verify_equal(
//            actual_error_code, //actual
//            expected_error_code //expected
//        )
//    );
//    void * actual_p_next = test_node -> p_next;
//    void * expected_p_next = nullptr;
//    run_test(
//        p_test_harness,
//        "get_node_size no new partition",
//        1,
//        //verify results
//		ptr_verify_equal(
//            actual_p_next, //actual
//            expected_p_next //expected
//        )
//    );
//
//    int actual_control_bits = test_node -> control;
//    int expected_control_bits = 1;
//    run_test(
//        p_test_harness,
//        "get_node_size control bits",
//        1,
//        //verify results
//        int_verify_equal(
//            actual_control_bits, //actual
//            expected_control_bits //expected
//        )
//    );
//    //clean test
//    free(test_node);
//    //end of test
//}
//
//int test_allocate_node_2(){
//
//    //create a partition with a taken node
//
//
//    //initialize test parameters
//    m_node * test_node = malloc(sizeof(m_node));
//    test_node -> size = 12;
//    test_node -> p_next = nullptr;
//    test_node -> control = 1;
//    //initialize expected data
//    int requested_size = 12;
//
//    int actual_error_code = allocate_node(test_node, requested_size);
//    int expected_error_code = -1;
//
//    //log results
//    run_test(
//        p_test_harness,
//        "get_node_size error code",
//        2,
//        //verify results
//        int_verify_equal(
//            actual_error_code, //actual
//            expected_error_code //expected
//        )
//    );
//    void * actual_p_next = test_node -> p_next;
//    void * expected_p_next = nullptr;
//    run_test(
//        p_test_harness,
//        "get_node_size no new partition",
//        2,
//        //verify results
//		ptr_verify_equal(
//            actual_p_next, //actual
//            expected_p_next //expected
//        )
//    );
//
//    int actual_control_bits = test_node -> control;
//    int expected_control_bits = 1;
//    run_test(
//        p_test_harness,
//        "get_node_size control bits",
//        2,
//        //verify results
//        int_verify_equal(
//            actual_control_bits, //actual
//            expected_control_bits //expected
//        )
//    );
//    //clean test
//    free(test_node);
//    //end of test
//}
//
//int test_allocate_node_3(){
//
//    //create a partition with more than exact requested size but not enough to partition a new node
//
//    //current expected behaviour is the node is just returned
//
//    //initialize test parameters
//    m_node * test_node = malloc(sizeof(m_node));
//    test_node -> size = 16;
//    test_node -> p_next = nullptr;
//    test_node -> control = 0;
//    //initialize expected data
//    int requested_size = 12;
//
//    int actual_error_code = allocate_node(test_node, requested_size);
//    int expected_error_code = 0;
//
//    //log results
//    run_test(
//        p_test_harness,
//        "get_node_size error code",
//        3,
//        //verify results
//        int_verify_equal(
//            actual_error_code, //actual
//            expected_error_code //expected
//        )
//    );
//    void * actual_p_next = test_node -> p_next;
//    void * expected_p_next = nullptr;
//    run_test(
//        p_test_harness,
//        "get_node_size no new partition",
//        3,
//        //verify results
//		ptr_verify_equal(
//            actual_p_next, //actual
//            expected_p_next //expected
//        )
//    );
//
//    int actual_control_bits = test_node -> control;
//    int expected_control_bits = 1;
//    run_test(
//        p_test_harness,
//        "get_node_size control bits",
//        3,
//        //verify results
//        int_verify_equal(
//            actual_control_bits, //actual
//            expected_control_bits //expected
//        )
//    );
//    //clean test
//    free(test_node);
//    //end of test
//}
//
//int test_allocate_node_4(){
//
//    //create a new node and partition after
//
//
//    //initialize test parameters
//    m_node * test_node = malloc(sizeof(m_node));
//    test_node -> size = 50;
//    test_node -> p_next = nullptr;
//    test_node -> control = 0;
//    //initialize expected data
//    int requested_size = 12;
//
//    int actual_error_code = allocate_node(test_node, requested_size);
//    int expected_error_code = 1;
//
//    //log results
//    run_test(
//        p_test_harness,
//        "get_node_size error code",
//        4,
//        //verify results
//        int_verify_equal(
//            actual_error_code, //actual
//            expected_error_code //expected
//        )
//    );
//    void * actual_p_next = test_node -> p_next;
//    void * expected_p_next = test_node + 24;
//    run_test(
//        p_test_harness,
//        "get_node_size no new partition",
//        4,
//        //verify results
//		ptr_verify_equal(
//            actual_p_next, //actual
//            expected_p_next //expected
//        )
//    );
//
//    int actual_control_bits = test_node -> control;
//    int expected_control_bits = 1;
//    run_test(
//        p_test_harness,
//        "get_node_size control bits",
//        4,
//        //verify results
//        int_verify_equal(
//            actual_control_bits, //actual
//            expected_control_bits //expected
//        )
//    );
//    //clean test
//    free(test_node);
//    //end of test
//}
//
//int test_usr_k_mem_alloc_1(){
//
//    /* Test Case 1*/
//    // uninitialized
//    //initialize test parameters
//
//    //initialize expected data
//
//    extern int initialized;
//    extern m_node* head_sentinel;
//
//    initialized = 0;
//    head_sentinel = malloc(sizeof(m_node));
//    int expected = NULL;
//    //run function to get actual results
//    int actual = usr_k_mem_alloc(12);
//    //log results
//    run_test(
//        p_test_harness,
//        "usr_k_mem_alloc",
//        1,
//        //verify results
//        int_verify_equal(
//            actual, //actual
//            expected //expected
//        )
//    );
//
//    //clean test
//    // free(test_node);
//    free(head_sentinel);
//    //end of test
//}
//
//int test_usr_k_mem_alloc_2(){
//
//    /* Test Case 2*/
//    // all taken blocks
//    //initialize test parameters
//
//    //initialize expected data
//
//    extern int initialized;
//    extern m_node* head_sentinel;
//    extern m_node* tail_sentinel;
//    initialized = 1;
//    head_sentinel = malloc(sizeof(m_node));
//    tail_sentinel = malloc(sizeof(m_node));
//
//    head_sentinel -> control = 2;
//    tail_sentinel -> control = 4;
//
//    m_node * test_node = malloc(sizeof(m_node));
//    test_node -> control = 1;
//
//    head_sentinel -> p_next = test_node;
//    test_node -> p_next = tail_sentinel;
//
//    int expected = NULL;
//    //run function to get actual results
//    int actual = usr_k_mem_alloc(12);
//    //log results
//    run_test(
//        p_test_harness,
//        "usr_k_mem_alloc",
//        2,
//        //verify results
//        int_verify_equal(
//            actual, //actual
//            expected //expected
//        )
//    );
//
//    //clean test
//    free(test_node);
//    free(head_sentinel);
//    free(tail_sentinel);
//    //end of test
//}
//
//int test_usr_k_mem_alloc_3(){
//
//    /* Test Case 3*/
//    // not enough size
//    //initialize test parameters
//
//    //initialize expected data
//
//    extern int initialized;
//    extern m_node* head_sentinel;
//    extern m_node* tail_sentinel;
//
//    initialized = 1;
//    head_sentinel = malloc(sizeof(m_node));
//    tail_sentinel = malloc(sizeof(m_node));
//
//    head_sentinel -> control = 2;
//    tail_sentinel -> control = 4;
//
//    m_node * test_node = malloc(sizeof(m_node) + 500);
//    test_node -> size = 12;
//    test_node -> control = 1;
//
//    head_sentinel -> p_next = test_node;
//    test_node -> p_next = tail_sentinel;
//
//    int expected = NULL;
//    //run function to get actual results
//    int actual = usr_k_mem_alloc(24);
//    //log results
//    run_test(
//        p_test_harness,
//        "usr_k_mem_alloc",
//        3,
//        //verify results
//        int_verify_equal(
//            actual, //actual
//            expected //expected
//        )
//    );
//
//    //clean test
//    free(test_node);
//    free(head_sentinel);
//    free(tail_sentinel);
//    //end of test
//}
//
//int test_coalesce_1(){
//
//    /* Test Case 1*/
//    //test that the node was taken
//    //initialize test parameters
//    m_node * test_node = malloc(sizeof(m_node));
//    m_node * first_free_test_node;
//
//    test_node -> control = 1;
//    //initialize expected data
//    int expected_return_code = -1;
//    //run function to get actual results
//
//    int actual_return_code = coalesce(first_free_test_node, test_node);
//
//    //log results
//    run_test(
//        p_test_harness,
//        "coalesce return status",
//        1,
//        //verify results
//        int_verify_equal(
//            actual_return_code, //actual
//            expected_return_code //expected
//        )
//    );
//
//    //clean test
//    free(test_node);
//
//}
//
//int test_coalesce_2(){
//
//    /* Test Case 2*/
//    //test that the node was taken
//    //initialize test parameters
//    m_node * test_node = malloc(sizeof(m_node));
//    m_node * first_free_test_node = NULL;
//
//    test_node -> control = 0;
//    //initialize expected data
//    int expected_return_code = 0;
//    //run function to get actual results
//    int actual_return_code = coalesce(first_free_test_node, test_node);
//    //log results
//    run_test(
//        p_test_harness,
//        "coalesce return status",
//        2,
//        //verify results
//        int_verify_equal(
//            actual_return_code, //actual
//            expected_return_code //expected
//        )
//    );
//
//    //clean test
//    free(test_node);
//
//}
//
//int test_coalesce_3(){
//
//    /* Test Case 3*/
//    //test that the nodes are coalesced
//    //initialize test parameters
//    m_node * test_node = malloc(sizeof(m_node));
//    m_node * first_free_test_node = malloc(sizeof(m_node));
//
//
//    test_node -> size = 20;
//    test_node -> control = 0;
//    test_node -> p_next = nullptr;
//
//    first_free_test_node -> size = 50;
//    first_free_test_node -> p_next = test_node;
//    first_free_test_node -> control = 0;
//
//    //initialize expected data
//    int expected_return_code = 1;
//    //run function to get actual results
//    int actual_return_code = coalesce(first_free_test_node, test_node);
//    //log results
//    run_test(
//        p_test_harness,
//        "coalesce return status",
//        3,
//        //verify results
//        int_verify_equal(
//            actual_return_code, //actual
//            expected_return_code //expected
//        )
//    );
//
//
//    //check size
//
//    int expected_size = 82;
//    //run function to get actual results
//    int actual_size = first_free_test_node -> size;
//    printf("%d\n", actual_size);
//    //log results
//    run_test(
//        p_test_harness,
//        "coalesce size",
//        3,
//        //verify results
//        int_verify_equal(
//            actual_size, //actual
//            expected_size //expected
//        )
//    );
//
//
//    //clean test
//    free(test_node);
//    free(first_free_test_node);
//
//}
//
//int test_usr_k_mem_dealloc_1(){
//
//    /* Test Case 1*/
//    // deallocate
//
//    extern int initialized;
//
//    m_node * address_to_free;
//    initialized = 0;
//
//    //initialize expected data
//    int expected_return_code = -1;
//    //run function to get actual results
//    int actual_return_code = usr_k_mem_dealloc(address_to_free);
//    //log results
//    run_test(
//        p_test_harness,
//        "usr_k_mem_dealloc",
//        1,
//        //verify results
//        int_verify_equal(
//            actual_return_code, //actual
//            expected_return_code //expected
//        )
//    );
//
//}
//
//int test_usr_k_mem_dealloc_2(){
//
//    /* Test Case 3*/
//    // nullptr
//
//    extern int initialized;
//
//    initialized = 1;
//
//    m_node * address_to_free = NULL;
//
//
//    //initialize expected data
//    int expected_return_code = -1;
//    //run function to get actual results
//    int actual_return_code = usr_k_mem_dealloc(address_to_free);
//    //log results
//    run_test(
//        p_test_harness,
//        "usr_k_mem_dealloc",
//        2,
//        //verify results
//        int_verify_equal(
//            actual_return_code, //actual
//            expected_return_code //expected
//        )
//    );
//
//}
//
//
//int test_usr_k_mem_dealloc_3(){
//
//    /* Test Case 2*/
//    // deallocate
//
//    extern int initialized;
//
//    initialized = 1;
//
//    m_node * address_to_free = malloc(sizeof(m_node));
//    address_to_free ->control = 4;
//
//    //initialize expected data
//    int expected_return_code = -1;
//    //run function to get actual results
//    int actual_return_code = usr_k_mem_dealloc(address_to_free);
//    //log results
//    run_test(
//        p_test_harness,
//        "usr_k_mem_dealloc",
//        3,
//        //verify results
//        int_verify_equal(
//            actual_return_code, //actual
//            expected_return_code //expected
//        )
//    );
//
//}
//
//int test_usr_k_mem_dealloc_4(){
//
//    /* Test Case 3*/
//    // double deallocate
//
//    extern int initialized;
//    extern m_node * head_sentinel;
//    extern m_node * tail_sentinel;
//
//    head_sentinel = malloc(sizeof(m_node));
//    tail_sentinel = malloc(sizeof(m_node));
//
//    initialized = 1;
//
//    m_node * address_to_free = malloc(sizeof(m_node) + 20);
//    address_to_free -> control = 0;
//    address_to_free -> size = 20;
//
//    head_sentinel -> p_next = address_to_free;
//    address_to_free -> p_next = tail_sentinel;
//
//    //initialize expected data
//    int expected_return_code = -1;
//    //run function to get actual results
//    int actual_return_code = usr_k_mem_dealloc(address_to_free);
//    //log results
//    run_test(
//        p_test_harness,
//        "usr_k_mem_dealloc",
//        4,
//        //verify results
//        int_verify_equal(
//            actual_return_code, //actual
//            expected_return_code //expected
//        )
//    );
//    free(head_sentinel);
//    free(tail_sentinel);
//    free(address_to_free);
//
//}
//
//int test_usr_k_mem_dealloc_5() {
//
//    /* Test Case 4*/
//    // nothing
//
//    extern int initialized;
//    extern m_node * head_sentinel;
//    extern m_node * tail_sentinel;
//
//    head_sentinel = malloc(sizeof(m_node));
//    tail_sentinel = malloc(sizeof(m_node));
//
//    initialized = 1;
//
//    m_node * address_to_free = malloc(sizeof(m_node) + 20);
//    address_to_free -> control = 1;
//    address_to_free -> size = 20;
//
//    head_sentinel -> p_next = address_to_free;
//    address_to_free -> p_next = tail_sentinel;
//
//    //initialize expected data
//    int expected_return_code = -1;
//    //run function to get actual results
//    int actual_return_code = usr_k_mem_dealloc(address_to_free + 2);
//    //log results
//    run_test(
//        p_test_harness,
//        "usr_k_mem_dealloc",
//        5,
//        //verify results
//        int_verify_equal(
//            actual_return_code, //actual
//            expected_return_code //expected
//        )
//    );
//    free(head_sentinel);
//    free(tail_sentinel);
//    free(address_to_free);
//}
//
//int test_usr_k_mem_dealloc_6(){
//
//    /* Test Case 6*/
//    // deallocate on a single node
//
//     extern int initialized;
//    extern m_node * head_sentinel;
//    extern m_node * tail_sentinel;
//
//    initialized = 1;
//    head_sentinel = malloc(sizeof(m_node));
//    tail_sentinel = malloc(sizeof(m_node));
//
//    head_sentinel -> control = 2;
//    tail_sentinel -> control = 4;
//    initialized = 1;
//
//    m_node * address_to_free = malloc(sizeof(m_node) + 20);
//    address_to_free -> control = 1;
//    address_to_free -> size = 20;
//
//    head_sentinel -> p_next = address_to_free;
//    address_to_free -> p_next = tail_sentinel;
//
//    //initialize expected data
//    int expected_return_code = 0;
//    //run function to get actual results
//    int actual_return_code = usr_k_mem_dealloc(address_to_free + 12);
//    //log results
//    run_test(
//        p_test_harness,
//        "usr_k_mem_dealloc",
//        6,
//        //verify results
//        int_verify_equal(
//            actual_return_code, //actual
//            expected_return_code //expected
//        )
//    );
//
//    //initialize expected data
//    int expected_control = 0;
//    //run function to get actual results
//    int actual_control = address_to_free -> control;
//    //log results
//    run_test(
//        p_test_harness,
//        "usr_k_mem_dealloc",
//        6,
//        //verify results
//        int_verify_equal(
//            actual_control, //actual
//            expected_control //expected
//        )
//    );
//
//    free(head_sentinel);
//    free(tail_sentinel);
//    free(address_to_free);
//
//}
//
//int test_usr_k_mem_alloc_4(){
//
//    /* Test Case 4*/
//    // create a new node
//    //initialize test parameters
//
//    //initialize expected data
//
//    extern int initialized;
//    extern m_node* head_sentinel;
//    extern m_node* tail_sentinel;
//
//    head_sentinel = malloc(sizeof(m_node));
//    tail_sentinel = malloc(sizeof(m_node));
//    initialized = 1;
//
//    m_node * test_node = malloc(sizeof(m_node) + 500);
//    test_node -> size = 50;
//    test_node -> control = 0;
//
//    head_sentinel -> p_next = test_node;
//    test_node -> p_next = tail_sentinel;
//
//    int expected = test_node + 12;
//    //run function to get actual results
//    int actual = usr_k_mem_alloc(12);
//    //log results
//    run_test(
//        p_test_harness,
//        "usr_k_mem_alloc",
//        4,
//        //verify results
//        int_verify_equal(
//            actual, //actual
//            expected //expected
//        )
//    );
//
//    //clean test
//    free(test_node);
//    free(head_sentinel);
//    free(tail_sentinel);
//    //end of test
//}
//
//
///* Helper Functions for the Test Harness */
//
//void run_test(test_harness * p_test_harness, char * test_name, int test_number, int test_result) {
//    //count passed cases
//    char test_name_copy[1000] = "";
//    char test_result_copy[100];
//    if(test_result) {
//        p_test_harness -> passed_cases += 1;
//        snprintf(test_result_copy, 100, " case %d passed \n", test_number);
//    } else{
//        p_test_harness -> failed_cases += 1;
//        snprintf(test_result_copy, 100, " case %d failed \n", test_number);
//    }
//    strcat(test_name_copy, test_name);
//    strcat(test_name_copy, test_result_copy);
//
//    strcat(p_test_harness -> logs, test_name_copy);
//}
//void log_results(test_harness * p_test_harness) {
//    printf("\n");
//    printf("--------------------------Output Start---------------------------------");
//    printf("\n");
//    printf("%s \n", p_test_harness -> logs);
//    printf("Passed Cases : %d \n", p_test_harness -> passed_cases);
//    printf("Failed Cases : %d \n", p_test_harness -> failed_cases);
//    printf("\n");
//    printf("--------------------------Output End---------------------------------");
//    printf("\n");
//}
//int int_verify_equal(int actual, int expected) {
//    return (actual == expected);
//}
//int int_verify_not_equal(int actual, int expected) {
//    return (actual != expected);
//}
//int ptr_verify_equal(void * actual, void * expected) {
//    return (actual == expected);
//}
//int ptr_not_verify(void * actual, void * expected) {
//    return (actual != expected);
//}
