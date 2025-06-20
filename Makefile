NAME	:= cub3D
NAMEB	:= cub3D_bonus

include cub3d.mk

BUILD_DIR	:= .build/
BUILD_DIR_BONUS	:= .build_bonus/
OBJS 		:= $(patsubst $(SRCSDIR)%.c,$(BUILD_DIR)%.o,$(SRCS))
OBJSB		:= $(patsubst $(SRCSDIR)%.c,$(BUILD_DIR_BONUS)%.o,$(SRCSBONUS))
DEPS		:= $(OBJS:.o=.d)
DEPSB		:= $(OBJSB:.o=.d)

# ********** FLAGS AND COMPILATION FLAGS ************************************* #

CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror -g3

CPPFLAGS	:= -MMD -MP -I incs/ -I libft/incs/ -I mlx/
CPPFLAGS_BONUS	:= -MMD -MP -I incs/ -I libft/incs/ -I mlx/ -I incs_external/

MLX_FLAGS	:= -L mlx -lmlx_Linux -L/usr/lib -I mlx -lX11 -lm -lz -lXext $(MLX_LIB)
MLX_DIR		:= mlx/
MLX_LIB		:= $(MLX_DIR)libmlx_Linux.a
RM			:= rm -f
RMDIR		+= -r
MAKEFLAGS	+= --no-print-directory
DIR_DUP		= mkdir -p $(BUILD_DIR)
DIR_DUP_BONUS	= mkdir -p $(BUILD_DIR_BONUS)

.DEFAULT_GOAL	:= all

# ********** COUNT FILES ***************************************************** #

DEBUG_MODE	?= 0

NEED_REBUILD_SRC := $(shell find $(SRCSDIR) -name "*.c" -newer $(NAME) 2>/dev/null | wc -l)
NEWER_HEADERS := $(shell find incs/ libft/incs/ -name "*.h" -newer $(NAME) 2>/dev/null | wc -l)
EXECUTABLE_EXISTS := $(shell [ -f $(NAME) ] && echo 1 || echo 0)

RE_TARGET := $(filter re debug,$(MAKECMDGOALS))

ifneq ($(RE_TARGET),)
	NEED_REBUILD := $(words $(SRCS))
else
	ifeq ($(EXECUTABLE_EXISTS),0)
		NEED_REBUILD := $(words $(SRCS))
	else
		ifeq ($(NEWER_HEADERS),0)
			NEED_REBUILD := $(NEED_REBUILD_SRC)
		else
			NEED_REBUILD := $(words $(SRCS))
		endif
	endif
endif

BONUS_TARGET := $(filter bonus debugb,$(MAKECMDGOALS))

ifneq ($(BONUS_TARGET),)
    NEED_REBUILD := $(words $(SRCSBONUS))
else
    ifneq ($(RE_TARGET),)
        NEED_REBUILD := $(words $(SRCS))
    else
        ifeq ($(EXECUTABLE_EXISTS),0)
            NEED_REBUILD := $(words $(SRCS))
        else
            ifeq ($(NEWER_HEADERS),0)
                NEED_REBUILD := $(NEED_REBUILD_SRC)
            else
                NEED_REBUILD := $(words $(SRCS))
            endif
        endif
    endif
endif

# ********** RULES *********************************************************** #

-include $(DEPS)
-include $(DEPSB)

.PHONY: init
init: ensure_mlx FORCE
	@mkdir -p $(BUILD_DIR)
	@echo "$(NEED_REBUILD)" > $(BUILD_DIR)total_files
	@echo "0" > $(BUILD_DIR)current_file

.PHONY: init_bonus
init_bonus: ensure_mlx FORCE
	@mkdir -p $(BUILD_DIR_BONUS)
	@echo "$(NEED_REBUILD)" > $(BUILD_DIR_BONUS)total_files
	@echo "0" > $(BUILD_DIR_BONUS)current_file

.PHONY: all
all: init $(NAME)
	@$(RM) .bonus

$(NAME): libft/libft.a mlx/libmlx_Linux.a mlx/libmlx.a Makefile $(OBJS)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -o $(NAME) $(OBJS) -L libft -lft $(MLX_FLAGS)
	@echo "\n$(GREEN_BOLD)✓ $(NAME) is ready $(RESETC)\n"

libft/libft.a: FORCE
	@$(MAKE) -C libft

mlx/libmlx_Linux.a: ensure_mlx
	@if [ -d "$(MLX_DIR)" ]; then \
		$(MAKE) -C mlx; \
	else \
		echo "$(RED_BOLD)Error: MLX directory not found and could not be cloned$(RESETC)"; \
		exit 1; \
	fi

