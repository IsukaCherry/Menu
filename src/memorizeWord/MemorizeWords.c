#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../entity/struct.h"
#include "MemorizeWords.h"
#include "../logiAndRegister/LoginRegister.h"

extern User users[100];
extern Word wrongwords[10000];
extern Word wordbook[10000];
extern User Logined;
extern int TotalWords;
extern int Bianhao;
char HelpWord[1000][100]={0};
int assitant=0;
int HighestMark=0;
int Viewtimes=0;
char location[100];
int score=0;

void ViewWrongWords()
{
    char str1[]="D:/ClionProject/Project/WrongWordList/";
    char str2[]=".txt";
    if(Viewtimes==0) {
        char temp0[100];
        char temp1[100];
        strcpy(temp1,Logined.UsersName);
        strcat(temp1,str2);
        strcpy(temp0,temp1);
        strcpy(location, strcat(str1,temp0));
        Viewtimes++;
    }
    int WordCount=ReadWordBook(location, wrongwords);
    if (WordCount==0) {
        printf("你还没有错题!");
        return;
    }
    for(int i=0;i<WordCount;i++)
        printf("%s %s %s \n",wrongwords[i].word, wrongwords[i].partOfSpeech, wrongwords[i].meaning);
}//查看错题本

void StartLearning()
{
    char booklist[MAX]="D:/ClionProject/Project/WordList/wordbook.txt";
    int WordCount=ReadWordBook(booklist, wordbook);
    int ways,mode;
    do
    {
        printf("选择你的提示模式：\n");
        printf("1.提供英文提示\n");
        printf("2.提供中文提示\n");
        printf("0.退出\n");
        printf("请输入你的选项: ");
        scanf("%d", &ways);
        switch(ways)
        {
            case 1:
                assitant=1;
                for(int i=0;i<=WordCount;i++)
                {
                    strcpy(HelpWord[i],wordbook[i].word);
                }
                ways=0;
            break;
            case 2:
                assitant=2;
                for(int i=0;i<=WordCount;i++)
                {
                    strcpy(HelpWord[i],wordbook[i].meaning);
                }
                ways=0;
            break;
            case 0:
                printf("退出选项\n");
                memset(HelpWord, 0, sizeof(HelpWord));
            return;
            default:
                printf("错误选项\n");
        }
        do
        {
            printf("请选择你的学习方式\n");
            printf("1.选择题\n");
            printf("2.填空题\n");
            printf("0.退出\n");
            printf("请输入你的选项: ");
            scanf("%d", &mode);
            switch(mode)
            {
                case 1:
                    FourQuestions();
                mode=0;
                break;
                case 2:
                    SpellWords();
                mode=0;
                break;
                case 0:
                    printf("返回上一步\n");
                break;
                default:
                    printf("Wrong\n");
            }
        }while (mode!=0);
    } while (ways!=0);
}//开始学习菜单,同时录入提示词

