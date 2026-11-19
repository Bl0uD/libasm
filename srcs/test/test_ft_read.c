/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_read.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 19:10:00 by jdupuis           #+#    #+#             */
/*   Updated: 2026/11/18 19:10:00 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/test.h"

static bool	check_read_pipe(const char *desc, const char *input_data, size_t count)
{
	int		pipe_exp[2];
	int		pipe_act[2];

	if (pipe(pipe_exp) < 0 || pipe(pipe_act) < 0)
		return (false);

	if (input_data)
	{
		size_t in_len = strlen(input_data);
		write(pipe_exp[1], input_data, in_len);
		write(pipe_act[1], input_data, in_len);
	}
	close(pipe_exp[1]);
	close(pipe_act[1]);

	char buf_exp[512] = {0};
	char buf_act[512] = {0};

	errno = 0;
	ssize_t ret_exp = read(pipe_exp[0], buf_exp, count);
	int err_exp = errno;

	errno = 0;
	ssize_t ret_act = ft_read(pipe_act[0], buf_act, count);
	int err_act = errno;

	bool ok = (ret_exp == ret_act && err_exp == err_act);
	if (ok && ret_exp > 0)
	{
		if (memcmp(buf_exp, buf_act, ret_exp) != 0)
			ok = false;
	}

	close(pipe_exp[0]);
	close(pipe_act[0]);

	if (!ok)
	{
		printf("\n  %s[FAIL ft_read]%s : %s\n", R, RES, desc);
		printf("    -> Retour attendu : %zd | Obtenu : %zd\n", ret_exp, ret_act);
		printf("    -> Errno attendu  : %d (%s) | Obtenu : %d (%s)\n",
			err_exp, strerror(err_exp), err_act, strerror(err_act));
	}

	return (ok);
}

static bool	check_read_error(const char *desc, int fd, void *buf, size_t count)
{
	errno = 0;
	ssize_t ret_exp = read(fd, buf, count);
	int err_exp = errno;

	errno = 0;
	ssize_t ret_act = ft_read(fd, buf, count);
	int err_act = errno;

	bool ok = (ret_exp == ret_act && err_exp == err_act);

	if (!ok)
	{
		printf("\n  %s[FAIL ft_read error]%s : %s\n", R, RES, desc);
		printf("    -> Retour attendu : %zd | Obtenu : %zd\n", ret_exp, ret_act);
		printf("    -> Errno attendu  : %d (%s) | Obtenu : %d (%s)\n",
			err_exp, strerror(err_exp), err_act, strerror(err_act));
	}

	return (ok);
}

bool	test_read(void)
{
	int passed = 0;
	int total = 0;

	// --- 1. Cas nominaux : lecture valide depuis un pipe ---
	const char *sample = "Hello from pipe reading test 12345 !";

	total++;
	if (check_read_pipe("Lecture complète d'une chaîne", sample, strlen(sample)))
		passed++;

	total++;
	if (check_read_pipe("Lecture avec count = 0 (doit renvoyer 0)", sample, 0))
		passed++;

	total++;
	if (check_read_pipe("Lecture partielle (10 octets)", sample, 10))
		passed++;

	total++;
	if (check_read_pipe("1 seul octet", sample, 1))
		passed++;

	total++;
	if (check_read_pipe("Lecture sur pipe vide (sans écriture préalable, EOF)", NULL, 10))
		passed++;

	// --- 2. Cas d'erreur : descripteurs invalides ---
	char dummy[64];

	total++;
	if (check_read_error("Bad FD négatif (fd = -1)", -1, dummy, sizeof(dummy)))
		passed++;

	total++;
	if (check_read_error("Bad FD très grand (fd = 4242)", 4242, dummy, sizeof(dummy)))
		passed++;

	// --- 3. Cas d'erreur : buffer invalide (NULL avec count > 0 -> EFAULT) ---
	int pipe_null[2];
	if (pipe(pipe_null) == 0)
	{
		write(pipe_null[1], "abc", 3);

		total++;
		if (check_read_error("Buffer NULL avec count > 0 (EFAULT)", pipe_null[0], NULL, 10))
			passed++;

		total++;
		if (check_read_error("Buffer NULL avec count = 0", pipe_null[0], NULL, 0))
			passed++;

		close(pipe_null[0]);
		close(pipe_null[1]);
	}

	// --- 4. Erreur : lecture sur l'extrémité d'écriture d'un pipe (EBADF) ---
	int pipe_wo[2];
	if (pipe(pipe_wo) == 0)
	{
		total++;
		if (check_read_error("Lecture sur l'extrémité d'écriture d'un pipe (EBADF)", pipe_wo[1], dummy, sizeof(dummy)))
			passed++;
		close(pipe_wo[0]);
		close(pipe_wo[1]);
	}

	print_suite_status("ft_read", passed, total);
	return (passed == total);
}
