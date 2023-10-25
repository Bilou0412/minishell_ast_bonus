/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 14:23:35 by bmoudach          #+#    #+#             */
/*   Updated: 2023/05/13 14:52:25 by bmoudach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	int	i;
	int	signe;
	int	base;

	base = 0;
	signe = 1;
	i = 0;
	while ((str[i] < 14 && str[i] > 8) || str[i] == 32)
	{
		i++;
	}
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			signe = signe * -1;
		i++;
	}
	while (str[i] <= '9' && str[i] >= '0')
	{
		base = (base * 10) + str[i] - '0';
		i++;
	}
	return (base * signe);
}

/*int	main(void) 
{
	const char	str[] = "      +123hef";
	printf("%d",ft_atoi(str));
}*/
