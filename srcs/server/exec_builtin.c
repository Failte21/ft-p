/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 16:21:47 by lsimon            #+#    #+#             */
/*   Updated: 2019/08/22 16:27:41 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_p.h"

int	exec_builtin(t_server_handler *handler, char *bin, char **args)
{
	int				status;
	struct rusage	m_rusage;

	pid_t			pid;

	pid = fork();

	if (pid < 0)
		return int_error("fork error");
	if (pid == 0)
	{
		dup2(handler->pi_connection.cs, 1);
		if (execv(bin, args) < 0)
			return (int_error("execv error"));
	}
	else
	{
		wait4(pid, &status, 0, &m_rusage);
		if (WEXITSTATUS(status))
			return (-1);
		send(handler->pi_connection.cs, "\0", 1, 0);
		return (0);
	}
	return (0);
	
}