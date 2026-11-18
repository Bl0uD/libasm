/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 17:40:06 by jdupuis           #+#    #+#             */
/*   Updated: 2026/11/18 20:16:43 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST
# define TEST

# include	"libasm.h"
# include	<stdio.h>
# include	<string.h>
# include	<stdbool.h>
# include	<stdlib.h>
# include	<unistd.h>
# include	<errno.h>
# include	<fcntl.h>
# include	<stdint.h>

#define G   "\033[0;32m"
#define R   "\033[0;31m"
#define Y   "\033[0;33m"
#define BOLD "\033[1m"
#define RES "\033[0m"

void	print_suite_status(const char *name, int passed, int total);
bool	test_strcmp(void);
bool	test_strcpy(void);
bool	test_strlen(void);
bool	test_write(void);
bool	test_read(void);
bool	test_strdup(void);
bool	test_calloc(void);
bool	test_read(void);
bool	test_calloc(void);

#endif