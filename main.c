#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "functions.h"
int main()
{
    char *instruction = 0;
    char *t_instruction = 0;
    char *command;
    char *password = 0;
    char *username = 0;
    char *post = 0;
    user_ptr head = (user_ptr)malloc(sizeof(users));
    if (head == NULL)
        exit(EXIT_FAILURE);
    user_ptr new_user = (user_ptr)malloc(sizeof(users));
    if (new_user == NULL)
        exit(EXIT_FAILURE);
    user_ptr main_head = head;
    post_ptr new_post = 0;
    post_ptr head_post = (post_ptr)malloc(sizeof(post_ptr));
    if (head_post = NULL)
        exit(EXIT_FAILURE);
    post_ptr main_head_post = head_post;
    char *post_id = 0;
    head->next_user = NULL;
    instruction1(instruction, command, t_instruction, username, password, new_user, head, main_head, post, post_id, new_post, head_post, main_head_post);
}

