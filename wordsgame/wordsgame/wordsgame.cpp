#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_WORDS 100
#define MAX_LENGTH 50

char englishWords[MAX_WORDS][MAX_LENGTH];
char chineseWords[MAX_WORDS][MAX_LENGTH];

void readWordsFromFile() {
    FILE* fp;
    char word[MAX_LENGTH], meaning[MAX_LENGTH];

    fp = fopen("c:\\words.txt", "r");
    if (fp == NULL) {
        printf("无法打开文件\n");
        return;
    }

    int index = 0;
    while (fscanf(fp, "%s %s", word, meaning) != EOF) {
        strcpy(englishWords[index], word);
        strcpy(chineseWords[index], meaning);
        index++;
    }
    fclose(fp);
}

// 游戏主逻辑
void playGame() {
    int level = 1, correctCount = 0, totalQuestions = 10, num = 0;
    int currentQuestion = 0;
    srand((unsigned int)time(NULL));

    while (1) {
        if (num == totalQuestions) {
            double accuracy = (double)correctCount / totalQuestions * 100;
            printf("关卡 %d 结束，您的准确率为：%.2f%%\n", level, accuracy);

            if (accuracy > 60.0) {
                level++;
                printf("难度升级！\n");
                if (level == 2) {
                    totalQuestions = 20;
                }
                else if (level == 3) {
                    totalQuestions = 30;
                }
                num = 0;
                correctCount = 0;
                continue;
            }
            else {
                printf("游戏结束\n");
                return;
            }
        }
        currentQuestion = rand() % 201;
        printf("单词：%s\n", englishWords[currentQuestion]);
        printf("[调试demo]答案：%s\n", chineseWords[currentQuestion]);
        char answer[MAX_LENGTH];
        printf("您的回答是：");
        scanf("%s", answer);

        if (strcmp(answer, chineseWords[currentQuestion]) == 0) {
            correctCount++;
            printf("回答正确，加一分\n");
        }
        else {
            printf("回答错误\n");
        }
        num++;
    }
}

int main() {
    printf("=======================================\n");
    printf("\t欢迎进行词汇游戏\n");
    printf("\t随机生成词汇中......\n");
    printf("\t生成完毕！\n");
    printf("\t当前难度，第一关\n");
    printf("=======================================\n");
    readWordsFromFile();
    playGame();

    return 0;
}