/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_strcmp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 17:43:40 by jdupuis           #+#    #+#             */
/*   Updated: 2026/11/18 17:44:29 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/test.h"

bool	test_strcmp(void)
{
	const char *tests[] = {
		"Hello World",
		"42 Perpignan",
		"",
		"a",
		"Une chaine un peu plus longue avec des espaces et des symboles !?#$",
		"\xff",
		"\x01",
		NULL
	};

	int passed = 0;
	int total = 0;

	// 1. Tests d'égalité parfaite (chaque chaîne avec elle-même)
	for (size_t i = 0; tests[i] != NULL; i++)
	{
		total++;
		int exp = strcmp(tests[i], tests[i]);
		int act = ft_strcmp(tests[i], tests[i]);

		if (exp == act)
			passed++;
		else
		{
			printf("\n  %s[FAIL ft_strcmp égalité]%s sur \"%s\"\n", R, RES, tests[i]);
			printf("    -> Attendu : %d | Obtenu : %d\n", exp, act);
		}
	}

	// 2. Tests croisés (chaîne i vs chaîne j)
	for (size_t i = 0; tests[i] != NULL; i++)
	{
		for (size_t j = i + 1; tests[j] != NULL; j++)
		{
			total++;
			int exp = strcmp(tests[i], tests[j]);
			int act = ft_strcmp(tests[i], tests[j]);

			// On vérifie que les signes correspondent (+ / - / 0)
			bool sign_ok = (exp == 0 && act == 0) ||
			               (exp < 0 && act < 0) ||
			               (exp > 0 && act > 0);

			if (sign_ok && exp == act)
				passed++;
			else
			{
				printf("\n  %s[FAIL ft_strcmp croisé]%s \"%s\" vs \"%s\"\n",
					R, RES, tests[i], tests[j]);
				printf("    -> Attendu : %d | Obtenu : %d\n", exp, act);
			}
		}
	}

	print_suite_status("ft_strcmp", passed, total);
	return (passed == total);
}