/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_strdup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 19:50:00 by jdupuis           #+#    #+#             */
/*   Updated: 2026/11/18 19:50:00 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/test.h"

static bool	check_strdup_case(const char *input)
{
	char	*real_copy = strdup(input);
	char	*my_copy = ft_strdup(input);

	if (!my_copy)
	{
		printf("\n  %s[FAIL ft_strdup]%s : renvoie NULL sur \"%s\"\n", R, RES, input);
		free(real_copy);
		return (false);
	}

	bool diff_ptr = (my_copy != input);
	bool match_content = (strcmp(my_copy, real_copy) == 0);
	bool match_len = (strlen(my_copy) == strlen(real_copy));

	bool ok = diff_ptr && match_content && match_len;

	if (!ok)
	{
		printf("\n  %s[FAIL ft_strdup]%s sur \"%s\"\n", R, RES, input);
		if (!diff_ptr)
			printf("    -> Erreur : pointeur retourné identique à la source (pas d'allocation heap) !\n");
		if (!match_content)
		{
			printf("    -> Attendu : \"%s\"\n", real_copy);
			printf("    -> Obtenu  : \"%s\"\n", my_copy);
		}
		if (!match_len)
			printf("    -> Longueur différente !\n");
	}

	free(real_copy);
	free(my_copy);
	return (ok);
}

bool	test_strdup(void)
{
	int passed = 0;
	int total = 0;

	const char *tests[] = {
		"Hello World",
		"42 Perpignan",
		"",
		"a",
		"Une chaîne de caractères plus longue avec \t tabulation et retour \n !",
		"Special chars: !@#$%^&*()_+=-`~[]{}|;:',.<>/?",
		"\xff\x80\x01\x42",
		NULL
	};

	for (size_t i = 0; tests[i] != NULL; i++)
	{
		total++;
		if (check_strdup_case(tests[i]))
			passed++;
	}

	print_suite_status("ft_strdup", passed, total);
	return (passed == total);
}
