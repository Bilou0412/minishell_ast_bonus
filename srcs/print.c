/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 16:50:50 by soutin            #+#    #+#             */
/*   Updated: 2023/12/05 19:35:38 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	printtokens(t_tokens **head)
{
	t_tokens	*current;

	current = *head;
	while (current)
	{
		ft_printf("%s ", current->string);
		// if (current->type == WORD)
		// 	ft_printf("WORD");
		// else if (current->type == LIMITER)
		// 	ft_printf("LIMITER");
		// else if (current->type == RESERVEDW)
		// 	ft_printf("RESERVEDw");
		// else if (current->type == DOLLARS)
		// 	ft_printf("ENVVARIABLE");
		// else if (current->type == GREAT)
		// 	ft_printf("GREAT");
		// else if (current->type == DGREAT)
		// 	ft_printf("DGREAT");
		// else if (current->type == LESS)
		// 	ft_printf("LESS");
		// else if (current->type == DLESS)
		// 	ft_printf("DLESS");
		// else if (current->type == PIPE)
		// 	ft_printf("PIPE");
		// else if (current->type == AND)
		// 	ft_printf("AND");
		// else if (current->type == OR)
		// 	ft_printf("OR");
		// else if (current->type == O_PARENTHESIS)
		// 	ft_printf("O_PARENTHESIS");
		// else if (current->type == C_PARENTHESIS)
		// 	ft_printf("C_PARENTHESIS");
		current = current->next;
	}
	printf("\n");
}

void	printtab(char **v)
{
	static int	i;

	while (*v)
	{
		printf("argv[%d] : %s\n", i, *v);
		v++;
	}
	i++;
}

void	print_tree(t_ast *ast, int depth)
{
	int	i;

	i = 0;
	if (!ast)
		return ;
	print_tree(ast->right, depth + 1);
	while (i++ < depth)
		ft_printf("    ");
	if (!ast->tokens)
	{
		if (ast->type == PIPE)
			printf("| %d\n", ast->type);
		if (ast->type == OR)
			printf("|| %d\n", ast->type);
		if (ast->type == AND)
			printf("&& %d\n", ast->type);
	}
	else
	{
		printf("%d ", ast->type);
		printtokens(&ast->tokens);
	}
	print_tree(ast->left, depth + 1);
}

void	my_usleep(unsigned int microseconds)
{
	int				fd;
	unsigned int	i;

	fd = open("/dev/null", O_WRONLY);
	i = 0;
	if (fd == -1)
	{
		perror("Error opening /dev/null");
		return ;
	}
	while (i++ < microseconds)
		write(fd, "", 1);
	close(fd);
}

void	sleepprintf(char *str)
{
	my_usleep(150000);
	printf("%s", str);
}

void	slllllprintf(char *str)
{
	my_usleep(1500);
	printf("%s", str);
}

void	bye_print2(void)
{
	slllllprintf("           /\\___/      |\n");
	slllllprintf("    /         (      `.__,     /\\ /,     /           ");
	slllllprintf("            \\/__/       |\n");
	slllllprintf("   :           ;-.___         /__\\/|    /      ___");
	slllllprintf("/‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ \n");
	slllllprintf("   |         ,'      `--.      -,\\ |   /    __/ \n");
	slllllprintf("   :        /            \\    .__/    /  __/    \n");
	slllllprintf("    \\      (__            \\    |_    / /       \n");
	slllllprintf("     \\       ,`-, *       /   _|,\\             \n");
	slllllprintf("      \\    ,'   `-.     ,'_,-'    \\            \n");
	slllllprintf("     (_\\,-'    ,'\\\")--,'-'       __\\         \n");
	slllllprintf("      \\       /  // ,'|      ,--'  `-.          \n");
	slllllprintf("       `-.    `-/ \\\'  |   _,'         `.       \n");
	slllllprintf("          `-._ /      `--'/             \\       \n");
	slllllprintf("             ,'           |              \\      \n");
	slllllprintf("            /             |               \\     \n");
	slllllprintf("         ,-'              |               /      \n");
	slllllprintf("        /                 |             -'       \n");
	printf("\033[0m");
}

void	bye_print(void)
{
	printf("\033[0;31m");
	slllllprintf("                               __             \n");
	slllllprintf("                     _ ,___,-'\",-=-.         |‾‾‾‾");
	slllllprintf("‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾|\n");
	slllllprintf("                 _,-'_)_  ("
					"`'-._\\ `.         |   _");
	slllllprintf("___                        |\n");
	slllllprintf("               ,' ,-' __)  ,-     /. |       |  /\\  ");
	slllllprintf("_`\\                      |\n");
	slllllprintf("              |     -'  _)/         `\\       |  \\ ");
	slllllprintf("\\ \\L\\ \\  __  __     __     |\n");
	slllllprintf("            ,'       ,-'_,`           :      |   \\ ");
	slllllprintf("\\  _ <'/\\ \\/\\ \\  /'__`\\   |\n");
	slllllprintf("         ,-'       ,(,-(              :      |    \\ ");
	slllllprintf("\\ \\L\\ \\ \\ \\_\\ \\/\\  __/   |\n");
	slllllprintf("       ,'       ,-' ,    _            ;      |     \\");
	slllllprintf(" \\____/\\/`____ \\ \\____\\  |\n");
	slllllprintf("      /        ,-._/`---'            /      /       ");
	slllllprintf("\\/___/  `/___/> \\/____/  |\n");
	slllllprintf("     /        (____)(----. )       ,'     _/          ");
	bye_print2();
}

void	shrek_print3(void)
{
	sleepprintf("            |I|⠀⠀⠀⣿⡾⢿⣀⢀⣀⣦⣾⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣾⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡰⣫⣿");
	sleepprintf("⡿⠟⠻⠶⠀⠀⠀⠀⠀⢳⠀|I|\n");
	sleepprintf("            |I|⠀⠀⢀⣿⣧⡾⣿⣿⣿⣿⣿⡷⣶⣤⡀⠀⠀⠀⠀⠀⠀⠀⢀⡴⢿⣿⣧⠀⡀⠀⢀⣀⣀⢒⣤⣶⣿⣿");
	sleepprintf("⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⡇|I|\n");
	sleepprintf("            |I|⠀⠀⡾⠁⠙⣿⡈⠉⠙⣿⣿⣷⣬⡛⢿⣶⣶⣴⣶⣶⣶⣤⣤⠤⠾⣿⣿⣿⡿⠿⣿⠿⢿⣿⣿⣿⣿⣧");
	sleepprintf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡇|I|\n");
	sleepprintf("            |I|⠀⣸⠃⠀⠀⢸⠃⠀⠀⢸⣿⣿⣿⣿⣿⣿⣷⣾⣿⣿⠟⡉⠀⠀⠀⠈⠙⠛⠻⢿⣿⣿⣿⣿⣿⣿⣿⣿");
	sleepprintf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡇|I|\n");
	sleepprintf("            |I|⠀⣿⠀⠀⢀⡏⠀⠀⠀⢸⣿⣿⣿⣿⣿⣿⣿⠿⠿⠛⠛⠉⠁⠀⠀⠀⠀⠀⠉⠠⠿⠟⠻⠟⠋⠉⢿⣿");
	sleepprintf("⣦⡀⢰⡀⠀⠀⠀⠀⠀⠀⠁|I|\n");
	sleepprintf("            |I|⢀⣿⡆⢀⡾⠀⠀⠀⠀⣾⠏⢿⣿⣿⣿⣯⣙⢷⡄⠀⠀⠀⠀⠀⢸⡄⠀⠀⠀⠀⠀⠀⠀⠀⢀⣤⣿⣻");
	sleepprintf("⢿⣷⣀⣷⣄⠀⠀⠀⠀⢸⠀|I|\n");
	sleepprintf("            |I|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
	sleepprintf("~~|I|\n");
	sleepprintf("             ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾");
	sleepprintf("‾‾‾‾\n");
	sleepprintf("\033[0m");
}

void	shrek_print2(void)
{
	sleepprintf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀|I|\n");
	sleepprintf("            |I|⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠉⢻⣿⣿⡿⣿⠿⣿⡿⢼⣿⣿⡿⣿⣎⡟⠉⠀⠀⠀⠀");
	sleepprintf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀|I|\n");
	sleepprintf("            |I|⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣼⡟⠉⠛⢛⣛⡉⠀⠀⠙⠛⠻⠛⠑⣷⠀⠀⠀⠀⠀");
	sleepprintf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀|I|\n");
	sleepprintf("            |I|⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⣿⣧⣤⣴⠿⠿⣷⣤⡤⠴⠖⠳⣄⣀⣹⠀⠀⠀⠀⠀");
	sleepprintf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀|I|\n");
	sleepprintf("            |I|⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⣿⣀⣟⠻⢦⣀⡀⠀⠀⠀⠀⣀⡈⠻⣿⠀⠀⠀⠀⠀");
	sleepprintf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀|I|\n");
	sleepprintf("            |I|⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣼⡿⠉⡇⠀⠀⠛⠛⠛⠋⠉⠉⠀⠀⠀⠹⢧⡀⠀⠀⠀");
	sleepprintf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀|I|\n");
	sleepprintf("            |I|⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣾⡟⠀⢦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠃⠀⠈⠑⠪⠷");
	sleepprintf("⠤⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀|I|\n");
	sleepprintf("            |I|⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⣾⣿⣿⣿⣦⣼⠛⢦⣤⣄⡀⠀⠀⠀⠀⡀⠀⠀⠀⠀⠀⠀⠀⠀");
	sleepprintf("⠀⠀⠉⠑⠢⡀⠀⠀⠀⠀⠀|I|\n");
	sleepprintf("            |I|⠀⠀⠀⠀⠀⠀⠀⢀⣠⠴⠲⠖⠛⠻⣿⡿⠛⠉⠉⠻⠷⣦⣽⠿⠿⠒⠚⠋⠉⠁⡞⠁⠀⠀⠀⠀⠀⠀");
	sleepprintf("⠀⠀⠀⠀⠀⠘⢦⠀⠀⠀⠀|I|\n");
	sleepprintf("            |I|⠀⠀⠀⠀⠀⢀⣾⠛⠁⠀⠀⠀⠀⠀⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠤⠒⠉⠀⠀⠀⠀⠀⠀⠀⠀");
	sleepprintf("⠀⠀⠀⠀⠀⠀⠈⢣⠀⠀⠀|I|\n");
	sleepprintf("            |I|⠀⠀⠀⠀⣰⡿⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣑⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀");
	sleepprintf("⠀⠀⠀⠀⠀⠀⠀⠈⡇⠀⠀|I|\n");
	sleepprintf("            |I|⠀⠀⠀⣰⣿⣁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣷⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣾");
	sleepprintf("⣧⣄⠀⠀⠀⠀⠀⠀⢳⡀⠀|I|\n");
	shrek_print3();
}

void	shrek_print(void)
{
	sleepprintf("\033[0;31m   ________          __                   __   ");
	sleepprintf("           ___    ___      \n\033[0m");
	sleepprintf("\033[0;32m  /\\_____  \\        /\\ \\      __         /\\");
	sleepprintf(" \\            /\\_ \\  /\\_ \\     \n\033[0m");
	sleepprintf("\033[0;33m  \\/____//'/'     __\\ \\ \\____/\\_\\    ____");
	sleepprintf("\\ \\ \\___      __\\//\\ \\ \\//\\ \\    \n\033[0m");
	sleepprintf("\033[0;34m       //'/'    /'__`\\ \\ '__`\\/\\ \\  /',__");
	sleepprintf("\\ \\  _ `\\  /'__`\\ \\ \\  \\ \\ \\   \n\033[0m");
	sleepprintf("\033[0;35m      //'/'___ /\\  __/\\ \\ \\L\\ \\ \\ \\/\\__");
	sleepprintf(", `\\ \\ \\ \\ \\/\\  __/ \\_\\ \\_ \\_\\ \\_ \n\033[0m");
	sleepprintf("\033[0;36m      /\\_______\\ \\____\\ \\_,__/\\ \\_\\/\\_");
	sleepprintf("___/ \\ \\_\\ \\_\\ \\____\\/\\____\\/\\____\\\n\033[0m");
	sleepprintf("\033[0;30m      \\/_______/\\/____/ \\/___/  \\/_/\\/___/ ");
	sleepprintf("  \\/_/\\/_/\\/____/\\/____/\\/____/\n\033[0m");
	sleepprintf("\033[0;32m");
	sleepprintf("             ________________________________________________");
	sleepprintf("_____\n");
	sleepprintf("            |I|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
	sleepprintf("~~~|I|\n");
	sleepprintf("            |I|⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⣤⣤⣤⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀");
	sleepprintf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀|I|\n");
	sleepprintf("            |I|⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣀⠀⠀⠀⢀⣴⠟⠉⠀⠀⠀⠈⠻⣦⡀⠀⠀⠀⣤⡀⠀⠀");
	sleepprintf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀|I|\n");
	sleepprintf("            |I|⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⣷⣀⢀⣾⠿⠻⢶⣄⠀⠀⣠⣶⡿⠶⣄⣠⣾⣿⠗⠀⠀");
	shrek_print2();
	// bye_print();
}
