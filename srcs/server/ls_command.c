/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 11:38:56 by lsimon            #+#    #+#             */
/*   Updated: 2019/08/22 15:32:31 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_p.h"

static unsigned int dir_display_size(DIR *dirp)
{
    struct dirent	*dp;

	if ((dp = readdir(dirp)) != NULL)
	{
		// + 1 is for space between filenames
		// No need for a -1 (extra will be used for a \0)
		return (ft_strlen(dp->d_name) + 1 + dir_display_size(dirp));
	}
	return (0);
}

void				fill(char *to_fill, DIR *dirp)
{
    struct dirent	*dp;
	int				len;

	if ((dp = readdir(dirp)) != NULL)
	{
		len = ft_strlen(dp->d_name);
		ft_memcpy(to_fill, dp->d_name, len);
		to_fill[len] = ' ';
		fill(to_fill + len + 1, dirp);
	}
}

char		*lookup()
{
    DIR				*dirp;
	char			*s;
	int				len;

    if ((dirp = opendir(".")) == NULL)
		return ptr_error("Could not open .\n");

	len = dir_display_size(dirp);
	if ((s = (char *)malloc(len)) == NULL)
		return ptr_error("malloc error\n");
	closedir(dirp);

    if ((dirp = opendir(".")) == NULL)
		return ptr_error("Could not open .\n");
	fill(s, dirp);
	closedir(dirp);
	s[len - 1] = '\0';
	return s;
}

int		ls_command(t_server_handler *handler, char **args)
{
	char *ls_display;

	while (*args != NULL)
		args = args + 1;
	ls_display = lookup();
	send(handler->pi_connection.cs, ls_display, ft_strlen(ls_display), 0);
	return (0);
}