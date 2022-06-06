/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoslee <hyoslee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 19:19:51 by hyoslee           #+#    #+#             */
/*   Updated: 2022/06/02 19:19:52 by hyoslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_info	g_info;

void	print_cd_error(char *str, int *err_var)
{
	char	*err;

	ft_putstr_fd(RED"bash: cd: ", STD_ERR);
	if (*err_var == CD_HOME_NOTSET)
	{
		ft_putstr_fd("HOME not set\n"RESET, STD_ERR);
		return ;
	}
	ft_putstr_fd(str, STD_ERR);
	free(str);
	str = NULL;
	ft_putstr_fd(": ", STD_ERR);
	err = strerror(errno);
	ft_putstr_fd(err, STD_ERR);
	ft_putendl_fd(""RESET, 2);
}

static char	*target_dir(t_cmdinfo *cmdinfo, int *err_var)
{
	char	*str;

	if (cmdinfo->argc == 1 || !ft_strcmp("~", cmdinfo->argv[1]))
	{
		str = env_search("HOME");
		if (!(ft_strcmp("", str)))
		{
			free(str);
			*err_var = CD_HOME_NOTSET;
			return (NULL);
		}
	}
	else if (ft_strcmp(cmdinfo->argv[1], "-") == 0)
	{
		str = env_search("OLDPWD");
		if (str)
			ft_putendl_fd(str, 1);
	}
	else
		str = ft_strdup(cmdinfo->argv[1]);
	return (str);
}

int	env_change(char *key, char *value)
{
	t_env	*cur;

	cur = g_info.env;
	while (cur)
	{
		if (!ft_strcmp(cur->key, key))
		{
			if (cur->value)
				free(cur->value);
			cur->value = value;
			return (1);
		}
		cur = cur->next;
	}
	return (0);
}

static void	renew_pwd(char *pwd, char *oldpwd)
{
	env_change("OLDPWD", ft_strdup(oldpwd));
	free(oldpwd);
	pwd = getcwd(pwd, 0);
	env_change("PWD", ft_strdup(pwd));
	free(pwd);
}

int	ft_cd(t_cmdinfo *cmdinfo, int *err_code)
{
	char	*pwd;
	char	*oldpwd;
	char	*str;
	int		err_var;

	pwd = 0;
	err_var = 0;
	oldpwd = 0;
	oldpwd = getcwd(oldpwd, 0);
	str = target_dir(cmdinfo, &err_var);
	if (chdir(str) < 0)
	{
		free(oldpwd);
		if (str)
			err_var = CD_NSFD;
		print_cd_error(str, &err_var);
		*err_code = err_var;
		return (TRUE);
	}
	free(str);
	renew_pwd(pwd, oldpwd);
	return (TRUE);
}
