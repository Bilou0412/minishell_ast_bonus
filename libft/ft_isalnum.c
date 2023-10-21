/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:43:14 by bmoudach          #+#    #+#             */
/*   Updated: 2023/05/07 18:03:27 by bmoudach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalnum(int argument)
{
	if ((argument < 91 && argument > 64) || (argument < 123 && argument > 96))
		return (1);
	if (argument < 58 && argument > 47)
		return (1);
	return (0);
}
