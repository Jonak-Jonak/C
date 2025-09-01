#include "user.h"

void sortNewsByAuthor(News *news, int ascending)
{
    if (!news || !news->next)
        return;

    for (News *i = news; i != NULL; i = i->next)
    {
        for (News *j = i->next; j != NULL; j = j->next)
        {
            int cmp = strcmp(i->author->name, j->author->name);
            if (ascending ? cmp > 0 : cmp < 0)
            {
                // 交换指针，而不是结构体内容
                News *temp = i->next;
                i->next = j->next;
                j->next = temp;
            }
        }
    }

    printf("News sorted by author %s\n", ascending ? "ascending" : "descending");
}