void FourQuestions()
{
    char booklist[MAX]="D:/ClionProject/Project/WordList/wordbook.txt";
    int WordCount=ReadWordBook(booklist, wordbook);
    char str1[]="D:/ClionProject/Project/WrongWordList/";
    char str2[]=".txt";
    if(Viewtimes==0) {
        char temp0[100];
        char temp1[100];
        strcpy(temp1,strcat(Logined.UsersName,str2));
        strcpy(temp0,temp1);
        strcpy(location, strcat(str1,temp0));
        Viewtimes++;
    }
    FILE *fp = fopen(location, "a");//以追加模式打开错题本
    int count=ReadWordBook(location, wrongwords);
    int numbers=0;
    do
    {
        printf("请输入你今天想学的单词数");
        scanf("%d",&numbers);
        if(numbers<=0 || numbers>(WordCount/4))
        {
            printf("输入无效，请再输一次！\n");
            continue;
        }
        if (numbers>0 && numbers<=10)
        {
            printf("Emmm，有点少，但我们还是开始吧\n");
            break;
        }
        if (numbers>10 && numbers<=(WordCount/4))
        {
            printf("Wow，你太棒了，我们开始吧\n");
            break;
        }
    }while (!(numbers>0 && numbers<=(WordCount/4)));
    HighestMark+=Logined.score+numbers*10;
    int generatedNumbers[WordCount];
    memset(generatedNumbers, 0, sizeof(generatedNumbers));
    int RandNumbers[numbers][4];
    int i, j, num;
    srand(time(0));
    for (i = 0; i < numbers; i++) {
        for (j = 0; j < 4;)
        {
            num = rand() % (WordCount);
            if (generatedNumbers[num] == 0)
            {
                RandNumbers[i][j] = num;
                generatedNumbers[num] = 1;
                j++;
            }
        }
    }
    for (i = 0; i < numbers; i++)
    {
        char Answer;
        int CorrectAnswer=rand() %4 ;
        if (assitant==1)
        {
            printf("本题的提示词为：%s\n",HelpWord[RandNumbers[i][CorrectAnswer]]);
            printf("A.%s\n",wordbook[RandNumbers[i][0]].meaning);
            printf("B.%s\n",wordbook[RandNumbers[i][1]].meaning);
            printf("C.%s\n",wordbook[RandNumbers[i][2]].meaning);
            printf("D.%s\n",wordbook[RandNumbers[i][3]].meaning);//显示选项
        }
        if (assitant==2)
        {
            printf("本题的提示词为：%s\n",HelpWord[RandNumbers[i][CorrectAnswer]]);
            printf("A.%s\n",wordbook[RandNumbers[i][0]].word);
            printf("B.%s\n",wordbook[RandNumbers[i][1]].word);
            printf("C.%s\n",wordbook[RandNumbers[i][2]].word);
            printf("D.%s\n",wordbook[RandNumbers[i][3]].word);//显示选项
        }
        printf("请输入正确选项\n");
        scanf(" %c",&Answer);
        int select=(int)Answer;
        if (select-65==CorrectAnswer || select-97==CorrectAnswer)
        {
            printf("输入正确，加十分！\n");
            score+=10;//计分+10
        }
        else
        {
            printf("错误!\n正确答案是%s %s %s\n",wordbook[RandNumbers[i][CorrectAnswer]].word,
                wordbook[RandNumbers[i][CorrectAnswer]].partOfSpeech,wordbook[RandNumbers[i][CorrectAnswer]].meaning);
            score-=10;//计分-10
            strcpy(wrongwords[count].word,wordbook[RandNumbers[i][CorrectAnswer]].word);
            strcpy(wrongwords[count].partOfSpeech,wordbook[RandNumbers[i][CorrectAnswer]].partOfSpeech);
            strcpy(wrongwords[count].meaning,wordbook[RandNumbers[i][CorrectAnswer]].meaning);
            fprintf(fp, "%s %s %s\n", wrongwords[count].word, wrongwords[count].partOfSpeech, wrongwords[count].meaning);
            //这边为登录错题本
        }
    }
    fclose(fp);
    if ((score+Logined.score)==HighestMark)
    {
        printf("真棒，你完美的完成了本次背诵！");
    }
    else {
        printf("可惜,你这次有错，错题已经记录下来了，你可以随时复习");
    }
    char filename[MAX]="D:/ClionProject/Project/Users/users.txt";
    int UserCount=ReadUsersInf(filename, users);
    users[Bianhao].score=Logined.score+score;
    FILE *fp1 = fopen("D:/ClionProject/Project/Users/users.txt", "w");
    for (int i = 0; i < UserCount; i++)
    {
        fprintf(fp, "%s %s %d %d\n", users[i].UsersName, users[i].Password, users[i].score, users[i].daysStudied);
    }
    fclose(fp1);
}//选择题

