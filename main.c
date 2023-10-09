/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoto-gu <acoto-gu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 14:47:33 by acoto-gu          #+#    #+#             */
/*   Updated: 2023/10/07 14:46:24 by acoto-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int	main(void)
{
	int		fd1;
	fd1 = open("test.txt", O_RDONLY);
	// fd2 = open("a.txt", O_RDONLY);
	// fd3 = open("b.txt", O_RDONLY);

	if (fd1 == -1)
		printf("error opening file\n");
	//printf("%s", get_next_line(10));
	printf("%s", get_next_line(fd1));
	printf("%s", get_next_line(fd1));
	//printf("%s", "prueba");
	printf("%s", (char *)NULL);
	if (close(fd1) == -1)
		printf("error closing file\n");
}

// int main(void)
// {
//     int fd;
//     //char str[50];
//     fd = open("test.txt", O_RDONLY);
//     int a = read(fd, NULL, 50);
//     printf("%d\n", a);
//     // a = read(fd, str, 50);
//     // printf("%d\n", a);
//     //str = get_next_line(fd);
//     return (0);
// }

// int myfun()
// {
// 	printf("Hola");
// 	return (0);
// }

// int main(void)
// {
// 	if (1 && myfun())
// 		printf("no debe imprimir Hola");
// 	// printf("%s", get_next_line());
// 	// printf("%s", get_next_line());
// 	// printf("%s", get_next_line());

// }