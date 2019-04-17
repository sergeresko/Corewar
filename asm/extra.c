void	e__read_file(t_asm *asm_struct, int errorCase)
{
	switch (errorCase) {
		case 1: ft_printf("Syntax error at token [TOKEN][%03d:%03d] ENDLINE\n",
						  asm_struct->data.line, asm_struct->data.row + 1);
			break;
		default: ft_printf("Default\n", asm_struct->data.line,
						   asm_struct->data.row);
	}

	exit(-1);
}