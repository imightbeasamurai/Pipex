/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurei <yurei@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:36:28 by aerrahim          #+#    #+#             */
/*   Updated: 2023/05/09 18:41:57 by yurei            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void child(char **av, char **envpath, int *fd)
{
	int infile;

	infile = open(av[1], O_RDONLY, 0644);
	if (infile == -1)
		get_error();
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		return (get_error());
	if (dup2(infile, STDIN_FILENO) == -1)
		return (get_error());
	close(fd[0]);
	get_exe(av[2], envpath);
}

void parent(char **av, char **envpath, int *fd, int outfile)
{
	if (dup2(fd[0], STDIN_FILENO) == -1)
		return (get_error());
	if (dup2(outfile, STDOUT_FILENO) == -1)
		return (get_error());
	close(fd[1]);
	get_exe(av[3], envpath);
}

int get_outfile(char *filename)
{
	int outfile;

	outfile = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile == -1)
		get_error();
	return (outfile);
}

void get_panic(char *error)
{
	ft_putstr_fd(error, 2);
	exit(EXIT_FAILURE);
}

int main(int ac, char **av, char **envpath)
{
	int fd[2];
	pid_t pid;
	int out;

	if (!envpath || !*envpath)
		get_panic("\033[31mInvalid envirement!\033[0m");
	if (ac == 5)
	{
		if (!*av[2] || !*av[3])
			get_panic("\033[31mInvalid Command!\n\033[0m");
		out = get_outfile(av[4]);
		if (pipe(fd) == -1)
			get_error();
		pid = fork();
		if (pid == -1)
			get_error();
		if (pid == 0)
			child(av, envpath, fd);
		parent(av, envpath, fd, out);
		while (wait(NULL))
			;
	}
	else
		get_panic("\033[31mBad number of argument!\033[0m");
	return (0);
}
