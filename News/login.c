#include "user.h"
#include <stdio.h>
#include <string.h>

User *login(User *users)
{
    char username[50], password[50];

    // 获取用户输入的用户名和密码，使用fgets避免输入错误
    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0'; // 去除末尾的换行符

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0'; // 去除末尾的换行符

    // 检查用户列表是否为空
    if (users == NULL)
    {
        printf("No users available.\n");
        return NULL;
    }

    // 遍历用户链表并查找匹配的用户
    while (users)
    {
        // 调试输出，检查用户名和密码
        // printf("Checking user: %s with password: %s\n", users->username, users->password);

        if (strcmp(users->username, username) == 0 && strcmp(users->password, password) == 0)
        {
            printf("Login successful. Welcome, %s!\n", users->name);
            return users;
        }
        users = users->next;
    }

    printf("Invalid username or password. Please try again.\n");
    return NULL;
}
