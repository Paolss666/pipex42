/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 14:08:51 by npaolett          #+#    #+#             */
/*   Updated: 2023/09/13 12:36:46 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	ft_child_process(t_pipex *stack, int i, char **envp)
{
	char	*good_path;
	char	**s_cmd;

	ft_redirect(stack, i);
	if (ft_strcmpchr(stack->cmd[i], ' ') == 0)
		s_cmd = ft_split(stack->cmd[i], '\0');
	else
		s_cmd = ft_split(stack->cmd[i], ' ');
	if (!s_cmd[0] || !s_cmd)
		ft_error_split(stack, s_cmd);
	good_path = get_good_path(stack, s_cmd, envp);
	if (!good_path)
		ft_error_path(stack, s_cmd, good_path, i);
	execve(good_path, s_cmd, envp);
	perror("execve");
	ft_free_tab(s_cmd);
	free(good_path);
	free(stack);
	exit(1);
}

void	parent_process(t_pipex *stack, int i)
{
	close(stack->fd[1]);
	if (i)
		close(stack->prev);
	stack->prev = stack->fd[0];
}

void	exec_pipes(t_pipex *stack, char **envp)
{
	int	i;
	int	status;

	i = -1;
	if (!envp)
		return (ft_free_tab(envp), exit(1));
	while (++i < stack->nmbr_mcd)
	{
		if (pipe(stack->fd) == -1)
			perror("pipe error");
		stack->pid[i] = fork();
		if (stack->pid[i] == -1)
			perror("fork err");
		if (stack->pid[i] == 0)
			ft_child_process(stack, i, envp);
		else
			parent_process(stack, i);
	}
	i = 0;
	while (i < stack->nmbr_mcd)
		if (waitpid(stack->pid[i++], &status, 0) == -1)
			perror("waitpid error");
	return ;
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	*stack;

	if (ac <= 4 || ac >= 6)
		ft_putstr_fd("invalid numbers of arguments\n", 2);
	else
	{
		stack = (t_pipex *)malloc(sizeof(t_pipex));
		if (!stack)
			return (free(stack), 0);
		stack->here_doc = 0;
		ft_init_stack(stack, ac, av);
		exec_pipes(stack, envp);
		close(stack->fd[0]);
		free(stack);
	}
	return (0);
}
