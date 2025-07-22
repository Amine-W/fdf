/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amwahab <amwahab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 10:59:53 by amwahab           #+#    #+#             */
/*   Updated: 2025/07/22 11:43:18 by amwahab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi_base(const char *str, int base)
{
	int result;

	result = 0;
	if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
		str += 2;
	while ((*str >= '0' && *str <= '9') ||
		   (*str >= 'A' && *str <= 'F') ||
		   (*str >= 'a' && *str <= 'f'))
	{
		if (*str >= '0' && *str <= '9')
			result = result * base + (*str - '0');
		else if (*str >= 'A' && *str <= 'F')
			result = result * base + (*str - 'A' + 10);
		else if (*str >= 'a' && *str <= 'f')
			result = result * base + (*str - 'a' + 10);
		str++;
	}
	return (result);
}

