#include "user.h"

void sortNewsByDate(News *news, int ascending)
{
    if (!news || !news->next)
        return;

    for (News *i = news; i != NULL; i = i->next)
    {
        for (News *j = i->next; j != NULL; j = j->next)
        {
            struct tm tmI = {0}, tmJ = {0};

            sscanf(i->publishDate, "%d-%d-%d", &tmI.tm_year, &tmI.tm_mon, &tmI.tm_mday);
            sscanf(j->publishDate, "%d-%d-%d", &tmJ.tm_year, &tmJ.tm_mon, &tmJ.tm_mday);

            tmI.tm_year -= 1900;
            tmI.tm_mon -= 1;
            tmI.tm_hour = tmI.tm_min = tmI.tm_sec = 0;

            tmJ.tm_year -= 1900;
            tmJ.tm_mon -= 1;
            tmJ.tm_hour = tmJ.tm_min = tmJ.tm_sec = 0;

            int cmp = difftime(mktime(&tmI), mktime(&tmJ)) > 0 ? 1 : -1;

            if (ascending ? cmp > 0 : cmp < 0)
            {
                // 交换指针，而不是结构体内容
                News *temp = i->next;
                i->next = j->next;
                j->next = temp;
            }
        }
    }

    printf("News sorted by date %s\n", ascending ? "ascending" : "descending");
}
