/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddadi <mhaddadi@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:20:38 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/06/25 19:57:28 by mhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

/* ************************************************************************** */
/*                             Standard Libraries                             */
/* ************************************************************************** */

# include <stddef.h> /* For size_t */
# include <stdlib.h> /* For malloc, free */
# include <unistd.h> /* For write */

/* ************************************************************************** */
/*                                 Data Types                                 */
/* ************************************************************************** */

/**
 * @struct s_list
 * @brief Structure representing a node in a singly linked list.
 * 
 * @var content Pointer to the data held by the node.
 * @var next Pointer to the next node in the list.
 */
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}			t_list;

/* ************************************************************************** */
/*                               Libc Functions                               */
/* ************************************************************************** */

/* Character checks */
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
/* String functions */

size_t			ft_strlen(const char *s);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strnstr(const char *big, const char *little, size_t len);
size_t			ft_strlcpy(char *dst, const char *src, size_t size);
size_t			ft_strlcat(char *dst, const char *src, size_t n);

/* Memory functions */
void			*ft_memset(void *s, int c, size_t n);
void			ft_bzero(void *s, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);

/* Character transformations */
int				ft_toupper(int c);
int				ft_tolower(int c);

/* String and memory allocation */
void			*ft_calloc(size_t n, size_t size);
char			*ft_strdup(const char *s);

/* ************************************************************************** */
/*                              Additional Functions                         */
/* ************************************************************************** */

/* String manipulation */
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s1, char const *set);
char			**ft_split(char const *s, char c);
int				ft_atoi(const char *nptr);
char			*ft_itoa(int n);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void			ft_striteri(char *s, void (*f)(unsigned int, char*));

/* Output functions */
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);

/* ************************************************************************** */
/*                               Bonus Functions                              */
/* ************************************************************************** */

/* Linked list management */
t_list			*ft_lstnew(void *content);
void			ft_lstadd_front(t_list **lst, t_list *newl);
int				ft_lstsize(t_list *lst);
t_list			*ft_lstlast(t_list *lst);
void			ft_lstadd_back(t_list **lst, t_list *newl);
void			ft_lstdelone(t_list *lst, void (*del)(void *));
void			ft_lstclear(t_list **lst, void (*del)(void *));
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstmap(t_list *lst, void*(*f)(void *), void(*del)(void *));

#endif /* LIBFT_H */
