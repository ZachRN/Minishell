//
//  fd_handl_utils.h
//  x_mini
//
//  Created by Julia Demura on 10/09/2022.
//

#ifndef fd_handl_utils_h
#define fd_handl_utils_h

#include "form_exec_struct.h"

void	close_if_infile_if_heredoc_if_outfile(t_fd *fd);
int		open_outfile_with_without_append(int append, const char *path);
int		get_fd_infile_or_heredoc(int heredoc, const char *path_infile, int in_flag);

#endif /* fd_handl_utils_h */
