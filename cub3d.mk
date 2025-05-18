override SRCSDIR	:= srcs/
override SRCS		= $(addprefix $(SRCSDIR)$(MANDATORYDIR), $(SRC))
override SRCSBONUS	= $(addprefix $(SRCSDIR)$(BONUSDIR), $(SRCBONUS))

override MANDATORYDIR	:= mandatory/
override BONUSDIR		:= bonus/

override UTILSDIR		:= utils/
override DISPLAYDIR		:= display/
override PARSINGDIR		:= parsing/
override THREADDIR		:= threads/
override MAPDIR		    := $(PARSINGDIR)map/
override SCENEDIR		:= $(PARSINGDIR)scene/
override INITDIR		:= $(PARSINGDIR)init/

SRC	+= $(addsuffix .c, $(MAIN))

override MAIN			:= \
	cub3d \

SRC += $(addprefix $(UTILSDIR), $(addsuffix .c, $(UTILSSRC)))

override UTILSSRC		:= \
	cleanup \
	utils \
	main_struct \

SRC += $(addprefix $(INITDIR), $(addsuffix .c, $(INITSRC)))

override INITSRC		:= \
	check_param_validity \
	init \
	readlines_utils \
	readlines \

SRC += $(addprefix $(SCENEDIR), $(addsuffix .c, $(SCENESRC)))

override SCENESRC		:= \
	check_cardinal_directions \
	color_utils \
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
	render_one_ray \
	image_utils \
	player_facing \



SRCBONUS += $(addsuffix .c, $(MAINBONUS))

override MAINBONUS		:= \
	cub3d \

SRCBONUS += $(addprefix $(UTILSDIR), $(addsuffix .c, $(UTILSSRCBONUS)))

override UTILSSRCBONUS	:= \
	cleanup \
	utils \
	main_struct \

SRCBONUS += $(addprefix $(INITDIR), $(addsuffix .c, $(INITSRCBONUS)))

override INITSRCBONUS	:= \
	check_param_validity \
	init \
	readlines_utils \
	readlines \

SRCBONUS += $(addprefix $(SCENEDIR), $(addsuffix .c, $(SCENESRCBONUS)))

override SCENESRCBONUS	:= \
	check_cardinal_directions \
	color_utils \
	scene_validation_utils \
	scene_validation \
	texture_utils \

SRCBONUS += $(addprefix $(MAPDIR), $(addsuffix .c, $(MAPSRCBONUS)))

override MAPSRCBONUS	:= \
	map_char_validation \
	map_check_boundaries \
	map_check_doors \
	map_check_playable_area \
	map_check_validity \
	map_create_copy \
	map_debug_collectibles \
	map_debug \
	map_init_boundaries \
	map_main_check \
	map_player_check \
	map_store_entities \

SRCBONUS += $(addprefix $(DISPLAYDIR), $(addsuffix .c, $(DISPLAYSRCBONUS)))

override DISPLAYSRCBONUS	:= \
	frame_display \
	image_function \
	image_utils \
	inputs_define \
	lantern_hud_drawing \
	lantern_hud \
	minimap_drawing \
	minimap \
	mlx_loop \
	mouse_hook \
	overlay \
	player_facing \
	player \
	ray_check \
	render_one_ray \
	timer \
	window_start \

SRCBONUS += $(addprefix $(THREADDIR), $(addsuffix .c, $(THREADSRC)))

override THREADSRC	:= \
	threads_init \
	threads_utils \
