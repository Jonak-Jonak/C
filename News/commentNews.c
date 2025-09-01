#include "user.h"

void commentNews(News *news, struct User *currentUser)
{
    if (!news)
    {
        printf("Error: News not found.\n");
        return;
    }

    if (currentUser == NULL)
    {
        printf("You must be logged in to comment.\n");
        return;
    }

    char commentText[256];
    printf("Enter your comment (Max 255 characters): ");
    fgets(commentText, sizeof(commentText), stdin);

    // 去除换行符
    commentText[strcspn(commentText, "\n")] = '\0';

    Comment *newComment = (Comment *)malloc(sizeof(Comment));
    if (newComment == NULL)
    {
        printf("Error: Memory allocation failed for comment.\n");
        return;
    }

    strncpy(newComment->text, commentText, sizeof(newComment->text));
    newComment->commenter = currentUser;
    newComment->next = news->comments;
    news->comments = newComment;
    news->commentCount++;

    printf("Your comment has been added successfully!\n");
}
