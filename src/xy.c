/*
** xy.c for LemIPC in /home/la-val_c/rendu/PSU/lemipc
**
** Made by Cyril La Valle
** Login <la-val_c@epitech.eu>
**
** Started on  Wed Mar  4 08:58:50 2015 Cyril La Valle
** Last update Sun Mar  8 01:14:48 2015 Paul Carensac
*/

#include "player.h"

t_xy_list	*xy_list_alloc(void)
{
  t_xy_list	*list;

  list = malloc(sizeof(*list));
  if (list != NULL)
    {
      list->next = NULL;
      list->data.cpt = 0;
    }
  return (list);
}

void		xy_list_free(t_xy_list *list)
{
  t_xy_list	*to_free;
  t_xy_list	*nptr;

  nptr = list;
  while (nptr != NULL)
    {
      to_free = nptr;
      nptr = nptr->next;
      free(to_free);
    }
}

int		xy_list_append(t_xy_list **list, uint32_t data)
{
  t_xy_list	*nptr;

  if (*list == NULL)
    {
      *list = xy_list_alloc();
      (*list)->data.cpt = data;
      return (0);
    }
  for (nptr = *list ; nptr->next != NULL ; nptr = nptr->next)
    ;
  nptr->next = xy_list_alloc();
  if (nptr->next == NULL)
    return (-1);
  nptr->next->data.cpt = data;
  return (0);
}
