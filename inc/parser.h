/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:40:29 by soutin            #+#    #+#             */
/*   Updated: 2023/12/11 19:03:39 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef enum e_token_type
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
	CLOBBER,
	WORD,
	ERRORLVL,
}					t_token_type;

typedef enum e_node_type
{
	PIPEN = 4,
	ORN,
	ANDN,
	CMDN,
}					t_node_type;

typedef struct s_expand
{
	char			*to_expand;
	char			*value;
	struct s_expand	*next;
}					t_expand;

typedef struct s_tokens
{
	char			*string;
	int				type;
	struct s_expand	*expand;
	struct s_tokens	*next;
}					t_tokens;

typedef struct s_str_data
{
	char			*buff;
	int				buff_size;
	int				curpos;
}					t_str_data;

typedef struct s_ast
{
	struct s_tokens	*tokens;
	t_node_type		type;
	struct s_ast	*left;
	struct s_ast	*right;
}					t_ast;

#endif