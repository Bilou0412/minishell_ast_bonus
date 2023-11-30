/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 17:56:54 by soutin            #+#    #+#             */
/*   Updated: 2023/11/30 17:34:21 by soutin           ###   ########.fr       */
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
