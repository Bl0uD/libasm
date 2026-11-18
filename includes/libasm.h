/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libasm.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 18:52:28 by jdupuis           #+#    #+#             */
/*   Updated: 2026/11/18 20:16:30 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBASM
# define LIBASM

# include	<stdio.h>
# include	<string.h>
# include	<stdbool.h>
# include	<stdlib.h>
# include	<unistd.h>

size_t	ft_strlen(const char *s);
char	*ft_strcpy(char *dest, const char *src);
int		ft_strcmp(const char *s1, const char *s2);
ssize_t	ft_write(int fd, const void *buf, size_t count);
ssize_t	ft_read(int fd, void *buf, size_t count);
char	*ft_strdup(const char *s);
void	*ft_calloc(size_t nmemb, size_t size);
ssize_t	ft_read(int fd, void *buf, size_t count);
void	*ft_calloc(size_t nmemb, size_t size);

#endif