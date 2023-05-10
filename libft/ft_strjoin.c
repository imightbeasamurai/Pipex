/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrahim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:37:39 by aerrahim          #+#    #+#             */
/*   Updated: 2023/05/03 16:37:41 by aerrahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *str1, char const *str2)
{
	int		i;
	int		j;
	char	*s;

	if (!str1 || !str2)
		return (NULL);
	s = (char *)malloc(sizeof(char) * (ft_strlen(str1) + ft_strlen(str2) + 1));
	if (!s)
		return (NULL);
	i = 0;
	while (str1[i])
	{
		s[i] = str1[i];
		i++;
	}
	j = 0;
	while (str2[j])
	{
		s[i + j] = str2[j];
		j++;
	}
	s[i + j] = '\0';
	return (s);
}
