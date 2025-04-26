/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 14:05:51 by aychikhi          #+#    #+#             */
/*   Updated: 2025/04/26 16:35:08 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_pipe(char *input, t_tokenize_state *state)
{
	int	i;
	int	l;

	l = 0;
	i = *state->i;
	while (input[i] == '|')
	{
		i++;
		l++;
	}
	if (l > 2)
		return (printf("syntax error near unexpected token `|'\n"), 0);
	while (input[i] == ' ')
		i++;
	if (l == 2 && input[i])
		return (3);
	else if (input[i])
		return (1);
	else
		return (printf("syntax error near unexpected token `|'\n"), 0);
	return (1);
}

int	check_red(char *input, t_tokenize_state *state)
{
	int	i;
	int	l;

	l = 0;
	i = *state->i;
	if ((input[i] == '>' && input[i + 1] == '<') || (input[i] == '<' && input[i
				+ 1] == '>'))
		return (printf("syntax error\n"), 0);
	while (input[i] == '>' || input[i] == '<')
	{
		i++;
		l++;
	}
	if (l > 2)
		return (printf("syntax error\n"), 0);
	return (1);
}

int	check_tokens(t_token **tokens)
{
	t_token	*tmp;

	tmp = *tokens;
	if (tmp->type == 1)
		return (printf("syntax error near unexpected token `|'\n"), 0);
	while (tmp)
	{
		if ((tmp->type == 5 || tmp->type == 6 || tmp->type == 3
				|| tmp->type == 4) && tmp->next->type == 9)
			return (printf("syntax error\n"), 0);
		tmp = tmp->next;
	}
	return (1);
}
