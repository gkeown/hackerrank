#include <stdio.h>

void test_binary_tree(void);
void test_diameter(void);
void test_bst1(void);
void test_bst2(void);
void test_bst3(void);
void test_bst4(void);
void test_bst5(void);

void
fibonacci(void)
{
    int first = 0;
    int second = 1;
    int res = 0;


    for (int k = 0; k < 10; k++) {
        res = first + second;
        printf("%d, ", res);
        first = second;
        second = res;
    }
}

int
main(int argc, char *argv[])
{
    // test_binary_tree();
    // test_diameter();
    // test_bst1();
    // test_bst2();
    // test_bst3();
    // test_bst4();
    // test_bst5();
    // fibonacci();
}
