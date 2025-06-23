/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddadi <mhaddadi@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 17:47:18 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/04/25 17:47:34 by mhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}
/*
void ft_lstadd_front(t_list **lst, t_list *new) {
  if (!lst || !new)
    return;
  new->next = *lst;
  *lst = new;
}

int ft_lstsize(t_list *lst) {
  int i;
  t_list *temp;

  temp = lst;
  i = 0;
  while (temp) {
    i++;
    temp = temp->next;
  }
  return (i);
}

t_list *ft_lstlast(t_list *lst) {
  t_list *temp;

  temp = lst;
  while (temp->next) {
    temp = temp->next;
  }
  return (temp);
}

void ft_lstadd_back(t_list **lst, t_list *new) {
  t_list *temp;

  if (!lst || !new)
    return;
  if (!*lst) {
    *lst = new;
    return;
  }
  temp = ft_lstlast(*lst);
  temp->next = new;
}

void ft_lstdelone(t_list *lst, void (*del)(void *)) {
  if (!lst)
    return;
  if (del)
    del(lst->content);
  free(lst);
}

void ft_lstclear(t_list **lst, void (*del)(void *)) {
  t_list *temp;

  if (!lst || !*lst || !del)
    return;
  if (del) {
    while (*lst) {
      temp = (*lst)->next;
      ft_lstdelone(*lst, del);
      *lst = temp;
    }
    *lst = NULL;
  }
}

void ft_lstiter(t_list *lst, void (*f)(void *)) {
  t_list *current;
  t_list *next_node;

  if (!lst || !f)
    return;
  current = lst;

  while (current) {
    next_node = current->next;
    f(current->content);
    current = next_node;
  }
}

t_list *ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *)) {
  t_list *newlst;
  t_list *temp;

  if (!lst || !f || !del)
    return (NULL);
  newlst = NULL;
  while (lst) {
    temp = ft_lstnew(f(lst->content));
    if (!temp) {
      ft_lstclear(&newlst, del);
      return (NULL);
    }
    ft_lstadd_back(&newlst, temp);
    lst = lst->next;
  }
  return (newlst);
}

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

void print_list(t_list *lst) {
  printf("List: ");
  while (lst) {
    printf("%d -> ", *(int *)lst->content);
    lst = lst->next;
  }
  printf("NULL\n");
}

void increment(void *content) {
  if (content)
    (*(int *)content)++;
}

void *duplicate(void *content) {
  int *new = malloc(sizeof(int));
  if (!new)
    return (NULL);
  *new = *(int *)content;
  return (new);
}

void delete(void *content) { free(content); }

int main(void) {
  t_list *lst = NULL;
  t_list *map_lst = NULL;
  int *i;

  for (int j = 1; j <= 5; j++) {
    i = malloc(sizeof(int));
    *i = j;
    ft_lstadd_front(&lst, ft_lstnew(i));
  }

  printf("after ft_lstadd_front:\n");
  print_list(lst);

  printf("list size: %d\n", ft_lstsize(lst));

  t_list *last = ft_lstlast(lst);
  printf("Last element: %d\n", *(int *)last->content);

  int *val = malloc(sizeof(int));
  *val = 41;
  ft_lstadd_back(&lst, ft_lstnew(val));
  printf("After ft_lstadd_back:\n");
  print_list(lst);

  ft_lstiter(lst, increment);
  printf("After ft_lstiter:\n");
  print_list(lst);

  map_lst = ft_lstmap(lst, duplicate, delete);
  printf("Maped list:\n");
  print_list(map_lst);
  printf("Original list:\n");
  print_list(lst);

  ft_lstclear(&lst, delete);
  ft_lstclear(&map_lst, delete);

  if (!lst && !map_lst)
    printf("Lists succecfuly cleaned.\n");

  return (0);
}
*/
