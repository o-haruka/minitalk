#include "../includes/ft_list.h"
// #include <stdlib.h>
// #include <stdio.h>


// typedef struct s_list
// {
//     void *content;
//     struct s_list *next;
// } t_list;

t_list *ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *)){
    t_list *new_list = NULL; // 新しいリストの先頭
    t_list *new_tail = NULL; // 新しいリストの末尾（効率的な連結用）
    t_list *new_node;

    if (!lst || !f || !del)
        return (NULL);
    
    while (lst)
    {
        // fを適用したcontentで新しいノードを作成
        new_node = ft_lstnew(f(lst->content));
        if (!new_node)
        {
            // 失敗した場合、生成済みのリストを解放
            ft_lstclear(&new_list, del);
            return (NULL);
        }
        // 新しいノードをリストに追加
        if (!new_list)
        {
            new_list = new_node;
            new_tail = new_node;
        }
        else
        {
            new_tail->next = new_node;
            new_tail = new_node;
        }
        lst = lst->next;
    }

    return (new_list);
}

// contentを大文字に変換する関数
// void *to_upper(void *content)
// {
//     char *str = (char *)content;
//     char *result = strdup(str);
//     for (int i = 0; result[i]; i++)
//         if (result[i] >= 'a' && result[i] <= 'z')
//             result[i] -= 32;
//     return (result);
// }

// // contentを解放する関数
// void del_content(void *content)
// {
//     free(content);
// }

// int main(void)
// {
//     // テストリストの作成
//     t_list *lst = ft_lstnew(strdup("hello"));
//     lst->next = ft_lstnew(strdup("world"));
    
//     // ft_lstmapを呼び出し
//     t_list *new_list = ft_lstmap(lst, to_upper, del_content);
    
//     // 結果を表示
//     t_list *current = new_list;
//     while (current)
//     {
//         printf("%s\n", (char *)current->content);
//         current = current->next;
//     }
    
//     // メモリ解放
//     ft_lstclear(&lst, del_content);
//     ft_lstclear(&new_list, del_content);
//     return (0);
// }