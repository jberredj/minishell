/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_idllst.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 10:01:28 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/06 13:00:47 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_IDLLST_H
# define FT_IDLLST_H
# include <stdlib.h>
# include <stddef.h>
# include <stdbool.h>
# include "ft_string.h"

/*
** Intrusive Doubly Linked List
** Those list are used inside structs to link the parent struct directly.
** This implementation is based on the Linux kernel one.
** The first element of a list, point to himself in idllist->prev,
** similarly, the last element point to himself in idllist->next.
** If the list have only one element, both of the last rules applies.
**
** To get the parent struct from the list, an offset from the list link to
** the parent pointer is stored in the link.
*/

typedef struct s_idllist
{
	struct s_idllist	*prev;
	struct s_idllist	*next;
	void				*struct_addr;
}				t_idllist;

t_idllist	ft_idllst_init(t_idllist *list, void *struct_addr);
void		ft_idllst_add_after(t_idllist *new, t_idllist *node);
void		ft_idllst_add_before(t_idllist *new, t_idllist *node);
bool		ft_idllst_is_head(t_idllist *node);
t_idllist	*ft_idllst_get_head(t_idllist *node);
bool		ft_idllst_is_tail(t_idllist *node);
t_idllist	*ft_idllst_get_tail(t_idllist *node);
void		ft_idllst_add_front(t_idllist *new, t_idllist *list);
void		ft_idllst_add_back(t_idllist *new, t_idllist *list);
size_t		ft_idllst_nbr_to_tail(t_idllist *node);
size_t		ft_idllst_nbr_to_head(t_idllist *node);
t_idllist	*ft_idllst_pop(t_idllist *node, void (*del)(void*));
void		ft_idllst_clear_after(t_idllist *node, void (*del)(void*),
				bool include_current);
void		ft_idllst_clear_before(t_idllist *node, void (*del)(void*),
				bool include_current);
t_idllist	*ft_idllst_del(t_idllist *node, void (*del)(void*));
void		ft_idllst_clear(t_idllist *node, void (*del)(void*));
void		*ft_idllst_prev_content(t_idllist *node);
void		*ft_idllst_content(t_idllist *node);
void		*ft_idllst_next_content(t_idllist *node);
bool		ft_idllst_is_init(t_idllist *node);
size_t		ft_idllst_size(t_idllist *node);
#endif
