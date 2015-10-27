/*
** create_ipcs.c for e in /home/carens_p/rendu/PSU_2014_lemipc/src
**
** Made by Paul Carensac
** Login   <carens_p@epitech.net>
**
** Started on  Mon Mar  2 23:37:28 2015 Paul Carensac
** Last update Sun Mar  8 03:18:16 2015 Paul Carensac
*/

#include <string.h>
#include <errno.h>
#include "lemipc.h"

/*
** Semaphores :
**  - 0 : lock the shm
**  - 1 : starting barrier
*/

int	create_ipcs(char *path, t_conf *conf, t_keys *keys)
{
  int	i;
  key_t	group_key;

  if ((keys->shm_id = shmget(keys->global_key, conf->total_size,
			     IPC_CREAT | SHM_R | SHM_W)) < 0)
    return (fprintf(stderr, "Failed to create shared memory: %s\n",
		    strerror(errno)));
  printf("shared memory created\n");
  if ((keys->sem_id = semget(keys->global_key, 2,
			     IPC_CREAT | SHM_R | SHM_W)) < 0)
    return (fprintf(stderr, "Failed to create semaphore: %s\n",
		    strerror(errno)));
  i = 0;
  while (++i <= conf->nb_team)
    {
      if ((group_key = ftok(path, i)) < 0)
	return (fprintf(stderr, "Failed to create group ipc key\n"));
      if (msgget(group_key, IPC_CREAT | SHM_R | SHM_W) < 0)
	return (fprintf(stderr, "Failed to create a message queue\n"));
    }
  return (0);
}

int		init_shm(t_conf *conf, t_keys *keys)
{
  void		*addr;

  if ((addr = shmat(keys->shm_id, NULL, SHM_R | SHM_W)) == (void *)-1)
    return (fprintf(stderr, "Failed to retrieve shared memory address\n"));
  memset(addr, 0, conf->total_size);
  g_mem = addr;
  g_mem->magic = MAGIC_NBR;
  g_mem->current_round = 0;
  g_mem->nb_team = conf->nb_team;
  g_mem->max_players = conf->max_players;
  g_mem->current_player = 0;
  g_mem->living_players = 0;
  g_mem->map_size = conf->map_size;
  g_mem->winning_team = 0;
  if (semctl(keys->sem_id, 0, SETVAL, 1) == -1)
    return (fprintf(stderr, "Failed to init semaphore: %s\n",
		    strerror(errno)));
  if (semctl(keys->sem_id, 1, SETVAL, g_mem->nb_team * 2) == -1)
    return (fprintf(stderr, "Failed to init semaphore: %s\n",
		    strerror(errno)));
  return (0);
}

int	store_all_msg_ids(char *path, t_keys *keys)
{
  int	i;
  key_t	group_key;

  i = -1;
  while (++i < g_mem->nb_team)
    {
      if ((group_key = ftok(path, i + 1)) < 0)
	return (fprintf(stderr, "Failed to create group key\n"));
      if ((keys->msg_id[i] = msgget(group_key, SHM_R | SHM_W)) < 0)
	return (fprintf(stderr, "Failed to create message queue\n"));
    }
  while (i < 4)
    {
      keys->msg_id[i] = -1;
      ++i;
    }
  return (0);
}

int	create_keys(char *path, t_conf *conf, t_keys *keys,
		    t_player **player)
{
  if ((keys->global_key = ftok(path, GLOBAL_KEY)) < 0)
    return (fprintf(stderr, "Failed to find file key\n"));
  conf->total_size = sizeof(t_lem) + (conf->max_players * conf->nb_team)
    * sizeof(t_player)
    + SQ(conf->map_size) * sizeof(uint8_t);
  if ((keys->shm_id = shmget(keys->global_key, 0,
			     SHM_R | SHM_W)) < 0)
    {
      if (create_ipcs(path, conf, keys) || init_shm(conf, keys))
	return (-1);
    }
  else if ((keys->sem_id = semget(keys->global_key, 2, SHM_R | SHM_W)) < 0)
    return (fprintf(stderr, "Failed to create semaphore\n"));
  if (set_player(keys, player))
    return (-1);
  if (store_all_msg_ids(path, keys))
    return (-1);
  return (0);
}
