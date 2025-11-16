#include "../includes/ft_list.h"
// #include "libft.h"
// #include <stdlib.h>
// #include <stdio.h>

// typedef struct s_list
// {
//     void *content;
//     struct s_list *next;
// } t_list;

t_list *ft_lstnew(void *content){
    t_list *new_node;

    new_node = (t_list *)malloc(sizeof(t_list));
    if(new_node == NULL)
        return (NULL);

    new_node->content = content;
    new_node->next = NULL;

    return (new_node);
}

// int main(void) {
//     int value = 42;
//     t_list *node = ft_lstnew(&value);

//     printf("%d\n", *(int *)(node->content));
//     printf("%p\n", (void *)(node->next));

//     return 0;
// }