/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 13:46:39 by bmoudach          #+#    #+#             */
/*   Updated: 2023/12/08 16:33:24 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static void	ft_trim(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\n' && str[i])
		i++;
	if (str[i] == '\n')
		i++;
	str[i] = '\0';
}

static void	ft_mouv(char *buf, int byte)
{
	int	i;
	int	j;

	if (!ft_strchr(buf, '\n'))
		return ;
	i = ft_strchr(buf, '\n') - buf + 1;
	j = 0;
	while (buf[i] && (byte || ft_strchr(buf, '\n')))
		buf[j++] = buf[i++];
	buf[j] = '\0';
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	char		*line;
	int			byte;

	byte = 1;
	if (fd < 0 || read(fd, buf, 0))
		return (NULL);
	line = (char *)ft_collector(ft_strjoin_gnl(NULL, buf), false);
	while (!ft_strchr(line, '\n'))
	{
		byte = read(fd, buf, BUFFER_SIZE);
		buf[byte] = '\0';
		if (byte == 0)
			break ;
		if (byte < 0)
			return (ft_collector(line, true), NULL);
		line = (char *)ft_collector(ft_strjoin_gnl(line, buf), false);
		if (!line)
			return (NULL);
	}
	if (!line[0])
		return (ft_collector(line, true), NULL);
	return (ft_trim(line), ft_mouv(buf, byte), line);
}

/*int	main(void)
|{
  char	*str;
  int		fd;

  fd = open("texte", O_RDONLY);
  while (str = get_next_line(fd))
  {
  write(1, str, strlen(str));
  free(str);
  }
  close(fd);
  }*/
