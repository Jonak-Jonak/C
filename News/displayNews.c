#include "user.h"

void displayNews(News *news, int showAll)
{
    if (showAll)
    {
        printf("Displaying all news...\n");
        browseNews(news);
    }
    else
    {
        printf("Displaying news summaries (Title and View Count):\n");
        printf("-----------------------------------------------\n");

        if (news == NULL)
        {
            printf("No news available to display.\n");
            return;
        }

        while (news)
        {
            printf("Title: %s, Views: %d\n", news->title, news->viewCount);
            news = news->next;
        }
    }
    printf("\nEnd of news display.\n");
}
