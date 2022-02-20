/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadalya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 14:20:50 by abadalya          #+#    #+#             */
/*   Updated: 2021/01/31 14:28:22 by abadalya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		word_count(char const *s, char c)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

static int		word_length(char const *s, char c)
{
	int i;

	i = 0;
	while (s[i] != c && s[i] != '\0')
		i++;
	return (i);
}

static char		**matrix(char const *s, char c, char **result, int words_count)
{
	int i;
	int j;
	int w_len;

	while (*s == c)
		s++;
	i = -1;
	while (++i < words_count)
	{
		while (*s == c)
			s++;
		j = 0;
		w_len = word_length(s, c);
		if (!(result[i] = (char *)malloc(sizeof(char) * (w_len + 1))))
			return (NULL);
		while (j < w_len)
		{
			result[i][j] = *s;
			s++;
			j++;
		}
		result[i][j] = '\0';
	}
	result[i] = NULL;
	return (result);
}

char			**ft_split(char const *s, char c)
{
	char	**result;
	int		wcount;

	if (!s)
		return (NULL);
	wcount = word_count(s, c);
	if (!(result = (char **)malloc(sizeof(char *) * (wcount + 1))))
		return (NULL);
	result = matrix(s, c, result, wcount);
	return (result);
}
