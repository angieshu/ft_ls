#* ************************************************************************** *#
#*                                                                            *#
#*                                                        :::      ::::::::   *#
#*   Makefile                                           :+:      :+:    :+:   *#
#*                                                    +:+ +:+         +:+     *#
#*   By: ashulha <ashulha@student.us.org>           +#+  +:+       +#+        *#
#*                                                +#+#+#+#+#+   +#+           *#
#*   Created: 2017/05/09 15:55:29 by ashulha           #+#    #+#             *#
#*   Updated: 2017/05/09 15:55:31 by ashulha          ###   ########.fr       *#
#*                                                                            *#
#* ************************************************************************** *#

NAME =			ft_ls

LIBFT_DIR =		includes/libft

PRINT_DIR =		includes/ft_printf

GCCFLAG =		gcc -Wall -Wextra -Werror

SRCS =			src

INCL =			src/ft_ls.h


all: $(NAME)

$(NAME):
	@make -C $(LIBFT_DIR) re
	@make -C $(PRINT_DIR) re
	@$(GCCFLAG) -L $(LIBFT_DIR) -lft -L $(PRINT_DIR) $(SRCS)/*.c -lft -I $(INCL) -o $(NAME)

clean:
	@make -C $(LIBFT_DIR) clean
	@make -C $(PRINT_DIR) clean

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	@make -C $(PRINT_DIR) fclean
	@rm -rf $(NAME)

re: fclean all
