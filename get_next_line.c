/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 19:34:00 by hshimizu          #+#    #+#             */
/*   Updated: 2023/06/05 14:56:08 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int	read_enter(char *temp, char *enter, char *buf, int fd)
{
	int	size;

	size = 0;
	if (!enter)
	{
		size = read(fd, buf, BUFFER_SIZE);
		if (size <= 0)
			return (-(size == 0));
		enter = ft_strchr(buf, '\n');
	}
	buf[size] = '\0';
	if (enter)
	{
		temp = ft_strdup(enter + 1);
		if (!temp)
			return (1);
		*(enter + 1) = '\0';
	}
	return (0);
}

static int	_get_next_line(char **result, char **temp, int fd)
{
	char	buf[BUFFER_SIZE + 1];
	char	*enter;
	char	*_temp;
	int		code;

	_temp = NULL;
	enter = ft_strchr(*temp, '\n');
	*result = *temp;
	while (1)
	{
		*temp = *result;
		code = read_enter(_temp, enter, buf, fd);
		if (code)
			return (code);
		*result = ft_strjoin(*temp, buf);
		if (!*result)
			return (1);
		free(*temp);
		*temp = _temp;
		if (enter)
			return (0);
	}
}

char	*get_next_line(int fd)
{
	static char	*temp;
	char		*result;
	int			code;

	result = NULL;
	code = _get_next_line(&result, &temp, fd);
	if (code == -1)
	{
		if (result && !*result)
		{
			free(result);
			result = NULL;
		}
		temp = NULL;
	}
	else if (code)
	{
		if (temp != result)
			free(temp);
		free(result);
		temp = NULL;
		result = NULL;
	}
	return (result);
}
