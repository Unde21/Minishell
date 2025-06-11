/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 13:45:35 by samaouch          #+#    #+#             */
/*   Updated: 2025/06/11 18:02:37 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdarg.h>
# include <stdbool.h>
# include <stddef.h>

# define HEX_LOWER "0123456789abcdef"
# define HEX_UPPER "0123456789ABCDEF"

/* ************************************************************************** */
/*						Part 1: Libc functions								  */
/* ************************************************************************** */

void				ft_bzero(void *s, size_t n);
void				*ft_memset(void *s, int c, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
void				*ft_calloc(size_t nmemb, size_t size);
size_t				ft_strlen(const char *s);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
int					ft_toupper(int c);
int					ft_tolower(int c);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
int					ft_isprint(int c);
int					ft_isdigit(int c);
int					ft_isascii(int c);
bool				ft_isspace(int c);
int					ft_isalpha(int c);
int					ft_isalnum(int c);
int					ft_atoi(const char *nptr, int *check_error);
long long			ft_atoll(const char *nptr, int *check_error);
char				*ft_strrchr(const char *s, int c);
char				*ft_strnstr(const char *big, const char *little,
						size_t len);
char				*ft_strdup(const char *s);
char				*ft_strchr(const char *s, int c);
void				ft_swap_array(char **s1, char **s2);

/* ************************************************************************** */
/*						Part 2: Additional functions						  */
/* ************************************************************************** */

void				ft_striteri(char *s, void (*f)(unsigned int, char *));
void				ft_putstr_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putchar_fd(char c, int fd);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_itoa(int n);
char				**ft_split(char const *s, char c);

/* ************************************************************************** */
/*								Bonus part									  */
/* ************************************************************************** */

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

int					ft_lstsize(t_list *lst);

t_list				*ft_lstlast(t_list *lst);
t_list				*ft_lstmap(t_list *lst, void *(f)(void *),
						void (*del)(void *));
t_list				*ft_lstnew(void *content);

void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstadd_front(t_list **lst, t_list *new);
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));

/* ************************************************************************** */
/*								ft_printf								      */
/* ************************************************************************** */

int					ft_printf(const char *format,
						...) __attribute__((format(printf, 1, 2)));
int					print_char(int c);
int					print_str(char *str);
int					format_is_valid(const char *format);
int					print_addr(unsigned long ptr, int count, int index);
int					print_nbr(int n, int check_form, int count);
int					print_hexa(unsigned int n, const char *base, int count);
int					check_format(va_list *params, char format);

/* ************************************************************************** */
/*								ft_dprintf									  */
/* ************************************************************************** */

int					ft_dprintf(int fd, const char *format,
						...) __attribute__((format(printf, 2, 3)));
int					dprint_char(int c, int fd);
int					dprint_str(char *str, int fd);
int					dprint_addr(unsigned long ptr, int nb_char, int index,
						int fd);
int					dprint_nbr(int nb, int check_form, int nb_char, int fd);
int					dprint_hexa(unsigned int n, const char *base, int nb_char,
						int fd);

/* ************************************************************************** */
/*								get_next_line								  */
/* ************************************************************************** */

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef MAX_FD
#  define MAX_FD 1024
# endif

void				*ft_free(char *s);
size_t				ft_strlen_delim(const char *str, int check);
int					read_file(int fd, char *buffer);
char				*get_next_line(int fd);
char				*ft_strnjoin(char const *s1, char const *s2, int c);
char				*clear_buffer(char *buffer);
#endif
