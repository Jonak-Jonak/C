#include "user.h"

News *loadNewsFromFile(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        perror("Failed to open news file");
        return NULL;
    }

    News *head = NULL, *tail = NULL;
    while (!feof(file))
    {
        News *newsItem = (News *)malloc(sizeof(News));
        if (fscanf(file, "%d %d", &newsItem->id, (int *)&newsItem->category) != 2)
        {
            free(newsItem);
            break;
        }

        fscanf(file, " %255[^\n]s", newsItem->title);
        fscanf(file, " %1023[^\n]s", newsItem->content);
        fscanf(file, " %19s", newsItem->publishDate);
        fscanf(file, "%d %d", &newsItem->viewCount, &newsItem->commentCount);
        fscanf(file, " %255[^\n]s", newsItem->imagePath);

        // 读取作者的名字
        char authorName[1024];
        fscanf(file, " %99[^\n]s", authorName);

        // 为新闻项分配作者信息
        newsItem->author = (User *)malloc(sizeof(User));
        snprintf(newsItem->author->name, 1024, "%s", authorName);
        newsItem->author->id = newsItem->id; // 假设作者的ID与新闻ID相同，或者可以调整

        newsItem->comments = NULL;
        newsItem->next = NULL;

        if (tail)
        {
            tail->next = newsItem;
            tail = newsItem;
        }
        else
        {
            head = tail = newsItem;
        }
    }

    fclose(file);
    return head;
}
