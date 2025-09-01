#include "user.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void manageNews(News **news, struct User *currentUser)
{
    if (currentUser->role != ADMIN && currentUser->role != USER)
    {
        printf("Permission denied. Only admins can manage news.\n");
        return;
    }
    if (currentUser->role == USER)
    {
        goto addition;
    }
    int choice;
    printf("----------- News Management Menu -----------\n");
    printf("1. Add News\n2. Edit News\n3. Delete News\n4. Exit\nEnter choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        // Add news logic
        {
        addition:
            char title[256], content[1024], imagePath[256];
            int category, id;

            // 获取新闻信息
            printf("Enter news ID: ");
            scanf("%d", &id);
            printf("Enter news title: ");
            getchar(); // 清除缓存的换行符
            fgets(title, sizeof(title), stdin);
            title[strcspn(title, "\n")] = 0; // 去除换行符
            printf("Enter news content: ");
            fgets(content, sizeof(content), stdin);
            content[strcspn(content, "\n")] = 0;
            printf("Enter news image path: ");
            fgets(imagePath, sizeof(imagePath), stdin);
            imagePath[strcspn(imagePath, "\n")] = 0;

            // 获取新闻类别
            printf("Enter news category (0 - NOTICE, 1 - ANNOUNCEMENT, 2 - BRIEF): ");
            scanf("%d", &category);

            // 创建新新闻节点
            News *newNews = (News *)malloc(sizeof(News));
            newNews->id = id;
            newNews->category = (NewsCategory)category;
            strcpy(newNews->title, title);
            strcpy(newNews->content, content);
            newNews->viewCount = 0;
            newNews->commentCount = 0;
            newNews->author = currentUser;
            strcpy(newNews->imagePath, imagePath);
            newNews->comments = NULL;
            newNews->next = *news; // 将新新闻插入到链表头部

            *news = newNews; // 更新新闻链表的头部

            printf("News added successfully!\n");
        }
        break;

    case 2:
        // Edit news logic
        {
            if (currentUser->role == ADMIN)
            {
                int id;
                printf("Enter the news ID to edit: ");
                scanf("%d", &id);

                News *current = *news;
                while (current != NULL)
                {
                    if (current->id == id)
                    {
                        char title[256], content[1024], imagePath[256];

                        // 找到新闻，开始修改
                        printf("Enter new title (current: %s): ", current->title);
                        getchar(); // 清除缓存的换行符
                        fgets(title, sizeof(title), stdin);
                        title[strcspn(title, "\n")] = 0;

                        printf("Enter new content (current: %s): ", current->content);
                        fgets(content, sizeof(content), stdin);
                        content[strcspn(content, "\n")] = 0;

                        printf("Enter new image path (current: %s): ", current->imagePath);
                        fgets(imagePath, sizeof(imagePath), stdin);
                        imagePath[strcspn(imagePath, "\n")] = 0;

                        // 更新新闻（只有在用户输入不为空时才更新）
                        if (strlen(title) > 0)
                        {
                            strcpy(current->title, title);
                        }
                        if (strlen(content) > 0)
                        {
                            strcpy(current->content, content);
                        }
                        if (strlen(imagePath) > 0)
                        {
                            strcpy(current->imagePath, imagePath);
                        }

                        printf("News updated successfully!\n");
                        return;
                    }
                    current = current->next;
                }

                printf("News with ID %d not found.\n", id);
            }
            break;
        }

    case 3:
        // Delete news logic
        {
            if (currentUser->role == ADMIN)
            {
                int id;
                printf("Enter the news ID to delete: ");
                scanf("%d", &id);

                News *current = *news;
                News *previous = NULL;

                // 查找新闻
                while (current != NULL)
                {
                    if (current->id == id)
                    {
                        // 找到新闻，进行删除
                        if (previous == NULL) // 删除的是头节点
                        {
                            *news = current->next;
                        }
                        else
                        {
                            previous->next = current->next;
                        }
                        free(current); // 释放内存
                        printf("News with ID %d deleted successfully!\n", id);
                        return;
                    }
                    previous = current;
                    current = current->next;
                }

                printf("News with ID %d not found.\n", id);
            }
            break;
        }

    case 4:
        printf("Exiting news management menu.\n");
        break;

    default:
        printf("Invalid choice. Please select a valid option.\n");
    }
}