void SpellWords()
{
    char booklist[MAX]="D:/ClionProject/Project/WordList/wordbook.txt";
    int WordCount=ReadWordBook(booklist, wordbook);
    char str1[]="D:/ClionProject/Project/WrongWordList/";
    char str2[]=".txt";
    if(Viewtimes==0) {
        char temp0[100];
        char temp1[100];
        strcpy(temp1,Logined.UsersName);
        strcat(temp1,str2);
        strcpy(temp0,temp1);
        strcpy(location, strcat(str1,temp0));
        Viewtimes++;
    }
    FILE *fp = fopen(location, "a");//以追加模式打开错题本
    int count=ReadWordBook(location, wrongwords);
    int numbers=0;
    do
    {
        printf("请输入你今天想学的单词数");
        scanf("%d",&numbers);
        if(numbers<=0 || numbers>WordCount)
        {
            printf("输入无效，请再输一次！\n");
            continue;
        }
        if (numbers>0 && numbers<=10)
        {
            printf("Emmm，有点少，但我们还是开始吧\n");
            break;
        }
        if (numbers>10 && numbers<=WordCount)
        {
            printf("Wow，你太棒了，我们开始吧\n");
            break;
        }
    }while (!(numbers>0 && numbers<=WordCount));
    HighestMark+=Logined.score+numbers*10;
    int generatedNumbers[WordCount];
    memset(generatedNumbers, 0, sizeof(generatedNumbers));
    int RandNumbers[numbers];
    int i,num;
    srand(time(0));
    for (i = 0; i < numbers; i++)
    {
        num = rand() % (WordCount);
        if (generatedNumbers[num] == 0) \
           {
                RandNumbers[i] = num;
                generatedNumbers[num] = 1;  // 标记该数已经生成
           }
    }
    for (i = 0; i < numbers; i++)
    {
        char Answer[MAX];
        if (assitant==1)
        {
            printf("\n本题的提示词为：%s\n",HelpWord[RandNumbers[i]]);
        }
        if (assitant==2)
        {
            printf("\n本题的提示词为：%s\n",HelpWord[RandNumbers[i]]);
        }
        printf("请输入正确的英文单词:");
        scanf("%s",&Answer);
        if (!strcmp(Answer,wordbook[RandNumbers[i]].word))
        {
            printf("输入正确，加十分！\n");
            score+=10;
        }
        else
        {
            printf("错误!\n正确答案是%s\n",wordbook[RandNumbers[i]].word);
            score-=10;
            strcpy(wrongwords[count].word,wordbook[RandNumbers[i]].word);
            strcpy(wrongwords[count].partOfSpeech,wordbook[RandNumbers[i]].partOfSpeech);
            strcpy(wrongwords[count].meaning,wordbook[RandNumbers[i]].meaning);
            fprintf(fp, "%s %s %s\n", wrongwords[count].word, wrongwords[count].partOfSpeech, wrongwords[count].meaning);
            //这边为登录错题本
        }
    }
    fclose(fp);
    char filename[MAX]="D:/ClionProject/Project/Users/users.txt";
    int UserCount=ReadUsersInf(filename, users);
    users[Bianhao].score=Logined.score+score;
    FILE *fp1 = fopen("D:/ClionProject/Project/Users/users.txt", "w");
    for (int i = 0; i < UserCount; i++)
    {
        fprintf(fp, "%s %s %d %d\n", users[i].UsersName, users[i].Password, users[i].score, users[i].daysStudied);
    }
    fclose(fp1);
}//拼写题

