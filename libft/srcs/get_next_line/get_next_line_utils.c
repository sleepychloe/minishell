/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 15:51:40 by yhwang            #+#    #+#             */
/*   Updated: 2021/12/23 15:52:02 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}

char	*ft_strjoin(char *backup, char *buf)
{
	size_t	i;
	size_t	j;
	char	*new_str;

	if (!backup)
	{
		backup = (char *)malloc(sizeof(char) * 1);
		backup[0] = '\0';
	}
	if (!backup || !buf)
		return (NULL);
	new_str = malloc(sizeof(char) * ((ft_strlen(backup) + ft_strlen(buf))
				+ 1));
	if (new_str == NULL)
		return (NULL);
	i = -1;
	j = 0;
	if (backup)
		while (backup[++i] != '\0')
			new_str[i] = backup[i];
	while (buf[j] != '\0')
		new_str[i++] = buf[j++];
	new_str[ft_strlen(backup) + ft_strlen(buf)] = '\0';
	free(backup);
	return (new_str);
}

char	*ft_get_line(char *backup)
{
	int		i;
	char	*line_will_be_read;

	i = 0;
	if (!backup[i])
		return (NULL);
	while (backup[i] && backup[i] != '\n')
		i++;
	line_will_be_read = (char *)malloc(sizeof(char) * (i + 2));
	if (!line_will_be_read)
		return (NULL);
	i = 0;
	while (backup[i] && backup[i] != '\n')
	{
		line_will_be_read[i] = backup[i];
		i++;
	}
	if (backup[i] == '\n')
	{
		line_will_be_read[i] = backup[i];
		i++;
	}
	line_will_be_read[i] = '\0';
	return (line_will_be_read);
}

char	*ft_new_backup(char *backup)
{
	int		i;
	int		j;
	char	*new_backup;

	i = 0;
	while (backup[i] && backup[i] != '\n')
		i++;
	if (!backup[i])
	{
		free(backup);
		return (NULL);
	}
	new_backup = (char *)malloc(sizeof(char) * (ft_strlen(backup) - i + 1));
	if (!new_backup)
		return (NULL);
	i++;
	j = 0;
	while (backup[i])
		new_backup[j++] = backup[i++];
	new_backup[j] = '\0';
	free(backup);
	return (new_backup);
}
