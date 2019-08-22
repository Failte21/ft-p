/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 12:27:47 by lsimon            #+#    #+#             */
/*   Updated: 2019/08/22 12:31:00 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_p.h"

int		int_error(char *message)
{
	ft_putstr(RED);
	ft_putstr(message);
	ft_putstr(RESET);
	return (-1);
}

void	*ptr_error(char *message)
{
	ft_putstr(RED);
	ft_putstr(message);
	ft_putstr(RESET);
	return (NULL);
}