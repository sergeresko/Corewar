/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_name_and_description.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaliskyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 20:50:03 by vlvereta          #+#    #+#             */
/*   Updated: 2019/05/03 00:52:58 by zaliskyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "asm.h"

void check_instruction(char *eline, t_asm *asm_struct, int i)
{
	printf("Syntax error at token [TOKEN][%03d:%03d] INSTRUCTION \"%s\"\n",
			asm_struct->data.line, i + 1, eline);
	exit(-1);
}

void check_register(char *eline, t_asm *asm_struct, int i)
{
	int j = 1;
	if (ft_strlen(eline) > 3 || ft_strlen(eline) == 1)
		check_instruction(eline, asm_struct, i);
	if (eline[j] > 47 && eline[j] < 58 && j < 3)
		++j;
	else
		check_instruction(eline, asm_struct, i);
	printf("Syntax error at token [TOKEN][%03d:%03d] REGISTER \"%s\"\n",
		   asm_struct->data.line, i + 1, eline);
	exit(-1);
}

void check_direct_label(char *eline, t_asm *asm_struct, int i)
{
	printf("Syntax error at token [TOKEN][%03d:%03d] DIRECT_LABEL \"%s\"\n",
		   asm_struct->data.line, i + 1, eline);
	exit(-1);
}

void check_colon(char *eline, t_asm *asm_struct, int i)
{
	int j = 0;
	char *colon_line;
	if (get_substr_index(eline, ":") == 0)
	{
		printf("Syntax error at token [TOKEN][%03d:%03d] INDIRECT_LABEL \"%s\"\n",
			   asm_struct->data.line, i + 1, eline);
		exit(-1);
	}
	if (eline[0] == '%')
		check_direct_label(eline, asm_struct, i);

	while (eline[j] != ':')
		++j;
	if (!(colon_line = ft_strnew(j)))
		return ;
	j = 0;
	while (eline[j] != ':')
	{
		colon_line[j] = eline[j];
		++j;
	}
	colon_line[j] = eline[j];
	printf("Syntax error at token [TOKEN][%03d:%03d] LABEL \"%s\"\n",
		   asm_struct->data.line, i + 1, colon_line);
	exit(-1);
}

int		ft_nbr_lngth(long n)
{
	if (n == 0)
		return (1);
	if (n < 0)
		return (1 + ft_nbr_lngth(n * -1));
	if (n > 0 && n <= 9)
		return (1);
	if (n / 10 != 0)
		return (1 + ft_nbr_lngth(n / 10));
	return (0);
}

void check_lexical(char *eline, t_asm *asm_struct, int i)
{
	printf("Lexical error at [%d:%d]\n",asm_struct->data.line, i + 1);
	exit(-1);
}

void check_commands(char *eline, t_asm *asm_struct, int i)
{
	if (get_substr_index(eline, NAME_CMD_STRING) == 0)
	{
		printf("Syntax error at token [TOKEN][%03d:%03d] COMMAND_NAME \".name\"\n",
			   asm_struct->data.line, i + 1);
		exit(-1);
	}

	if (get_substr_index(eline, COMMENT_CMD_STRING) == 0)
	{
		printf("Syntax error at token [TOKEN][%03d:%03d] COMMAND_COMMENT \".comment\"\n",
			   asm_struct->data.line, i + 1);
		exit(-1);
	}
	check_lexical(eline, asm_struct, i);
}

bool check_for_letters(char *eline, t_asm *asm_struct, int i)
{
	int j;

	j = 0;
	while (j < ft_strlen(eline))
	{
		if (!(eline[j]> 47 && eline[j] < 58 ))
			return (true);
		++j;
	}
	return (false);
}

void check_for_symbols(char *eline, t_asm *asm_struct, int i)
{
	int j;

	j = 0;
	while (j < ft_strlen(eline))
	{
		if (!(eline[j]> 47 && eline[j] < 58 ) && !(eline[j] > 64 && eline[j] < 91 )
		&& !(eline[j] > 96 && eline[j] < 123 ))
			check_lexical(eline, asm_struct, i + j + 1);
		++j;
	}
}

void check_indirect(char *eline, t_asm *asm_struct, int i)
{
	if (eline[0] == '-' && !(eline[1] > 47 && eline[1] < 58))
		check_lexical(eline, asm_struct, i);
	if (eline[1] == ':')
		check_direct_label(eline, asm_struct, i);
	check_for_symbols(eline, asm_struct, i);
	if (check_for_letters(eline, asm_struct, i))
		check_instruction(eline, asm_struct, i);
	printf("Syntax error at token [TOKEN][%03d:%03d] INDIRECT \"%s\"\n",asm_struct->data.line, i + 1, eline);
	exit(-1);
}

void check_direct(char *eline, t_asm *asm_struct, int i)
{
	char *direct_line;
	int j = 1;
	int k = 0;

	if (!(eline[1] > 47 && eline[1] < 58))
		check_lexical(eline, asm_struct, i);
	if (eline[1] == ':')
		check_direct_label(eline, asm_struct, i);



	while (eline[j] > 47 && eline[j] < 58)
		++j;
	if (!(direct_line = ft_strnew(j)))
		return ;
	while (k < j)
	{
		direct_line[k] = eline[k];
		++k;
	}

	printf("DIRECT \"%s\"", direct_line);
	exit(-1);
}

void	get_error_code(char *line, t_asm *asm_struct, int i)
{
	char *eline;
	int j;
	int elineIndex = 0;

	j = i;

	while (line[j] != ' ' && line[j] != '\0' && line[j] != '"')
		++j;

	if (!(eline = ft_strnew(j-i)))
		return ;
	j = i;
	while(line[j] != ' ' && line[j] != '\0' && line[j] != '"')
		eline[elineIndex++] = line[j++];

	if (get_substr_index(eline, ":") >= 0)
		check_colon(eline, asm_struct, i);

	if (line[i] == 35 || line[i] == '\0')
	{
		printf("Syntax error at token [TOKEN][%03d:%03d] ENDLINE \n",
			   asm_struct->data.line, (int)(ft_strlen(line)) + 1);
		exit(-1);
	}
	else if ((line[i] > 64 && line[i] < 91) || (line[i] > 96 && line[i] < 123) ||
	 line[i] == 95 || (line[i] > 47 && line[i] < 58) || line[i] == 45)
	{
		if (line[i] == 'r')
			check_register(eline, asm_struct, i);
		if ((line[i] > 47 && line[i] < 58) || line[i] == '-')
			check_indirect(eline, asm_struct, i);

		check_instruction(eline, asm_struct, i);
	}
	else if (line[i] > 47 && line[i] < 58)
	{
		printf("indirect");
		exit(-1);
	}
	else if (line[i] == ',')
	{
		printf("Syntax error at token [TOKEN][%03d:%03d] SEPARATOR \",\" \n",
			   asm_struct->data.line, i + 1);
		exit(-1);
	}
	else if (line[i] == '.')
	{
		check_commands(eline, asm_struct, i);
	}
	else if (line[i] == '%')
	{
		check_direct(eline, asm_struct, i);
	}
	else
	{
		check_lexical(eline, asm_struct, i);
	}
}

void	get_champs_name(char *line, t_asm *asm_struct)
{
	size_t	i;
	size_t	j;
	char	*field;

	i = 0;
	j = 0;
	if (!(field = ft_strnew(NAME_LENGTH)))
		return ;
	if (line[i] == '.')
		i++;
	if (strncmp(".name", line, 5) != 0)
		printf("qweq"); //TODO go to error management
	else
		i = i + 4;
	while (line[i] == ' ')
		i++;
	if (line[i] == '"')
	{
		i++;
		while (i < ft_strlen(line) && line[i] != '"')
			i++ && j++;
		i = i - j;
		j = 0;
		while (i < ft_strlen(line) && line[i] != '"')
			field[j++] = line[i++];
		if (line[i] == '\0')
			get_error_code(line, asm_struct, i);
		make_hex_name(asm_struct->header.hex_name, field);
		ft_strdel(&field);
		asm_struct->data.got_name = 1;
	}
	else
		get_error_code(line, asm_struct, i);
	++i;
	while (line[i] == ' ')
		i++;
	if (line[i] != '\0' && line[i] != '#')
		get_error_code(line, asm_struct, i);
//	if (line[i] == '\0')
//		asm_struct->data.errorCase = 1;
}

void	make_hex_name(char *hex_name, char *name)
{
	int 	i;
	int 	j;
	int 	len;
	char	*temp;

	ft_memset((void *)hex_name, '0', HEX_NAME_LENGTH);
	hex_name[HEX_NAME_LENGTH] = '\0';
	i = 0;
	j = 0;
	len = ft_strlen(name);
	while (i < len && j < HEX_NAME_LENGTH - 1)
	{
		temp = ft_itoa_base(name[i++], 16);
		hex_name[j++] = ft_tolower(temp[0]);
		hex_name[j++] = ft_tolower(temp[1]);
		ft_strdel(&temp);
	}
}

void	get_champs_description(char *line, t_asm *asm_struct)
{
	size_t	i;
	size_t	j;
	char 	*field;

	i = 0;
	j = 0;
	if (!(field = ft_strnew(DESC_LENGTH)))
		return ;
	if (line[i] == '.')
		i++;
	if (strncmp(".comment", line, 8) != 0)
		printf("qweq"); //TODO go to error management
	else
		i = i + 7;
	while (line[i] == ' ')
		i++;
	if (line[i] == '"')
	{
		i++;
		while (i < ft_strlen(line) && line[i] != '"')
			i++ && j++;
		i = i - j;
		j = 0;
		while (i < ft_strlen(line) && line[i] != '"')
			field[j++] = line[i++];
		make_hex_description(asm_struct->header.hex_description, field);
		ft_strdel(&field);
		asm_struct->data.got_description = 1;
	}
	else if (line[i] == '\0')
		asm_struct->data.errorCase = 1;
}

void	make_hex_description(char *hex_description, char *description)
{
	int 	i;
	int 	j;
	int 	len;
	char	*temp;

	ft_memset((void *)hex_description, '0', HEX_DESC_LENGTH);
	hex_description[HEX_DESC_LENGTH] = '\0';
	i = 0;
	j = 0;
	len = ft_strlen(description);
	while (i < len && j < HEX_DESC_LENGTH - 1)
	{
		temp = ft_itoa_base(description[i++], 16);
		hex_description[j++] = ft_tolower(temp[0]);
		hex_description[j++] = ft_tolower(temp[1]);
		ft_strdel(&temp);
	}
}
