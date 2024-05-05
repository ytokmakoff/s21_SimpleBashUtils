#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void output_line(char *line, int n);

typedef struct arguments {
  int e, i, v, c, l, n, h, s, f, o;
  char pattern[1024];
  int len_pattern;
  int file_count;
} arguments;
