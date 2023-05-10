/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurei <yurei@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:36:43 by aerrahim          #+#    #+#             */
/*   Updated: 2023/05/10 19:06:49 by yurei            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "libft/libft.h"

typedef struct s_path{
	char	**paths;
	char	*path;
	int		i;
	char	*partpath;
}	t_path;

void	get_panic(char *error);
char	*get_path(char *cmd, char **envpath);
int		get_next_line(char **line);
void	get_exe(char *av, char **envpath);
char	*get_cmd(char **path, char *av, char **envpath);

#endif
