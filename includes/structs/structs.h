#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct	s_env
{
    char			*var_name;
    char			*var_content;
    char			*var_together;
    struct s_env	*next;
}				t_env;

#endif