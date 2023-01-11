#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "functions.h"

int instruction1(char *instruction, char *command, char *t_instruction, char *username, char *password, user_ptr new_user, user_ptr head, user_ptr main_head, char *post, char *post_id, post_ptr new_post, post_ptr head_post_each_user, post_ptr main_head_post_each_user)
{
    char *newCommand = 0;
    char *new_instruction = 0;
    int if_right = 0, login_right = 0, update_signup = 0, update_post = 0;
    user_ptr current_user = 0;
    FILE *accounts;
    FILE *fpost;
    while (1)
    {
        accounts = fopen("account.txt", "w");
        fpost = fopen("posts.txt", "w");
        if (update_signup)
        {
            update_signup_function(main_head, accounts);
            update_signup = 0;
            fclose(accounts);
        }
        if (update_post)
        {
            update_post_function(main_head, fpost);
            update_post = 0;
            fclose(fpost);
        }

        fflush(stdin);
        login_right = 0;
        new_user = (user_ptr)malloc(sizeof(users));
        if (new_user == NULL)
        {
            printf("not allocating memory\n");
            exit(EXIT_FAILURE);
        }
        fflush(stdin);

        printf("what do you want to do?\n");
        myIn(&instruction);
        if (strchr(instruction, ' ') == NULL)
        {
            printf("the input is not valid.please try again.press any key to continue \n");
            if (getchar())
            {
                system("cls");
                continue;
            }
        }
        find_instruction(&command, &instruction);

        if ((strcmp(command, "login") == 0))
        {
            find_username_password(&instruction, &password, &username);
            if (login(&instruction, main_head, &password, &username, &current_user) == 0)
            {

                login_right = 1;
                printf("you are in your account !.press any key to continue\n");
                if (getchar())
                {
                    system("cls");
                }
            }
            else
            {
                printf("login is not successful.press any key to continue\n");
                if (getchar())
                {
                    system("cls");
                    continue;
                }
            }

            while (login_right)
            {
                fflush(stdin);
                if (update_signup)
                {
                    update_signup_function(main_head, accounts);
                    update_signup = 0;
                    fclose(accounts);
                }
                if (update_post)
                {
                    update_post_function(main_head, fpost);
                    update_post = 0;
                    fclose(fpost);
                }
                printf("what do you wish to do in your account?\n");
                myIn(&new_instruction);
                fflush(stdin);
                if (strchr(new_instruction, ' ') == NULL)
                {
                    printf("the input is not valid.please try again.press any key to continue \n");
                    if (getchar())
                    {
                        system("cls");
                        continue;
                    }
                }
                find_instruction(&newCommand, &new_instruction);
                fflush(stdin);
                if (strcmp(newCommand, "delete") == 0)
                {
                    find_delete_id(&new_instruction, &post_id);
                    printf("%s", post_id);
                    int success= delete_post(current_user, &post_id);
                    if (success== 0)
                    {
                        update_post = 1;
                        printf("your post was deleted successfully.press any key to continue:\n");
                        if (getchar())
                        {
                            system("cls");
                            continue;
                        }
                    }
                    else
                    {
                        printf("your input was not valid.press any key to continue:\n");
                        if (getchar())
                        {
                            system("cls");
                            continue;
                        }
                    }
\
                }

                else if (strcmp(newCommand, "like") == 0)
                {
                    find_username_post_id(&new_instruction, &post_id, &username);
                    int success= like_post(&username, &post_id, current_user, main_head);
                    if (success== 0)
                    {
                        printf("like is successful\n");
                        update_post = 1;
                        continue;
                    }
                    else
                    {
                        printf("like is not sucessful\n");
                        continue;
                    }

                }
                else if (strcmp(newCommand, "info") == 0)
                {

                    if (info(current_user) == 0)
                    {
                        printf("your info have show successfully.press any key to contonue;\n");
                        if (getchar())
                        {
                            system("cls");
                            continue;
                        }
                    }
                    else
                    {
                        printf("showing info was unsuccessful.press any key to continue:\n");
                        if (getchar())
                        {
                            system("cls");
                            continue;
                        }
                    }
                }
                else if (strcmp(newCommand, "find_user") == 0)
                {
                    find_user_id(&new_instruction, &username);
                    int success = find_user(&username, main_head);
                    if (success == 0)
                    {
                        printf("searching user is successful.press any key to continue\n");
                        if (getchar())
                        {
                            system("cls");
                            continue;
                        }
                    }
                    else
                    {
                        printf("searching user was not succssfull.press any key to continue\n");
                        if (getchar())
                        {
                            system("cls");
                            continue;
                        }
                    }
                }
                else if (strcmp(newCommand, "post") == 0)
                {
                    get_post(&new_instruction, &post);
                    new_post = (post_ptr)malloc(sizeof(posts));
                    if (new_post == NULL)
                    {
                        printf("not allocating memory\n");
                        exit(EXIT_FAILURE);
                    }
                    int success = add_post(current_user, &post, new_post, &head_post_each_user);
                    printf("%s", new_post->post);
                    if (success == 0)
                    {

                        printf("you succesfully posted.press any key to continue\n");
                        update_post = 1;
                        update_signup = 1;
                        if (getchar())
                        {
                            
                            system("cls");
                            continue;
                        }
                    }
                    else
                    {
                        printf("posting is not successful.press any key to continue\n");
                        if (getchar())
                        {
                            system("cls");
                            continue;
                        }
                    }
                }
                else if (strcmp(newCommand, "logout") == 0)
                {
                    printf("you succesfully logged out.press any key to continue\n");
                    if (getchar())
                    {
                        system("cls");
                        break;
                    }
                }
                else
                {
                    printf("the input is not valid.please try again.press any key to continue \n");
                    if (getchar())
                    {

                        system("cls");
                        continue;
                    }
                }
            }
        }
        else if (strcmp(command, "signup") == 0)

        {
            if (new_user == NULL)
            {
                printf("not allocating memory\n");
                exit(EXIT_FAILURE);
            }
            find_username_password(&instruction, &password, &username);
            if (username[0] == '\0' || password[0] == '\0' || password[0] == '\n' || username[0] == '\n' || password[0] == ' ' || username[0] == ' ')
            {
                printf("the input is not valid.press any key to continue\n");
                if (getchar())
                {

                    system("cls");
                    continue;
                }
            }
            if (signup(&head, new_user, &password, &username, main_head, &instruction) == 0)
            {
                printf("you succussefully signed in,press any key to continoue:\n");
                update_signup = 1;
            
                if (getchar())
                {
                    system("cls");
                    continue;
                }
            }
            else
            {
                free(new_user);
                printf("the signning up is unsuccessfull,press any key to continoue:\n");
                if (getchar())
                {

                    system("cls");
                    continue;
                }
            }
        }
        else
        {
            printf("the input is not valid.press any key to continue \n");
            if (getchar())
            {

                system("cls");
                continue;
            }
        }
    }
}
int signup(user_ptr *head, user_ptr new_user, char **password, char **username, user_ptr main_head, char **instruction)
{
   
    if (head == NULL)
        return -2;
    new_user->username = (char *)malloc(strlen(*username) + 1);
    strcpy(new_user->username, *username);
    new_user->password = (char *)malloc(strlen(*password) + 1);
    strcpy(new_user->password, *password);
    (*head)->next_user = new_user;
    new_user->previous_user = (*head);
    new_user->post_counter = 0;
    new_user->next_user = NULL;
    (*head) = new_user;
    new_user->posts_for_user = (post_ptr)malloc(sizeof(posts));
    (new_user->posts_for_user)->next_post = NULL;
    if (check_username(username, main_head) == -1)
    {

        printf("the username is used.try again\n");
        return -1;
    }
    if (check_password(instruction) > 2)
    {
        printf("the password cannot have space\n");
        return -2;
    }
    return 0;
}

