#include<stdio.h>
#include "add.h"
#include "sub.h"
#include "mul.h"
#include <hello_static.h>

void test();
inline void test() {
    printf("test\n");
}

void test1() {
    printf("test1\n");

}

int main(void)
{
    printf("Hello add! = %d\n",add(6,6));
    printf("Hello sub! = %d\n",sub(5,6));
    printf("Hello mul! = %d\n",mul(5,6));
    test();
    test1();
    Hello();
    return 0;
}

