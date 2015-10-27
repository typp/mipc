/*
** graphic.h for e in /home/carens_p/rendu/PSU_2014_lemipc
**
** Made by Paul Carensac
** Login   <carens_p@epitech.net>
**
** Started on  Wed Mar  4 11:12:36 2015 Paul Carensac
** Last update Sat Mar  7 13:03:05 2015 Paul Carensac
*/

#ifndef GRAPHIC_H_
#define GRAPHIC_H_

#include <SDL/SDL.h>
#include <err.h>
#include "mem.h"

#define EMPTY 0x0F0F

#define TEAM_1 0xFF00
#define TEAM_2 0xFFFF00
#define TEAM_3 0xFF0000
#define TEAM_4 0xFFFF

#define MLSECONDS(msec) ((msec) * 1000000L)
#define FPS_TO_NSECONDS(fps) (1000000000L / (fps))

void	fill_map(SDL_Surface *screen, t_lem *mem, int *colors);
void	my_pause(SDL_Surface *, t_lem *, int *, int);

#endif
