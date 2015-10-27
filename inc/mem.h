/*
** mem.h for e in /home/carens_p/rendu/PSU_2014_lemipc
**
** Made by Paul Carensac
** Login   <carens_p@epitech.net>
**
** Started on  Wed Mar  4 10:44:30 2015 Paul Carensac
** Last update Sun Mar  8 00:52:12 2015 Paul Carensac
*/

#ifndef MEM_H_
#define MEM_H_

/*
** GLOBAL_KEY must be greater than 4
*/
#define GLOBAL_KEY 32

#define MAGIC_NBR 0xBABE1234

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define SQ(a) ((a) * (a))

typedef struct s_player	t_player;

struct		s_player
{
  uint32_t	round;
  int16_t	posx;
  int16_t	posy;
  uint8_t	team;
  bool		alive;
  bool		attacking;
};

/*
** players is an array
**
** map is a tab of chars, 0 if there is no player on the case,
** the number of the team whether
**
** max_players => maximum number of players in a team
*/
typedef struct	s_lem
{
  uint8_t	*map;
  t_player	*players;
  uint32_t	magic;
  uint32_t	current_round;
  uint8_t	nb_team;
  uint8_t	max_players;
  uint16_t	current_player;
  uint16_t	living_players;
  uint8_t       map_size;
  bool		winning_team;
}		t_lem;

extern t_lem	*g_mem;

#define MAP	((uint8_t *)((void *)g_mem + sizeof(t_lem)))
#define PLAYERS	((t_player *)(MAP + SQ(g_mem->map_size)))

#endif
