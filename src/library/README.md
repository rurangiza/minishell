# Libft

## Personal Library of function in C

This project consists of re-writing built-in functions in C from scratch using our own logic and later, adding new functions.

The goal being to understand how they work exactly, what clever tricks were used to implement them, and recognize their strengths/limitations so we can use them in a more deliberate way.

In this project, I learned how to:
- Implement functions for tasks like string handling (identify characters type / copy, concatenate, trim, split, search / convert to a string to a number,...) 
- Create a custom library
- Write a Makefile 


## Checkers
| Function name                                                        | Description |
|---------------                                                       |-------------|
| [isalpha](https://github.com/rurangiza/libft/blob/main/ft_isalpha.c) | checks whether a character is an alphabet or not                                     |
| [isdigit](https://github.com/rurangiza/libft/blob/main/ft_isdigit.c) | checks whether a character is numeric character (0-9) or not                         |
| [isalnum](https://github.com/rurangiza/libft/blob/main/ft_isalnum.c) | checks whether the argument is an alphanumeric character (alphabet or number) or not |
| [isascii](https://github.com/rurangiza/libft/blob/main/ft_isascii.c) | check whether the argument is an ascii value                                         |
| [isprint](https://github.com/rurangiza/libft/blob/main/ft_isprint.c) | check whether the argument is a printable character                                  |
  
## Converters
| Function name                                                        | Description |
|---------------                                                       |-------------|
| [toupper](https://github.com/rurangiza/libft/blob/main/ft_toupper.c) | converts a lowercase alphabet to an uppercase                                        |
| [tolower](https://github.com/rurangiza/libft/blob/main/ft_tolower.c) | converts an uppercase alphabet to lowercase                                          |
| [atoi](https://github.com/rurangiza/libft/blob/main/ft_atoi.c)       | converts a string into an integer                                                    |
| [itoa](https://github.com/rurangiza/libft/blob/main/ft_itoa.c)             | converts an integer into a string                                                                |

## String Handling
| Function name                                                        | Description                                                                          |
|----------------------------------------------------------------------|--------------------------------------------------------------------------------------|
| [strlen](https://github.com/rurangiza/libft/blob/main/ft_strlen.c)   | calculate the length of a string                                                     |
| [strlcpy](https://github.com/rurangiza/libft/blob/main/ft_strlcpy.c) | copies a certain number of characters from one string to another                     |
| [strlcat](https://github.com/rurangiza/libft/blob/main/ft_strlcat.c) | concatenates a certain number of characters from one string to another               |
| [strchr](https://github.com/rurangiza/libft/blob/main/ft_strchr.c)   | searches for the first occurence of a character in a given string                    |
| [strrchr](https://github.com/rurangiza/libft/blob/main/ft_strrchr.c) | searches for the last occurence of a character in a given string                     |
| [strncmp](https://github.com/rurangiza/libft/blob/main/ft_strncmp.c) | compares at most the first n characters of two strings                               |
| [strnstr](https://github.com/rurangiza/libft/blob/main/ft_strnstr.c) | locates the first occurence of a string in another                                   |
| [strdup](https://github.com/rurangiza/libft/blob/main/ft_strdup.c)   | duplicates a string (deep copy)                                                      |
| [substr](https://github.com/rurangiza/libft/blob/main/ft_substr.c)         | duplicates part of a string                                                                      |
| [strjoin](https://github.com/rurangiza/libft/blob/main/ft_strjoin.c)       | concatenates two strings to create a third                                                       |
| [strtrim](https://github.com/rurangiza/libft/blob/main/ft_strtrim.c)       | removes a set of characters at beginning and end of a string                                     |
| [split](https://github.com/rurangiza/libft/blob/main/ft_split.c)           | breaks up a string into an array of substrings based on a seperator character                    |
| [strmapi](https://github.com/rurangiza/libft/blob/main/ft_strmapi.c)       | applies a function to each character of a string to create a new string (returns the new string) |
| [striteri](https://github.com/rurangiza/libft/blob/main/ft_striteri.c)     | applies a function to each character of a string to create a new string                          |

## Memory Area
| Function name | Description |
|---------------|-------------|
| [memset](https://github.com/rurangiza/libft/blob/main/ft_memset.c)   | copies a character to the first n characters of a string                             |
| [bzero](https://github.com/rurangiza/libft/blob/main/ft_bzero.c)     | erases the data in the first n bytes of a given memory location                      |
| [memcpy](https://github.com/rurangiza/libft/blob/main/ft_memcpy.c)   | copies n bytes from memory area src to dest                                          |
| [memmove](https://github.com/rurangiza/libft/blob/main/ft_memmove.c) | copies n bytes from memory area src to dest (handles overlap)                        |
| [memchr](https://github.com/rurangiza/libft/blob/main/ft_memchr.c)   | searches for the first occurence of a character in a given memory area               |
| [memcmp](https://github.com/rurangiza/libft/blob/main/ft_memcmp.c)   | compares the first n bytes of two different memory areas                             |

## Memory Allocation
| Function name | Description |
|---------------|-------------|
| [calloc](https://github.com/rurangiza/libft/blob/main/ft_calloc.c)   | allocates a specified amount of memory and initialize it to zero                     |

## File I/O
| Function name | Description |
|---------------|-------------|
| [putchar_fd](https://github.com/rurangiza/libft/blob/main/ft_putchar_fd.c) | outputs a character to a given file descriptor                                                   |
| [putstr_fd](https://github.com/rurangiza/libft/blob/main/ft_putstr_fd.c)   | outputs a string to a given file descriptor                                                      |
| [putendl_fd](https://github.com/rurangiza/libft/blob/main/ft_putendl_fd.c) | outputs a string to a given file descriptor, followed by a new line                              |
| [putnbr_fd](https://github.com/rurangiza/libft/blob/main/ft_putnbr_fd.c)   | outputs an integer to a given file descriptor                                                    |
| [ft_split_fd](https://github.com/rurangiza/libft/blob/main/ft_split_fd.c)  | breaks text file into an array of substrings based on a separator |

## Linked Lists
| Function name                                                                        | Description                                         |
|--------------------------------------------------------------------------------------|-----------------------------------------------------|
| [lstnew](https://github.com/rurangiza/libft/blob/main/ft_lstnew_bonus.c)             | creates a node containing given content             |
| [lstadd_front](https://github.com/rurangiza/libft/blob/main/ft_lstadd_front_bonus.c) | adds a given node at the beginning of a linked list |
| [lstsize](https://github.com/rurangiza/libft/blob/main/ft_lstsize_bonus.c)           | counts the number of nodes in a linked list         |
| [lstlast](https://github.com/rurangiza/libft/blob/main/ft_lstlast_bonus.c)           | returns the last node of a linked list              |
| [lstadd_back](https://github.com/rurangiza/libft/blob/main/ft_lstadd_back_bonus.c)   | adds a given node at the end of a linked list       |
| [lstdelone](https://github.com/rurangiza/libft/blob/main/ft_lstdelone_bonus.c)       | deletes a node                                      |
| [lstclear](https://github.com/rurangiza/libft/blob/main/ft_lstclear_bonus.c)         | deletes a linked list one node at a time            |

