/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:40:29 by soutin            #+#    #+#             */
/*   Updated: 2023/10/25 16:00:04 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

enum				e_token_type
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

typedef struct s_tokens
{
	char			*string;
	int				type;
	struct s_tokens	*next;
}					t_tokens;

typedef struct s_input_str
{
	char			*buff;
	int				buff_size;
	int				curpos;
}					t_input_str;

typedef struct s_cmds
{
	char			*string;
	int				type;
	struct s_cmds	*next;
}					t_cmds;

typedef struct s_ast
{
	struct s_cmds	*cmds;
	struct s_ast	*left;
	struct s_ast	*right;
}					t_ast;

int					token_m(t_input_str *str_in, t_tokens **tok);
int					tok_type(char *content);

void				launch_ast(t_tokens **head, t_ast **root);
int					is_command_line(t_tokens *current, t_ast **root);
void				is_command(t_tokens **current, t_ast *node);

int					check_char(t_input_str *str_in);
char				*del_quote(char *word);

#endif