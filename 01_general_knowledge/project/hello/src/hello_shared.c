#include "hello_shared.h"
#include <stdio.h>

void Hello_so(void) {
	printf("Hello from function in shared library.\n");
}

void share_print(void){
	printf("share lib print!!!\n");
}

