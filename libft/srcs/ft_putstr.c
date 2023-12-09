/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 15:48:14 by bmoudach          #+#    #+#             */
/*   Updated: 2023/12/09 16:59:08 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	ft_putstr(char *str)
{
	if (str == NULL)
		return (write(2, "(null)", 6), 6);
	write(2, str, ft_strlen(str));
	return (ft_strlen(str));
}
