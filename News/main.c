#include "news.h"
#include "user.h"
#include <stdio.h>
#include <stdlib.h>

// 打印一条分隔线，增强界面美观
void printLine(char c, int length)
{
    for (int i = 0; i < length; i++)
    {
        printf("%c", c);
    }
    printf("\n");
}

// 打印主菜单
void printMenu(User *currentUser)
{
    printLine('-', 50);
    printf("Welcome to the compus news release system\n");

    // 根据用户角色打印不同的菜单
    if (currentUser->role == ADMIN)
    {
        printf("[ADMIN] Please select the operation:\n");
        printf("1. Manage the news\n");
        printf("2. Manage users\n");
        printf("3. Query the news\n");
        printf("4. Quit\n");
    }
    else if (currentUser->role == USER)
    {
        printf("[USER] Please select the operation:\n");
        printf("1. Browse the news\n");
        printf("2. Comment on the news\n");
        printf("3. Query the news\n");
        printf("4. Add the news.\n");
        printf("5. Quit\n");
    }
    else
    {
        printf("[GUEST] Please select the operation:\n");
        printf("1. Browse the news\n");
        printf("2. Quit\n");
    }

    printf("Please enter your choice: ");
}

// 处理用户输入并调用相应功能
void handleUserChoice(int choice, User *currentUser, News **news, User **users)
{
    switch (choice)
    {
    case 1:
        if (currentUser->role == ADMIN)
        {
            // 管理员管理新闻
            manageNews(news, currentUser);
        }
        else if (currentUser->role == USER)
        {
            // 普通用户浏览新闻
            browseNews(*news);
        }
        else
        {
            // 访客浏览新闻
            browseNews(*news);
        }
        break;

    case 2:
        if (currentUser->role == ADMIN)
        {
            // 管理员管理用户
            manageUsers(users, currentUser);
        }
        else if (currentUser->role == USER)
        {
            // 普通用户评论新闻
            commentNews(*news, currentUser);
        }
        else
        {
            // 退出
            printf("Exit the system...\n");
            saveNewsToFile(*news, "news.txt");
            saveUsersToFile(*users, "users.txt");
            exit(0);
        }
        break;

    case 3:
        if (currentUser->role == ADMIN)
        {
            // 管理员查询新闻
            queryNews(*news);
        }
        else if (currentUser->role == USER)
        {
            // 普通用户查询新闻
            queryNews(*news);
        }
        else
        {
            // 退出
            printf("Exit the system...\n");
            saveNewsToFile(*news, "news.txt");
            saveUsersToFile(*users, "users.txt");
            exit(0);
        }
        break;

    case 4:
        if (currentUser->role != GUEST && currentUser->role != USER)
        {
            printf("Exit the system...\n");
            saveNewsToFile(*news, "news.txt");
            saveUsersToFile(*users, "users.txt");
            exit(0);
        }
        else if (currentUser->role == USER)
        {
            // 普通用户增加新闻
            manageNews(news, currentUser);
        }
        break;
    case 5:
        break;

    default:
        printf("Invalid selection, please select again!\n");
        break;
    }
}

int main()
{
    // 加载新闻和用户数据
    News *news = loadNewsFromFile("news.txt");
    User *users = loadUsersFromFile("users.txt");

    // 用户登录
    User *currentUser = login(users);
    if (currentUser == NULL)
    {
        printf("Login failed, and the program ended.\n");
        return 0;
    }

    int choice;
    while (1)
    {
        // 打印交互菜单
        printMenu(currentUser);

        // 获取用户输入
        int validInput = scanf("%d", &choice);
        getchar(); // 吸收多余的换行符

        // 判断输入是否合法
        if (validInput != 1)
        {
            printf("Please enter a valid number option\n");
            continue;
        }

        // 处理用户的选择
        handleUserChoice(choice, currentUser, &news, &users);
    }

    // 程序退出时保存数据
    saveNewsToFile(news, "news.txt");
    saveUsersToFile(users, "users.txt");

    return 0;
}
