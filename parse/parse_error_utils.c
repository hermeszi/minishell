/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hui-lim <hui-lim@student.42singapore.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 21:51:01 by hui-lim           #+#    #+#             */
/*   Updated: 2025/02/27 21:51:05 by hui-lim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_error(char *cmd, char *error, int status, t_shell **shell)
{
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(error, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	(*shell)->exit_status = status;
}

int	ispath(char *t)
{
	if (t[0] == '/')
		return (1);
	if ((t[0] == '.' && t[1] == '/'))
		return (2);
	return (0);
}

int	handle_path(char *t, t_shell **s)
{
	int	path_type;

	path_type = ispath(t);
	if (path_type != 0)
	{
		if (check_path_type(t) == TYPE_DIR)
			return (parse_error(t, "Is a directory", 126, s), -1);
		else if (check_path_type(t) == TYPE_FILE)
		{
			if ((path_type == 2 && access(t, X_OK) == -1))
				return (parse_error(t, "Permission denied", 126, s), -1);
			if (path_type == 1 && access(t, W_OK) == -1)
				return (parse_error(t, "Permission denied", 126, s), -1);
		}
		else
			return (parse_error(t, "No such file or directory", 127, s), -1);
		return (1);
	}
	return (0);
}