int get_post(char **instruction, char **post)
{
    int i = 0,space_counter = 0,k = 0;
    *post = NULL;
    while ((*instruction)[i] != '\0')
    {
        if (space_counter > 0)
        {
            char temp = (*instruction)[i];
            (*post) = (char *)realloc(*post, sizeof(char) * (k + 1));
            if ((*post) == NULL)
            {
                printf("not allocating memory\n");
                exit(EXIT_FAILURE);
            }
            (*post)[k] = temp;
            k++;
        }
        if ((*instruction)[i] == ' ')
        {
            space_counter++;
        }
        i++;
    }
    (*post) = (char *)realloc(*post, sizeof(char) * (k + 1));
    (*post)[k] = '\0';
    return 0;
}
int login(char **instruction, user_ptr head, char **password, char **username, user_ptr *current_user)
{
    int username_right = 0;
    int password_right = 0;
    user_ptr current;
    user_ptr next;
    current = head;
    current = current->next_user;
    while (current)
    {
        if (strcmp(current->username, *username) == 0)
        {
            (*current_user) = current;
            username_right = 1;
            break;
        }
        else
        {
            current = current->next_user;
            continue;
        }
    }
    if (username_right)
    {
        
        if (strcmp(current->password, *password) == 0)  /*checking if password right*/
        {
            password_right = 1;
        }
    }
    else
    {
        printf("we can't find this user.try again\n");
        return -1;
    }
    if (password_right == 0)
    {
        printf("the password is wrong.try again\n");
        return -2;
    }
    else
    {
        printf("you succesfully logged on\n");
        (*current_user) = current;
        return 0;
    }
}
int find_instruction(char **command, char **instruction)
{
    char tmp;
    int j = 0;
    *command = 0;

    while (1)
    {
        char c = (*instruction)[j];
        if (c == ' ')
            break;
        else
        {
            *command = (char *)realloc(*command, j + 1);
            (*command)[j] = c;
            j++;
        }
    }
    *command = (char *)realloc(*command, j + 1);
    (*command)[j] = '\0';
    return j;
}
int get_instruction(char **instruction, char **t_instruction)
{
    char tmp;
    int j = 1;
    char *c = 0;
    while (1)
    {
        c = (char *)realloc(c, j);
        tmp = getchar();
        c[j - 1] = tmp;
        j++;
        if (tmp == '\n')
        {
            c = (char *)realloc(c, j);
            tmp = '\0';
            c[j - 1] = tmp;
            j++;
            (*instruction) = (char *)malloc(j);
            (*t_instruction) = (char *)malloc(j);

            for (int i = 0; i < j - 1; i++)
                (*instruction)[i] = c[i];
            free(c);
            break;
        }
    }
    return j;
}
/*
 */
