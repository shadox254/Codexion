/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz <rruiz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 11:16:21 by rruiz             #+#    #+#             */
/*   Updated: 2026/03/12 16:12:51 by rruiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

# define TAKE_DONGLE		"[%u] %i has taken a dongle"
# define COMPILING			"[%u] %i is compiling"
# define DEBUGGING			"[%u] %i is debugging"
# define REFACTORING		"[%u] %i is refactoring"
# define BURNOUT			"[%u] %i burned out"

# define USAGE_ERROR		"Error, invalid arguments. Usage: \"./codexion \
number_of_coders time_to_burnout time_to_compile time_to_debug \
time_to_refactor number_of_compiles_required dongle_cooldown scheduler\"."

# define ARGS_ERROR			"Error, invalid arguments, the first 7 arguments \
must be int higher than 0."

# define LAST_ARGS_ERROR	"Error, invalid argument, the eighth argument \
must be either “fifo/FIFO” or “edf/EDF\"."

# define C_MALLOC_ERROR		"Error, Malloc failed for coders."

# define D_MALLOC_ERROR		"Error, Malloc failed for dongles."

typedef struct s_data	t_data;
typedef struct s_dongle	t_dongle;
typedef struct s_coder	t_coder;
typedef struct s_rules	t_rules;
typedef struct s_timer	t_timer;

typedef struct s_rules
{
	unsigned int	number_of_coders;
	unsigned int	time_to_burnout;
	unsigned int	time_to_compile;
	unsigned int	time_to_debug;
	unsigned int	time_to_refactor;
	unsigned int	number_of_compiles_required;
	unsigned int	dongle_cooldown;
	char			*scheduler;
}	t_rules;

typedef struct s_coder
{
	t_data			*data;
	int				id;
	int				nbr_of_compilations;
	int				finished;
	t_dongle		*left_dongle;
	t_dongle		*right_dongle;
	pthread_t		thread_id;
	int				last_compile;
	pthread_mutex_t	data_lock;
}	t_coder;

typedef struct s_dongle
{
	t_data			*data;
	pthread_mutex_t	lock;
    pthread_cond_t  cond;
    long long       last_release;
    unsigned int    ticket_counter;
    unsigned int    serving_ticket;
}	t_dongle;

typedef struct s_data
{
	t_rules			rules;
	t_coder			*coders;
	t_dongle		*dongles;
	pthread_mutex_t	print_lock;
	int				dead;
	int				is_fifo;
	int				start_time;
	pthread_t		monitor;
}	t_data;

/* init */
int	init_data(t_data *data, char **av);
int	init_coders_dongles(t_data *data);

/* SRC/CODEXION */
void	codexion(char **av);

/* SRC/PARSING/ARGS_VERIFICATION*/
int		args_verif(char **av);

/* SRC/PARSING/RULES_MANAGEMENT*/
void	fill_rules(t_rules *rules, char **av);

/* DEBUG */
void	print_all(t_data data);
void	print_data(t_data data);
void	print_rules(t_rules rules);
void	print_coders(t_data data);


/* SRC/UTILS/ERROR */
void	print_error(char *str);
void	free_data(t_data *data);

/* SRC/UTILS/TIME */
int	get_time();

/* SRC/FIFO */
void	fifo(t_coder *coder);
void	compiling(t_coder *coder);

void	print_action(t_coder *coder, char *action);

#endif