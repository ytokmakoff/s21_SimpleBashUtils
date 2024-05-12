#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void output_line(char *line, int n);
void process_file(arguments arg, char *path, regex_t *reg);
void output_line(char *line, int n);
arguments arguments_parser(int argc, char *argv[]);
void print_match(regex_t *reg, char *line, int v);
void add_reg_from_file(arguments *arg, char *filepath);
void pattern_add(arguments *arg, char *pattern);

typedef struct arguments {
    int e, i, v, c, l, n, h, s, f, o;
    char pattern[1024];
    int len_pattern;
    int file_count;
} arguments;