void ReLearnWrongWords()
{
    char str1[]="D:/ClionProject/Project/WrongWordList/";
    char str2[]=".txt";
    if(Viewtimes==0) {
        char temp0[100];
        char temp1[100];
        strcpy(temp1,Logined.UsersName);
        strcat(temp1,str2);
        strcpy(temp0,temp1);
        strcpy(location, strcat(str1,temp0));
        Viewtimes++;
    }
    int WordCount=ReadWordBook(location, wrongwords);
    int list[WordCount]={},number=0;
    if (WordCount==0) {
        printf("你还没有错题需要复习!");
        return;
    }
    printf("你的错题有:\n");
    for(int i=0;i<WordCount;i++)
        printf("%d %s %s %s \n",i+1,wrongwords[i].word, wrongwords[i].partOfSpeech, wrongwords[i].meaning);
    do {
        printf("请问你要选择重背的错题数:\n");
        scanf("%d",&number);
        if (number>WordCount || number<0)
        {
            printf("输入错误，再输入一次吧！\n");
        }
    }while(number>WordCount || number<0);
    int flag=1;
    do {
        for (int j=0;j<WordCount;j++) {
            list[j]='\0';
        }
        if (!flag) {
            printf("输入有效内容\n");
        }
        printf("请问你要选择重背的错题编号:\n");
        printf("ps:如果输了两个一样的编号，答对一题后自动进入下一题\n");
        int temp=0;
        //重置flag
        flag=1;
        for (int i = 0; i < number; ++i) {
            scanf("%d",&temp);
            list[i]=temp-1;
        }
        for (int i=0;i<number;++i) {
            if (list[i]>=WordCount) {
                flag=0;
            }
        }
    } while (!flag);

    printf("我将会把这些词的中英文都给你，请你复习后拼写一遍，这将有助于你掌握词汇:\n");
    for (int i=0;i<number;i++)
    {
        char Answer[MAX];
        printf("%s %s \n",wrongwords[list[i]].word, wrongwords[list[i]].meaning);
        printf("请输入对应的英文:");
        scanf("%s",&Answer);
        if (!strcmp(Answer,wrongwords[list[i]].word))
        {
            printf("你成功掌握了%s这个词！\n",wrongwords[list[i]].word);
            for (int j = 0; j <=WordCount; j++)
            {
                if (!strcmp(wrongwords[j].word, wrongwords[list[i]].word))
                {
                    for (int k = j; k < WordCount - 1; k++)
                    {
                        strcpy(wrongwords[k].word,wrongwords[k + 1].word);
                        strcpy(wrongwords[k].partOfSpeech,wrongwords[k + 1].partOfSpeech);
                        strcpy(wrongwords[k].meaning,wrongwords[k + 1].meaning);
                    }
                    WordCount--;
                    break;
                }
            }
        }
        else
        {
            printf("你仍然有错,再尝试学习一遍吧\n");
        }
    }
    FILE *fp = fopen(location, "w");
    for (int i = 0; i < WordCount; i++) {
        fprintf(fp, "%s %s %s\n", wrongwords[i].word, wrongwords[i].partOfSpeech, wrongwords[i].meaning);
    }
    fclose(fp);
    if (WordCount==0) {
        printf("你掌握了所有的错题!\n");
    }
    else {
        printf("你的剩余的错题有:\n");
    }
    for(int i=0;i<WordCount;i++)
        printf("%d %s %s %s \n",i+1,wrongwords[i].word, wrongwords[i].partOfSpeech, wrongwords[i].meaning);
}

void ScoreManagement()//成绩查看系统
{
    int choice=0;
    if (HighestMark==0)
    {
        printf("你今天还没有学习，请学习后再来吧\n");
        return;
    }
    printf("你的成绩是:%d\n",score);
    if (score+users[Bianhao].score<HighestMark)
    {
        printf("你没能完全掌握，以下是你的错题:\n");
        ViewWrongWords();
        do {
            printf("是否要复习你的错题\n");
            printf("1:复习错题\n");
            printf("0.返回\n");
            printf("请输入你的选项\n");
            scanf("%d",&choice);
            switch (choice) {
                case 1:
                    printf("请问你需要复习你的错题吗?");
                    ReLearnWrongWords();
                    choice=0;
                break;
                case 0:
                    return;
                default:
                    printf("无效选项！\n");
            }
        } while (choice!= 0);
    }
    else
    {
        printf("Wow,你已经全部掌握了今天的单词，继续努力吧");
    }
}