#include <stdio.h>
#include <string.h>

int main() {
    char filename[] = "main3.c";  // 要讀取的檔案
    FILE *fp;
    char line[256];  // 存放讀取的每一行
    int line_number = 0;  // 計算行號

    // 開啟檔案
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("無法開啟 %s\n", filename);
        return 1;
    }

    // 逐行讀取檔案內容
    while (fgets(line, sizeof(line), fp) != NULL) {
        line_number++;

        // 檢查是否包含 "int main(" (忽略前面空白)
        char *trimmed_line = line;
        while (*trimmed_line == ' ' || *trimmed_line == '\t') {
            trimmed_line++;  // 跳過空白與 tab
        }

        if (strncmp(trimmed_line, "int main(", 9) == 0) {
            printf("main 函式位於第 %d 行\n", line_number);
            break;
        }
    }

    // 關閉檔案
    fclose(fp);

    return 0;
}
