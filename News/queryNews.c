#include "user.h"

void queryNews(News *news)
{
    int id = 0;
    char keyword[256] = "";
    struct tm startDate = {0}, endDate = {0};
    int queryOption, totalNews = 0, inDateRange = 0, matchingKeyword = 0;

    printf("----------- News Query Menu -----------\n");
    printf("1. Query by ID\n2. Query by Keyword\n3. Query by Date Range\n4. Query by ID and Keyword\n5. Query by Keyword and Date Range\n6. Query by ID, Keyword and Date Range\n7. Exit\nEnter your choice: ");
    scanf("%d", &queryOption);

    switch (queryOption)
    {
    case 1:
        // 查询新闻ID
        printf("Enter news ID to search for: ");
        scanf("%d", &id);
        break;

    case 2:
        // 查询关键字
        printf("Enter keyword to search for: ");
        getchar(); // 清除换行符
        fgets(keyword, sizeof(keyword), stdin);
        keyword[strcspn(keyword, "\n")] = 0; // 去除换行符
        break;

    case 3:
        // 查询日期范围
        printf("Enter start date (YYYY-MM-DD): ");
        scanf("%d-%d-%d", &startDate.tm_year, &startDate.tm_mon, &startDate.tm_mday);
        startDate.tm_year -= 1900; // tm_year 从 1900 开始
        startDate.tm_mon -= 1;     // tm_mon 从 0 开始
        startDate.tm_hour = startDate.tm_min = startDate.tm_sec = 0;

        printf("Enter end date (YYYY-MM-DD): ");
        scanf("%d-%d-%d", &endDate.tm_year, &endDate.tm_mon, &endDate.tm_mday);
        endDate.tm_year -= 1900; // tm_year 从 1900 开始
        endDate.tm_mon -= 1;     // tm_mon 从 0 开始
        endDate.tm_hour = endDate.tm_min = endDate.tm_sec = 0;
        break;

    case 4:
        // 查询 ID 和 关键字
        printf("Enter news ID to search for: ");
        scanf("%d", &id);
        printf("Enter keyword to search for: ");
        getchar(); // 清除换行符
        fgets(keyword, sizeof(keyword), stdin);
        keyword[strcspn(keyword, "\n")] = 0; // 去除换行符
        break;

    case 5:
        // 查询 关键字 和 日期范围
        printf("Enter keyword to search for: ");
        getchar(); // 清除换行符
        fgets(keyword, sizeof(keyword), stdin);
        keyword[strcspn(keyword, "\n")] = 0; // 去除换行符

        printf("Enter start date (YYYY-MM-DD): ");
        scanf("%d-%d-%d", &startDate.tm_year, &startDate.tm_mon, &startDate.tm_mday);
        startDate.tm_year -= 1900; // tm_year 从 1900 开始
        startDate.tm_mon -= 1;     // tm_mon 从 0 开始
        startDate.tm_hour = startDate.tm_min = startDate.tm_sec = 0;

        printf("Enter end date (YYYY-MM-DD): ");
        scanf("%d-%d-%d", &endDate.tm_year, &endDate.tm_mon, &endDate.tm_mday);
        endDate.tm_year -= 1900; // tm_year 从 1900 开始
        endDate.tm_mon -= 1;     // tm_mon 从 0 开始
        endDate.tm_hour = endDate.tm_min = endDate.tm_sec = 0;
        break;

    case 6:
        // 查询 ID、关键字 和 日期范围
        printf("Enter news ID to search for: ");
        scanf("%d", &id);

        printf("Enter keyword to search for: ");
        getchar(); // 清除换行符
        fgets(keyword, sizeof(keyword), stdin);
        keyword[strcspn(keyword, "\n")] = 0; // 去除换行符

        printf("Enter start date (YYYY-MM-DD): ");
        scanf("%d-%d-%d", &startDate.tm_year, &startDate.tm_mon, &startDate.tm_mday);
        startDate.tm_year -= 1900; // tm_year 从 1900 开始
        startDate.tm_mon -= 1;     // tm_mon 从 0 开始
        startDate.tm_hour = startDate.tm_min = startDate.tm_sec = 0;

        printf("Enter end date (YYYY-MM-DD): ");
        scanf("%d-%d-%d", &endDate.tm_year, &endDate.tm_mon, &endDate.tm_mday);
        endDate.tm_year -= 1900; // tm_year 从 1900 开始
        endDate.tm_mon -= 1;     // tm_mon 从 0 开始
        endDate.tm_hour = endDate.tm_min = endDate.tm_sec = 0;
        break;

    case 7:
        printf("Exiting query menu.\n");
        return;

    default:
        printf("Invalid option, please try again.\n");
        return;
    }

    // 开始查询新闻
    printf("Querying news...\n");

    while (news)
    {
        int match = 1;

        // 打印当前新闻的 ID，检查 ID 匹配情况
        printf("Checking news ID: %d\n", news->id); // 添加调试信息

        // 根据选定的条件进行查询
        if (id != 0 && news->id != id)
        {
            match = 0; // ID不匹配
        }
        if (strlen(keyword) > 0 && !strstr(news->title, keyword) && !strstr(news->content, keyword))
        {
            match = 0; // 关键字不匹配
        }

        // 检查日期范围
        if (match)
        {
            struct tm tmDate;
            sscanf(news->publishDate, "%d-%d-%d", &tmDate.tm_year, &tmDate.tm_mon, &tmDate.tm_mday);
            tmDate.tm_year -= 1900;
            tmDate.tm_mon -= 1;
            tmDate.tm_hour = tmDate.tm_min = tmDate.tm_sec = 0;

            if ((startDate.tm_year > 0 && difftime(mktime(&tmDate), mktime(&startDate)) < 0) ||
                (endDate.tm_year > 0 && difftime(mktime(&tmDate), mktime(&endDate)) > 0))
            {
                match = 0; // 日期不匹配
            }
        }

        // 如果新闻匹配，则输出相关信息
        if (match)
        {
            totalNews++;
            printf("Found News (ID: %d, Date: %s, Views: %d, Comments: %d):\n",
                   news->id, news->publishDate, news->viewCount, news->commentCount);
            printf("Title: %s\n", news->title);
            printf("Content: %s\n\n", news->content);

            // 统计日期范围和关键字匹配情况
            struct tm tmDate;
            sscanf(news->publishDate, "%d-%d-%d", &tmDate.tm_year, &tmDate.tm_mon, &tmDate.tm_mday);
            tmDate.tm_year -= 1900;
            tmDate.tm_mon -= 1;
            tmDate.tm_hour = tmDate.tm_min = tmDate.tm_sec = 0;

            if ((startDate.tm_year > 0 && difftime(mktime(&tmDate), mktime(&startDate)) >= 0) &&
                (endDate.tm_year > 0 && difftime(mktime(&tmDate), mktime(&endDate)) <= 0))
            {
                inDateRange++;
            }

            if (strstr(news->title, keyword) || strstr(news->content, keyword))
            {
                matchingKeyword++;
            }
        }

        // 更新新闻指针，继续遍历下一条新闻
        news = news->next;
    }

    // 输出查询结果统计
    printf("\nTotal news found: %d\n", totalNews);
    printf("News in date range: %d\n", inDateRange);
    printf("News matching keyword '%s': %d\n", keyword, matchingKeyword);
}
