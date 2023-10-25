/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <bmoudach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 12:49:29 by bmoudach          #+#    #+#             */
/*   Updated: 2023/08/25 22:33:17 by bmoudach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdarg.h>
#include<stdio.h>
#include"libft.h"

static	int	check_str(const char *str)
{
	int			i;
	char		*verif;

	i = 0;
	verif = "cspdiuxX%";
	while (str[i])
	{
		if (str[i] == '%' && ft_strchr(verif, str[i + 1]))
			i = i + 2;
		else if (str[i] != '%')
			i++;
		else
			return (1);
	}
	return (0);
}

static const char	*ft_distrib_arg(va_list args, const char *str, int *len)
{
	if (*str == 'd' || *str == 'i')
		ft_putnbr(va_arg(args, int), len);
	else if (*str == 'c')
		*len += ft_putchar(va_arg(args, int));
	else if (*str == 's')
		*len += ft_putstr(va_arg(args, char *));
	else if (*str == 'p')
		ft_putptr(va_arg(args, unsigned long), len);
	else if (*str == 'u')
		ft_put_unsigned(va_arg(args, unsigned int), len);
	else if (*str == 'x' || *str == 'X')
		ft_puthexa(va_arg(args, unsigned int), *str, len);
	else if (*str == '%')
		*len += write(1, "%", 1);
	return (str + 1);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		len;

	len = 0;
	if (str == NULL)
		return (-1);
	if (check_str(str))
		return (0);
	va_start(args, str);
	while (*str)
	{
		if (*str == '%')
			str = ft_distrib_arg(args, str + 1, &len);
		else
			str = ft_put_text(str, &len);
	}
	return (len);
	va_end(args);
}
