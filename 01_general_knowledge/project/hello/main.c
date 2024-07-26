#include<stdio.h>
#include "add.h"
#include "sub.h"

void test();
inline void test() {
    printf("test\n");
}

void test1() {
    printf("test1\n");

}

int main(void)
{
    printf("Hello world! = %d\n",add(6,6));
    printf("Hello world! = %d\n",sub(5,6));

    test();
    test1();
    return 0;
}
