#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if(argc == 1) {
        printf("wunzip: file1 [file2 ...]\n");
        exit(1);
    }

    FILE *out = stdout;

    for(int i=1; i<argc; i++) {
        FILE *f = fopen(argv[i], "r");
        if(f == NULL) {
            printf("wunzip: cannot open file\n");
            exit(1);
        }

        char buf[5000000];
        size_t n = fread((void*)buf, 5, 1000000, f);

        for(int j=0; j<n; j++) {
        // mac use little-endian
            int cnt = (int)buf[5*j] + ((int)buf[5*j+1] << 8) + ((int)buf[5*j+2] << 16)  + ((int)buf[5*j+3] << 24);
            for(int k=0; k<cnt; k++) fwrite(buf+5*j+4, 1, 1, out);
        }
    }
}