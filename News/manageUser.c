#include "user.h"

void manageUsers(User **users, User *currentUser)
{
    if (currentUser->role != ADMIN)
    {
        printf("Permission denied. Only admins can manage users.\n");
        return;
    }

    int choice;
    printf("----------- User Management Menu -----------\n");
    printf("1. Add User\n2. Edit User\n3. Delete User\n4. Exit\nEnter choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        // Add user logic
        {
            char username[256], password[256], name[256];
            int role, id;

            // Get user details
            printf("Enter user ID: ");
            scanf("%d", &id);
            printf("Enter username: ");
            getchar(); // Clean up any leftover newline character
            fgets(username, sizeof(username), stdin);
            username[strcspn(username, "\n")] = 0; // Remove newline character
            printf("Enter password: ");
            fgets(password, sizeof(password), stdin);
            password[strcspn(password, "\n")] = 0;
            printf("Enter real name: ");
            fgets(name, sizeof(name), stdin);
            name[strcspn(name, "\n")] = 0;

            // Get user role
            printf("Enter user role (0 - GUEST, 1 - USER, 2 - ADMIN): ");
            scanf("%d", &role);

            // Create a new user node
            User *newUser = (User *)malloc(sizeof(User));
            newUser->id = id;
            strcpy(newUser->username, username);
            strcpy(newUser->password, password);
            strcpy(newUser->name, name);
            newUser->role = (Role)role;
            newUser->next = *users; // Insert the new user at the head of the list

            *users = newUser; // Update the users list

            printf("User added successfully!\n");
        }
        break;

    case 2:
        // Edit user logic
        {
            int id;
            printf("Enter the user ID to edit: ");
            scanf("%d", &id);

            User *current = *users;
            while (current != NULL)
            {
                if (current->id == id)
                {
                    char password[256] = "", name[256] = "";
                    int role;

                    // Found the user, now edit their details
                    printf("Enter new password (current: %s, press Enter to keep): ", current->password);
                    getchar(); // Clean up any leftover newline character
                    fgets(password, sizeof(password), stdin);
                    password[strcspn(password, "\n")] = 0;
                    if (strlen(password) > 0)
                    {
                        strcpy(current->password, password);
                    }

                    printf("Enter new real name (current: %s, press Enter to keep): ", current->name);
                    fgets(name, sizeof(name), stdin);
                    name[strcspn(name, "\n")] = 0;
                    if (strlen(name) > 0)
                    {
                        strcpy(current->name, name);
                    }

                    printf("Enter new role (current: %d, press Enter to keep): ", current->role);
                    char roleInput[10] = "";
                    fgets(roleInput, sizeof(roleInput), stdin);
                    roleInput[strcspn(roleInput, "\n")] = 0;
                    if (strlen(roleInput) > 0)
                    {
                        sscanf(roleInput, "%d", &role);
                        current->role = (Role)role;
                    }

                    printf("User updated successfully!\n");
                    return;
                }
                current = current->next;
            }

            printf("User with ID %d not found.\n", id);
        }
        break;

    case 3:
        // Delete user logic
        {
            int id;
            printf("Enter the user ID to delete: ");
            scanf("%d", &id);

            User *current = *users;
            User *previous = NULL;

            // Find the user
            while (current != NULL)
            {
                if (current->id == id)
                {
                    // Found the user, now delete them
                    if (previous == NULL) // Deleting the head node
                    {
                        *users = current->next;
                    }
                    else
                    {
                        previous->next = current->next;
                    }
                    free(current); // Free the memory
                    printf("User with ID %d deleted successfully!\n", id);
                    return;
                }
                previous = current;
                current = current->next;
            }

            printf("User with ID %d not found.\n", id);
        }
        break;

    case 4:
        printf("Exiting user management menu.\n");
        break;

    default:
        printf("Invalid choice. Please select a valid option.\n");
    }
}
