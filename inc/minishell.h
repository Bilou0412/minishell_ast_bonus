/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <bmoudach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 12:18:19 by bmoudach          #+#    #+#             */
/*   Updated: 2023/10/25 12:19:47 by bmoudach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <string.h>
# include <sys/types.h>

typedef struct s_ast_tokens
{
	char				**token;
	int					type;
	struct s_ast_tokens	*right;
	struct s_ast_tokens	*left;
}						t_ast_tokens;

typedef struct s_tokens
{
	struct s_tokens		*next;
	char				*token;
	int					type;
}						t_tokens;

typedef struct s_input_str
{
	char				*buff;
	int					curpos;
	int					buff_size;
}						t_input_str;

enum					e_token_type
{
	LESS,
	DLESS,
	GREAT,
	DGREAT,
	PIPE,
	OR,
	AND,
	O_PARENTHESIS,
	C_PARENTHESIS,
	WORD,
	ERRORLVL,
	DOLLARS,
	LIMITER,
	RESERVERDW,
	FILEM,
	INDEFINE,
};

void					ft_lstadd_back(t_tokens **lex_tok, t_tokens *new);
t_tokens				*ft_lstnew(char *content, int type);
t_tokens				*ft_lstlast(t_tokens **tok);
int						token_m(t_input_str *str_in, t_tokens **tok);
int						free_struc(t_tokens *tok);
void					ft_lstadd_front(t_tokens **tok, t_tokens *new);
int						tok_type(char *content);
int						check_char(t_input_str *str_in);
char					*del_quote(char *word);

#endif