.PHONY: ensure_mlx
ensure_mlx: FORCE
	@if [ ! -d "$(MLX_DIR)" ]; then \
		echo "$(CYAN)Adding minilibx as submodule...$(RESETC)"; \
		git submodule add https://github.com/42Paris/minilibx-linux.git $(MLX_DIR); \
		git submodule update --init --recursive; \
	fi

$(BUILD_DIR)%.o: $(SRCSDIR)%.c
	@mkdir -p $(dir $@)
	@CURRENT=`cat $(BUILD_DIR)current_file`; \
	CURRENT=$$((CURRENT+1)); \
	echo "$$CURRENT" > $(BUILD_DIR)current_file; \
	TOTAL=`cat $(BUILD_DIR)total_files`; \
	POSITION=$$((CURRENT % 6)); \
	printf "$(ERASE)$(CYAN)["; \
	if [ "$$POSITION" -eq 0 ]; then \
		printf "⠋"; \
	elif [ "$$POSITION" -eq 1 ]; then \
		printf "⠙"; \
	elif [ "$$POSITION" -eq 2 ]; then \
		printf "⠹"; \
	elif [ "$$POSITION" -eq 3 ]; then \
		printf "⠸"; \
	elif [ "$$POSITION" -eq 4 ]; then \
		printf "⠼"; \
	else \
		printf "⠴"; \
	fi; \
	printf "] [%d/%d] $(RESETC)%s" "$$CURRENT" "$$TOTAL" "$<"
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $< -D DEBUG_MODE=$(DEBUG_MODE)

$(BUILD_DIR_BONUS)%.o: $(SRCSDIR)%.c
	@mkdir -p $(dir $@)
	@CURRENT=`cat $(BUILD_DIR_BONUS)current_file`; \
	CURRENT=$$((CURRENT+1)); \
	echo "$$CURRENT" > $(BUILD_DIR_BONUS)current_file; \
	TOTAL=`cat $(BUILD_DIR_BONUS)total_files`; \
	POSITION=$$((CURRENT % 6)); \
	printf "$(ERASE)$(CYAN)["; \
	if [ "$$POSITION" -eq 0 ]; then \
		printf "⠋"; \
	elif [ "$$POSITION" -eq 1 ]; then \
		printf "⠙"; \
	elif [ "$$POSITION" -eq 2 ]; then \
		printf "⠹"; \
	elif [ "$$POSITION" -eq 3 ]; then \
		printf "⠸"; \
	elif [ "$$POSITION" -eq 4 ]; then \
		printf "⠼"; \
	else \
		printf "⠴"; \
	fi; \
	printf "] [%d/%d] $(RESETC)%s" "$$CURRENT" "$$TOTAL" "$<"
	@$(CC) $(CFLAGS) $(CPPFLAGS_BONUS) -c -o $@ $< -D DEBUG_MODE=$(DEBUG_MODE)

.PHONY: debug
debug: clean
	@$(MAKE) DEBUG_MODE=1

.PHONY: debugb
debugb: clean
	@$(MAKE) bonus DEBUG_MODE=1

.PHONY: bonus
bonus: init_bonus .bonus

.bonus: libft/libft.a mlx/libmlx_Linux.a mlx/libmlx.a Makefile $(OBJSB)
	@$(CC) $(CFLAGS) $(CPPFLAGS_BONUS) -o $(NAMEB) $(OBJSB) -L libft -lft $(MLX_FLAGS)
	@echo "\n$(GREEN_BOLD)✓ $(NAMEB) bonus is ready $(RESETC)\n"
	@touch .bonus

.PHONY: clean
clean:
	$(MAKE) clean -C libft/
	@$(RM) $(OBJS) $(DEPS) $(OBJSB) $(DEPSB)
	@echo "$(RED_BOLD)[Cleaning]$(RESETC)"

.PHONY: fclean
fclean: clean
	$(MAKE) fclean -C libft/
	@$(RM) $(RMDIR) $(NAME) $(NAMEB) $(BUILD_DIR) $(BUILD_DIR_BONUS) .bonus
	@echo "$(RED_BOLD)✓ $(NAME) is fully cleaned!$(RESETC)"

.PHONY: re
re: fclean all

.PHONY: FORCE
FORCE:

.SILENT: clean fclean

# ********** COLORS AND BACKGROUND COLORS ************************************ #

RESETC				:= \033[0m
ERASE				:= \033[2K\r

GREEN_BOLD			:= \033[1;32m
RED_BOLD			:= \033[1;31m
CYAN				:= \033[0;36m
