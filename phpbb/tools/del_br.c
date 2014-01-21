#include <stdio.h>
#include <stdbool.h>

#define OUTPUT_FILE_NAME "./no_br_out.txt"

int main(int argc, char **argv)
{
    FILE *fp_src, *fp_des;
    int ch, ch_2;
    bool in_table;

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
    while ((ch = fgetc(fp_src)) != EOF) {
        if (!(in_table == true && ch == '\n'))
            fputc(ch, fp_des);
        if (ch == '[') {
            if ((ch_2 = ch = fgetc(fp_src)) == 't' && fputc(ch, fp_des)
                    && (ch = fgetc(fp_src)) == 'a' && fputc(ch, fp_des)
                    && (ch = fgetc(fp_src)) == ']' && fputc(ch, fp_des))
                in_table = true;
            else
                fputc(ch, fp_des);
            if (ch_2 == '/') {
                if ((ch = fgetc(fp_src)) == 't' && fputc(ch, fp_des)
                        && (ch = fgetc(fp_src)) == 'a' && fputc(ch, fp_des)
                        && (ch = fgetc(fp_src)) == ']' && fputc(ch, fp_des))
                    in_table = false;
                else
                    fputc(ch, fp_des);
            }
        }
    }

    fclose(fp_src);
    fclose(fp_des);

    return 0;
}
