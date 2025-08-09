#------------------------------------------------------------------------------#
#                                  GENERICS                                    #
#------------------------------------------------------------------------------#

# Special variables
DEFAULT_GOAL:= all
.DELETE_ON_ERROR: $(NAME)
.PHONY: all bonus clean fclean re cleanall
#------------------------------------------------------------------------------#
#                                VARIABLES                                     #
#------------------------------------------------------------------------------#

# Compiler and flags
CC		=	c++
CFLAGS	=	-Wall -Werror -Wextra -std=c++98  -g3 -O0 -I./includes
RM		=	rm -rf

# Dir and file names
NAME	=	btc
SRCS	=	./src/main.cpp ./src/BitcoinExchange.cpp
BIN_DIR =	./bin
OBJS	=	$(addprefix $(BIN_DIR)/, $(notdir $(SRCS:.cpp=.o)))
INC		=	$(wildcard /includes/*.hpp)

GREEN	=	"\033[32;1m"
RED		=	"\033[31;1m"
CYAN	=	"\033[36;1;3m"
WHITE_U	=	"\033[37;1;4m"
WHITE_B	=	"\033[37;1m"
LIMITER =	"\033[0m"

#------------------------------------------------------------------------------#
#                                 TARGETS                                      #
#------------------------------------------------------------------------------#

all: $(BIN_DIR) $(NAME)

# Generates output file
$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $@
	@echo $(WHITE_U)Compilation Complete!$(LIMITER)
	@echo
	@echo $(CYAN)run it with$(LIMITER) $(WHITE_B)./$(NAME)" input.txt"$(LIMITER)

# Compiles sources into objects
$(BIN_DIR)/%.o: ./src/%.cpp $(INC)
	@echo $(GREEN)[Compiling $<]$(LIMITER) $(WHITE_U)with$(LIMITER) $(CYAN)[$(CC) $(CFLAGS)]$(LIMITER)
	@$(CC) $(CFLAGS) -c $< -o $@

# Create bin directory
$(BIN_DIR): input.txt
	@echo $(GREEN)[Creating example "input.txt"]$(LIMITER)
	@echo $(GREEN)[Creating $(BIN_DIR)]$(LIMITER)
	@mkdir -p $@
# Downloads and extracts data.csv
	@wget https://cdn.intra.42.fr/document/document/34440/cpp_09.tgz
	@tar -xzf cpp_09.tgz --strip-components=1 -C ./
	@rm cpp_09.tgz

# Removes objects
clean:
	@echo $(GREEN)[Cleaning objects]$(LIMITER)
	@$(RM) $(OBJS)

# Removes objects and executables
fclean: clean
	@echo $(GREEN)[Cleaning $(NAME)]$(LIMITER)
	@$(RM) $(NAME)
	@$(RM) $(BIN_DIR)
	@echo $(GREEN)[Cleaning example input file and database]$(LIMITER)
	@$(RM) input.txt
	@$(RM) data.csv
# Removes objects and executables and remakes
re: fclean all

input.txt:
	@echo "date | value" > input.txt
	@echo "2011-01-03 | 3" >> input.txt
	@echo "2011-01-03 | 2" >> input.txt
	@echo "2011-01-03 | 1" >> input.txt
	@echo "2011-01-03 | 1.2" >> input.txt
	@echo "2011-01-09 | 1" >> input.txt
	@echo "2012-01-11 | -1" >> input.txt
	@echo "2001-42-42" >> input.txt
	@echo "2012-01-11 | 1" >> input.txt
	@echo "2012-01-11 | 2147483648" >> input.txt

cleanall:
	@cd ../ex00 && make fclean
	@cd ../ex01 && make fclean
	@cd ../ex02 && make fclean


