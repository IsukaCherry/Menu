#include <stdio.h>
#include "../logiAndRegister/LoginRegister.h"
#include "../entity/struct.h"
#include <stdlib.h>
#include <string.h>
#include <windows.h>
extern Word wordbook[10000];

int ReadWordBook(char* fname,Word wordbook[])
{
    FILE *fp;
    int i=0;
    fp=fopen(fname,"r");
    if(!fp)
    {
        printf("There is no files to read\n");
        return 0;
    }
    while(!feof(fp))//文件位置指针未到结束标志
    {
        fscanf(fp,"%s %s %s",wordbook[i].word,wordbook[i].partOfSpeech,wordbook[i].meaning);//注意格式
        i++;
    }
    fclose(fp);
    return i-1; //因为文件写入时输入格式里的换行会写入文件，最后一条记录后面会有一个空行
}

void AddWord()
{
    char filename[MAX]="D:/ClionProject/Project/WordList/wordbook.txt";
    int WordCount=ReadWordBook(filename, wordbook);
    char word[MAX], partOfSpeech[MAX],meaning[MAX];
    int Number;
    printf("请输入你想添加的单词数:");
    scanf("%d",&Number);
    for (int i = WordCount; i < WordCount+Number; i++)
    {
        printf("请输入单词的英文:");
        scanf("%s",word);

        printf("请输入词性:");
        scanf("%s", partOfSpeech);

        printf("请输入解释");
        scanf(" %[^\n]", meaning);
        strcpy(wordbook[i].word, word);
        strcpy(wordbook[i].partOfSpeech, partOfSpeech);
        strcpy(wordbook[i].meaning,meaning );
        FILE *fp = fopen("D:/ClionProject/Project/WordList/wordbook.txt", "a");
        if (!fp)
        {
            printf("Error opening file for writing.\n");
        }
        // 写入用户数据到文件
        fprintf(fp, "%s %s %s \n", word, partOfSpeech, meaning);
        fclose(fp);
        printf("Add successfully.\n");
    }
}

void DeleteWord()
{
    int temp=0;
    char filename[MAX]="D:/ClionProject/Project/WordList/wordbook.txt";
    char Delete[MAX];
    int WordCount=ReadWordBook(filename, wordbook);
    printf("请输入你想删除的单词");
    scanf("%s", Delete);
    for (int i = 0; i < WordCount; i++)
    {
        if (strcmp(wordbook[i].word, Delete)==0)
        {
            temp=1;
            for (int j = i; j < WordCount - 1; j++)
            {
                strcpy(wordbook[j].word,wordbook[j + 1].word);
                strcpy(wordbook[j].partOfSpeech,wordbook[j + 1].partOfSpeech);
                strcpy(wordbook[j].meaning,wordbook[j + 1].meaning);
            }
            WordCount--;
            break;
        }
    }
    if (temp==1) {
        printf("删除成功");
    }
    else {
        printf("没找到这个单词");
    }
    FILE *fp = fopen("D:/ClionProject/Project/WordList/wordbook.txt", "w");
    for (int i = 0; i < WordCount; i++) {
        fprintf(fp, "%s %s %s\n", wordbook[i].word, wordbook[i].partOfSpeech, wordbook[i].meaning);
    }
    fclose(fp);
}

void ModifyWord()
{
    int temp=0;
    char filename[MAX]="D:/ClionProject/Project/WordList/wordbook.txt";
    char Modify[MAX], Word[MAX],Character[MAX];
    int WordCount=ReadWordBook(filename, wordbook);
    printf("请输入你想修改的单词部分及修改后的内容\n");
    printf("例如:输入 apple noun verb,就会将apple的词性改为verb\n");
    printf("又或者:输入 apple 苹果 梨子,就会将apple的中文释义改为梨子\n");
    scanf("%s %s %s",Word, Character, Modify);
    for (int i = 0; i < WordCount; i++)
    {
        if (strcmp(wordbook[i].word, Word)==0)
        {
            temp=1;
            if (strcmp(wordbook[i].partOfSpeech, Character)==0)
            {
                strcpy(wordbook[i].partOfSpeech, Modify);
                break;
            }
            else if (strcmp(wordbook[i].meaning, Character)==0)
            {
                strcpy(wordbook[i].meaning,Modify);
                break;
            }
            else {
                printf("输入错误！");
                return;
            }
        }
    }
    if (temp==1) {
        printf("修改成功");
    }
    else {
        printf("没找到这个单词");
    }
    FILE *fp = fopen("D:/ClionProject/Project/WordList/wordbook.txt", "w");
    for (int i = 0; i < WordCount; i++) {
        fprintf(fp, "%s %s %s \n", wordbook[i].word, wordbook[i].partOfSpeech, wordbook[i].meaning);
    }
    fclose(fp);
}

void AddMeaning()
{
    int temp1=0;
    char filename[MAX]="D:/ClionProject/Project/WordList/wordbook.txt";
    char Add[MAX], Word[MAX];
    int WordCount=ReadWordBook(filename, wordbook);
    printf("请输入你想补充的单词及释义 ");
    scanf("%s %s",Word, Add);
    int len = strlen(Add);
    char temp[len + 2];
    temp[0] = ',';
    for (int i = 0; i < len; i++) {
        temp[i + 1] = Add[i];
    }
    temp[len + 1] = '\0';
    strcpy(Add, temp);//为补充的意义前添加,
    for (int i = 0; i < WordCount; i++)
    {
        if (strcmp(wordbook[i].word, Word)==0)
        {
            temp1=1;
            strcpy(wordbook[i].meaning,strcat(wordbook[i].meaning, Add));
        }

    }
    if (temp1==1) {
        printf("补充解释成功");
    }
    else
    {
        printf("没有这个单词\n");
    }
    FILE *fp = fopen("D:/ClionProject/Project/WordList/wordbook.txt", "w");
    for (int i = 0; i < WordCount; i++) {
        fprintf(fp, "%s %s %s \n", wordbook[i].word,wordbook[i].partOfSpeech, wordbook[i].meaning);
    }
    fclose(fp);
}

void ViewWords()
{
    char filename[MAX]="D:/ClionProject/Project/WordList/wordbook.txt";
    int WordCount=ReadWordBook(filename, wordbook);
    for(int i=0;i<=WordCount;i++)
        printf("%s %s %s\n",wordbook[i].word, wordbook[i].partOfSpeech, wordbook[i].meaning);
    printf("%s %d %s","共计",WordCount,"个单词");
}
