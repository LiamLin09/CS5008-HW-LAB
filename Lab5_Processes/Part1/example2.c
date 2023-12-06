#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(){

	// Variable to store the process id
	pid_t pid;
	// Variable 'x' allocated on the stack
	int x = 1;

	// pid returns the child process id.
	// 0 if it is the child
	// >0 is the process id of the child which the parent recieves
	pid = fork();

	if(pid==0){
		printf("Terminating Child, PID= x=%d\n",getpid());
		exit(0);
	}else{
    	    // Run the parent
	    printf("Running parent forever(pretend I am a server): pid=%d\n",getpid());
    	    while(1){
    	    }
  	}

	return 0;
}
