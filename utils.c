/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrahim <aerrahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:36:58 by aerrahim          #+#    #+#             */
/*   Updated: 2023/05/04 15:01:43 by aerrahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	get_error(void)
{
	perror("Error occured");
	exit(EXIT_FAILURE);
}

int	has_backslash(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

char	*get_path(char *cmd, char **envpath)
{
	t_path	path;

	path.i = 0;
	if (access(cmd, F_OK | X_OK) == 0)
		return (cmd);
	else if (has_backslash(cmd))
		return (0);
	while (ft_strnstr(envpath[path.i], "PATH", 4) == 0)
		path.i++;
	path.paths = ft_split(envpath[path.i] + 5, ':');
	path.i = -1;
	while (path.paths[++(path.i)])
	{
		path.partpath = ft_strjoin(path.paths[path.i], "/");
		path.path = ft_strjoin(path.partpath, cmd);
		free(path.partpath);
		if (access(path.path, F_OK | X_OK) == 0)
			return (path.path);
		free(path.path);
	}
	path.i = -1;
	while (path.paths[++(path.i)])
		free(path.paths[path.i]);
	free(path.paths);
	return (0);
}

void	get_exe(char *av, char **envpath)
{
	int		i;
	char	*path;
	char	**cmd;

	i = -1;
	cmd = ft_split(av, ' ');
	path = get_path(cmd[0], envpath);
	if (!path)
	{
		while (cmd[++i])
			free(cmd[i]);
		free(cmd);
		get_error();
	}
	if (execve(path, cmd, envpath) == -1)
		get_error();
}

int	get_next_line(char **line)
{
	char	*buffer;
	int		i;
	int		r;
	char	c;

	i = 0;
	r = 0;
	buffer = (char *)malloc(10000);
	if (!buffer)
		return (-1);
	r = read(0, &c, 1);
	while (r && c != '\n' && c != '\0')
	{
		if (c != '\n' && c != '\0')
			buffer[i] = c;
		i++;
		r = read(0, &c, 1);
	}
	buffer[i] = '\n';
	buffer[++i] = '\0';
	*line = buffer;
	free(buffer);
	return (r);
}
