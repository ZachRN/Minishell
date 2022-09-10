//
//  fd_management.h
//  minishell_xcd
//
//  Created by Julia Demura on 06/09/2022.
//

#ifndef fd_management_h
#define fd_management_h

#include "form_exec_struct.h"

void	pick_fd_for_child(t_param *param, int index, int comm_number);
void	manage_parent_fd(int index, int comm_numb, t_fd *fd);

#endif /* fd_management_h */
