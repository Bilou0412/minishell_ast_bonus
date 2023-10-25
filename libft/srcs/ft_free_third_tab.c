/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_third_tab.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <bmoudach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 20:19:19 by bmoudach          #+#    #+#             */
/*   Updated: 2023/09/26 03:44:34 by bmoudach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_free_third_tab(char ***tab)
{
	int	i;

	i = 0;
	while (tab[i])
		ft_free_tab(tab[i++]);
	free(tab);
	return (0);
}
