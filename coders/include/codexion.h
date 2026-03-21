/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz <rruiz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 11:16:21 by rruiz             #+#    #+#             */
/*   Updated: 2026/03/20 17:35:35 by rruiz            ###   ########.fr       */
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

# define TAKE_DONGLE		"%u %i has taken a dongle\n"
# define COMPILING			"%u %i is compiling\n"
# define DEBUGGING			"%u %i is debugging\n"
# define REFACTORING		"%u %i is refactoring\n"
# define BURNOUT			"%u %i burned out\n"

# define USAGE_ERROR		"Error, invalid arguments. Usage: \"./codexion \
number_of_coders time_to_burnout time_to_compile time_to_debug \
time_to_refactor number_of_compiles_required dongle_cooldown scheduler\"."

# define ARGS_ERROR			"Error, invalid arguments, the first 7 arguments \
must be int higher than 0."

# define LAST_ARGS_ERROR	"Error, invalid argument, the eighth argument \
must be either “fifo” or “edf\"."

# define CODER_ALONE_ERROR	"Error: A coder can't code alone. Please find \
them a friend."

# define MAX_CODERS_NBR 300

# define CODERS_NBR_ERROR	"Error, the number of coders is too high, the \
maximum is 300."

# define C_MALLOC_ERROR		"Error, Malloc failed for coders."

# define D_MALLOC_ERROR		"Error, Malloc failed for dongles."

# define N_MALLOC_ERROR		"Error, Malloc failed for nodes."

typedef struct s_data	t_data;
typedef struct s_dongle	t_dongle;
typedef struct s_coder	t_coder;
typedef struct s_rules	t_rules;
typedef struct s_timer	t_timer;
typedef struct s_node	t_node;
typedef struct s_heap	t_heap;

typedef struct s_node
{
	int				coder_id;
	long long		deadline;
}	t_node;

typedef struct s_heap
{
	t_node			*nodes;
	int				size;
}	t_heap;

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
	long long		last_compile;
	long long		last_compile_start;
	pthread_mutex_t	data_lock;
}	t_coder;

typedef struct s_dongle
{
	t_data			*data;
	pthread_mutex_t	lock;
	pthread_cond_t	cond;
	long long		last_release;
	unsigned int	ticket_counter;
	unsigned int	serving_ticket;
	t_heap			heap;
}	t_dongle;

typedef struct s_data
{
	t_rules			rules;
	t_coder			*coders;
	t_dongle		*dongles;
	pthread_mutex_t	print_lock;
	int				is_fifo;
	long long		start_time;
	pthread_t		monitor;
	int				is_simu;
	pthread_mutex_t	lock;
}	t_data;

/* CODERS */
void		codexion(char **av);

	/* ENGINE */
		/* ACTION */
void		print_action(t_coder *coder, char *action);
		/* MONITORING */
void		*monitoring(void *arg);
int			is_simu(t_data *data);
		/* MUTEX */
void		init_mutex(t_data *data);
void		destroy_mutex(t_data *data);
		/* THREAD */
void		init_thread(t_data *data);

	/* INIT */
		/* DATA */
int			init_data(t_data *data, char **av);
		/* INITIALIZATION */
int			init_all(t_data *data);

	/* PARSING */
		/* ARGS_VERIFICATION */
int			args_verif(char **av);
		/* RULES_MANAGEMENT */
int			fill_rules(t_rules *rules, char **av);

	/* SCHEDULERS */
		/* EDF */
void		edf(t_coder *coder);
void		edf_compiling(t_coder *coder);
		/* FIFO */
void		fifo(t_coder *coder);
void		debugging_and_refactoring(t_coder *coder);

/* UTILS/DEBUG */
void		print_all(t_data data);
void		print_data(t_data data);
void		print_rules(t_rules rules);
void		print_coders(t_data data);
void		print_error(char *str);

		/* EDF_UTILS */
int			do_compile_edf(t_coder *coder, t_dongle *dongle1,
				t_dongle *dongle2);
void		put_heap(t_coder *coder, t_dongle *dongle);
		/* ERROR */
void		free_data(t_data *data);
void		print_dongles(t_data data);
		/* FIFO_UTILS */
void		fifo_compiling(t_coder *coder);
		/* HEAP_UTILS */
void		heap_insert(t_heap *heap, t_node new_node);
t_node		heap_extract_min(t_heap *heap);
		/* TIME */
long long	get_time(void);
void		custom_sleep(long long time_in_ms, t_data *data);
		/* UTILS */
int			have_finish(t_coder *coder);
void		set_order(t_coder *coder, t_dongle **first, t_dongle **second);
t_node		*create_node(t_node *node, int coder_id, long long deadline);
int			ft_tolower(int c);

#endif