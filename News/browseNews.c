#include "user.h"

void browseNews(News *news)
{
    if (news == NULL)
    {
        printf("No news available to display.\n");
        return;
    }

    printf("---------- News Browsing ----------\n");

    while (news)
    {
        // 输出调试信息，查看新闻数据是否正确
        printf("DEBUG: Checking news with ID %d\n", news->id);

        printf("\nTitle: %s\n", news->title);
        printf("Category (int value): %d\n", news->category); // 输出整数值帮助调试

        // 确保新闻分类正确输出
        printf("Category: ");
        switch (news->category)
        {
        case NOTICE:
            printf("Notice\n");
            break;
        case ANNOUNCEMENT:
            printf("Announcement\n");
            break;
        case BRIEF:
            printf("Brief\n");
            break;
        default:
            printf("Unknown\n");
            break;
        }

        printf("Published on: %s\n", news->publishDate);
        printf("View Count: %d\n", news->viewCount);
        printf("Comment Count: %d\n", news->commentCount);

        if (news->author)
        {
            printf("Author name: %s\n", news->author->name); // 输出作者名称
            printf("Published by: %s\n", news->author->name);
        }
        else
        {
            printf("Author not available.\n");
        }

        // 确保评论数据正确
        if (news->commentCount > 0)
        {
            printf("Comments available.\n");
        }
        else
        {
            printf("No comments for this news.\n");
        }

        // 检查图片路径
        if (strlen(news->imagePath) > 0)
        {
            printf("Image Path: %s\n", news->imagePath);
        }
        else
        {
            printf("No image associated with this news.\n");
        }

        printf("------------------------------------\n");

        news = news->next;
    }

    printf("Do you want to sort the news?\n");
    printf("If you want to do this, please srlect the sorting method.\n");
    printf("1. By the author in ascending order.\n");
    printf("2. By the author in descending order.\n");
    printf("3. By the Date in ascending order.\n");
    printf("4. By the Date in descending order.\n");
    int chose;
    scanf("%d", &chose);
    switch (chose)
    {
    case 1:
        sortNewsByAuthor(news, 1);
    case 2:
        sortNewsByAuthor(news, 0);
    case 3:
        sortNewsByDate(news, 1);
    case 4:
        sortNewsByDate(news, 0);
    default:
        printf("Invalid order!");
    }
}
