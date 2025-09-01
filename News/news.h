#ifndef NEWS_H
#define NEWS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// 定义新闻类别枚举
typedef enum
{
    NOTICE = 1,   // 通知
    ANNOUNCEMENT, // 公告
    BRIEF         // 简讯
} NewsCategory;

// 定义评论结构体
typedef struct Comment
{
    char text[1024];        // 评论内容
    struct User *commenter; // 评论者
    struct Comment *next;   // 下一条评论
} Comment;

// 定义新闻结构体
typedef struct News
{
    int id;                // 新闻ID
    NewsCategory category; // 新闻类别
    char title[256];       // 新闻标题
    char content[1024];    // 新闻内容
    char publishDate[20];  // 发布日期 (可以是日期格式，如 "YYYY-MM-DD")
    int viewCount;         // 浏览量
    int commentCount;      // 评论数
    struct User *author;   // 新闻发布者
    char imagePath[200];   // 图片路径
    Comment *comments;     // 新闻评论链表
    struct News *next;     // 下一条新闻

} News;

// 函数声明
News *loadNewsFromFile(const char *filename);                                                 // 从文件加载新闻
void saveNewsToFile(News *news, const char *filename);                                        // 保存新闻到文件
void manageNews(News **news, struct User *currentUser);                                       // 管理新闻（添加、删除、修改）
void browseNews(News *news);                                                                  // 浏览新闻
void queryNews(News *news);                                                                   // 查询新闻
void commentNews(News *news, struct User *currentUser);                                       // 评论新闻
void sortNewsByDate(News *news, int ascending);                                               // 按日期排序新闻
void sortNewsByAuthor(News *news, int ascending);                                             // 按发布人姓名排序新闻
void displayNews(News *news, int showAll);                                                    // 显示新闻
void generatePieChart(const char *chartTitle, int data[], const char *labels[], int numData); // 生成饼图
int parseDate(const char *dateStr, struct tm *tmDate);                                        // 解析时间
#endif                                                                                        // NEWS_H
