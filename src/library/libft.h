/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 14:01:48 by arurangi          #+#    #+#             */
/*   Updated: 2023/01/16 11:38:17 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <errno.h>
# include <stdio.h>
# include <stdarg.h>
# include <fcntl.h>
# include <stdarg.h>

# define BUFFER_SIZE 1

# define CRED     "\x1b[31m"
# define CGREEN   "\x1b[32m"
# define CYELLOW  "\x1b[33m"
# define CBLUE    "\x1b[34m"
# define CMAGENTA "\x1b[35m"
# define CCYAN    "\x1b[36m"
# define CRESET   "\x1b[0m"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

/* CHECKERS */
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_isspace(char ch);
int		ft_issign(char ch);

/* CONVERTERS */
int		ft_toupper(int c);
int		ft_tolower(int c);
long	ft_atoi(const char *str);

/* MEMORY HANDLING */
void	*ft_calloc(size_t count, size_t size);

/* FILE I/O */
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

char	*get_next_line(int fd);

char	*ft_strjoin_mod(char *stash, char *buffer);
int		ft_strchr_mod(const char *s, char ch);
char	*free_stash(char *stash);

void	ft_putnbr(int nbr);

/* MEMORY FUNCTIONS */
void	ft_bzero(void *s, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memset(void *str, int ch, size_t nbr);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);

/* STRING HANDLING */
int		ft_strlen(const char *str);
void	ft_putchar(char ch);
void	ft_putstr(char *str);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strlcat(char *dest, const char *src, size_t dstsize);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *str);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);

char	**ft_split(char const *str, char ch);
char	**ft_split_fd(int fd, char seperator);
char	**ft_split_sep(char const *str, char ch, char seperator);

char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));

/* LINKED LISTS */
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/* SWAP */
void	ft_swap(int *a, int *b);
int		ft_abs(int x);

/* ERROR HANDLING */
int		success_msg(int return_code, char *message, ...);
int		error_msg(int return_code, char *message, ...);
int		info_msg(int return_code, char *message, ...);

int		ft_printf(const char *str, ...);

void	ft_putfs(char ch, va_list args, int *counter);
int		ft_putnbr_u(unsigned int nbr, int *counter);
int		ft_puthex(unsigned long nbr, char format, int *counter);
int		ft_putnbr_mod(int nbr, int *counter);
int		ft_putstr_mod(char *str);
int		ft_putchar_mod(char c);

/* FREE */
void	ft_free_matrix(char **matrix);

#endif