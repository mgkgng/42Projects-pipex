/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 18:12:33 by min-kang          #+#    #+#             */
/*   Updated: 2022/05/05 22:27:01 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	heredoc(char *limiter)
{
	char	*line;
	char	*r;
	int		fd;

	r = NULL;
	line = get_next_line(0);
	while (line)
	{
		if (ft_strlen(limiter) == ft_strlen(line) - 1
			&& !ft_strncmp(limiter, line, ft_strlen(limiter)))
			break ;
		r = ft_strcat(r, line);
		free(line);
		line = get_next_line(0);
	}
	fd = open("heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	write(fd, r, sizeof(r));
	free(r);
	return (fd);
}

int	terminate(t_pipex pipex)
{
	int	i;

	i = -1;
	while (pipex.args[++i])
		free(pipex.args[i]);
	free(pipex.paths);
	unlink("heredoc");
	return (0);
}

void	pipex_in_loop(t_pipex pipex, int *fd, int i)
{
	if (!i)
		fd[0] = open(pipex.filename[0], O_RDONLY);
	if (i == pipex.size - 1)
		fd[1] = open(pipex.filename[1], O_CREAT | O_WRONLY | O_APPEND, 0777);
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	execve(get_cmdpath(pipex.args[i][0], pipex.paths), pipex.args[i], pipex.envp);
	ft_putendl_fd("Error: execve didn't work expectedly.", STDERR_FILENO);
	exit(EXIT_FAILURE);
}

int	ft_pipex(t_pipex pipex)
{
	int		fd[2];
	pid_t	pid;
	int		i;

	i = -1;
	while (++i < pipex.size)
	{
		pipe(fd);
		pid = fork();
		if (!pid)
			pipex_in_loop(pipex, fd, i);
		else
		{
			wait(NULL);
			close(fd[0]);
			close(fd[1]);
		}
	}
	return (terminate(pipex));
}

int	main(int argc, char **argv, char **envp)
{
	if (argc < 5)
	{
		ft_putendl_fd("Wrong number of arguments.", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	return (ft_pipex(parse(argc, argv, envp)));
}
