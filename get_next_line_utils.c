/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 19:34:06 by hshimizu          #+#    #+#             */
/*   Updated: 2023/05/25 17:43:02 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

int	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (*s++)
		len++;
	return (len);
}

char	*ft_strdup(const char *s1)
{
	char	*s2;
	char	*_s2;
	int		size;

	if(!s1)
		return (NULL);
	size = ft_strlen(s1) + 1;
	s2 = (char *)malloc(size * sizeof(char));
	_s2 = s2;
	if (s2)
		while (size--)
			*s2++ = *s1++;
	return (_s2);
}

char	*ft_strchr(const char *s, int c)
{

	while (s)
	{
		if (*s == (char)c)
			return ((char *)s);
		if (!*s++)
			break ;
	}
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	char	*_result;

	if(!s1)
		s1 = "";
	if(!s2)
		s2 = "";
	result = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	_result = result;
	while (*s1)
		*result++ = *s1++;
	while (*s2)
		*result++ = *s2++;
	*result = '\0';
	return (_result);
}
