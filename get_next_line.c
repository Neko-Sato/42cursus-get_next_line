/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 19:34:00 by hshimizu          #+#    #+#             */
/*   Updated: 2023/05/23 00:36:11 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

char	*get_next_line(int fd)
{
	char		buf[BUFFER_SIZE];
	static char	*temp;
	char		*_temp;
	char		*enter;
	char		*result;
	ssize_t		size;

	//	tempを空文字に初期化
	if (!temp)
		temp = ft_strdup("");
	//	改行をなしに初期化
	enter = NULL;
	while (!enter)
	{
		//	bufを空の文字列に初期化
		buf[0] = '\0';
		//	tempから改行を検索
		enter = ft_strchr(temp, '\n');
		//	tempに改行がなければ
		if (!enter)
		{
			size = read(fd, buf, BUFFER_SIZE);
			//	bufに読み取りそこから改行を探す
			if(size == 0 && *temp)
				enter = buf + size;
			else if (size <= 0)
				return (NULL);
			else
				enter = ft_strchr(buf, '\n');
		}
		//	改行があればそれを終端文字に変える
		if (enter)
			*enter = '\0';
		//	tempとbufをつなげた文字を作る
		result = ft_strjoin(temp, buf);
		//	改行があればtempを改行から一つ先の文字列にする
		_temp = temp;
		if (enter)
			temp = ft_strdup(enter + 1);
		else
			temp = result;
		free(_temp);
		//	改行があれば抜ける
	}
	return (result);
}
