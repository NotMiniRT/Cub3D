override SRCSDIR	:= srcs/
override SRCS		= $(addprefix $(SRCSDIR)$(MANDATORYDIR), $(SRC))
override SRCSBONUS	= $(addprefix $(SRCSDIR)$(BONUSDIR), $(SRCBONUS))

override MANDATORYDIR	:= mandatory/
override BONUSDIR		:= bonus/

override UTILSDIR		:= utils/
override PARSINGDIR		:= parsing/

SRC	+= $(addsuffix .c, $(MAIN))

override MAIN			:= \
	cub3d \

SRC += $(addprefix $(UTILSDIR), $(addsuffix .c, $(UTILSSRC)))

override UTILSSRC		:= \
	utils \

SRC += $(addprefix $(PARSINGDIR), $(addsuffix .c, $(PARSINGSRC)))

override PARSINGSRC		:= \
	check_param_validity \
	fill_scene_infos \
	init \
	readlines_utils \
	readlines \
	utils
