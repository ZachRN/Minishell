//
//  fd_handl_utils.h
//  x_mini
//
//  Created by Julia Demura on 10/09/2022.
//

#ifndef fd_handl_utils_h
#define fd_handl_utils_h

#include "form_exec_struct.h"

void	direct_open_dup_infile(const char *path, t_fd *fd);
void	direct_open_dup_outfile(const char *path, t_fd *fd);

#endif /* fd_handl_utils_h */
