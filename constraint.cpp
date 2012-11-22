#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <syscall.h>
#include <unistd.h>
#include <wait.h>
#include "constraint.h"

static char *fdpath(int fd) {
	char *path;
	if(asprintf(&path,"/proc/self/fd/%d",fd) < 0) {
		return NULL;
	}
	return path;
}

int constrain(int cloneflags,char *prog,char **argv,char **env) {
	int cpid;
	siginfo_t sigstuff;
	cpid = syscall(SYS_clone,(cloneflags & (CLONE_NEWNS|CLONE_NEWPID|CLONE_NEWIPC|CLONE_NEWNET|CLONE_NEWUTS)) | SIGCHLD,0);
	if(cpid < 0) {
		return -1;
	}
	else if(!cpid) {
		//char *dirpath = fdpath(dir);
		//if(!dirpath || chroot(dirpath)) {
		//	exit(EXIT_FAILURE);
		//}
		//free(dirpath);
		execve(prog,argv,env);
		exit(EXIT_FAILURE);
	}
	else {
		while(true) {
			if(!waitid(P_PID,cpid,&sigstuff,WEXITED)) {
				return sigstuff.si_status;
			}
		}
	}
}
