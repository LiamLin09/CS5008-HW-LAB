// CS 5008 LAB 5
// Author: Nianlong lin
// Date: 10/10/2023

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void run_command(const char* command, char* const arguments[]) {
    pid_t pid;
    pid_t wpid;
    int status;

    pid = fork();
    if (pid == 0) {
        if (execvp(command, arguments) == -1) {
            perror("Sorry, Error executing command!!");
            exit(EXIT_FAILURE);
        }
    } else if (pid < 0) {
        perror("Error forking!!!!");
        exit(EXIT_FAILURE);
    } else {
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
}


int main(int argc, char** argv) {

    char* ls_args[] = {"ls", NULL};
    run_command("ls", ls_args);

    char* echo_args[] = {"echo", "testing", NULL};
    run_command("echo", echo_args);

    char* nl_args[] = {"nl", "example.c", NULL};
    run_command("nl", nl_args);

    return 0;
}
