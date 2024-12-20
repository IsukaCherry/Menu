#include "LoginRegister.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../entity/struct.h"
#include <time.h>
#include "unistd.h"
int ReadTime(char* fname,Time time[]);
int ReadUsersInf(char* filename,User users[]);
int Login();
int RegisterUser();
void DayPlusOne();
void Encourgement();

extern Time LoginTime;
extern Time CurrentTime[100000];
extern User users[MAX];
extern User Logined;
extern int success;
extern int Bianhao;

char TimeLocation[100];
int Login()
{
    char filename[MAX]="D:/ClionProject/Project/Users/users.txt";
    int UserCount=ReadUsersInf(filename, users);
    char username[MAX], password[MAX];
    printf("请输入你的用户名: ");
    scanf("%s", username);
    printf("请输入你的密码: ");
    scanf("%s", password);
    for (int i = 0; i < UserCount; i++)
    {
        if (strcmp(users[i].UsersName, username) == 0 && strcmp(users[i].Password, password) == 0)
        {
            printf("登陆成功,您的信息已录入！\n");
            success = 1;
            Bianhao=i;
            strcpy(Logined.UsersName,users[i].UsersName);
            strcpy(Logined.Password,users[i].Password);
            Logined.score=users[i].score;
            Logined.daysStudied=users[i].daysStudied;
            time_t rawtime;
            struct tm * timeinfo;
            time(&rawtime);
            timeinfo = localtime(&rawtime);
            LoginTime.year = timeinfo->tm_year + 1900;
            LoginTime.month = timeinfo->tm_mon + 1;
            LoginTime.day = timeinfo->tm_mday;
            char str1[]="D:/ClionProject/Project/LoginingTimeList/";
            char str2[]=".txt";
            char temp0[100];
            char temp1[100];
            strcpy(temp1,Logined.UsersName);
            strcat(temp1,str2);
            strcpy(temp0,temp1);
            strcpy(TimeLocation, strcat(str1,temp0));
            FILE *fp = fopen(TimeLocation, "a");
            fprintf(fp, "%d %d %d\n", LoginTime.year,LoginTime.month,LoginTime.day);
            fclose(fp);
            Encourgement();
            return i;
        }
    }
    printf("用户名或密码错误!\n");
    return -1;
}

int RegisterUser()
{
    char filename[MAX]="D:/ClionProject/Project/Users/users.txt";
    int userCount=ReadUsersInf(filename, users);
    char username[MAX], password[MAX];
    printf("请输入你的用户名: ");
    scanf("%s", username);
    printf("请输入你的密码: ");
    scanf("%s", password);
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].UsersName, username)==0)
        {
            printf("该用户名已存在！\n");
            return -1;
        }
    }
    strcpy(users[userCount].UsersName, username);
    strcpy(users[userCount].Password, password);
    users[userCount].score = 0;
    users[userCount].daysStudied = 0;
    FILE *fp = fopen("D:/ClionProject/Project/Users/users.txt", "a");
    if (!fp) {
        printf("Error opening file for writing.\n");
        return -1;
    }
    fprintf(fp, "%s %s %d %d\n", username, password, users[userCount].score, users[userCount].daysStudied);
    fclose(fp);
    printf("注册成功,同时已为你创建错题本.\n");//录入信息
    char str1[]="D:/ClionProject/Project/WrongWordList/";
    char str2[]=".txt";
    char location[100];
    strcpy(location, strcat(str1, strcat(username,str2)));
    FILE *fp1 = fopen(location, "w");
    if (!fp1) {
        return -1;
    }
    char str3[]="D:/ClionProject/Project/LoginingTimeList/";
    char location1[100];
    strcpy(location1, strcat(str3, username));
    FILE *fp2 = fopen(location1, "w");
    if (!fp2) {
        printf("已为你创建登录系统时间表\n");
        return -1;
    }
    return userCount - 1;
}

int ReadUsersInf(char* fname,User Information[])
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
        fscanf(fp,"%s %s %d %d",Information[i].UsersName,Information[i].Password,&Information[i].score,&Information[i].daysStudied);//注意格式
        i++;
    }
    fclose(fp);
    return i-1; //因为文件写入时输入格式里的换行会写入文件，最后一条记录后面会有一个空行
}

//读取时间文件，返回最后一行下标
int ReadTime(char* fname,Time time[])
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
        fscanf(fp,"%d %d %d",&time[i].year,&time[i].month,&time[i].day);//注意格式
        i++;
    }
    fclose(fp);
    return i-2; //因为文件写入时输入格式里的换行会写入文件，最后一条记录后面会有一个空行
}

//退出时打开
void DayPlusOne()
{
    char filename[MAX]="D:/ClionProject/Project/Users/users.txt";
    int UserCount=ReadUsersInf(filename, users);
    int TimeCount=ReadTime(TimeLocation, CurrentTime);
    for (int i = 0; i < UserCount; i++)
    {
        if (!strcmp(users[i].UsersName, Logined.UsersName))
        {
                if (CurrentTime[TimeCount].year !=CurrentTime[TimeCount-1].year || CurrentTime[TimeCount].month
                    !=CurrentTime[TimeCount-1].month || CurrentTime[TimeCount].day !=CurrentTime[TimeCount-1].day)
                {
                    users[i].daysStudied+=1;
                }
        }
    }
    FILE *fp = fopen("D:/ClionProject/Project/Users/users.txt", "w"); // 打开文件以追加模式写入
    for (int i = 0; i < UserCount; i++)
        {
        fprintf(fp,"%s %s %d %d \n",users[i].UsersName,users[i].Password,users[i].score,users[i].daysStudied);
    }
}

void Encourgement()
{
    int count=0;
    int TimeCount=ReadTime(TimeLocation, CurrentTime);
    for (int i = TimeCount; i >0;i--) {
        if (CurrentTime[i].year ==CurrentTime[i-1].year && CurrentTime[i].month ==CurrentTime[i-1].month
            && CurrentTime[i].day ==CurrentTime[i-1].day)
        {
            count++;
        }
        else {
            break;
        }
    }
    srand(time(0));
    printf("你今天已经学习%d次了，真棒！\n请记住:精诚所至,金石为开\n",count);
    int EncourWord=rand() %10 +1;
    switch (EncourWord) {
        case 1:
            printf("你比你想象的更强大，每一次努力都是进步的脚步。\n");
        break;
        case 2:
            printf("没有什么能够阻挡你，只要你不放弃。\n");
        break;
        case 3:
            printf("不要害怕失败，因为每一次失败都是通向成功的一部分。\n");
        break;
        case 4:
            printf("你有无限的潜力，勇敢去追求自己的梦想吧！\n");
        break;
        case 5:
            printf("每一个艰难的时刻，都是你成长的机会。\n");
        break;
        case 6:
            printf("相信自己，你已经做得很好了，继续坚持下去！\n");
        break;
        case 7:
            printf("成功并不遥远，只要你踏实前行，每一步都在向目标靠近。\n");
        break;
        case 8:
            printf("无论前方多么崎岖，你的坚持和努力一定会带来回报。\n");
        break;
        case 9:
            printf("最黑暗的时刻往往是黎明前的那一刻，坚持住，光明就在前方。\n");
        break;
        default:
            printf("你是独一无二的，拥有改变世界的力量，别轻易放弃自己！\n");
    }
}