/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 09:45:41 by dda-silv          #+#    #+#             */
/*   Updated: 2021/05/11 12:39:22 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdio.h>
# include "constants_libft.h"
# include "structs_libft.h"

/*
** MEMORY FUNCTIONS
*/

void				*ft_realloc(void *ptr, size_t orig_size, size_t new_size);
void				*ft_calloc(size_t nmemb, size_t size);
void				*ft_memset(void *s, int c, size_t n);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memccpy(void *dest, const void *src, int c, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);

/*
** CONVERSION FUNCTIONS
*/

char				*ft_ftoa(long double nb, int precision);
char				*ft_convert_base(unsigned long long nbr, char *base_to);
char				*ft_itoa(long long n);
char				*ft_ultoa(unsigned long long n);
long long			ft_atoi(const char *str);

/*
** PRINTING FUNCTIONS
*/

int					ft_putchar(char c);
int					ft_putstr(char *str);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);

/*
** STRINGS FUNCTIONS
*/

size_t				ft_strlen(const char *s);
char				*ft_strcpy(char *dest, const char *src);
char				*ft_strncpy(char *dest, char *src, size_t n);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
char				*ft_strncat(char *dest, char *src, unsigned int nb);
char				*ft_strcat(char *dest, char *src);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(char *str, char *to_find);
char				*ft_strnstr(const char *big,
						const char *little,
						size_t len);
int					ft_strcmp(char *s1, char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_strdup(const char *s);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_strtrim_all(char const *s1, char const *set);
char				**ft_split(char *str, char *charset);
int					get_next_line(int fd, char **line);
int					ft_strisdigit(char *s);
int					ft_strisnumber(char *s);
int					ft_strisspace(char *str);
int					ft_strchr_freq(const char *s, int c);

/*
** CHAR FUNCTIONS
*/

int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
int					ft_isspace(char c);

/*
** LINKED LISTS FUNCTIONS
*/

t_list				*ft_lstnew(void *data);
void				ft_lstadd_front(t_list **lst, t_list *new);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstadd_after_another(t_list *node,
						t_list *node_to_insert);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstdelone(t_list *lst, void (*del)(void*));
void				ft_lstdel_first(t_list **lst, void (*del)(void*));
void				ft_lstdel_last(t_list *lst, void (*del)(void*));
void				ft_lstclear(t_list **lst, void (*del)(void*));
void				ft_lstclear_if(t_list **lst,
						int (*cmp)(void *),
						void (*del)(void *));
void				ft_lstdel_int(void *data);
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst,
						void *(*f)(void *),
						void (*del)(void *));
void				ft_lst_print_s(t_list *lst);
void				ft_lst_print_d(t_list *lst);
long long			ft_lst_get_min(t_list *lst);
long long			ft_lst_get_max(t_list *lst);
long long			ft_lst_get_median(t_list *lst);
long long			ft_lst_get_qrtl(t_list *lst, int qrtl_picked);
long long			ft_lst_get_decile(t_list *lst, int dcl_picked);
long long			ft_lst_get_centile(t_list *lst, int ctl_picked);
int					ft_lst_get_node_index(t_list *lst, long long data_to_find);
void				*ft_lst_get_data_node(t_list *lst, int index);
t_list				*ft_lstdup(t_list *lst);
void				ft_lst_sort(t_list **lst, int (*op)(int, int));
int					ascending(int a, int b);
int					descending(int a, int b);
void				*ft_lst_get_data_last_node(t_list *lst);

/*
** DOUBLE LINKED LISTS FUNCTIONS
*/

t_dlist				*ft_dlstnew(void *data);
void				ft_dlstadd_front(t_dlist **lst, t_dlist *new);
void				ft_dlstadd_back(t_dlist **lst, t_dlist *new);
t_dlist				*ft_dlstlast(t_dlist *lst);
void				ft_dlstadd_after_another(t_dlist *node,
						t_dlist *node_to_insert);
int					ft_dlstsize(t_dlist *lst);
void				ft_dlstdelone(t_dlist *lst, void (*del)(void*));
void				ft_dlstdel_first(t_dlist **lst, void (*del)(void*));
void				ft_dlstdel_last(t_dlist *lst, void (*del)(void*));
void				ft_dlstclear(t_dlist **lst, void (*del)(void*));

/*
** MATH FUNCTIONS
*/

int					ft_is_even(long long nb);
long double			ft_remainder(long double numer, long double denom);
long long			ft_power(long long nb, long long power);
long long			ft_sqrt(long long nb);
long long			ft_abs(long long n);
long double			ft_fabs(long double n);
size_t				get_len_int(long long nb);
size_t				get_len_float(long double nb);
size_t				get_len_uint(unsigned long long nb);
long long			ft_round(long double nb);
long double			ft_roundf(long double nb, int decimal_places);

/*
** ARRAY FUNCTIONS
*/

void				reverse_arr(int *arr, int size);
void				free_arr(void **ptr);
void				print_arr_int(int *arr, int len);
void				print_arr_str(char **strs);

/*
** COMPARISON FUNCTIONS
*/

int					is_equal(int a, int b);
int					is_greater_than_or_equal(int a, int b);
int					is_greater_than(int a, int b);
int					is_less_than_or_equal(int a, int b);
int					is_less_than(int a, int b);

#endif
