// CS 5008 Assignment 5
// Author: Nianlong Lin
// Date: 10/7/2023

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <time.h>

#define BUFFER_SIZE 80
#define MAX_ARGS 10

// define a function pointer type for the built-in commands.
typedef void (*builtin_func_t) (char**);

// define a structure for the built-in commands.
typedef struct {
    char *name;
    builtin_func_t func;
} builtin_t;

// list of built-in commands and their corresponding function pointers.
builtin_t builtins[] = {
    {"exit", exit_shell},
    {"cd", change_directory},
    {"help", print_help},
    {"guessinggame", guessinggame},
    {"edit", editsummary},
    {NULL, NULL}
};

// function to print the shell prompt with the host name.
void print_prompt() {
    char hostname[1024];
    gethostname(hostname, 1024);
    printf("mini-shell@%s", hostname);
    fflush(stdout);
}

// function to read and parse the command entered by the user.
int read_command(char* buffer, char** args) {
    int i = 0;
    char* token = strtok(buffer, " \t\n");
    while (token != NULL && i < MAX_ARGS - 1) {
        args[i++] = token;
        token = strtok(NULL, " \t\n");
    }
    args[i] = NULL;
    return i;
}

// signal handler to handle the termination of the mini-shell
void signal_handler(int sig) {
    printf("\nmini-shell terminated\n");
    exit(0);
}

// function to fork a new process and execute the command
void launch_process(char** args, int input_fd, int output_fd) {
    pid_t pid = fork();
    if (pid == 0) {
        if (input_fd != STDIN_FILENO) {
            dup2(input_fd, STDIN_FILENO);
            close(input_fd);
        }
        if (output_fd != STDOUT_FILENO) {
            dup2(output_fd, STDOUT_FILENO);
            close(output_fd);
        }
        execvp(args[0], args);
        perror("execvp");
        exit(1);
    } else if (pid < 0) {
        perror("fork");
        exit(1);
    }
    waitpid(pid, NULL, 0);
}

// function to handle commands separated by pipes
void handle_pipes(char** args) {
    char* command1[MAX_ARGS];
    char* command2[MAX_ARGS];
    int i = 0;

    // parse the first command before the pipe.
    while (args[i] != NULL && strcmp(args[i], "|") != 0) {
        command1[i] = args[i];
        i++;
    }
    command1[i] = NULL;
    if (args[i] == NULL) {
        launch_process(command1, STDIN_FILENO, STDOUT_FILENO);
    } else {
        int pipefd[2];
        pipe(pipefd);
        launch_process(command1, STDIN_FILENO, pipefd[1]);
        close(pipefd[1]);
        int j = 0;

        // after the pipe, parse the second command.
        while (args[i + j + 1] != NULL) {
            command2[j] = args[i + j + 1];
            j++;
        }
        command2[j] = NULL;
        launch_process(command2, pipefd[0], STDOUT_FILENO);
        close(pipefd[0]);
    }
}

// function to find a built-in command based on its name
builtin_func_t find_builtin(char* name) {
    for (int i = 0; builtins[i].name != NULL; i++) {
        if (strcmp(name, builtins[i].name) == 0) {
            return builtins[i].func;
        }
    }
    return NULL;
}

// function to execute a built-in command.
void execute_builtin(char** args) {
    builtin_func_t func = find_builtin(args[0]);
    if (func == NULL) {
        printf("mini-shell: command not found: %s\n", args[0]);
        return;
    }
    func(args);
}

// function to execute an external command.
void execute_command(char** args) {
    pid_t pid = fork();
    if (pid == 0) {
        execvp(args[0], args);  // execute the command
        perror("execvp");
        exit(1);
    } else if (pid < 0) {
        perror("fork");
        exit(1);
    }
    waitpid(pid, NULL, 0);  // wait for the child process to complete.
}

// built in commands implementations.
void exit_shell(char** args) {
    exit(0);
}

// open README.md
void editsummary(char** args) {
    system("nano README.md");
}

void change_directory(char** args) {
    if (args[1] == NULL) {
        chdir(getenv("HOME"));
    } else {
        chdir(args[1]);
    }
}

void print_help(char** args) {
    printf("mini-shell built-in commands: \n");
    for (int i = 0; builtins[i].name != NULL; i++) {
        printf(" %s\n", builtins[i].name);
    }
}


void guessinggame() {
    int number;
    int guess;
    int num_guesses = 0;
    time_t start_time;
    time_t end_time;

    srand(time(NULL));
    number = rand() % 5 + 1;

    printf("I am thinking of a number between 1 and 5. Can you guess what it is? \n");
    start_time = time(NULL);

    while (num_guesses < 3) {
        printf("Enter your guess: ");
        scanf("%d", &guess);
        num_guesses++;

        if (guess == number) {
            printf("Congratulations!! You guessed the number in %d guesses.\n", num_guesses);
            break;
        } else {
            printf("Sorry!!! that's not the number i am thinking of. PLZ try again!!\n");
        }
    }

    if (num_guesses == 3) {
        printf("Sorry!! you did not guess the number in time. the number is %d.\n", number);
    }

    end_time = time(NULL);

    printf("you took %ld seconds to guess the number.\n", end_time - start_time);
}



int main() {
    char buffer[BUFFER_SIZE];
    char* args[MAX_ARGS];
    signal(SIGINT, signal_handler);

    while(1) {
        print_prompt();
        if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
            break;
        }
        int num_args = read_command(buffer, args);
        if (num_args == 0) {
            continue;
        }
        if (find_builtin(args[0])!= NULL) {
            execute_builtin(args);
        } else if (strcmp(args[0], "|") == 0) {
            printf("mini-shell: syntax error: unexpected '|'\n");
        } else {
            handle_pipes(args);
        }
    }
    printf("\n");

    return 0;
}
