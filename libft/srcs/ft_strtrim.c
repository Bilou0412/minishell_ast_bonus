/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:51:59 by bmoudach          #+#    #+#             */
/*   Updated: 2023/05/13 15:32:28 by bmoudach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int	start;
	int	end;

	start = 0;
	if (!s1)
		return (NULL);
	end = ft_strlen(s1) - 1;
	if (!set)
		return (ft_strdup(s1));
	while (ft_strchr(set, s1[start]))
		start++;
	while (ft_strrchr(set, s1[end]))
		end--;
	return (ft_substr(s1, start, end - start + 1));
}

/*int	main()
{
	const char	 *s1 = "dedrffgoulderfsffr";
	const char	*set = "derf";

	printf("%s",ft_strtrim(s1,set));
}*/
