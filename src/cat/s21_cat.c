#include "s21_cat.h"

int main(int argc, char *argv[]) {
    arguments arg = arguments_parser(argc, argv);
    output(argc, argv, &arg);
    return 0;
}

void output(int argc, char **argv, arguments *arg) {
    for (int i = optind; i < argc; i++) {
        FILE *f = fopen(argv[i], "r");
        if (f != NULL)
            print_file(f, arg);
        else
            printf("no such file");
    }
}

arguments arguments_parser(int argc, char *argv[]) {
    int opt = 0;
    arguments arg = {0};
    struct option long_options[] = {{"number",          0, 0, 'n'},
                                    {"number-nonblank", 0, 0, 'b'},
                                    {"squeeze-blank",   0, 0, 's'},
                                    {0,                 0, 0, 0}};

    while ((opt = getopt_long(argc, argv, "benstvTE", long_options, 0)) != -1) {
        switch (opt) {
            case 'b':
                arg.b = 1;
                break;
            case 'e':
                arg.e = 1;
                arg.v = 1;
                break;
            case 'n':
                arg.n = 1;
                break;
            case 's':
                arg.s = 1;
                break;
            case 't':
                arg.t = 1;
                arg.v = 1;
                break;
            case 'v':
                arg.v = 1;
                break;
            case 'T':
                arg.t = 1;
                break;
            case 'E':
                arg.e = 1;
                break;
            default:
                printf("cat: illegal option -- %s\nusage: cat [-belnstuv] [file ...]",
                       argv[optind]);
                break;
        }
    }
    if (arg.n == 1 && arg.b == 1) {
        arg.n = 0;
    }
    return arg;
}

void print_file(FILE *f, arguments *option) {
    int line_counter = 0;
    int sflag = 0;
    int bflag = 0;
    int nflag = 0;
    int eflag = 0;
    int ch;
    while ((ch = fgetc(f)) != EOF) {
        if (option->s == 1) {
            if (ch == '\n') {
                sflag++;
                if (sflag >= 2) {
                    continue;
                }
            } else {
                sflag = -1;
            }
        }
        if (option->b == 1) {
            if (ch != '\n') {
                if (bflag == 0) {
                    line_counter++;
                    printf("%6d\t", line_counter);
                    bflag = 1;
                }
            } else {
                bflag = 0;
            }
        }
        if (option->n == 1) {
            if (nflag == 0) {
                line_counter++;
                printf("%6d\t", line_counter);
                nflag = 1;
            }
            if (ch == '\n') nflag = 0;
        }
        if (option->e == 1) {
            if (ch == '\n') {
                if (eflag == 0 && option->b == 1) printf("      \t");
                putchar('$');
                eflag = 0;
            } else
                eflag = 1;
        }
        if (option->t == 1) {
            if (ch == '\t') {
                printf("^I");
                continue;
            }
        }
        if (option->v == 1) {
            if ((ch <= 31 || ch == 127) && (ch != '\n' && ch != '\t')) {
                if (ch == 127)
                    printf("^?");
                else
                    printf("^%c", ch + 64);
                continue;
            }
        }
        putchar(ch);
    }
    fclose(f);
}