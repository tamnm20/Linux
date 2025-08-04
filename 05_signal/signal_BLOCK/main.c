#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


void sig_handler1(int signum) {
    printf("Im signal handler1\n");
    exit(EXIT_SUCCESS);
}

void print_sigset(const sigset_t *set) {
	printf("Kill list %d: ",NSIG - 1);
    for (int i = 1; i < NSIG; ++i) {
        // if (sigismember(set, i))
        //     //printf("Signal %d is in the set\n", i);
		// else printf("0");
		printf("%d",sigismember(set, i));
    }
	printf("\n");
}

int main() {
	//time_t start, finish;
  	sigset_t new_set, old_set;
	
	if (signal(SIGINT, sig_handler1) == SIG_ERR) {
        fprintf(stderr, "Cannot handle SIGINT\n");
        exit(EXIT_FAILURE);
    }
	
    sigemptyset(&new_set);
	sigemptyset(&old_set);

    sigaddset(&new_set, SIGINT);
	sigaddset(&new_set, SIGCHLD);
	printf("new_set\n");
	print_sigset(&new_set);

	if (sigprocmask(SIG_SETMASK, &new_set, &old_set) == 0) {
		// sigprocmask(SIG_SETMASK, NULL, &old_set);
		if (sigismember(&new_set, SIGINT) == 1 ) {
			printf("SIGINT exist\n");
		} else if (sigismember(&new_set, SIGINT) == 0) {
			printf("SIGINT does not exist\n");
		}
	}

	while (1);
	
				
	return 0;
}