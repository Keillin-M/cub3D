/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   welcome_banner.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:18:35 by kmaeda            #+#    #+#             */
/*   Updated: 2025/10/07 11:20:51 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

void	print_welcome_banner(void)
{
	printf("\n");
	printf("             " GREEN "░█▀▀░█░█░█▀▄░▀▀█░█▀▄░" RESET "\n");
	printf("             " GREEN "░█░░░█░█░█▀▄░░▀▄░█░█░" RESET "\n");
	printf("             " GREEN "░▀▀▀░▀▀▀░▀▀░░▀▀▀░▀▀░░" RESET "\n");
	printf("\n");
	printf("    " GREEN "W" RESET ": move forward        \
		" GREEN "S" RESET ": move backward\n");
	printf("    " GREEN "A" RESET ": move left           \
		" GREEN "D" RESET ": move right\n");
	printf("    " GREEN "←" RESET ": rotate left         \
		" GREEN "→" RESET ": rotate right\n");
	printf("    " GREEN "M" RESET ": toggle minimap      \
		" GREEN "L" RESET ": toggle mouse look\n");
	printf("    " GREEN "ESC" RESET ": exit game\n");
	printf("\n");
}
