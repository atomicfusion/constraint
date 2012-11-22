#include <fcntl.h>
#include <sched.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "constraint.h"

int parseflags(char *arg) {
	int ret = 0;
	for(int i = 0; i < strlen(arg); i++) {
		switch(arg[i]) {
			case 'p':
				ret |= CLONE_NEWPID;
			case 'm':
				ret |= CLONE_NEWNS;
			case 'i':
				ret |= CLONE_NEWIPC;
			case 'n':
				ret |= CLONE_NEWNET;
			case 'u':
				ret |= CLONE_NEWUTS;
		}
	}
	return ret;
}

extern char **environ;

int main(int argc, char **argv) {
	if(argc < 4) {
		return EXIT_FAILURE;
	}
	//int dir = open(argv[2],O_RDONLY);
	//if(dir < 0) {
	//	return EXIT_FAILURE;
	//}
	int flags = parseflags(argv[1]);
	
//	int ret = constrain(dir,flags,argv[3],argv+3,environ);
	int ret = constrain(flags,argv[2],argv+2,environ);
	if(0 <= ret < 256) {
		return ret;
	}
	return EXIT_FAILURE;
}
