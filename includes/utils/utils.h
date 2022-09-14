//
//  utils.h
//  x_mini
//
//  Created by Julia Demura on 06/09/2022.
//

#ifndef UTILS_H
# define UTILS_H

# include "utils_write.h"
# include "utils_malloc.h"
# include "utils_strings.h"
# include "utils_basics.h"
# include "ft_atoi.h"
# include "ft_calloc.h"
# include "ft_itoa.h"
# include "ft_split.h"
# include "ft_strdup.h"
# include "ft_strjoin.h"
# include "ft_strlen.h"
# include "ft_strncmp.h"
# include "ft_substr.h"

#endif /* utils_h */

//==> ./configure --prefix=/Users/ydemura/.brew/Cellar/readline/8.1.2
//==> make install
//==> Caveats
//readline is keg-only, which means it was
//										not symlinked into /Users/ydemura/.brew,
//because macOS provides BSD libedit.
//
//For compilers to find readline you may need to set:
//  export LDFLAGS="-L/Users/ydemura/.brew/opt/readline/lib"
//  export CPPFLAGS="-I/Users/ydemura/.brew/opt/readline/include"
//
//==> Summary
//🍺  /Users/ydemura/.brew/Cellar/readline/8.1.2:
//											48 files, 1.6MB, built in 21 seconds
//==> Running `brew cleanup readline`...
//Disable this behaviour by setting HOMEBREW_NO_INSTALL_CLEANUP.
//Hide these hints with HOMEBREW_NO_ENV_HINTS (see `man brew`).
//f1r2s19%
