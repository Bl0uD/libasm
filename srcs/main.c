/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.C                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 18:54:37 by jdupuis           #+#    #+#             */
/*   Updated: 2026/11/18 19:09:17 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libasm.h"
#include "../includes/test.h"

void	print_suite_status(const char *name, int passed, int total)
{
	if (passed == total)
		printf(" %s[OK]%s %s%-15s%s (%d/%d tests passés)\n",
			G, RES, BOLD, name, RES, passed, total);
	else
		printf(" %s[KO]%s %s%-15s%s (%d/%d tests passés, %s%d échecs%s)\n",
			R, RES, BOLD, name, RES, passed, total, R, total - passed, RES);
}

int	main(void)
{
	printf("\n%s================== LIBASM TESTS ==================%s\n", BOLD, RES);

	bool ok = true;
	ok &= test_strlen();
	ok &= test_strcpy();
	ok &= test_strcmp();
	ok &= test_write();
	ok &= test_read();
	ok &= test_strdup();
	ok &= test_calloc();

	printf("%s==================================================%s\n", BOLD, RES);
	if (ok)
		printf(" %s>>> TOUS LES TESTS SONT VALIDES AVEC SUCCÈS ! <<<%s\n\n", G, RES);
	else
		printf(" %s>>> DES ERREURS ONT ÉTÉ DÉTECTÉES ! <<<%s\n\n", R, RES);

	return (ok ? 0 : 1);
}