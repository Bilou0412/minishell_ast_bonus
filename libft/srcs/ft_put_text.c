/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_text.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 13:58:36 by bmoudach          #+#    #+#             */
/*   Updated: 2023/12/09 17:01:29 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_put_text(const char *str, int *len)
{
	char	*strverif;

	strverif = ft_strchr(str, '%');
	if (!strverif)
	{
		*len += write(2, str, ft_strlen(str));
		return ((char *)str + ft_strlen(str));
	}
	else
	{
		*len += write(2, str, (int)(ft_strchr(str, '%') - str));
		return (ft_strchr(str, '%'));
	}
}
