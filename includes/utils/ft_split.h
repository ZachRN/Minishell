#ifndef FT_SPLIT_H
# define FT_SPLIT_H

/*Used to split a variable into seperate strings, used for finding the path in
this program*/
char	**ft_split(char const *s, char c);
char	**free_my_lines(char **str);

#endif