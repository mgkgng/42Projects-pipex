/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 20:21:05 by min-kang          #+#    #+#             */
/*   Updated: 2022/05/01 20:25:31 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	***get_args(int argc, char **argv)
{
	char	***res;
	int		i;
	int		j;
	int		size;

	size = argc - 2;
	i = 1;
	if (!ft_strcmp("here_doc", argv[1]))
	{
		size--;
		i++;
	}
	res = ft_calloc(size + 1, sizeof(char **));
	j = 0;
	while (i < argc - 1)
		res[j++] = ft_split(argv[i++], ' ');
	res[j] = NULL;
	return (res);
}

char	**get_paths(char **envp)
{
	int		i;
	char	**res;

	i = 0;
	while (ft_strncmp(envp[i], "PATH:", 5))
		i++;
	res = ft_split(envp[i] + 5, ':');
	return (res);
}

char	*get_cmdpath(char *s, char **paths)
{
	char	*cmd;
	int		i;

    if (!access(s, F_OK))
        return (s);
	i = -1;
	while (paths[++i])
	{
		cmd = NULL;
		cmd = ft_strcat(paths[i], "/");
		cmd = ft_strcat(cmd, s);
		if (!access(cmd, F_OK))
			return (cmd);
		else
			free(cmd);
	}
	return (NULL);
}

t_pipex	parse(int argc, char **argv, char **envp)
{
	t_pipex	res;

	if (!ft_strcmp(argv[1], "here_doc"))
		res.filename[0] = argv[2];
	else
		res.filename[0] = argv[1];
	res.filename[1] = argv[argc - 1];
	res.args = get_args(argc, argv);
	res.paths = get_paths(envp);
	res.envp = envp;
	return (res);
}