#include "user.h"

void generatePieChart(const char *chartTitle, int data[], const char *labels[], int numData)
{
    if (numData == 0)
    {
        printf("Error: No data available to generate chart.\n");
        return;
    }

    int total = 0;
    for (int i = 0; i < numData; i++)
    {
        total += data[i];
    }

    printf("\n%s\n", chartTitle);
    printf("-----------------------------\n");

    if (total == 0)
    {
        printf("Error: Total value is 0, unable to generate chart.\n");
        return;
    }

    for (int i = 0; i < numData; i++)
    {
        int percentage = (data[i] * 100) / total;
        int numStars = percentage / 2; // 每个 * 代表 2% 的比例

        printf("%s: ", labels[i]);
        for (int j = 0; j < numStars; j++)
        {
            printf("*");
        }
        printf(" (%d%%)\n", percentage);
    }

    printf("-----------------------------\n");
    printf("\nChart generation complete.\n");
}
