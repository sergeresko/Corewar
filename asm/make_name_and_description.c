/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_name_and_description.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaliskyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 20:50:03 by vlvereta          #+#    #+#             */
/*   Updated: 2019/04/23 23:39:07 by zaliskyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void check_instruction(char *eline, t_asm *asm_struct, int i)
{
	printf("INSTRUCTION \"%s\"\n", eline);
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
	printf("REGISTER \"%s\"\n", eline);
	exit(-1);
}

void check_direct_label(char *eline, t_asm *asm_struct, int i)
{
	printf("DIRECT_LABEL \"%s\"", eline);
	exit(-1);
}

void check_colon(char *eline, t_asm *asm_struct, int i)
{
	int j = 0;
	char *colon_line;
	if (get_substr_index(eline, ":") == 0)
	{
		printf("INDIRECT_LABEL \"%s\"\n", eline);
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
	printf("LABEL \"%s\"\n", colon_line);
	exit(-1);//TODO check if colon in the begin or end
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
	printf("Lexical error at [%d:%d]\n",asm_struct->data.line,i);
	exit(-1);
}

void check_commands(char *eline, t_asm *asm_struct, int i)
{
	if (get_substr_index(eline, NAME_CMD_STRING) == 0)
	{
		printf("COMMAND_NAME .name[%d:%d]\n",asm_struct->data.line,i);
		exit(-1);
	}

	if (get_substr_index(eline, COMMENT_CMD_STRING) == 0)
	{
		printf("COMMAND_NAME .command[%d:%d]\n",asm_struct->data.line,i);
		exit(-1);
	}
	check_lexical(eline, asm_struct, i);
}

void check_indirect(char *eline, t_asm *asm_struct, int i)
{
	if (eline[0] == '-' && !(eline[1] > 47 && eline[1] < 58))
		check_lexical(eline, asm_struct, i);
	if (eline[1] == ':')
		check_direct_label(eline, asm_struct, i);
	if ((eline[0] > 47 && eline[0] < 58) && eline[1] != '\0' && !(eline[1] > 47 && eline[1] < 58))
		check_instruction(eline, asm_struct, i);
	long num_string = ft_atoi(eline);
	printf("INDIRECT \"%s\"\n", eline);  //TODO check 000 & 000a
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

	if (line[i] == 35)
	{
		printf("endline");
		exit(-1);
	}
	else if ((line[i] > 64 && line[i] < 91) || (line[i] > 96 && line[i] < 123) ||
	 line[i] == 95 || (line[i] > 47 && line[i] < 58) || line[i] == 45)
	{
		if (line[i] == 'r')
			check_register(eline, asm_struct, i);
		if ((line[i] > 47 && line[i] < 58) || line[i] == '-')
			check_indirect(eline, asm_struct, i);

		printf("INSTRUCTION \"%s\"", eline);
		exit(-1);
	}
	else if (line[i] > 47 && line[i] < 58)
	{
		printf("indirect");
		exit(-1);
	}
	else if (line[i] == ',')
	{
		printf("SEPARATOR \"%c\"",line[i]);
		exit(-1);
	}
	else if (line[i] == 33)
	{
		printf("lexical");
		exit(-1);
	}
	else if (line[i] == '.')
	{
		check_commands(eline, asm_struct, i);
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
		make_hex_name(asm_struct->header.name, field);
		ft_strdel(&field);
	}
	else
		get_error_code(line, asm_struct, i); //TODO error management
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
		make_hex_description(asm_struct->header.description, field);
		ft_strdel(&field);
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
