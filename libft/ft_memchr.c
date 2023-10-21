/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:13:37 by bmoudach          #+#    #+#             */
/*   Updated: 2023/05/13 14:44:35 by bmoudach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*src;

	i = 0;
	src = (unsigned char *)s;
	while (i < n)
	{
		if (src[i] == (unsigned char)c)
		{
			return ((unsigned char *)s + i);
		}
		i++;
	}
	return (0);
}

/*int main() {

  char data[] = { 10, 20, 30, 40, 50, 60, 70, 80, 90, 100 };
  const unsigned int size = 10;

// On recherche une valeur inhéxistante :
void * found = ft_memchr( data, 57, size );
printf( "57 is %s\n", ( found != NULL ? "found" : "not found" ) );

// On recherche une valeur existante :
found = ft_memchr( data, 50, size );
printf( "50 is %s\n", ( found != NULL ? "found" : "not found" ) );
if ( found != NULL ) {
printf( "La valeur à la position calculée est %d\n", *((char *) found) );
}

return EXIT_SUCCESS;
}*/

/*int main(void)
  {

  char s[] = {0, 1, 2 ,3 ,4 ,5};
  printf("%p\n",ft_memchr(s, 2 + 256, 3));
  printf("%p\n",memchr(s, 2 + 256, 3));
  printf("%p",s + 2);
  return (0);
  }*/
