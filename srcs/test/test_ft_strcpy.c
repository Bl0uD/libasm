/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_strcpy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 17:43:09 by jdupuis           #+#    #+#             */
/*   Updated: 2026/11/18 17:44:40 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/test.h"

bool	test_strcpy(void)
{
	const char *tests[] = {
		"Hello World",
		"42 Perpignan",
		"",
		"a",
		"Copie d'une phrase avec symboles et retours \n \t 123",
		NULL
	};

	int passed = 0;
	int total = 0;
	char dest_expected[256];
	char dest_actual[256];

	for (size_t i = 0; tests[i] != NULL; i++)
	{
		total++;
		memset(dest_expected, 'A', sizeof(dest_expected));
		memset(dest_actual, 'A', sizeof(dest_actual));

		strcpy(dest_expected, tests[i]);
		char *ret_actual = ft_strcpy(dest_actual, tests[i]);

		bool content_ok = (strcmp(dest_actual, dest_expected) == 0);
		bool return_ptr_ok = (ret_actual == dest_actual);

		if (content_ok && return_ptr_ok)
			passed++;
		else
		{
			printf("\n  %s[FAIL ft_strcpy]%s sur l'entrée \"%s\"\n", R, RES, tests[i]);
			if (!content_ok)
			{
				printf("    -> Contenu attendu : \"%s\"\n", dest_expected);
				printf("    -> Contenu obtenu  : \"%s\"\n", dest_actual);
			}
			if (!return_ptr_ok)
				printf("    -> Pointeur retourné invalide (n'est pas dest) !\n");
		}
	}

	print_suite_status("ft_strcpy", passed, total);
	return (passed == total);
}