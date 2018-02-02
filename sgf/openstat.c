#include <stdio.h>
#include <dirent.h>
#include <string.h>

#define BUFFER_SIZE 400
int main(int argc, char *argv[]) {
    DIR *dir;
    char buffer[BUFFER_SIZE+1] = {0};
    struct dirent *ent;
    long count = 0;
    long count55 = 0;
    long count44 = 0;
    long count54 = 0;
    FILE *fp;   
    int bufSize;
    char filename[300] = {0};
    dir = opendir(argv[1]);
    while((ent = readdir(dir))) {
        if(strstr(ent->d_name, ".sgf") != NULL) {
            ++count;
            sprintf(filename, "%s/%s", argv[1], ent->d_name);
            fp = fopen(filename, "r");
            bufSize = fread(buffer, 1, BUFFER_SIZE, fp);
            buffer[bufSize] = 0;
            if(strstr(buffer, "B[ee") != NULL) ++count55;

            if(strstr(buffer, "B[fe") != NULL) ++count54;
            if(strstr(buffer, "B[ef") != NULL) ++count54;
            if(strstr(buffer, "B[de") != NULL) ++count54;
            if(strstr(buffer, "B[ed") != NULL) ++count54;

            if(strstr(buffer, "B[ff") != NULL) ++count44;
            if(strstr(buffer, "B[fd") != NULL) ++count44;
            if(strstr(buffer, "B[df") != NULL) ++count44;
            if(strstr(buffer, "B[dd") != NULL) ++count44;
            fclose(fp);
        }
    }
    closedir(dir);

    printf("Total games: %ld\n", count);
    printf("Games with start at 5-5: %ld\n", count55);
    printf("Games with start at 5-4: %ld\n", count54);
    printf("Games with start at 4-4: %ld\n", count44);

    return 0;
}