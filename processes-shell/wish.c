#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void print_error() {
    char error_message[30] = "An error has occurred\n";
    write(STDERR_FILENO, error_message, strlen(error_message)); 
}

int get_next_word(const char *s, char* buf, int st) {
    int i;

    // get rid of whitespace
    for(i=st; s[i]; i++) if(s[i] != ' ' && s[i] != '\n') break;

    int idx = 0;
    buf[0] = 0;
    for(; s[i]; i++) {
        if(s[i] == ' ' || s[i] == '\n') return i;
        buf[idx++] = s[i];
        buf[idx] = 0;
    } 
    return -1;
}

int builtin_cmd(char *cmd) {
    char buf[128]; 
    int nxt = get_next_word(cmd, buf, 0);

    if(nxt == -1) return 0;

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

void parse_cmd(char *cmd, ssize_t len) {

    if(builtin_cmd(cmd)) return;

    char buf[128]; 
    int nxt = get_next_word(cmd, buf, 0);

    if(nxt == -1) return;
}

int main(int argc, char *argv[]) {

    FILE* input = stdin;
    if(argc == 2) {
        input = fopen(argv[1], "r");
        if(input == NULL) {
            print_error();
            exit(1);
        }
    }
    else if(argc > 2) {
        print_error();
        exit(1);
    }

    while(1) {
        if(input == stdin) {
            printf("wish> ");
        }

        char *line = NULL;
        size_t linecap = 0;
        ssize_t linelen;

        linelen = getline(&line, &linecap, input);
        if(linelen == -1) break;

        parse_cmd(line, linelen);
    }

    return 0;
}