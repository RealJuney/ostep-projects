#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    for(int i=1; i<argc; i++) {
        const char *file_name = argv[i];
        FILE *f = fopen(file_name, "r");

        if (f == NULL) {
            printf("wcat: cannot open file\n");
            exit(1);
        }

        char buff[500];
        while(fgets(buff, 500, f) != NULL) {
            printf("%s", buff);
        }
    }
}