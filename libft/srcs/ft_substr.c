/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 15:26:21 by bmoudach          #+#    #+#             */
/*   Updated: 2023/05/11 13:11:17 by bmoudach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*str;
	size_t		len_str;
	size_t		sizestr;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
	{
		str = malloc(sizeof(char));
		if (!str)
			return (NULL);
		str[0] = '\0';
		return (str);
	}
	len_str = ft_strlen(s) - start;
	if (len > len_str)
		sizestr = len_str;
	else
		sizestr = len;
	str = malloc((sizestr + 1) * sizeof(char));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s + start, sizestr + 1);
	return (str);
}
/*char	*ft_substr(char const *s, unsigned int start, size_t len)
  {
  char			*str;
  size_t			len_str;
  size_t			sizestr;

  str = malloc(sizeof(char));
  if (!str)
  return (NULL);
  if (s == NULL)
  return (NULL);
  if (start > ft_strlen(s))
  {
  str[0] = '\0';
  return (str);
  }
  len_str = ft_strlen(s + start);
  if (len > len_str)
  sizestr = len_str;
  else
  sizestr = len;
  str = malloc((sizestr + sizeof(char)) * sizeof(char));
  if (!str)
  return (NULL);
  ft_strlcpy(str, s + start, sizestr + 1);
  return (str);
  }*/

/*int	main()
  {
  char	*str;
  unsigned int	start;
  size_t	len;
  char const	*s = "tripouille";

  len = 42000000;
  start = 42;
  str = ft_substr(s,start,len);
  printf("%s",str);
  }*/
