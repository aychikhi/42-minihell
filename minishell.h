/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:13:29 by aychikhi          #+#    #+#             */
/*   Updated: 2025/04/26 18:35:38 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_SPACE,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_SINGLE_QUOTE,
	TOKEN_DOUBLE_QUOTE,
	TOKEN_EOF,
}					t_token_type;

typedef struct s_file
{
	char			*name;
	int				type;
	struct s_file	*next;
}					t_file;

typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	t_file			*file;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_env
{
	char			*var;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_command
{
	t_env			*env;
	t_cmd			*cmd;
	unsigned char	exit_status;
}					t_command;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}					t_token;

typedef struct s_tokenize_state
{
	int				*i;
	t_token			**tokens;
	t_token			**last;
}					t_tokenize_state;

typedef struct s_exp_data
{
	int				i;
	int				in_sq;
	int				in_dq;
	t_env			*env;
	char			*expanded;
}					t_exp_data;

int					error_fun(void);
char				*ft_itoa(int n);
int					ft_isdigit(int c);
int					ft_isalpha(int c);
int					ft_isalnum(int c);
void				malloc_error(void);
char				*add_word(char *str);
t_env				*env_init(char **env);
void				one_space(char **line);
char				*extract_var(char *var);
int					check_quotes(char *line);
void				check_unprint(char **line);
int					ft_strlen(const char *str);
char				*ft_strdup(const char *s1);
char				*extract_value(char *value);
void				free_tokens(t_token *tokens);
int					check_tokens(t_token **tokens);
int					skip_fun(char *line, int flag);
int					skip_spaces(char *input, int *i);
t_env				*ft_lstnew(void *var, void *value);
char				*expand_env(char *input, t_env *env);
void				check_and_join_token(t_token ***token);
void				ft_lstadd_back(t_env **lst, t_env *new);
char				*ft_strcpy(char *dest, const char *src);
int					ft_strcmp(const char *s1, const char *s2);
char				*add_word_inside_quote(char c, char *str);
void				handle_out_redirection(char *input, int *i,
						t_token **tokens, t_token **last);
void				add_token(t_token **tokens, t_token **last,
						t_token_type type, const char *value);
char				*ft_strjoin(char const *s1, char const *s2);
t_tokenize_state	tokenize_state_init(int *i, t_token **tokens,
						t_token **last);
char				*ft_substr(char const *s, int start, int len);
void				tokeniser(char *input, t_env *env, t_cmd *cmd);
char				*ft_strncpy(char *dest, const char *src, int n);
int					check_red(char *input, t_tokenize_state *state);
int					check_pipe(char *input, t_tokenize_state *state);
void				handle_word(char *input, int *i, t_token **tokens,
						t_token **last);
void				handle_quotes(char *input, int *i, t_token **tokens,
						t_token **last);
char				*extract_env(char *input, t_env *env, int dollar_pos,
						char *var_name);
void				handle_redirection(char *input, int *i, t_token **tokens,
						t_token **last);
void				handle_in_redirection(char *input, int *i, t_token **tokens,
						t_token **last);

#endif