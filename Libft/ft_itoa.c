/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:04:37 by kmaeda            #+#    #+#             */
/*   Updated: 2025/05/21 17:38:50 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_convert(int n, int count, int sign)
{
	int		num;
	char	*result;

	num = n;
	while (num / 10 != 0)
	{
		num /= 10;
		count++;
	}
	result = malloc(sizeof (char) * (count + 1));
	if (!result)
		return (NULL);
	result[count] = '\0';
	while (count-- > 0)
	{
		result[count] = (n % 10) + '0';
		n /= 10;
		if (sign && count == 0)
			result[0] = '-';
	}
	return (result);
}

char	*ft_itoa(int n)
{
	int		count;
	int		sign;
	char	*result;

	count = 1;
	sign = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n < 0)
	{
		n = -n;
		sign = 1;
		count++;
	}
	result = ft_convert(n, count, sign);
	return (result);
}
