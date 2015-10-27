/*
** aff_pause.c for e in /home/carens_p/rendu/PSU_2014_lemipc/src
**
** Made by Paul Carensac
** Login   <carens_p@epitech.net>
**
** Started on  Sat Mar  7 13:01:05 2015 Paul Carensac
** Last update Sun Mar  8 03:18:42 2015 Paul Carensac
*/

#include <err.h>
#include <time.h>
#include "graphic.h"

void		aff_change_shm_state(bool lock, int sem_id)
{
  struct sembuf sops;

  sops.sem_num = 0;
  sops.sem_flg = 0;
  if (lock)
    sops.sem_op = -1;
  else
    sops.sem_op = 1;
  if (semop(sem_id, &sops, 1) == -1)
    errx(1, "Exit printing\n");
}

void            	my_pause(SDL_Surface *screen, t_lem *mem, int *colors,
				 int sem_id)
{
  struct timespec	sleeptime;
  int           	check;
  SDL_Event     	event;

  sleeptime.tv_sec = 0;
  sleeptime.tv_nsec = FPS_TO_NSECONDS(25);
  check = 1;
  while (check)
    {
      while (SDL_PollEvent(&event))
	{
	  if (event.type == SDL_QUIT)
	    check = 0;
	  else if (event.type == SDL_KEYDOWN)
	    {
	      if (event.key.keysym.sym == SDLK_ESCAPE)
		check = 0;
	    }
	}
      nanosleep(&sleeptime, NULL);
      aff_change_shm_state(true, sem_id);
      fill_map(screen, mem, colors);
      aff_change_shm_state(false, sem_id);
    }
}
