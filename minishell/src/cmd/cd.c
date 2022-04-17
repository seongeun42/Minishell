/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongele <seongele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 15:05:19 by sujo              #+#    #+#             */
/*   Updated: 2022/04/17 17:02:52 by seongele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_pwd(void)
{
	int		size;
	char	*buffer;

	size = 2;
	while (1)
	{
		buffer = (char *)malloc(sizeof(char) * size);
		if (!buffer)
			return (0);
		getcwd(buffer, size);
		if (*buffer == '/')
			break ;
		size += 2;
		free(buffer);
	}
	buffer = memory_fit(buffer);
	return (buffer);
}

static void	update_cd_env(t_env *start, char *key_, char *value_)
{
	t_env	*new_node;

	if (search_env(start, key_))
	{
		update_env_node(start, key_, value_);
	}
	else
	{
		new_node = create_env_new_node(key_, value_);
		insert_new_env_node(start, new_node);
	}
}

static int	check_is_file(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}

static int	update_cd(int result, t_env *start, char *old_path, char *origin)
{
	char	*old_pwd;
	char	*new_pwd;
	char	*new_path;

	if (result == 0)
	{
		old_pwd = ft_strdup("OLDPWD");
		new_pwd = ft_strdup("PWD");
		new_path = get_pwd();
		update_cd_env(start, old_pwd, old_path);
		update_cd_env(start, new_pwd, new_path);
		return (OK);
	}
	else
	{
		free(old_path);
		if (check_is_file(origin))
			erro_message("Not a directory\n", "cd", origin, 1);
		else
			erro_message("No such file or directory\n", "cd", origin, 1);
		return (ERR);
	}
}

int	ft_cd(t_env *start, char *path)
{
	int		result;
	char	*old_path;
	char	*new_path;

	old_path = get_pwd();
	if (path == NULL || !ft_strncmp(path, "~", 2))
	{
		new_path = search_env(start, "HOME");
		if (new_path == NULL)
		{
			free(old_path);
			erro_message("HOME not set\n", "cd", NULL, 1);
		}
		result = chdir(new_path);
	}
	else
		result = chdir(path);
	return (update_cd(result, start, old_path, path));
}
