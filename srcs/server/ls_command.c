/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 11:38:56 by lsimon            #+#    #+#             */
/*   Updated: 2019/08/25 16:36:52 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_p.h"

// might cause leaks
char				**append(char **arr, char *to_append)
{
	char	**updated_arr;
	int		i;

	i = 0;
	updated_arr = (char **)malloc(sizeof(arr) + 1);
	updated_arr[0] = to_append;
	while (arr[i])
	{
		updated_arr[i + 1] = arr[i];
		i++;
	}
	updated_arr[i + 1] = NULL;
	return (updated_arr);
}

int					ls_command(t_server_handler *handler, char **args)
{
	char	*default_params[] = {"/bin/ls", ".", NULL};
	char	**params;

	params = NULL;
	params = args[0] ? append(args, "/bin/ls") : default_params;
	return exec_builtin(handler, "/bin/ls", params);
}