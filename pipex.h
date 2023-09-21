/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 14:13:35 by npaolett          #+#    #+#             */
/*   Updated: 2023/09/14 17:44:31 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define STDIN 0
# define STDOUT 1
# define INFILE 0
# define OUTFILE 1

typedef struct s_pipex
{
	char	**envp;
	char	**cmd;
	char	*fd_infile;
	char	*fd_outfile;
	int		fd[2];
	int		prev;
	int		nmbr_mcd;
	pid_t	pid[1024];
	int		here_doc;
}			t_pipex;

// ------------ pipex_utils ------------ //

char		*find_path(char **env);
char		*get_good_path(t_pipex *stack, char **cmd, char **env);
int			ft_strcmpchr(const char *s, int c);
int			open_file(t_pipex *stack, int ind);
int			fd_in_open(int fd, t_pipex *stack);
int			fd_out_open(int fd, t_pipex *stack);
void		ft_init_stack(t_pipex *stack, int ac, char **av);
void		ft_redirect(t_pipex *stack, int i);
void		ft_child_process(t_pipex *stack, int i, char **envp);
void		parent_process(t_pipex *stack, int i);
void		exec_pipes(t_pipex *stack, char **envp);
void		ft_here_doc(t_pipex *stack, char *delim);

// ------------ gestion d'erreur  ------------ //

void		ft_error_path(t_pipex *stack, char **s_cmd, char *good_path, int i);
void		ft_error_split(t_pipex *stack, char **s_cmd);
void		ft_error_directory(t_pipex *stack);
void		ft_error_directory_fd_out(t_pipex *stack);
void		ft_free_tab(char **tab);

#endif