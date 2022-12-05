/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nerrakeb <nerrakeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 00:11:09 by nerrakeb          #+#    #+#             */
/*   Updated: 2022/12/06 00:14:20 by nerrakeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	char		*new_line;
	static char	*stash[1024];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash[fd] = ft_read_and_add_to_stash(fd, stash[fd]);
	if (stash[fd] == NULL)
		return (NULL);
	new_line = ft_new_line (stash[fd]);
	stash[fd] = ft_save(stash[fd]);
	return (new_line);
}

char	*ft_read_and_add_to_stash(int fd, char *stash)
{
	char	*buf;
	int		rd;

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buf == NULL)
		return (NULL);
	rd = 1;
	while (rd != 0 && !ft_strchr(stash, '\n'))
	{
		rd = read(fd, buf, BUFFER_SIZE);
		if (rd == -1)
		{
			free(buf);
			free(stash);
			stash = NULL;
			return (NULL);
		}
		buf[rd] = '\0';
		stash = ft_strjoin(stash, buf);
	}
	free(buf);
	return (stash);
}

char	*ft_new_line(char *stash)
{
	int		len;
	char	*line;

	if (!(*stash))
		return (NULL);
	len = 0;
	while (stash[len] && stash[len] != 10)
		len++;
	line = ft_substr(stash, 0, len + 1);
	return (line);
}

char	*ft_save(char *stash)
{
	size_t	len;
	char	*str;

	len = 0;
	while (stash[len] && stash[len] != 10)
		len++;
	if (!stash[len])
	{
		free(stash);
		return (NULL);
	}
	str = ft_substr(stash, len + 1, ft_strlen(stash) - len + 1);
	free(stash);
	return (str);
}
