/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoto-gu <acoto-gu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 09:36:18 by acoto-gu          #+#    #+#             */
/*   Updated: 2023/10/11 10:32:02 by acoto-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*free_and_return(char **ptr)
{
	free(*ptr);
	*ptr = NULL;
	return (NULL);
}

char	*process_str(char **str)
{
	char	*str_nl;
	char	*str_tmp;

	str_nl = NULL;
	if (*str && ft_strchr(*str, '\n'))
	{
		str_nl = ft_substr(*str, 0, ft_strchr(*str, '\n') - *str + 1);
		if (!str_nl)
			return (free_and_return(str));
		str_tmp = *str;
		*str = ft_substr(ft_strchr(str_tmp, '\n') + 1, 0, ft_strlen(str_tmp));
		free(str_tmp);
		if (!*str)
			return (free_and_return(&str_nl));
		if (ft_strlen(*str) == 0)
			free_and_return(str);
	}
	else if (*str)
	{
		str_nl = ft_substr(*str, 0, ft_strlen(*str));
		free_and_return(str);
		if (!str_nl)
			return (NULL);
	}
	return (str_nl);
}

int	buf_to_str_aux(int fd, char *str_buf, char **str)
{
	int		read_result;
	char	*tmp_str;

	read_result = read(fd, str_buf, BUFFER_SIZE);
	if (read_result > 0)
	{
		str_buf[read_result] = '\0';
		if (*str == NULL)
		{
			*str = str_buf;
			return (read_result);
		}
		tmp_str = ft_strjoin(*str, str_buf);
		free(str_buf);
		if (!tmp_str)
			return (-1);
		free(*str);
		*str = tmp_str;
	}
	else
		free(str_buf);
	return (read_result);
}

char	*get_next_line(int fd)
{
	static char	*str_arr[1024];
	int			r_result;
	char		*str_nl;
	char		*str_buf;

	str_nl = NULL;
	if (str_arr[fd] && ft_strchr(str_arr[fd], '\n'))
		return (process_str(&str_arr[fd]));
	r_result = BUFFER_SIZE;
	while (!str_nl && r_result > 0)
	{
		str_buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!str_buf)
		{
			r_result = -1;
			break ;
		}
		r_result = buf_to_str_aux(fd, str_buf, &str_arr[fd]);
		if ((r_result >= 0 && r_result < BUFFER_SIZE)
			|| (r_result == BUFFER_SIZE && ft_strchr(str_arr[fd], '\n')))
			return (process_str(&str_arr[fd]));
	}
	if (r_result == -1 && str_arr[fd])
		free_and_return(&str_arr[fd]);
	return (str_nl);
}
