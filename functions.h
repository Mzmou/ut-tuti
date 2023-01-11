#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H
typedef struct post
{
    char *user;
    char *post_id;
    struct like *like;
    char *post;
    int like_counter;
    struct post *next_post;
    struct post *previous_post;
} posts;

typedef posts *post_ptr;
typedef struct linked_lists_user
{
    char *username;
    char *password;
    int post_counter;
    post_ptr posts_for_user;
    struct linked_lists_user *next_user;
    struct linked_lists_user *previous_user;
} users;

typedef users *user_ptr;
typedef posts *post_ptr;
typedef struct like
{
    char *liker_username;
    struct like *next_liker;
} like;
typedef like *like_ptr;
#endif
int get_instruction(char **instruction, char **t_instruction);
int find_instruction(char **command, char **instruction);
int instruction1(char *instruction, char *command, char *t_instruction, char *username, char *password, user_ptr new_user, user_ptr head, user_ptr main_head, char *post, char *post_id, post_ptr new_post, post_ptr head_post_each_user, post_ptr main_head_post_each_user);
int signup(user_ptr *head, user_ptr new_user, char **password, char **username, user_ptr main_head, char **instruction);
int myIn(char **instruction);
void find_username_password(char **instruction, char **password, char **username);
int login(char **instruction, user_ptr head, char **password, char **username, user_ptr *currunt_user);
int check_username(char **user_name, user_ptr head);
int check_password(char **instruction);
int get_post(char **instruction, char **post);
int add_post(user_ptr current_user, char **post, post_ptr new_post, post_ptr *head_post);
int info(user_ptr current_user);
int find_delete_id(char **instruction, char **post_id);
int delete_post(user_ptr current_user, char **post_id);
int find_user(char **username, user_ptr head);
int find_user_id(char **instruction, char **username);
void find_username_post_id(char **instruction, char **post_id, char **username);
int like_post(char **username, char **post_id, user_ptr current_user, user_ptr head);
void update_signup_function(user_ptr head, FILE *accounts);
void update_post_function(user_ptr head, FILE *post_properties);
