#------------------------------------------------------------------------------#
#                                  GENERICS                                    #
#------------------------------------------------------------------------------#

# Special variables
DEFAULT_GOAL: all
.DELETE_ON_ERROR: $(NAME)
.PHONY: all bonus clean fclean re test

#------------------------------------------------------------------------------#
#                                VARIABLES                                     #
#------------------------------------------------------------------------------#

# Compiler and flags
CC		=	c++
CFLAGS	=	-Wall -Werror -Wextra -std=c++98 -g3 -O0 -I./includes
RM		=	rm -rf

# Dir and file names
NAME	=	ft_sed
SRCS	=	./src/main.cpp ./src/ft_sed.cpp
BIN_DIR =	./bin
OBJS	=	$(addprefix $(BIN_DIR)/, $(notdir $(SRCS:.cpp=.o)))
INC		=	$(wildcard ./includes/*.hpp)

GREEN	=	"\033[32;1m"
RED		=	"\033[31;1m"
CYAN	=	"\033[36;1;3m"
WHITE_U	=	"\033[37;1;4m"
LIMITER =	"\033[0m"

#------------------------------------------------------------------------------#
#                                 TARGETS                                      #
#------------------------------------------------------------------------------#

all: $(BIN_DIR) $(NAME)

# Generates output file
$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $@

# Compiles sources into objects
$(BIN_DIR)/%.o: ./src/%.cpp $(INC)
	@echo $(GREEN)[Compiling $<]$(LIMITER) $(WHITE_U)with$(LIMITER) $(CYAN)[$(CC) $(CFLAGS)]$(LIMITER)
	@$(CC) $(CFLAGS) -c $< -o $@

# Create bin directory
$(BIN_DIR):
	@echo $(GREEN)[Creating $(BIN_DIR)]$(LIMITER)
	@mkdir -p $@

# Removes objects
clean:
	@echo $(GREEN)[Cleaning objects]$(LIMITER)
	@$(RM) $(OBJS)

# Removes objects and executables
fclean: clean
	@echo $(GREEN)[Cleaning $(NAME)]$(LIMITER)
	@$(RM) $(NAME)
	@$(RM) $(BIN_DIR)
	@$(RM) test.txt
	@$(RM) test.txt.replace

# Removes objects and executables and remakes
re: fclean all

# Test target
test: all
	@echo $(GREEN)[Creating test.txt\n]$(LIMITER)
	@echo "This is the first paragraph.\nIt contains some text.\n\nThis is the second paragraph.\nIt also contains some text." > test.txt
	@echo $(GREEN)[Content of test.txt before modification]$(LIMITER)
	@cat test.txt
	@echo
	@echo $(GREEN)[Running ft_sed with parameters: test.txt \"paragraph\" \"section\"]$(LIMITER)
	@./$(NAME) test.txt "paragraph" "section"
	@echo $(GREEN)[Content of test.txt.replace after modification]$(LIMITER)
	@cat test.txt.replace
	@echo