int myIn(char **instruction)
{
    int j = 1;
    // free(*instruction);
    *instruction = 0;
    while (1)
    {
        char c = getchar();

        *instruction = (char *)realloc(*instruction, j);
        if (*instruction == NULL)
        {
            printf("not allocating memory\n");
            exit(EXIT_FAILURE);
        }
        (*instruction)[j - 1] = c;
        j++;

        if (c == '\n')
        {

            break;
        }
    }
    (*instruction)[j - 1] = '\0';
    fflush(stdin);
    return j;
}
/*



*/
void find_username_password(char **instruction, char **password, char **username)
{
    int j = 0;
    int k = 0;
    int i = 0;
    int counter = 0;
    // (*username) = (char *)malloc(sizeof(char) * 256);
    // (*password) = (char *)malloc(sizeof(char) * 256);

    //  free(*username);
    // free(*password);
    *password = 0;
    *username = 0;

    while ((*instruction)[i] != '\0')
    {
        // printf("i is%d",i);
        if (counter == 1)
        {
            char c = (*instruction)[i];
            (*username) = (char *)realloc(*username, j + 1);
            (*username)[j] = c;
            j++;
        }

        if (counter == 2)
        {
            char c = (*instruction)[i];
            (*password) = (char *)realloc(*password, k + 1);
            (*password)[k] = c;
            k++;
        }
        if ((*instruction)[i] == ' ')
        {

            counter++;
            // printf("counter is %d and i is %d",counter,i);
        }
        i++;
    }
    (*username) = (char *)realloc(*username, j + 1);
    (*password) = (char *)realloc(*password, k + 1);
    (*username)[j] = '\0';
    (*password)[k] = '\0';
}
int check_username(char **user_name, user_ptr head)
{
    user_ptr current;
    user_ptr next;
    current = (head);
    current = current->next_user;
    int k = 0;
    while (current)
    {
        int a = 0;
        a = strcmp(current->username, *user_name);
        if (a == 0)
        {
            k++;
        }
        current = current->next_user;
    }
    if (k == 1)
    {
        return 0;
    }
    else
    {
        return -1;
    }
}
int check_password(char **instruction)
{
    int i = 0;
    int counter = 0;
    while ((*instruction)[i] != '\0')
    {
        if ((*instruction)[i] == ' ')
        {
            counter++;
        }
        i++;
    }
    return counter;
}
int add_post(user_ptr current_user, char **post, post_ptr new_post, post_ptr *head_post)
{
    post_ptr temp = current_user->posts_for_user;
    post_ptr current_post = current_user->posts_for_user;
    post_ptr previous_post;
    int i = 0;       /* when a new post added , add to other posts*/
    while (1)
    {
        i++;
        if (((current_post)->next_post) == NULL)
        {

            (current_post)->next_post = new_post;
            current_post = (current_post)->next_post;
            (current_post)->next_post = NULL;
            ((current_user)->post_counter)++;
            int temp_id = (current_user)->post_counter;
            current_post->post_id = (char *)malloc(sizeof(char) * ((int)log10(temp_id) + 1 + 1));
            int size = ((int)log10(temp_id) + 1 + 1);
            (current_post->post_id)[size - 1] = '\0';
            sprintf(current_post->post_id, "%d", temp_id);
            printf("post Id is%s\n", current_post->post_id);
            break;
        }
        current_post = (current_post)->next_post;
    }
    (new_post)->user = (char *)malloc(strlen(current_user->username) + 1);
    (new_post)->post = (char *)malloc(strlen(*post) + 1);
    new_post->like = (like_ptr)malloc(sizeof(like));
    new_post->like->next_liker = NULL;
    strcpy(new_post->user, current_user->username);
    strcpy(new_post->post, *post);
    (new_post)->like_counter = 0;
    i = 0;
    temp = (temp)->next_post;
    return 0;
}

