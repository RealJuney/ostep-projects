#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int search(char* s, char *t) {
    for(int i=0; s[i]; i++) {
        int match = 1;

        for(int j=0; t[j]; j++) {
            if(s[i+j] == 0) break;
            if(s[i+j] != t[j]) {
                match = 0;
                break;
            }
        }

        if(match) return 1;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    if(argc == 1) {
        printf("wgrep: searchterm [file ...]\n");
        exit(1);
    }

    char buf[500];

    if(argc == 2) {
        while(fgets(buf, 500, stdin) != NULL) {
            if(search(buf, argv[1]))
                printf("%s", buf);
        }
    }


    for(int i=2; i<argc; i++) {
        FILE *f = fopen(argv[i], "r");
        if (f == NULL) {
            printf("wgrep: cannot open file\n");
            exit(1);
        }


        while(fgets(buf, 500, f) != NULL) {
            if(search(buf, argv[1]))
                printf("%s", buf);
        }
    }

    return 0;
}