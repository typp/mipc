/*
** aff_main.c for e in /home/carens_p/rendu/PSU_2014_lemipc/src/aff
**
** Made by Paul Carensac
** Login   <carens_p@epitech.net>
**
** Started on  Wed Mar  4 10:15:33 2015 Paul Carensac
** Last update Sat Mar  7 13:03:06 2015 Paul Carensac
*/

#include <time.h>
#include "graphic.h"

int	retrieve_shm_sem(t_lem **mem, int *sem_id)
{
  key_t	key;
  char	*path;
  void	*addr;
  int	shm_id;

  if ((path = getcwd(NULL, 0)) == NULL)
    return (fprintf(stderr, "Can't find directory path\n"));
  if ((key = ftok(path, GLOBAL_KEY)) < 0)
    return (fprintf(stderr, "Failed to find file key\n"));
  if ((shm_id = shmget(key, 0, SHM_R | SHM_W)) < 0)
    return (fprintf(stderr, "No shared memory exists\n"));
  if ((addr = shmat(shm_id, NULL, SHM_R | SHM_W)) == (void *)-1)
    return (fprintf(stderr, "Failed to retrieve shared memory adress\n"));
  *mem = addr;
  (*mem)->map = (uint8_t *)((void *)(*mem) + sizeof(t_lem));
  (*mem)->players = (t_player *)((void *)(*mem)->map + SQ((*mem)->map_size));
  if ((*mem)->magic != MAGIC_NBR)
    return (fprintf(stderr, "Wrong magic number in shared memory\n"));
  if ((*sem_id = semget(key, 1, SHM_R | SHM_W)) < 0)
    return (fprintf(stderr, "Failed to retrieve semaphore\n"));
  return (0);
}

SDL_Surface	*init_sdl(t_lem *mem)
{
  SDL_Surface	*screen;
  int		size;

  if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
      fprintf(stderr, "SDL init failed\n");
      return (NULL);
    }
  size = mem->map_size * 10 + 10;
  screen = SDL_SetVideoMode(size, size, 32, SDL_SWSURFACE | SDL_DOUBLEBUF);
  if (!screen)
    {
      fprintf(stderr, "Screen creation failed\n");
      return (NULL);
    }
  SDL_WM_SetCaption("J'aime la soeur de Mbappe (la jeune)", NULL);
  return (screen);
}

void		fill_map(SDL_Surface *screen, t_lem *mem, int *colors)
{
  SDL_Rect	rec;
  int		x;
  int		y;
  int		pos;

  rec.w = 8;
  rec.h = 8;
  x = 0;
  y = 0;
  while (y < mem->map_size)
    {
      rec.x = 5 + x * 10;
      rec.y = 5 + y * 10;
      pos = y * mem->map_size + x;
      SDL_FillRect(screen, &rec, colors[mem->map[pos]]);
      ++x;
      if (x == mem->map_size)
	{
	  x = 0;
	  ++y;
	}
    }
  SDL_Flip(screen);
}

void	init_colors(int *colors)
{
  colors[0] = EMPTY;
  colors[1] = TEAM_1;
  colors[2] = TEAM_2;
  colors[3] = TEAM_3;
  colors[4] = TEAM_4;
}

int		main()
{
  t_lem		*mem;
  int		sem_id;
  SDL_Surface	*screen;
  int		colors[5];

  if (retrieve_shm_sem(&mem, &sem_id) != 0)
    return (1);
  if ((screen = init_sdl(mem)) == NULL)
    return (2);
  init_colors(colors);
  fill_map(screen, mem, colors);
  my_pause(screen, mem, colors, sem_id);
  SDL_Quit();
  return (0);
}
