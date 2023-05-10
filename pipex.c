/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurei <yurei@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:36:28 by aerrahim          #+#    #+#             */
/*   Updated: 2023/05/10 19:08:07 by yurei            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void child(char **av, char **envpath, int *fd)
{
	int infile;

	infile = open(av[1], O_RDONLY, 0644);
	if (infile == -1)
		get_panic("\033[31mError: can't open infile\033[0m");
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		get_panic("\033[31mError: child dup2\033[0m");
	if (dup2(infile, STDIN_FILENO) == -1)
		get_panic("\033[31mError: child dup2\033[0m");
	close(fd[0]);
	get_exe(av[2], envpath);
}

void parent(char **av, char **envpath, int *fd, int outfile)
{
	if (dup2(fd[0], STDIN_FILENO) == -1)
		get_panic("\033[31mError: parent dup2\033[0m");
	if (dup2(outfile, STDOUT_FILENO) == -1)
		get_panic("\033[31mError: parent dup2\033[0m");
	close(fd[1]);
	get_exe(av[3], envpath);
}

int get_outfile(char *filename)
{
	int outfile;

	outfile = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile == -1)
		get_panic("\033[31mError: can't create outfile\033[0m");
	return (outfile);
}

int main(int ac, char **av, char **envpath)
{
	int fd[2];
	pid_t pid;
	int out;

	if (!envpath || !*envpath)
		get_panic("\033[31mError: environment not found\033[0m");
	if (ac == 5)
	{
		if (!*av[2] || !*av[3])
			get_panic("\033[31mError: invalid action\n\033[0m");
		out = get_outfile(av[4]);
		if (pipe(fd) == -1)
			get_panic("\033[31mError: pipe\n\033[0m");
		pid = fork();
		if (pid == -1)
			get_panic("\033[31mError: fork\n\033[0m");
		if (pid == 0)
			child(av, envpath, fd);
		parent(av, envpath, fd, out);
		while (wait(NULL))
			;
	}
	else
		get_panic("\033[31mError: invalid action\033[0m");
	return (0);
}
