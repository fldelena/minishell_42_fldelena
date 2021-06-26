/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fldelena <fldelena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 09:42:53 by frdescam          #+#    #+#             */
/*   Updated: 2021/04/29 20:43:01 by fldelena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

int				ft_atoi(const char *str);
int				ft_count_char(char *str, char c);
int				ft_endline(char *fullstr);
int				ft_isdigit(int ch);
void			ft_putchar(char c);
void			ft_putendl(char const *s);
void			ft_putstr(char const *s);
int				ft_simbcount(char *arr, char c);
char			**ft_split(char const *s, char c);
char			*ft_strchr(const char *str, int ch);
size_t			ft_strcpy(char *dst, char *src);
char			*ft_strdup(const char *str);
char			*ft_strjoin(char const *s1, char const *s2);
size_t			ft_strlcpy(char *dst, char *src, size_t size);
size_t			ft_strlen(const char *s);
int				ft_strnstr(const char *str1, const char *str2, size_t size);
char			*ft_strtrim(char *s1, char *set);
char			*ft_substr(char *s);
int				ft_trim(char *str);
int				get_next_line(int fd, char **line);

#endif
