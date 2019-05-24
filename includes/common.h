/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 23:00:03 by vlvereta          #+#    #+#             */
/*   Updated: 2019/05/22 23:28:41 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

# include <fcntl.h>
# include <stdio.h>

# define TRUE 1
# define FALSE 0
# define BYTE 8

# define LABEL_SIZE_2 2
# define LABEL_SIZE_4 4

#define IND_SIZE				2
#define REG_SIZE				4
#define DIR_SIZE				REG_SIZE


# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3


#define MAX_ARGS_NUMBER			4
#define MAX_PLAYERS				4
#define MEM_SIZE				(4*1024)
#define IDX_MOD					(MEM_SIZE / 8)
#define CHAMP_MAX_SIZE			(MEM_SIZE / 6)

#define COMMENT_CHAR			'#'
#define ALT_COMMENT_CHAR		';'

#define LABEL_CHAR				':'
#define DIRECT_CHAR				'%'
#define SEPARATOR_CHAR			','

#define LABEL_CHARS				"abcdefghijklmnopqrstuvwxyz_0123456789"

#define NAME_CMD_STRING			".name"
#define COMMENT_CMD_STRING		".comment"

#define REG_NUMBER				16

#define CYCLE_TO_DIE			1536
#define CYCLE_DELTA				50
#define NBR_LIVE				21
#define MAX_CHECKS				10

/*
**
*/

typedef char	t_arg_type;

#define T_REG					1
#define T_DIR					2
#define T_IND					4
#define T_LAB					8

/*
 * Champ's header
 */
# define CHAR_HEADER			5480
# define HEX_HEADER 			4384
# define NAME_LENGTH			128
# define HEX_NAME_LENGTH 		256
# define DESC_LENGTH			2048
# define HEX_DESC_LENGTH 		4096
# define COREWAR_EXEC_MAGIC		0xea83f3

# define ASM_USAGE "Usage: ./asm [-a] <sourcefile.s>\n    -a : Instead of creating a .cor file, outputs a stripped and annotated version of the code to the standard output\n    -d : Disassembling .cor file"
# define ASM_INITIALIZATION_ERROR "Asm initialization failed"

# define COR_USAGE "Usage: ./corewar [-d N -s N -v N | -b --stealth | -n --stealth] [-a] <champion1.cor> <...>\n    -a        : Prints output from \"aff\" (Default is to hide it)"

# define OPEN_FILE_ERROR "Can't read source file "
# define READ_FILE_ERROR "Cannot read file"
# define TRIM_LINE_ERROR "Something went wrong while trimming a line: "


/*
 * Current index and size of the champion / asm
 */
extern int g_index;

/*
 * Dumping annotated mode / asm
 */
extern int g_dump_mode;

/*
 * Global error mode for reading / asm
 */
extern int g_error_mode;

/*
 * Is dump flag / corewar
 */
extern int g_is_dump;
extern int g_dump_cycles;

/*
 * Commands' arguments list
 */
extern const t_arg_type LIVE[3][3];
extern const t_arg_type LD[3][3];
extern const t_arg_type ST[3][3];
extern const t_arg_type ADD[3][3];
extern const t_arg_type SUB[3][3];
extern const t_arg_type AND[3][3];
extern const t_arg_type OR[3][3];
extern const t_arg_type XOR[3][3];
extern const t_arg_type ZJMP[3][3];
extern const t_arg_type LDI[3][3];
extern const t_arg_type STI[3][3];
extern const t_arg_type FORK[3][3];
extern const t_arg_type LLD[3][3];
extern const t_arg_type LLDI[3][3];
extern const t_arg_type LFORK[3][3];
extern const t_arg_type AFF[3][3];

/*
 * Common staff
 */
typedef struct		s_player
{
	char 			*name;
	char 			*comment;
	int				size;
	int 			number;
	int 			fd;
	int 			self;
	const char 		*filename;
	struct s_player	*next;
}					t_player;

char	*convert_int_to_hex(int num);
unsigned int		parse_int(void *buf);

void				read_headers(t_player *players);
void	            check_magic(char *header, t_player *player);
char                *read_player_name(const char *header);
char                *read_player_comment(const char *header);

/*
 * Error staff
 */
void	exit_with_usage(void);
void    e__args_amount(void);
void	e__open_file(const char *name);

#endif
