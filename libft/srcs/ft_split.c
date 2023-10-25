/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 18:52:15 by bmoudach          #+#    #+#             */
/*   Updated: 2023/05/12 18:10:22 by bmoudach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"libft.h"

static int	count_array(char const *s1, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s1[i])
	{
		if ((s1[i] != c && s1[i + 1] == '\0') || (s1[i] != c && s1[i + 1] == c))
		{
			count++;
			i++;
		}
		else
			i++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char		**array;
	int			max_size;
	int			j;

	if (!s)
		return (NULL);
	j = 0;
	max_size = count_array(s, c);
	array = malloc((max_size + 1) * sizeof(char **));
	if (!array)
		return (NULL);
	array[max_size] = NULL;
	while (max_size--)
	{
		while (*s == c)
			s++;
		array[j] = ft_substr(s, 0, ft_strchr(s, c) - s);
		if (!array[j++])
			return (NULL);
		while (*s != c && *s != '\0')
			s++;
	}
	return (array);
}

/*int	main(void)
{
	char	**array;
	char	*s = "Tripouille";
	char	c = ' ';
	int	i = 0;

	array = ft_split(s, c);
	while (array[i])
		printf("%s\n", array[i++]);
}*/
