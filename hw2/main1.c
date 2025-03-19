#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_NUM 69
#define NUM_COUNT 7

// 交換函數 (用於打亂數字)
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 產生一組不重複的樂透號碼
void generate_lotto_numbers(int numbers[]) {
    int pool[MAX_NUM];
    
    // 初始化號碼池 (1~69)
    for (int i = 0; i < MAX_NUM; i++) {
        pool[i] = i + 1;
    }

    // 使用 Fisher-Yates shuffle 演算法隨機選擇 7 個數字
    for (int i = 0; i < NUM_COUNT; i++) {
        int j = rand() % (MAX_NUM - i) + i;
        swap(&pool[i], &pool[j]);
        numbers[i] = pool[i];
    }
}

// 取得當前日期字串
void get_current_date(char *date_str) {
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    strftime(date_str, 20, "%B %d %Y", tm_info); // 格式: "March 19 2025"
}

int main() {
    int n;
    
    // 固定亂數種子為 2025
    srand(2025);

    // 輸入購買樂透組數 (1 <= n <= 5)
    printf("Enter number of lotto sets (1~5): ");
    scanf("%d", &n);
    
    if (n < 1 || n > 5) {
        printf("Invalid input! Please enter a number between 1 and 5.\n");
        return 1;
    }

    // 取得當前日期
    char date_str[20];
    get_current_date(date_str);

    // 開啟 lotto.txt 以寫入模式
    FILE *file = fopen("lotto.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    // 寫入標題與日期
    fprintf(file, "========= lotto649 =========\n");
    fprintf(file, "======== %s ========\n", date_str);

    // 產生並寫入樂透組合
    int numbers[NUM_COUNT];
    for (int i = 0; i < n; i++) {
        generate_lotto_numbers(numbers);

        // 排序 (選擇排序)
        for (int j = 0; j < NUM_COUNT - 1; j++) {
            for (int k = j + 1; k < NUM_COUNT; k++) {
                if (numbers[j] > numbers[k]) {
                    swap(&numbers[j], &numbers[k]);
                }
            }
        }

        // 輸出該組樂透號碼
        fprintf(file, "[%d]: ", i + 1);
        for (int j = 0; j < NUM_COUNT; j++) {
            fprintf(file, "%02d ", numbers[j]);
        }
        fprintf(file, "\n");
    }

    // 如果 n < 5，補上空白行
    for (int i = n; i < 5; i++) {
        fprintf(file, "[%d]: -- -- -- -- -- -- --\n", i + 1);
    }

    // 寫入底部資訊
    fprintf(file, "======== csie@CGU ========\n");

    // 關閉檔案
    fclose(file);
    
    printf("Lotto numbers saved to lotto.txt\n");
    return 0;
}
