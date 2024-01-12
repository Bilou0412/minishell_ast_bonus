/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nice_prints.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 20:26:15 by soutin            #+#    #+#             */
/*   Updated: 2024/01/12 20:26:47 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	slllllprintf("                     _ ,___,-'\",-=-.          ____");
	slllllprintf("___________________________ \n");
	slllllprintf("                 _,-'_)_  (""`'-._\\ `.         |   _");
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
	sleepprintf("            |I|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
	sleepprintf("~~~~~~~|I|\n");
	sleepprintf("             ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾");
	sleepprintf("‾‾‾‾‾‾‾‾\n");
	sleepprintf("\033[0m");
}

void	shrek_print2(void)
{
	sleepprintf("            |I|⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⣷⣀⢀⣾⠿⠻⢶⣄⠀⠀⣠⣶⡿⠶⣄⣠⣾⣿⠗⠀⠀");
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
	sleepprintf("             ____________________________________________");
	sleepprintf("_________\n");
	sleepprintf("            |I|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
	sleepprintf("~~~~~~~|I|\n");
	sleepprintf("            |I|⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⣤⣤⣤⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀");
	sleepprintf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀|I|\n");
	sleepprintf("            |I|⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣀⠀⠀⠀⢀⣴⠟⠉⠀⠀⠀⠈⠻⣦⡀⠀⠀⠀⣤⡀⠀⠀");
	sleepprintf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀|I|\n");
	shrek_print2();
}
