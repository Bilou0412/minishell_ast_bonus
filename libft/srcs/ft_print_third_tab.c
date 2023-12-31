/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_third_tab.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 03:47:05 by bmoudach          #+#    #+#             */
/*   Updated: 2023/10/25 17:41:47 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	ft_print_third_tab(char ***tab)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (tab[i])
	{
		ft_printf("tab[%d]:\n", i);
		while (tab[i][j])
		{
			ft_printf("tab[%d][%d]: %s\n", i, j, tab[i][j]);
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}
