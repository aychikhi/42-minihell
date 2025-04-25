/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:11:41 by aychikhi          #+#    #+#             */
/*   Updated: 2025/04/25 13:13:48 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	len_value(char *input, t_env *env, int len_var)
{
	t_env	*tmp;
	int		l;

	l = 0;
	tmp = env;
	while (*input)
	{
		if (*input == '$')
		{
			input++;
			break ;
		}
		input++;
	}
	while (env)
	{
		if (!ft_strncmp(env->var, input, len_var))
			return (ft_strlen(env->value));
		env = env->next;
	}
	env = tmp;
	return (0);
}

static int	ft_newstrlen(char *input)
{
	int	i;
	int	l;

	i = 0;
	l = 0;
	while (input[i])
	{
		if (input[i] == '$')
			l++;
		i++;
	}
	return (i - l);
}

static void	handle_env_var(char **input, t_env **env, char **new_input, int *i)
{
	int		k;
	char	*var_part;
	t_env	*tmp;

	tmp = *env;
	var_part = ft_substr(*input, i[1], i[2]);
	while (tmp)
	{
		if (!ft_strncmp(tmp->var, var_part, i[2]))
		{
			k = 0;
			while (tmp->value[k])
				(*new_input)[i[0]++] = tmp->value[k++];
			i[1] += i[2];
			break ;
		}
		tmp = tmp->next;
	}
	free(var_part);
	*env = tmp;
}

static void	process_input(char *input, t_env *env, char *new_input, int len_var)
{
	int	i[3];

	i[0] = 0;
	i[1] = 0;
	i[2] = len_var;
	while (input[i[1]])
	{
		if (input[i[1]] == '$')
		{
			i[1]++;
			handle_env_var(&input, &env, &new_input, i);
		}
		else
			new_input[i[0]++] = input[i[1]++];
	}
	new_input[i[0]] = '\0';
}

char	*extract_env(char *input, t_env *env, int len_var)
{
	int		l;
	char	*new_input;
	t_env	*tmp;

	tmp = env;
	l = (ft_newstrlen(input) - len_var) + len_value(input, env, len_var);
	new_input = malloc(l + 1);
	if (!new_input)
		malloc_error();
	process_input(input, env, new_input, len_var);
	return (new_input);
}
