/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 17:04:31 by aychikhi          #+#    #+#             */
/*   Updated: 2025/04/25 13:18:31 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_token(t_token **tokens, t_token **last, t_token_type type,
		const char *value)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		malloc_error();
	new_token->type = type;
	new_token->value = ft_strdup(value);
	new_token->next = NULL;
	if (!*tokens)
	{
		*tokens = new_token;
		*last = new_token;
	}
	else
	{
		(*last)->next = new_token;
		*last = new_token;
	}
}

static int	handle_dollar(char *input)
{
	int	i;
	int	l;

	i = 0;
	l = 0;
	if (ft_isalpha(input[1]) || input[1] == '_')
	{
		i++;
		while (input[i] && (ft_isalnum(input[i]) || input[i] == '_'))
		{
			l++;
			i++;
		}
	}
	return (l);
}

static int	check_env_name(char *input, int len, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (env)
	{
		if (!ft_strncmp(env->var, input, len))
			return (1);
		env = env->next;
	}
	env = tmp;
	return (0);
}

static char	*handle_env_expansion(char *input, int i, t_env *env)
{
	int		l;
	char	*result;

	l = handle_dollar(input + i);
	if (check_env_name(input + (i + 1), l, env))
	{
		result = extract_env(input, env, l);
		return (result);
	}
	return (NULL);
}

char	*expand_env(char *input, t_env *env)
{
	int		in_sq;
	int		i;
	char	*result;
	char	*original_input;

	i = 0;
	in_sq = 0;
	original_input = input;
	while (input[i])
	{
		if (input[i] == '\'')
			in_sq = !in_sq;
		else if (input[i] == '$' && !in_sq)
		{
			result = handle_env_expansion(input + i, 0, env);
			if (result)
			{
				if (input != original_input)
					free(input);
				return (result);
			}
		}
		i++;
	}
	return (input);
}
