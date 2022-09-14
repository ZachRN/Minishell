//
//  fd_handl_utils.h
//  x_mini
//
//  Created by Julia Demura on 10/09/2022.
//

#ifndef FD_HANDL_UTILS_H
# define FD_HANDL_UTILS_H

# include "form_exec_struct.h"

void	close_if_infile_if_heredoc_if_outfile(t_fd *fd);
int		open_outfile_with_without_append(int append, const char *path);
int		get_fd_infile_or_heredoc(int heredoc, const char
			*path_infile, int in_flag);
void	direct_open_dup_infile(const char *path, t_fd *fd);
void	direct_open_dup_outfile(const char *path, t_fd *fd);

#endif /* fd_handl_utils_h */
