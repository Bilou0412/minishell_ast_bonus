/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 18:52:15 by bmoudach          #+#    #+#             */
/*   Updated: 2023/11/30 18:47:26 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

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
	array = (char**)ft_collector(ft_calloc((max_size + 1), sizeof(char **)), false);
	array[max_size] = NULL;
	while (max_size--)
	{
		while (*s == c)
			s++;
		array[j] = (char*)ft_collector(ft_substr(s, 0, ft_strchr(s, c) - s), false);
		j++;
		while (*s != c && *s != '\0')
			s++;
	}
	array[j] = NULL;
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
