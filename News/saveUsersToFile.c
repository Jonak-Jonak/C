#include "user.h"

void saveUsersToFile(User *users, const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Error opening file %s for writing.\n", filename);
        return;
    }

    while (users)
    {
        // 写入每个用户的信息
        fprintf(file, "%d %s %s %s %d\n",
                users->id,
                users->username,
                users->password,
                users->name,
                users->role);

        users = users->next;
    }

    fclose(file);
    printf("User data saved to %s.\n", filename);
}