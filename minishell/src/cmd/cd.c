/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujo <sujo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 15:05:19 by sujo              #+#    #+#             */
/*   Updated: 2022/04/10 12:25:14 by sujo             ###   ########.fr       */
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
	t_env	*new_node;

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
		if (check_is_file(origin))
			printf("bash: cd: %s: Not a directory\n", origin);
		else
			printf("bash: cd: %s: No such file or directory\n", origin);
		free(old_path);
		return (ERR);
	}
}

//인자를 여러개 받아도 처음 한개만을 인식
int	ft_cd(t_env *start, char *path)
{
	int		result;
	char	*old_path;
	char	*new_path;
	t_env	*new_node;

	old_path = get_pwd();
	if (path == NULL || !ft_strncmp(path, "~", 2))
	{
		new_path = search_env(start, "HOME");
		if (new_path == NULL)
		{
			printf("bash: cd: HOME not set\n");
			free(old_path);
			return (ERR);
		}
		result = chdir(new_path);
	}
	else
		result = chdir(path);
	return (update_cd(result, start, old_path, path));
}
