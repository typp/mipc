/*
** main.c for e in /home/carens_p/rendu/PSU_2014_lemipc/src
**
** Made by Paul Carensac
** Login   <carens_p@epitech.net>
**
** Started on  Mon Mar  2 10:45:06 2015 Paul Carensac
** Last update Sun Mar  8 03:02:33 2015 Paul Carensac
*/

#include <signal.h>
#include <errno.h>
#include <err.h>
#include "lemipc.h"

extern int errno;

t_lem		*g_mem = NULL;

static t_keys	g_keys;
static t_player	*g_player = NULL;

void		change_shm_state(bool lock)
{
  struct sembuf sops;

  sops.sem_num = 0;
  sops.sem_flg = 0;
  if (lock)
    sops.sem_op = -1;
  else
    sops.sem_op = 1;
  if (semop(g_keys.sem_id, &sops, 1) == -1)
    errx(1, "Failed to change shm semaphore state\n");
}

void	print_winning(void)
{
  if (g_mem->winning_team != 0)
    {
      printf("            *\n");
      printf("     *      |\n");
      printf("      \\     |    *\n");
      printf("       \\    |   /\n");
      printf("-*-*- Team %i wins !! -*-*-\n", g_player->team);
      printf("         /    \\\n");
      printf("        *      *\n");
    }
}

void		delete_ipcs()
{
  int		i;
  uint16_t	living;

  living = 1;
  change_shm_state(true);
  g_player->alive = false;
  g_mem->living_players -= 1;
  living = g_mem->living_players;
  MAP[g_player->posx + g_player->posy * g_mem->map_size] = 0;
  change_shm_state(false);
  if (living == 0)
    {
      print_winning();
      shmctl(g_keys.shm_id, IPC_RMID, NULL);
      semctl(g_keys.sem_id, 0, IPC_RMID);
      i = 0;
      while (i < 4 && g_keys.msg_id[i] > -1)
	{
	  msgctl(g_keys.msg_id[i], IPC_RMID, NULL);
	  ++i;
	}
    }
}

int		wait_players()
{
  struct sembuf	sops;

  if (semctl(g_keys.sem_id, 1, GETVAL, g_mem->nb_team * 2) > 0)
    {
      sops.sem_num = 1;
      sops.sem_flg = IPC_NOWAIT;
      sops.sem_op = -1;
      if (semop(g_keys.sem_id, &sops, 1) == -1)
	return (fprintf(stderr, "Failed to decr starting barrier\n"));
      sops.sem_flg = 0;
      sops.sem_op = 0;
      if (semop(g_keys.sem_id, &sops, 1) == -1)
	return (fprintf(stderr, "Failed to create starting barrier\n"));
    }
  return (0);
}

int		main(int ac, char **av)
{
  t_conf	conf;
  char		*path;

  init_conf(&conf);
  if (ac > 1)
    parse_config(av[1], &conf);
  if (check_config(&conf))
    return (1);
  if ((path = getcwd(NULL, 0)) == NULL)
    {
      fprintf(stderr, "Can't find directory path\n");
      return (2);
    }
  if (create_keys(path, &conf, &g_keys, &g_player) != 0)
    return (3);
  free(path);
  atexit(&delete_ipcs);
  signal(SIGINT, &player_die);
  if (wait_players() != 0)
    return (4);
  player_play(&g_keys, g_player);
  return (0);
}
