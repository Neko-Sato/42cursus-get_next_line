/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 19:34:00 by hshimizu          #+#    #+#             */
/*   Updated: 2023/05/24 15:02:37 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int	_get_next_line(char **result, char **temp, int fd)
{
	char	buf[BUFFER_SIZE];
	char	*enter;
	int		size;

	buf[0] = '\0';
	enter = NULL;
	if (*temp)
		enter = ft_strchr(*temp, '\n');
	*result = *temp;
	//ここから
	while (!enter)
	{
		*temp = *result;
		size = read(fd, buf, BUFFER_SIZE - 1);
		buf[size] = '\0';
		if (!size)
			return (-1);
		enter = ft_strchr(buf, '\n');
		if (enter)
			*enter = '\0';
		if (!*temp)
			*temp = ft_strdup("");
		if (!*temp)
			return (1);
		*result = ft_strjoin(*temp, buf);
		if (!*result)
			return (1);
		free(*temp);
	}
	//ここまで別関数化
	*enter = '\0';
	*temp = ft_strdup(enter + 1);
	if (!*temp)
		return (1);
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*temp;
	char		*result;
	int			code;

	result = NULL;
	code = _get_next_line(&result, &temp, fd);
	if (code == -1)
		temp = NULL;
	else if (code == 1)
	{
		if (temp && temp != result)
			free(temp);
		if (result)
			free(result);
		result = NULL;
	}
	return (result);
}
