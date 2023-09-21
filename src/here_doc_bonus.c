/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 13:51:45 by npaolett          #+#    #+#             */
/*   Updated: 2023/09/14 17:44:05 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	ft_strlencmp(char *line, char *delim)
{
	int	len;
	int	len2;

	len = ft_strlen(line);
	len2 = ft_strlen(delim) + 1;
	return (len2 - len);
}

void	ft_here_doc(t_pipex *stack, char *delim)
{
	char	*line;
	int		fd;

	line = NULL;
	fd = open("/tmp/here_doc", O_RDWR | O_CREAT, 0666);
	if (fd < 0)
		return (perror("here_doc"), free(stack), exit(1));
	delim = ft_strdup(delim);
	while (1)
	{
		ft_putstr_fd("here_doc>", 1);
		line = get_next_line(0);
		if (!line)
			break ;
		if ((ft_strncmp(line, delim, ft_strlen(delim)) == 0)
			&& (ft_strlencmp(line, delim)) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd);
		free(line);
	}
	free(delim);
	close(fd);
}
