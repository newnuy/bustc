#include <stdio.h>
#include <stdbool.h>

#define OUTPUT_FILE_NAME "./no_br_out.txt"

int main(int argc, char **argv)
{
    FILE *fp_src, *fp_des;
    int ch, ch_2;
    bool in_table;
    bool in_code;

    if (argc != 2) {
        printf("error: no input file\n");
        return 1;
    }

    fp_src = fopen(*++argv, "r");
    if (fp_src == NULL) {
        printf("error: open input file fail\n");
        return 1;
    }

    fp_des = fopen(OUTPUT_FILE_NAME, "w");
    if (fp_des == NULL) {
        printf("error: open output file fail\n");
        fclose(fp_src);
        return 1;
    }

    in_table = false;
    in_code = false;
    while ((ch = fgetc(fp_src)) != EOF) {
        if (in_code || !(in_table && ch == '\n'))
            fputc(ch, fp_des);
        if (ch == '[') {
            ch = fgetc(fp_src);
            if (in_code || !(in_table && ch == '\n'))
                fputc(ch, fp_des);
            if (ch == 'c') {
                if ((ch = fgetc(fp_src)) == 'o' && fputc(ch, fp_des)
                        && (ch = fgetc(fp_src)) == 'd' && fputc(ch, fp_des)
                        && (ch = fgetc(fp_src)) == 'e' && fputc(ch, fp_des)
                        && (ch = fgetc(fp_src)) == ']' && fputc(ch, fp_des))
                    in_code = true;
                else
                    fputc(ch, fp_des);
            }
            else if (ch == 't') {
                if ((ch = fgetc(fp_src)) == 'a' && fputc(ch, fp_des)
                        && (ch = fgetc(fp_src)) == ']' && fputc(ch, fp_des))
                    in_table = true;
                else
                    fputc(ch, fp_des);
            }
            else if (ch == '/') {
                ch = fgetc(fp_src);
                if (in_code || !(in_table && ch == '\n'))
                    fputc(ch, fp_des);
                if (ch == 'c') {
                    if ((ch = fgetc(fp_src)) == 'o' && fputc(ch, fp_des)
                            && (ch = fgetc(fp_src)) == 'd' && fputc(ch, fp_des)
                            && (ch = fgetc(fp_src)) == 'e' && fputc(ch, fp_des)
                            && (ch = fgetc(fp_src)) == ']' && fputc(ch, fp_des))
                        in_code = false;
                    else
                        fputc(ch, fp_des);
                }
                else if (ch == 't') {
                    if ((ch = fgetc(fp_src)) == 'a' && fputc(ch, fp_des)
                            && (ch = fgetc(fp_src)) == ']' && fputc(ch, fp_des))
                        in_table = false;
                    else
                        fputc(ch, fp_des);
                }
            }
        }
    }

    fclose(fp_src);
    fclose(fp_des);

    return 0;
}
