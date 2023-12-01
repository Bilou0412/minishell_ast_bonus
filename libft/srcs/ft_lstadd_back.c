/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <bmoudach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 17:56:54 by soutin            #+#    #+#             */
/*   Updated: 2023/12/01 16:28:03 by bmoudach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	ft_lstadd_back(t_list **lst, t_list *new)
{
	if (!new)
		return (-1);
	if (*lst)
		ft_lstlast(*lst)->next = new;
	else
		*lst = new;
	return (0);
}
