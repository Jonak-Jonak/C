#include "user.h"

User *loadUsersFromFile(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        perror("Failed to open users file");
        return NULL;
    }

    User *head = NULL, *tail = NULL;
    while (!feof(file))
    {
        User *user = (User *)malloc(sizeof(User));
        if (fscanf(file, "%d %49s %49s %99s %d", &user->id, user->username, user->password, user->name, (int *)&user->role) == 5)
        {
            user->next = NULL;

            if (tail)
            {
                tail->next = user;
                tail = user;
            }
            else
            {
                head = tail = user;
            }
        }
        else
        {
            free(user);
            break;
        }
    }

    fclose(file);
    return head;
}
