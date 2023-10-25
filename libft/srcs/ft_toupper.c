/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 12:12:38 by bmoudach          #+#    #+#             */
/*   Updated: 2023/05/07 18:06:08 by bmoudach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_toupper(int ch)
{
	if (ch > 96 && ch < 123)
		return (ch - 32);
	return (ch);
}
/*#include<stdio.h>
int	main(void)
{
	unsigned ch;
	ch = 'q';
	ch = ft_toupper(ch);
	printf("%c",ch);
}*/
