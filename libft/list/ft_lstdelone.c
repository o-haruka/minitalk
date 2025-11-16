#include "../includes/ft_list.h"
// #include "libft.h"
// #include <stdlib.h>
// #include <stdio.h>

// typedef struct s_list
// {
//     void *content;
//     struct s_list *next;
// } t_list;

void del_content(void *content){
    free(content);
}

void ft_lstdelone(t_list *lst, void (*del)(void *)){
    if(!lst || !del)
        return;
    del(lst->content);
    free(lst);
}

// int main(void) {
//     t_list *node = malloc(sizeof(t_list));
//     node->content = malloc(10);
//     node->next = NULL;

//     ft_lstdelone(node, del_content);
//     return 0;
// }