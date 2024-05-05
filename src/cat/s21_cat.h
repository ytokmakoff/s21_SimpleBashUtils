#include <getopt.h>
#include <stdio.h>
#include <unistd.h>
typedef struct arguments {
  int v;
  int b;
  int e;
  int n;
  int s;
  int t;
} arguments;

void output(int argc, char **argv, arguments *arg);
void print_file(FILE *f, arguments *option);
arguments arguments_parser(int argc, char *argv[]);