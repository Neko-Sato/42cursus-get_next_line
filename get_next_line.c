/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 19:34:00 by hshimizu          #+#    #+#             */
/*   Updated: 2023/05/26 18:17:01 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int	_get_next_line(char **result, char **temp, int fd)
{
	char	buf[BUFFER_SIZE + 1];
	char	*enter;
	char	*_temp;
	int		size;

	size = 0;
	enter = ft_strchr(*temp, '\n');
	*result = *temp;
	while (1)
	{
		*temp = *result;
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
			_temp = ft_strdup(enter + 1);
			if (!_temp)
				return (2);
			*(enter + 1) = '\0';
		}
		*result = ft_strjoin(*temp, buf);
		if (!*result)
			return (3);
		if (*temp)
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
