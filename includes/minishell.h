/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: znajda <znajda@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/15 15:39:54 by znajda        #+#    #+#                 */
/*   Updated: 2022/07/15 15:58:10 by znajda        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*This is defining all of our structs which will be used for minishell*/

enum tokens {
    Command_Name = 0,
    Command_Arg = 1,
    Break_PIPE = 2,
    Break_
};
/*This contains all of our token type ids, and is a list for when they come
this will store information so that way it is easier to parse later*/
typedef struct s_token
{
    enum tokens token_id;
    struct s_token *next;
}               t_token;

/*
This is the core part of minishell, launching it from main.c
it runs in an infinite loop reading an input from readline
which is then parsed and given away to the execution part after coming back the
input is then freed to avoid memory leaks and continues on
*/
int	minishell(void);

#endif