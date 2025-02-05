/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 21:11:22 by hui-lim           #+#    #+#             */
/*   Updated: 2025/02/03 15:54:02 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	has_redir(t_exe **exe, t_node *node)
{
	if (node->left->rootredir != NULL)
	{
		get_redir(node->left->rootredir, exe);
	}
}

int	checkif_builtin(t_shell **shell, char **cmd)
{
	if (ft_strcmp(cmd[0], "echo") == 1)
		return (ft_echo(cmd), 1);
	if (ft_strcmp(cmd[0], "cd") == 1)
		return (ft_cd(*shell, cmd[1]));
	if (ft_strcmp(cmd[0], "pwd") == 1)
		return (ft_pwd());
	if (ft_strcmp(cmd[0], "export") == 1)
		return (ft_export(*shell, cmd));
	if (ft_strcmp(cmd[0], "unset") == 1)
		return (ft_unset(*shell, cmd));
	if (ft_strcmp(cmd[0], "env") == 1)
		return (ft_env(*shell));
	if (ft_strcmp(cmd[0], "exit") == 1)
		return (ft_exit(*shell, cmd));
	return (-1);
}

int	execute(t_node *node, t_shell **shell)
{
	t_node	*left;
	t_exe	*exe;

	left = node->left;
	if (left == NULL)
		return (0);
	if (node->type == 0)
	{
		if (isbuiltin(left->args[0]) != -1)
		{
			if (node->right == NULL)
			{
				if (node->left->rootredir != NULL)
				{
					initexenode(&exe);
					exe_commands(node, &exe, shell);
				}
				else
					checkif_builtin(shell, left->args);
				return (0);
			}
		}
		if (left != NULL)
		{
			if (left->rootredir != NULL)
			{
				if (left->rootredir->type == TOKEN_HEREDOC)
					return (2);
			}
			initexenode(&exe);
			exe_commands(node, &exe, shell);
			free(exe);
		}
	}
	return (0);
}

int	exe_commands(t_node *node, t_exe **exe, t_shell **shell)
{
	t_sigs	*sigs;

	init_exesigs(&sigs);
	if (node->right != NULL || node->left->redirs != NULL)
	{
		if (pipe((*exe)->pipefd) == -1)
			return (-1);
	}
	(*exe)->pid = fork();
	if ((*exe)->pid == -1)
		return (-1);
	if ((*exe)->pid == 0)
	{
		do_sigaction(SIGQUIT, SIGINT, sigs);
		executechild(node, exe, shell);
	}
	else if ((*exe)->pid > 0)
		sigaction(SIGINT, &(sigs->ignore), NULL);
	closeputs(exe);
		wait_children(exe, shell);
	if (node->right != NULL)
		exe_rightnode(exe, node->right, shell);
	free(sigs);
	return ((*exe)->pid);
}

void	executechild(t_node *node, t_exe **exe, t_shell **shell)
{
	has_redir(exe, node);
	if ((*exe)->puts[0] != STDIN_FILENO)
	{
		dup2((*exe)->puts[0], STDIN_FILENO);
		close((*exe)->puts[0]);
	}
	if ((*exe)->puts[1] != STDOUT_FILENO)
	{
		dup2((*exe)->puts[1], STDOUT_FILENO);
		close((*exe)->puts[1]);
	}
	else if (node->right != NULL)
	{
		close((*exe)->pipefd[0]);
		dup2((*exe)->pipefd[1], STDOUT_FILENO);
		close((*exe)->pipefd[1]);
	}
	do_execution(shell, node->left->args);
}
