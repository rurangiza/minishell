/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 11:25:02 by akorompa          #+#    #+#             */
/*   Updated: 2023/03/01 13:17:15 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdio.h>

# define BUFFER_SIZE 1

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memchr(const void *str, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memset(void *str, int c, size_t n);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_striteri(char	*s, void (*f)(unsigned int, char *));
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list	*lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));

char	*ft_strchr(const char *str, int n);
char	*ft_strdup(const char *s1);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strrchr(const char *str, int c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_itoa(int n);

size_t	ft_strlcat(char *dest, const char *src, size_t size);
size_t	ft_strlen(const char *str);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);

long	ft_atoi(const char *str);
int		ft_isalnum(int c);
int		ft_isalpha(int i);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_tolower(int c);
int		ft_toupper(int c);
int		ft_lstsize(t_list *lst);

t_list	*ft_lstnew(void *content);
t_list	*ft_lstlast(t_list *list);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

char	*get_next_line(int fd);
char	*ft_strjoin_mod(char *stash, char *buffer);
int		ft_strchr_mod(const char *s, char ch);
int		ft_isspace(char ch);
char	*free_stash(char *stash);

// int	error_msg(int return_code, char *message, ...);
// int	success_msg(int return_code, char *message, ...);
// int	info_msg(int return_code, char *message, ...);

#endif