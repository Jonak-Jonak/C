#include "user.h"

void saveNewsToFile(News *news, const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Error opening file %s for writing.\n", filename);
        return;
    }

    while (news)
    {
        // 写入每一条新闻
        fprintf(file, "%d %d\n%s\n%s\n%s\n%d\n%d\n%s\n%s\n",
                news->id,
                news->category,
                news->title,
                news->content,
                news->publishDate,
                news->viewCount,
                news->commentCount,
                news->imagePath,
                news->author ? news->author->username : "Unknown"); // Assuming author's username is sufficient

        // 写入评论（可选）
        Comment *comment = news->comments;
        while (comment)
        {
            fprintf(file, "  COMMENT: %s by %s\n", comment->text, comment->commenter->username);
            comment = comment->next;
        }

        news = news->next;
    }

    fclose(file);
    printf("News data saved to %s.\n", filename);
}
