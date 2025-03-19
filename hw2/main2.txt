#include <stdio.h>

int main() {
    char filename[] = "main2.c";  // 原始碼檔案名稱
    char outputfile[] = "main2.txt";  // 輸出檔案名稱
    FILE *fp_in, *fp_out;
    char ch;

    // 開啟原始碼檔案 (讀取模式)
    fp_in = fopen(filename, "r");
    if (fp_in == NULL) {
        printf("無法開啟 %s\n", filename);
        return 1;
    }

    // 開啟輸出檔案 (寫入模式)
    fp_out = fopen(outputfile, "w");
    if (fp_out == NULL) {
        printf("無法開啟 %s\n", outputfile);
        fclose(fp_in);
        return 1;
    }

    // 逐字讀取原始碼並寫入到 main2.txt
    while ((ch = fgetc(fp_in)) != EOF) {
        fputc(ch, fp_out);
    }

    // 關閉檔案
    fclose(fp_in);
    fclose(fp_out);

    return 0;
}
