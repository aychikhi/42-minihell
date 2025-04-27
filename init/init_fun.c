/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fun.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:46:02 by aychikhi          #+#    #+#             */
/*   Updated: 2025/04/27 20:34:59 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_tokenize_state	tokenize_state_init(int *i, t_token **tokens,
		t_token **last)
{
	t_tokenize_state	state;

	state.i = i;
	state.tokens = tokens;
	state.last = last;
	return (state);
}

t_env	*env_init(char **env)
{
	t_env	*new_env;
	t_env	*last;
	t_env	*new_node;
	int		i;

	new_env = NULL;
	last = NULL;
	if (!env || !*env)
		return (NULL);
	new_env = ft_lstnew(extract_var(env[0]), extract_value(env[0]));
	if (!new_env)
		return (NULL);
	last = new_env;
	i = 1;
	while (env[i])
	{
		new_node = ft_lstnew(extract_var(env[i]), extract_value(env[i]));
		if (!new_node)
			return (NULL);
		ft_lstadd_back(&last, new_node);
		last = last->next;
		i++;
	}
	return (new_env);
}

static int	arg_size(t_token *tokens)
{
	t_token	*tmp;
	int		size;

	size = 0;
	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == 1 || tmp->type == 9)
			break ;
		else if (tmp->type == 3 || tmp->type == 4 || tmp->type == 5
			|| tmp->type == 6)
			tmp = tmp->next->next->next;
		else if (tmp->type == 2)
			tmp = tmp->next;
		else
		{
			size++;
			tmp = tmp->next;
		}
	}
	return (size);
}

void	init_command(t_command **cmd, t_token *tokens, t_env **env)
{
	if (!*cmd)
	{
		*cmd = malloc(sizeof(t_command));
		if (!*cmd)
			malloc_error();
	}
	(*cmd)->env = *env;
	init_cmd(&(*cmd)->cmd, tokens);
	(*cmd)->exit_status = 0;
}
