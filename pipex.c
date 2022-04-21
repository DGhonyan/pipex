/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 19:03:43 by dghonyan          #+#    #+#             */
/*   Updated: 2022/04/18 19:03:44 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "ft_printf.h"

int	check_args(char *s1, char *s2, int argc)
{
	int	a;

	a = access(s1, R_OK);
	if (argc != 5)
	{
		printf("Error: Too few arguments\n");

		exit(-1);
	}
	if (a == -1)
	{
		perror("Cannot read from a file");
		exit(-1);
	}
	a = access(s2, W_OK);
	if (a == -1)
	{
		perror("Cannot write to a file");
		exit(-1);
	}
	return (0);
}


void	child1(char *s, char **args, int pipe_write, char *f)
{
	int	fd;

	fd = open(f, O_RDONLY | O_CLOEXEC);
	fd = dup2(fd, STDIN_FILENO);
	printf("%s %s %s    ", s, args[1], f);
	pipe_write = dup2(pipe_write, STDOUT_FILENO);
	execve(s, args, NULL);
	perror("Execve failed at child1()");
	exit (-1);
}

void	child2(char *s, char **args, int pipe_read, char *f)
{
	int	fd;

	fd = open(f, O_WRONLY | O_CLOEXEC | O_TRUNC);
	fd = dup2(fd, STDOUT_FILENO);
	pipe_read = dup2(pipe_read, STDIN_FILENO);
	execve(s, args, NULL);
	perror("Execve failed at child2()");
	exit (-1);
}

int	*create_pipes(void)
{
	int	*pipes;

	pipes = malloc(2 * sizeof (*pipes));
	if (!pipes)
	{
		perror("Failed to allocate memory at create_pipes()");
		exit(-1);
	}
	if (pipe(pipes) == -1)
	{
		perror("Failed to create pipes at create_pipes()");
		exit(-1);
	}
	return (pipes);
}

int	main(int argc, char **argv)
{
	int		status;
	int	 	*pipes;
	int	 	*pipes_for_path;
	char	**args1;
	char	**args2;
	char	*script1;
	char	*script2;
	pid_t	pid;

	/// TODO add which command usage lol why not

	check_args(argv[1], argv[argc - 1], argc);
	printf("%s %s\n", script1, script2);
	pipes = create_pipes();
	pipes_for_path = create_pipes();
	pid = fork();
	if (!pid)
	{
		close(pipes_for_path[0]);
		args1 = ft_split(argv[2]);
		pipes_for_path[1] = dup2(pipes_for_path[1], STDOUT_FILENO);
		execve("/usr/bin/which", args1, NULL);
	}
	wait(&status);
	close(pipes_for_path[1]);
	script1 = ft_strjoin("/bin/bash -c ", argv[2]);
	script2 = ft_strjoin("/bin/bash -c ", argv[3]);
	args1 = ft_split(script1, ' ');
	args2 = ft_split(script2, ' ');
	pid = fork();
	if (!pid)
	{
		close(pipes[0]);
		child1(args1[0], args1, pipes[1], argv[1]);
		return (0);
	}
	wait(&status);
	close(pipes[1]);
	child2(args2[0], args2, pipes[0], argv[argc -1]);
}

/*
c2r12s3% cat ~/.ssh/id_rsa.pub
ssh-rsa AAAAB3NzaC1yc2EAAAADAQABAAABAQDhjqcShVyZHmeHbzoCt1UU+FKiqGyXHXSBx2BXZnKJO/2KrAJ8vcIQ4qXGnVE97B+qVB2WuSWjB86gHl47VD7yDuGTZcZy0Mvv2DT5Hr6AIdNrTjTXE4UqEVeiwEo8u7n+Q1n5KA8CtOALcqJo+rGLY6E5Bgb6NmYj8hwInbYhO8pMPceJuWjrkimre7q7hPG8PVH8LqYbbFlWRAAfCjZymWxiwu6zh3PV/nuM1rL16VLc11xDcfOpy1hLFYY51n/ggtwmK4t8VHi3hBPYU33A4Yylo7kCZ4aofmCfugr5cxalFh35G7I+NIeCQy2maqquXAsjKpiAqJ7k+46Q7pVX dghonyan@c1r5s2.42yerevan.am
c2r12s3% cat ~/.ssh/id_rsa
-----BEGIN OPENSSH PRIVATE KEY-----
b3BlbnNzaC1rZXktdjEAAAAABG5vbmUAAAAEbm9uZQAAAAAAAAABAAABFwAAAAdzc2gtcn
NhAAAAAwEAAQAAAQEA4Y6nEoVcmR5nh286ArdVFPhSoqhslx10gcdgV2ZyiTv9iqwCfL3C
EOKlxp1RPewfqlQdlrklowfOoB5eO1Q+8g7hk2XGctDL79g0+R6+gCHTa0401xOFKhFXos
BKPLu5/kNZ+SgPArTgC3KiaPqxi2OhOQYG+jZmI/IcCJ22ITvKTD3Hiblo65Ipq3u6u4Tx
vD1R/C6mG2xZVkQAHwo2cplsYsLus4dz1f57jNay9elS3NdcQ3HzqctYSxWGOdZ/4ILcJi
uLfFR4t4QT2FN9wOGMpaO5AmeGqH5gn7oK+XMWpRYd+RuyPjSHgkMtpmqqrlwLIyqYgKie
5PuOkO6VVwAAA9gdYHy4HWB8uAAAAAdzc2gtcnNhAAABAQDhjqcShVyZHmeHbzoCt1UU+F
KiqGyXHXSBx2BXZnKJO/2KrAJ8vcIQ4qXGnVE97B+qVB2WuSWjB86gHl47VD7yDuGTZcZy
0Mvv2DT5Hr6AIdNrTjTXE4UqEVeiwEo8u7n+Q1n5KA8CtOALcqJo+rGLY6E5Bgb6NmYj8h
wInbYhO8pMPceJuWjrkimre7q7hPG8PVH8LqYbbFlWRAAfCjZymWxiwu6zh3PV/nuM1rL1
6VLc11xDcfOpy1hLFYY51n/ggtwmK4t8VHi3hBPYU33A4Yylo7kCZ4aofmCfugr5cxalFh
35G7I+NIeCQy2maqquXAsjKpiAqJ7k+46Q7pVXAAAAAwEAAQAAAQEA4XNW55pJXfsX/DVe
xIw/DMDQyCiUsc8NPxLr5zBNV4KRAGTB77E0IvCIRqfEJqK3W+bL1HWnevc4vq7b/W1NpW
DedBgMbYLp9QgkmsTyINyul9kJ09h9B/lhoRmWmnIBjHYBnps9tbTZJFgmocvCXtLsuTSf
EMYC/fbnsm0BOODL7mgxiwA14nrYtuoZd+wTIQcxFfr7aP42VbTardgmD1b6qFKsc9elB0
10CFLQ59UBsvE42sNx3JCQ8vGS9+gjPKNjPGCMlQoKs7HrUKZtj/Sn4mxFoh8NZbevJNkp
eo59RDavMSL16SJCW5rQSGP9eWRXEzBE/TkejD0zyZA2YQAAAIEAgCB8kKaBoRT4P1hzPj
gdsAIz1yqhkynd4r/XqEAqT2UlZ8D0ov94w1ErYTHr/f0Gz2ZBVeP9XeoMBrMGRNDZLTna
kdLirAZTZ+oO+c41GBu12/Q6cKMqE9NdCoucd3oL8uo2aS1OZgYw6X8s9gkX3zK2QI0uHb
pGr/ZtXieYticAAACBAPVwyX8TgY7O9y9WMlZC+Kamq+Iimwo+MmKUHQ+nosIItXSjFTXi
x8NAeE1M/GTjzDrFdha6QmF7tIn5LJRTugklbGUdxegIZBj4kCymUR+3pDUZF7kPaZkz/E
C9J/f9tyQInJ2eBxaVTUybGBcDDliV477A/hYR9Wg4u2X/uAHpAAAAgQDrQuBHKt9E2GxB
qeJ+B4WBPM+3CL8RkQtp+bxDlHIHv6r7EsQgqmcZVNoewEKBDXCiWaIdVn1Uqt8AREDSSO
zwBIZySBNQ2KuN8KEae3M7DMGJM0liFhlbJpfpk6yFwXcmueD/FBwjfroeH+6RqJKomTmS
kN6jIQoBEpxnWc4VPwAAABxkZ2hvbnlhbkBjMXI1czIuNDJ5ZXJldmFuLmFtAQIDBAU=
-----END OPENSSH PRIVATE KEY-----
*/
