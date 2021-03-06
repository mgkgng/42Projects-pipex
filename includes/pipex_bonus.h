/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 19:42:14 by min-kang          #+#    #+#             */
/*   Updated: 2022/05/01 20:21:41 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdio.h>
# include <sys/types.h>
# include <fcntl.h>
# include "libft.h"


typedef struct s_pipex{
	char	*filename[2];
	int		size;
	char	***args;
	char	**paths;
	char	**envp;
}	t_pipex;

int		ft_pipex(t_pipex pipex);
int		heredoc(char *limiter);
char	*get_data(int fd);
char	**all_commands(int argc, char **argv);
void	execute_loop(t_pipex pipex);
t_pipex	parse(int argc, char **argv, char **envp);
char	*get_cmdpath(char *s, char **paths);



#endif
