#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_SIZE 10
#define MAX_LINE 1024

char** lines;
int count = 0;
int capacity = 0;

void init() {
    lines = malloc(INITIAL_SIZE * sizeof(char*));
    capacity = INITIAL_SIZE;
}

void addLine(char* line) {
    if (count == capacity) {
        capacity = capacity * 2;
        lines = realloc(lines, capacity * sizeof(char*));
        if (lines == NULL) {
            printf("realloc failed\n");
            exit(1);
        }
    }
    lines[count] = malloc(strlen(line) + 1);
    strcpy(lines[count], line);
    count++;
}

void loadFile(char* filename) {
    FILE* f = fopen(filename, "r");
    if (f == NULL) {
        printf("cant open file\n");
        return;
    }

    char buffer[MAX_LINE];
    while (fgets(buffer, MAX_LINE, f) != NULL) {
        int len = strlen(buffer);
        if (buffer[len-1] == '\n')
            buffer[len-1] = '\0';
        addLine(buffer);
    }
    fclose(f);
}

void searchKeyword(char* keyword) {
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strstr(lines[i], keyword) != NULL) {
            printf("line %d: %s\n", i+1, lines[i]);
            found++;
        }
    }
    printf("found %d match(es)\n", found);
}

void filterLines(char* pattern) {
    printf("lines containing '%s':\n", pattern);
    for (int i = 0; i < count; i++) {
        if (strstr(lines[i], pattern) != NULL) {
            printf("%s\n", lines[i]);
        }
    }
}

int countOccurrences(char* keyword) {
    int total = 0;
    for (int i = 0; i < count; i++) {
        char* temp = lines[i];
        while ((temp = strstr(temp, keyword)) != NULL) {
            total++;
            temp++;
        }
    }
    return total;
}

void cleanup() {
    for (int i = 0; i < count; i++) {
        free(lines[i]);
    }
    free(lines);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("usage: ./analyzer <filename>\n");
        return 1;
    }

    init();
    loadFile(argv[1]);

    if (count == 0) {
        printf("file is empty or couldn't be read\n");
        cleanup();
        return 1;
    }

    printf("loaded %d lines\n\n", count);

    printf("search results for 'error':\n");
    searchKeyword("error");

    printf("\nfilter for 'warning':\n");
    filterLines("warning");

    int n = countOccurrences("error");
    printf("\ntotal occurrences of 'error': %d\n", n);

    cleanup();
    return 0;
}
