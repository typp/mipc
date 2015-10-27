/*
** player.h for LemIPC in /home/la-val_c/rendu/PSU_2014_lemipc
**
** Made by Cyril La Valle
** Login <la-val_c@epitech.eu>
**
** Started on  Mon Mar  2 15:27:28 2015 Cyril La Valle
** Last update Sun Mar  8 01:57:56 2015 Paul Carensac
*/

#ifndef PLAYER_H
#define PLAYER_H

#include <stdint.h>
#include "lemipc.h"

#define POS(x, y) ((x) + (y) * g_mem->map_size)

enum
{
  PP_MSG_GATHER = 1,
  PP_MSG_ATTACK
};

typedef int32_t t_xy_cast;
typedef union u_xy t_xy;
union		u_xy
{
  t_xy_cast	cpt;
  struct
    {
      int16_t	x;
      int16_t	y;
    };
};

typedef struct s_xy_list t_xy_list;
struct		s_xy_list
{
  t_xy_list	*next;
  t_xy		data;
};

#define PP_MSGSIZ (sizeof(t_xy))
typedef struct s_pp_msg t_pp_msg;
struct		s_pp_msg
{
  long		type;
  t_xy		pos;
};

typedef struct s_playerinfo t_playerinfo;
struct		s_playerinfo
{
  t_xy		pos;
  t_xy		target;
  uint8_t	id_team;
  int		id_msq;
};

int        pp_enter(t_playerinfo *this);
void	   pp_with_message(t_playerinfo *this, t_pp_msg *msg);
void	   pp_without_message(t_playerinfo *this);
void       pp_attack(t_playerinfo *this);
void       pp_gather(t_playerinfo *this);

bool       pp_target_exists(t_playerinfo *pl);
uint8_t	   team_living_players(uint8_t id_team, t_player *players);
bool       pp_team_gathered(t_playerinfo *pl);

t_xy_list  *pp_scan_teammates(t_playerinfo *this);
t_xy_cast  pp_get_center(t_xy_list *list);
void       pp_follow_target(t_playerinfo *this);
t_xy_cast  pp_target_enemy(t_playerinfo const *this);

t_pp_msg   *pp_msq_recv(t_playerinfo *this);
void       pp_msq_send(t_playerinfo *this, long type, t_xy_cast pos);

void       pp_fatal_die(t_playerinfo *this);

t_xy_list  *xy_list_alloc(void);
void       xy_list_free(t_xy_list *list);
int        xy_list_append(t_xy_list **list, uint32_t data);

#endif
