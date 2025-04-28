override SRCSDIR	:= srcs/
override SRCS		= $(addprefix $(SRCSDIR)$(MANDATORYDIR), $(SRC))
override SRCSBONUS	= $(addprefix $(SRCSDIR)$(BONUSDIR), $(SRCBONUS))

override MANDATORYDIR	:= mandatory/
override BONUSDIR		:= bonus/

override UTILSDIR	:= utils/
override DISPLAYDIR	:= display/
override PARSINGDIR	:= parsing/

SRC	+= $(addsuffix .c, $(MAIN))

override MAIN			:= \
	cub3d \

SRC += $(addprefix $(UTILSDIR), $(addsuffix .c, $(UTILSSRC)))

override UTILSSRC		:= \
	utils \
	main_struct \

SRC += $(addprefix $(PARSINGDIR), $(addsuffix .c, $(PARSINGSRC)))

override PARSINGSRC		:= \
	check_param_validity \


SRC += $(addprefix $(DISPLAYDIR), $(addsuffix .c, $(DISPLAYSRC)))

override DISPLAYSRC		:= \
	inputs_define \
	window_start \
	frame_display \
	image_function \
	player \
	ray_check \
