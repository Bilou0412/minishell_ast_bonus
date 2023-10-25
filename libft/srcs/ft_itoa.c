/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 10:34:24 by bmoudach          #+#    #+#             */
/*   Updated: 2023/05/13 14:22:10 by bmoudach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"libft.h"

static int	len_n(int n)
{
	int			i;
	long int	nb;

	nb = (long int)n;
	i = 0;
	if (!nb)
		return (1);
	if (nb < 0)
	{
		nb = nb * -1;
		i++;
	}
	while (nb >= 1)
	{
		nb = nb / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char		*num_conv;
	int			len;
	long int	nb;

	nb = (long int)n;
	len = len_n(nb);
	num_conv = malloc((len + 1) * sizeof(char));
	if (!num_conv)
		return (NULL);
	if (nb == 0)
		num_conv[0] = '0';
	if (nb < 0)
	{
		num_conv[0] = '-';
		nb = nb * -1;
	}
	num_conv[len] = '\0';
	while (nb > 0)
	{
		len--;
		num_conv[len] = (nb % 10) + 48;
		nb = nb / 10;
	}
	return (num_conv);
}	

/*int	main(void)
{
	printf("%s", ft_itoa(10)); 
}*/
