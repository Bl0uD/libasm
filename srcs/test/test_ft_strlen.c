/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_strlen.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 17:42:19 by jdupuis           #+#    #+#             */
/*   Updated: 2026/11/18 17:45:00 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/test.h"

bool	test_strlen(void)
{
	const char *tests[] = {
		"Hello World",
		"42 Perpignan",
		"",
		"a",
		"Une chaine un peu plus longue avec des espaces et des symboles !?#$",
		NULL
	};

	int passed = 0;
	int total = 0;

	for (size_t i = 0; tests[i] != NULL; i++)
	{
		total++;
		size_t expected = strlen(tests[i]);
		size_t actual = ft_strlen(tests[i]);

		if (expected == actual)
			passed++;
		else
		{
			printf("\n  %s[FAIL ft_strlen]%s sur l'entrée \"%s\"\n", R, RES, tests[i]);
			printf("    -> Attendu : %zu\n", expected);
			printf("    -> Obtenu  : %zu\n", actual);
		}
	}

	print_suite_status("ft_strlen", passed, total);
	return (passed == total);
}