int info(user_ptr current_user)
{

    printf("user name is :%s\n", current_user->username);
    printf("password is :%s\n", current_user->password);   /*shwoing info*/
    post_ptr current_post = 0;
    current_post = (current_user->posts_for_user)->next_post;
    int i = 1;
    while (current_post)
    {
        printf("post_id is:%s\n", current_post->post_id);
        printf("%s", (current_post)->post);
        printf("like is:%d\n", (current_post)->like_counter);
        current_post = (current_post)->next_post;
        i++;
    }
    return 0;
}
int delete_post(user_ptr current_user, char **post_id)
{
    post_ptr current_post;
    current_post = ((current_user)->posts_for_user);
    int counter = 1;
    while (current_post)
    {
        int a = strcmp((current_post->next_post)->post_id, *post_id);
        if (strcmp((current_post->next_post)->post_id, *post_id) == 0)  /*deleting posts*/
        {

            post_ptr temp = current_post->next_post;
            current_post->next_post = (current_post->next_post)->next_post;
            free(temp);
            return 0;
        }
        current_post = current_post->next_post;
        if (current_post->next_post == NULL)
        {
            break;
        }
    }
    return 1;
}

int like_post(char **username, char **post_id, user_ptr current_user, user_ptr head)
{
    post_ptr current_post;
    user_ptr current_liker;       /*liking posts */
    user_ptr liked_user = (head)->next_user;
    while (liked_user)
    {
        int a = strcmp(liked_user->username, *username);
        if (strcmp(liked_user->username, *username) == 0)
        {
            current_post = (liked_user->posts_for_user)->next_post;
            while (current_post)
            {
                int b = strcmp(current_post->post_id, *post_id);
                if (strcmp(current_post->post_id, *post_id) == 0)
                {
                    like_ptr cur_likers_of_post = (current_post->like)->next_liker;
                    while (cur_likers_of_post)
                    {
                        if (strcmp(cur_likers_of_post->liker_username, current_user->username) == 0)
                        {
                            printf("you already liked\n");
                            return -2;
                        }

                        cur_likers_of_post = cur_likers_of_post->next_liker;
                    }

                    like_ptr new_liker = (like_ptr)malloc(sizeof(like));
                    new_liker->next_liker = current_post->like->next_liker;
                    current_post->like->next_liker = new_liker;
                    new_liker->liker_username = (char *)malloc(strlen(current_user->username) + 1);
                    strcpy(new_liker->liker_username, current_user->username);
                    current_post->like_counter++;
                    return 0;
                }
                current_post = current_post->next_post;
            }
        }

        liked_user = liked_user->next_user;
    }
    int repeated_like = 0;

    return -1;
}
int find_delete_id(char **instruction, char **post_id)
{
    int i = 0, j = 0,space_counter = 0;
    while ((*instruction)[i] != '\0')
    {                      /* finding which ID to delete*/
        if (space_counter == 1)
        {
            char c = (*instruction)[i];
            (*post_id) = (char *)realloc(*post_id, j + 1);
            (*post_id)[j] = c;
            j++;
        }
        if ((*instruction)[i] == ' ')
        {

            space_counter++;
        }
        if (space_counter > 1)
            break;
        i++;
    }
    (*post_id) = (char *)realloc(*post_id, j + 1);
    (*post_id)[j - 1] = '\0';
    return 0;
}
int find_user(char **username, user_ptr head)
{
    user_ptr current_user;
    current_user = (head);
    current_user = current_user->next_user;
    int k = 0;
    while (current_user)
    {
        int a = 0;             /*showing info of user*/
        a = strcmp(current_user->username, *username);
        if (a == 0)
        {
            k++;
            post_ptr current_post = (current_user->posts_for_user)->next_post;
            int i = 1;
            while (current_post)
            {
                printf("post_id is:%s\n", current_post->post_id);
                printf("post id:%s\n", (current_post)->post);
                printf("like is:%d\n", (current_post)->like_counter);
                current_post = (current_post)->next_post;
                i++;
            }
            break;
        }

        current_user = current_user->next_user;
    }
    if (k > 0)
    {

        return 0;
    }
    else
    {

        return -1;
    }
}
int find_user_id(char **instruction, char **username)
{
    int i = 0, j = 0,space_counter = 0;  /*finding the user name of user*/
    while ((*instruction)[i] != '\0')
    {
        if (space_counter == 1)
        {
            char c = (*instruction)[i];
            (*username) = (char *)realloc(*username, j + 1);
            (*username)[j] = c;
            j++;
        }
        if (space_counter > 1)
            break;
        if ((*instruction)[i] == ' ')
        {

            space_counter++;
        }
        i++;
    }
    (*username) = (char *)realloc(*username, j + 1);
    (*username)[j] = '\0';
    return 0;
}
void find_username_post_id(char **instruction, char **post_id, char **username)
{
    int j = 0;
    int k = 0;
    int i = 0;
    int counter = 0;
    *username = 0;
    *post_id = 0;
    while ((*instruction)[i] != '\0')
    {
        if (counter == 1)       /*finding which user to like*/
        {
            char c = (*instruction)[i];
            (*username) = (char *)realloc(*username, j + 1);
            (*username)[j] = c;
            j++;
        }

        if (counter == 2)
        {
            char c = (*instruction)[i];
            (*post_id) = (char *)realloc(*post_id, k + 1);
            (*post_id)[k] = c;
            k++;
        }
        if ((*instruction)[i] == ' ')
        {

            counter++;
        }
        i++;
    }
    (*username) = (char *)realloc(*username, j + 1);
    (*post_id) = (char *)realloc(*post_id, k + 1);
    (*username)[j] = '\0';
    (*post_id)[k - 1] = '\0';
}

void update_signup_function(user_ptr head, FILE *accounts)  /* updating accounts file*/
{
    user_ptr current_user = head->next_user;
    while (current_user)
    {

        int a = fprintf(accounts, "%s %s %d", current_user->username, current_user->password, current_user->post_counter);
        current_user = current_user->next_user;
    }
}
void update_post_function(user_ptr head, FILE *post_properties) /*updating post files*/
{
    user_ptr current_user = head->next_user;
    while (current_user)
    {
        post_ptr current_post = (current_user->posts_for_user)->next_post;
        while (current_post)
        {
            fprintf(post_properties, "%s %s %d", current_post->post, current_user->username, current_post->like_counter);
            current_post = current_post->next_post;
        }
        current_user = current_user->next_user;
    }
}
