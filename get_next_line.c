/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 19:34:00 by hshimizu          #+#    #+#             */
/*   Updated: 2023/05/23 13:24:29 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

static char	*read_enter(char **temp, char *buf, int fd, int *end)
{
	char	*enter;
	ssize_t	size;

	*end = 0;
	buf[0] = '\0';
	enter = ft_strchr(*temp, '\n');
	if (!enter)
	{
		size = read(fd, buf, BUFFER_SIZE);
		if (*buf)
			enter = ft_strchr(buf, '\n');
		else
		{
			*end = 1;
			if (*temp)
				enter = ft_strchr(buf, '\0');
		}
	}
	return (enter);
}

static char	*_get_next_line(char **temp, int fd)
{
	char	buf[BUFFER_SIZE];

	char *enter;  //	改行の位置
	char *result; //	結果
	char *_temp;  //	tempを解放する時に使う
	int end;      //	これ以上の入力がないことを示す

	while (1)
	{
		enter = read_enter(temp, buf, fd, &end);
		if (enter)
			*enter = '\0';
		_temp = *temp;
		result = ft_strjoin(*temp, buf);
		if (enter)
			*temp = ft_strdup(enter + !end);
		free(_temp);
		if (end && !*result)
			return (NULL);
		if (enter)
			return (result);
		*temp = result;
	}
}

char	*get_next_line(int fd)
{
	char		*result;
	static char	*temp;

	if (!temp)
		temp = ft_strdup("");
	result = _get_next_line(&temp, fd);
	if (!result)
	{
		free(temp);
		temp = NULL;
	}
	return (result);
}
