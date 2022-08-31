/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: znajda <znajda@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 15:35:35 by znajda        #+#    #+#                 */
/*   Updated: 2022/08/31 15:35:38 by znajda        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *c)
{
	int			sign;
	long int	value;

	sign = 1;
	value = 0;
	while (*c == ' ' || (*c >= 9 && *c <= 13))
		c++;
	if (*c == '-' || *c == '+')
	{
		if (*c == '-')
			sign = -1;
		c++;
	}
	while (*c >= '0' && *c <= '9')
	{
		if (((value * 10 * sign) > 922337203685477580 && *c > '7')
			|| (value * 10 * sign) >= 9223372036854775800)
			return (-1);
		else if (((value * 10 * sign) < -922337203685477580 && *c > '8')
			|| (value * 10 * sign) <= -9223372036854775800)
			return (0);
		value = (value * 10) + (*c - '0');
		c++;
	}
	return ((int)(value * sign));
}
