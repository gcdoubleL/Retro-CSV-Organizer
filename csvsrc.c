#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
CSVSRC TOOL V.1
READS AND WRITES CSV FILES
COMMAND LINE ARGUMETS
*/

void error_exit(char *string); // Error exit with string to output.
void remove_nline(char *string); // Removes \n from fgets
void get_csv_file(FILE *f); // Get input from user to create entry then output said entry in read_csv.
void read_csv_file(FILE *f); // Output CSV file formatted oldschool.

int main(int argc, char **argv) {
    if (argc < 3)
        error_exit(".\\csvsrc expected arguments: <filename> <option>\nOPTIONS: 1=READ 2=CREATE");

    int mode = atoi(argv[2]);
    char *filename = argv[1];
    FILE *f;
    if (mode == 1) {
        f = fopen(filename, "r");
        read_csv_file(f);
    } else if (mode == 2) {
        f = fopen(filename, "w");
        get_csv_file(f);
    } else {
        error_exit(".\\csvsrc only expects 2 arguments!");

    }

    return 0;
}

void error_exit(char *string) {
    puts(string);
    puts("");
    exit(1);
}

void remove_nline(char *string) {
    if ((strlen(string) > 0) && (string[strlen (string) - 1] == '\n'))
        string[strlen (string) - 1] = '\0';
}

void get_csv_file(FILE *f) {
    char buff[256], c;
    int i, headerNum, entryNum;
    int opt = 1;

    printf("Number Of Headers: ");
    scanf("%d", &headerNum);
    char headers[headerNum][32];

    for (i = 0; i < headerNum; i++) {
        printf("Header #%d Name: ", i);
        scanf("%s", headers[i]);
    }

    for (i = 0; i < headerNum; i++)
        fprintf(f, ",%s", headers[i]);
    fprintf(f, "\n");

    while (opt) {
        printf("\nNew Entry: ");
        scanf("%d", &opt);
        while ((c = getchar()) != '\n' && c != EOF);
        if (!opt) break;

        entryNum++;
        for (i = 0; i < headerNum; i++) {
            printf("%s %d: ", headers[i], entryNum);
            fgets(buff, sizeof(buff), stdin);
            remove_nline(buff);
            fprintf(f, ",%s", buff);
        }
        fprintf(f, "\n");
    }
}

void read_csv_file(FILE *f) {
    char buff[256];
    char *token;

    for (int line = 0; fscanf(f, "%[^\n] ", buff) != EOF; line++) {
        token = strtok(buff, ","); // Splits lines
        printf("%d", line);
        while (token != NULL) {
            printf("\t%-12s\t", token);
            token = strtok(NULL, ",");
        }
        line == 0 ? printf("\n\n\n") : printf("\n\n");
    }
}
