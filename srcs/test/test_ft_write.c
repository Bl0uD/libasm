/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_write.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 17:56:04 by jdupuis           #+#    #+#             */
/*   Updated: 2026/11/18 18:05:00 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/test.h"

static bool	check_write(const char *desc, int fd, const void *buf, size_t count, bool check_content)
{
	int		pipe_exp[2];
	int		pipe_act[2];
	int		test_fd_exp = fd;
	int		test_fd_act = fd;
	bool	using_pipes = false;

	if (check_content)
	{
		if (pipe(pipe_exp) < 0 || pipe(pipe_act) < 0)
			return (false);
		test_fd_exp = pipe_exp[1];
		test_fd_act = pipe_act[1];
		using_pipes = true;
	}

	errno = 0;
	ssize_t ret_exp = write(test_fd_exp, buf, count);
	int err_exp = errno;

	errno = 0;
	ssize_t ret_act = ft_write(test_fd_act, buf, count);
	int err_act = errno;

	bool ok = (ret_exp == ret_act && err_exp == err_act);

	if (ok && using_pipes && ret_exp > 0)
	{
		char read_exp[512] = {0};
		char read_act[512] = {0};

		read(pipe_exp[0], read_exp, ret_exp);
		read(pipe_act[0], read_act, ret_act);

		if (memcmp(read_exp, read_act, ret_exp) != 0)
			ok = false;
	}

	if (using_pipes)
	{
		close(pipe_exp[0]);
		close(pipe_exp[1]);
		close(pipe_act[0]);
		close(pipe_act[1]);
	}

	if (!ok)
	{
		printf("\n  %s[FAIL ft_write]%s : %s\n", R, RES, desc);
		printf("    -> Retour attendu : %zd | Obtenu : %zd\n", ret_exp, ret_act);
		printf("    -> Errno attendu  : %d (%s) | Obtenu : %d (%s)\n",
			err_exp, strerror(err_exp), err_act, strerror(err_act));
	}

	return (ok);
}

bool	test_write(void)
{
	int passed = 0;
	int total = 0;

	// --- 1. Cas nominaux (écriture valide dans un pipe et comparaison du contenu) ---
	const char *sample_str = "Hello World via Syscall !";
	total++;
	if (check_write("Chaîne normale avec comparaison de contenu", 0, sample_str, strlen(sample_str), true))
		passed++;

	total++;
	if (check_write("Chaîne vide (count = 0)", 0, "", 0, true))
		passed++;

	total++;
	if (check_write("Écriture partielle (5 octets sur 11)", 0, sample_str, 5, true))
		passed++;

	total++;
	if (check_write("1 seul octet", 0, "A", 1, true))
		passed++;

	// --- 2. Cas d'erreurs (descripteurs invalides & errno) ---
	total++;
	if (check_write("Bad FD négatif (fd = -1)", -1, "test", 4, false))
		passed++;

	total++;
	if (check_write("Bad FD très grand (fd = 4242)", 4242, "test", 4, false))
		passed++;

	// --- 3. Cas d'erreurs (buffer invalide / EFAULT) ---
	int dev_null = open("/dev/null", O_WRONLY);
	if (dev_null >= 0)
	{
		total++;
		if (check_write("Buffer NULL avec count > 0 (EFAULT)", dev_null, NULL, 10, false))
			passed++;

		total++;
		if (check_write("Buffer NULL avec count = 0", dev_null, NULL, 0, false))
			passed++;

		close(dev_null);
	}

	// --- 4. Erreur sur descripteur ouvert en lecture seule (EBADF) ---
	int pipe_ro[2];
	if (pipe(pipe_ro) == 0)
	{
		total++;
		if (check_write("Écriture sur l'extrémité de lecture d'un pipe (EBADF)", pipe_ro[0], "test", 4, false))
			passed++;
		close(pipe_ro[0]);
		close(pipe_ro[1]);
	}

	print_suite_status("ft_write", passed, total);
	return (passed == total);
}
