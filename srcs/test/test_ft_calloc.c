/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_calloc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 20:20:00 by jdupuis           #+#    #+#             */
/*   Updated: 2026/11/18 20:20:00 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/test.h"

static bool	is_all_zero(const unsigned char *buf, size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		if (buf[i] != 0)
			return (false);
	}
	return (true);
}

static bool	check_calloc_nominal(const char *desc, size_t nmemb, size_t size)
{
	size_t	total = nmemb * size;
	void	*ptr = ft_calloc(nmemb, size);

	if (total > 0 && !ptr)
	{
		printf("\n  %s[FAIL ft_calloc]%s : %s (renvoie NULL alors que l'allocation était attendue)\n",
			R, RES, desc);
		return (false);
	}

	if (ptr && total > 0)
	{
		if (!is_all_zero((const unsigned char *)ptr, total))
		{
			printf("\n  %s[FAIL ft_calloc]%s : %s (la mémoire n'est pas remplie de zéros !)\n",
				R, RES, desc);
			free(ptr);
			return (false);
		}
	}

	free(ptr);
	return (true);
}

static bool	check_calloc_overflow(const char *desc, size_t nmemb, size_t size)
{
	errno = 0;
	void *ptr = ft_calloc(nmemb, size);
	int err = errno;

	bool is_null = (ptr == NULL);
	bool has_enomem = (err == ENOMEM);

	if (ptr)
		free(ptr);

	bool ok = is_null && has_enomem;

	if (!ok)
	{
		printf("\n  %s[FAIL ft_calloc overflow]%s : %s\n", R, RES, desc);
		if (!is_null)
			printf("    -> Erreur : pointeur non-NULL retourné lors d'un overflow !\n");
		if (!has_enomem)
			printf("    -> Erreur : errno vaut %d (%s) au lieu de ENOMEM (12) !\n",
				err, strerror(err));
	}

	return (ok);
}

bool	test_calloc(void)
{
	int passed = 0;
	int total = 0;

	// --- 1. Cas nominaux : allocations normales et mise à zéro ---
	total++;
	if (check_calloc_nominal("10 entiers (40 octets mis à zéro)", 10, sizeof(int)))
		passed++;

	total++;
	if (check_calloc_nominal("1 élément de 1 octet", 1, 1))
		passed++;

	total++;
	if (check_calloc_nominal("1000 éléments de 8 octets (8000 octets)", 1000, 8))
		passed++;

	total++;
	if (check_calloc_nominal("Taille 0 avec nmemb = 5", 5, 0))
		passed++;

	total++;
	if (check_calloc_nominal("nmemb = 0 avec taille = 5", 0, 5))
		passed++;

	total++;
	if (check_calloc_nominal("0 élément de 0 octet", 0, 0))
		passed++;

	// --- 2. Cas d'overflow (Obligation explicite du sujet 42) ---
	total++;
	if (check_calloc_overflow("Overflow SIZE_MAX * 2", SIZE_MAX, 2))
		passed++;

	total++;
	if (check_calloc_overflow("Overflow (SIZE_MAX / 2 + 1) * 2", (SIZE_MAX / 2) + 1, 2))
		passed++;

	total++;
	if (check_calloc_overflow("Overflow 0xFFFFFFFF * 0xFFFFFFFF", 0xFFFFFFFFULL, 0xFFFFFFFFULL))
		passed++;

	total++;
	if (check_calloc_overflow("Overflow SIZE_MAX * SIZE_MAX", SIZE_MAX, SIZE_MAX))
		passed++;

	print_suite_status("ft_calloc", passed, total);
	return (passed == total);
}
