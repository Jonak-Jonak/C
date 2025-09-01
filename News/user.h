#ifndef USER_H
#define USER_H

#include "news.h"

// 用户角色枚举定义
typedef enum
{
    GUEST = 0, // 访客
    USER = 1,  // 普通用户
    ADMIN = 2  // 管理员
} Role;

// 用户结构体定义
typedef struct User
{
    int id;            // 用户ID
    char username[50]; // 用户名
    char password[50]; // 密码
    char name[100];    // 用户真实姓名
    Role role;         // 用户角色
    struct User *next; // 下一个用户（链表结构）
} User;

// 函数声明
User *loadUsersFromFile(const char *filename);
void saveUsersToFile(User *users, const char *filename);
User *login(User *users);
void manageUsers(User **users, User *currentUser);

#endif
