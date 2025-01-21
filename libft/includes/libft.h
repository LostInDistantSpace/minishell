/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:29:17 by bmouhib           #+#    #+#             */
/*   Updated: 2025/01/21 18:32:59 by bmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdarg.h>
# include <string.h>
# include <unistd.h>
# include <limits.h>
# include <math.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_flag
{
	int	left;
	int	sign;
	int	space;
	int	hash;
	int	zero;
	int	star;
	int	width;
	int	precision;
	int	type;
}	t_flag;

/**********************/
/******** LIBC ********/
/**********************/
int		ft_atoi(const char *nptr);
void	ft_bzero(void *s, size_t n);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
size_t	ft_strlcat(char *dst, const char *src, size_t siz);
size_t	ft_strlcpy(char *dst, const char *src, size_t siz);
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new_list);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new_list);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void*));
t_list	*ft_lstmap(t_list *lst, void*(*f)(void*), void (*del)(void*));

/*****************************/
/******** ADDITIONNAL ********/
/*****************************/

int		ft_iswhitespace(int c);
int		ft_isnumber(char *str, int base);
int		ft_isdigit_base(char c, int base);
int		ft_atoi_base(const char *str, int base);
int		ft_has_prefix(const char *str, int base);
long	ft_min(long a, long b);
long	ft_max(long a, long b);
int		ft_strcmp(char *s1, char *s2);

/***********************/
/****** FT_PRINTF ******/
/***********************/
t_flag	init_flag(void);
int		is_type(char c);
int		ft_pad_math(t_flag flag, char *num, long long nb);
int		ft_size(unsigned long int nb, long long int base);
void	ft_putnbr_caps(unsigned long nb, char *tab, int i, unsigned long base);
void	ft_putnbr(unsigned long nb, char *tab, int i, unsigned long base);
void	ft_print_var(va_list args, t_flag flag, int *count);
int		ft_printf(const char *format, ...);
void	ft_print_c(char c, int *count);
void	ft_print_char(char c, t_flag flag, int *count);
void	ft_print_s(char *c, int *count);
void	ft_print_string(char *c, t_flag flag, int *count);
void	ft_print_u(unsigned int nb, t_flag flag, int *count);
void	ft_print_x(unsigned int a, int add, t_flag flag, int *count);
int		ft_print_p(void *a, t_flag flag, int *count);
void	ft_print_padding(int len, char c, int *count);
void	ft_print_sign(t_flag flag, long long int nb, int *count);
void	ft_print_nb(long long int nb, t_flag flag, int *count);
void	flag_left(t_flag *flag);
char	*ft_itoa_printf(int n);
char	*ft_utoa(unsigned int n);
char	*ft_xtoa(unsigned long int n, int x);
char	*flag_digit(char *str, int *fdigit, t_flag *flag, va_list args);

/***********************/
/********* GNL *********/
/***********************/

char	*get_next_line(int fd);
char	*ft_copy_buffer(char *str);
int		ft_char_search(const char *s, int c);
size_t	ft_buffer_len(const char *s);
char	*ft_join_buffer(char *s1, char *s2);

#endif