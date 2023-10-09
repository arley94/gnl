/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoto-gu <acoto-gu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 09:36:18 by acoto-gu          #+#    #+#             */
/*   Updated: 2023/10/07 15:00:10 by acoto-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*process_str(char **str)
{
	char	*str_nl;
	char	*str_tmp;

	str_nl = NULL;
	if (*str && ft_strchr(*str, '\n'))
	{
		str_nl = ft_substr(*str, 0, ft_strchr(*str, '\n') - *str + 1);
		if (!str_nl)
		{
			free(*str);
			*str = NULL;
			return (NULL);
		}
		str_tmp = *str;
		*str = ft_substr(ft_strchr(*str, '\n') + 1, 0, ft_strlen(*str));
		free(str_tmp);
		if (!*str)
			return (NULL);
		if (ft_strlen(*str) == 0)
		{
			free(*str);
			*str = NULL;
		}
	}
	else if (*str)
	{
		str_nl = ft_substr(*str, 0, ft_strlen(*str));
		free(*str);
		*str = NULL;
		if (!str_nl)
			return (NULL);
	}
	return (str_nl);
}

int	buf_to_str(int fd, char **str)
{
	int		read_result;
	char	*str_buf;
	char	*tmp_str;

	str_buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!str_buf)
		return (-1);
	read_result = read(fd, str_buf, BUFFER_SIZE);
	if (read_result > 0)
	{
		str_buf[read_result] = '\0';
		if (*str == NULL)
			*str = str_buf;
		else
		{
			tmp_str = ft_strjoin(*str, str_buf);
			if (!tmp_str)
				return (-1);
			free(*str);
			*str = tmp_str;
			free(str_buf);
		}
	}
	else
		free(str_buf);
	return (read_result);
}

char	*get_next_line_aux(char **str, int fd)
{
	int		r_result;
	char	*str_nl;

	str_nl = NULL;
	if (*str && ft_strchr(*str, '\n'))
	{
		str_nl = process_str(str);
		return (str_nl);
	}
	r_result = BUFFER_SIZE;
	while (!str_nl && r_result > 0)
	{
		r_result = buf_to_str(fd, str);
		if ((r_result >= 0 && r_result < BUFFER_SIZE)
			|| (r_result == BUFFER_SIZE && ft_strchr(*str, '\n')))
			return (process_str(str));
	}
	if (r_result == -1 && *str)
	{
		free(*str);
		*str = NULL;
	}
	return (str_nl);	
}

char	*get_next_line(int fd)
{
	static char	*str;
	static int	fd_cpy;

	if (fd != fd_cpy)
	{
		fd_cpy = fd;
		if (str)
		{
			free(str);
			str = NULL;
		}
	}
	return (get_next_line_aux(&str, fd_cpy));
}
