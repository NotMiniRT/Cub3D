override SRCSDIR	:= srcs/
override SRCS		= $(addprefix $(SRCSDIR)$(MANDATORYDIR), $(SRC))
override SRCSBONUS	= $(addprefix $(SRCSDIR)$(BONUSDIR), $(SRCBONUS))

override MANDATORYDIR	:= mandatory/
override BONUSDIR		:= bonus/

override UTILSDIR		:= utils/
override PARSINGDIR		:= parsing/

override MAPDIR			:= $(PARSINGDIR)map/
override UTILSDIR	:= utils/
override DISPLAYDIR	:= display/
override PARSINGDIR	:= parsing/

SRC	+= $(addsuffix .c, $(MAIN))

override MAIN			:= \
	cub3d \

SRC += $(addprefix $(UTILSDIR), $(addsuffix .c, $(UTILSSRC)))

override UTILSSRC		:= \
	cleanup \
	utils \
	main_struct \

SRC += $(addprefix $(PARSINGDIR), $(addsuffix .c, $(PARSINGSRC)))

override PARSINGSRC		:= \
	check_cardinal_directions \
	check_param_validity \
	color_utils \
	init \
	readlines_utils \
	readlines \
	scene_validation_utils \
	scene_validation \
	texture_utils \

SRC += $(addprefix $(MAPDIR), $(addsuffix .c, $(MAPSRC)))

override MAPSRC			:= \
	map_char_validation \
	map_check_boundaries \
	map_check_playable_area \
	map_check_validity \
	map_create_copy \
	map_debug \
	map_init_boundaries \
	map_main_check \
	map_player_check \


SRC += $(addprefix $(DISPLAYDIR), $(addsuffix .c, $(DISPLAYSRC)))

override DISPLAYSRC		:= \
	inputs_define \
	window_start \
	frame_display \
	image_function \
	player \
	ray_check \
	mlx_loop \
	timer \
