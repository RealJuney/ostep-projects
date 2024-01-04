#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void print_error() {
    char error_message[30] = "An error has occurred\n";
    write(STDERR_FILENO, error_message, strlen(error_message)); 
}

int builtin_cmd(char *cmd) {
    char buf[128]; 

    if(strcmp(buf, "exit") == 0) {
        exit(0);
    }
    else if(strcmp(buf, "cd") == 0) {
        return 1;
    }
    else if(strcmp(buf, "path") == 0) {
        printf("you did path!\n");
        return 1;
    }

    return 0;
}

// execute the first-occuring commend of argv
// returns the end position of the first-ocurring command of argv
char** execute(char *argv[]) {
}

void parse_cmd(char *cmd) {
    // tokenize
    int argc = 0;
    char *argv[1024];
    char **ap;
    for (ap = argv; (*ap = strsep(&cmd, " \t")) != NULL;) {
        if (**ap != '\0') {
            argc++;
            if(++ap >= &argv[1024]) {
                print_error();
                return;
            }
        }
    }

    ap = argv;
    while (ap = execute(ap) != NULL);
}

int main(int argc, char *argv[]) {

    FILE* input = stdin;
    if (argc == 2) {
        input = fopen(argv[1], "r");
        if(input == NULL) {
            print_error();
            exit(1);
        }
    }
    else if (argc > 2) {
        print_error();
        exit(1);
    }

    while (1) {
        if (input == stdin) {
            printf("wish> ");
        }

        char *line = NULL;
        size_t linecap = 0;
        ssize_t linelen;

        linelen = getline(&line, &linecap, input);
        if (linelen == -1) break;

        parse_cmd(line);
    }

    return 0;
}