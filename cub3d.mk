override SRCSDIR	:= srcs/
override SRCS		= $(addprefix $(SRCSDIR)$(MANDATORYDIR), $(SRC))
override SRCSBONUS	= $(addprefix $(SRCSDIR)$(BONUSDIR), $(SRCBONUS))

override MANDATORYDIR	:= mandatory/
override BONUSDIR		:= bonus/

override UTILSDIR		:= utils/
override DISPLAYDIR		:= display/
override PARSINGDIR		:= parsing/
override THREADDIR		:= threads/
override SOUNDDIR		:= sound/
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

# ********** BONUS SOURCES *************************************************** #

SRCBONUS += $(addsuffix .c, $(MAINBONUS))

override MAINBONUS		:= \
	cub3d \

SRCBONUS += $(addprefix $(UTILSDIR), $(addsuffix .c, $(UTILSSRCBONUS)))

override UTILSSRCBONUS	:= \
	cleanup \
	free_main_struct \
	item_utils \
	main_struct \
	map_items \
	utils \

SRCBONUS += $(addprefix $(INITDIR), $(addsuffix .c, $(INITSRCBONUS)))

override INITSRCBONUS	:= \
	check_param_validity \
	init \
	readlines \
	readlines_utils \

SRCBONUS += $(addprefix $(SCENEDIR), $(addsuffix .c, $(SCENESRCBONUS)))

override SCENESRCBONUS	:= \
	check_cardinal_directions \
	color_utils \
	scene_validation \
	scene_validation_utils \
	texture_utils \

SRCBONUS += $(addprefix $(MAPDIR), $(addsuffix .c, $(MAPSRCBONUS)))

override MAPSRCBONUS	:= \
	map_char_validation \
	map_check_boundaries \
	map_check_doors \
	map_check_playable_area \
	map_check_validity \
	map_create_copy \
	map_debug \
	map_debug_collectibles \
	map_init_boundaries \
	map_main_check \
	map_player_check \
	map_store_entities \

SRCBONUS += $(addprefix $(DISPLAYDIR), $(addsuffix .c, $(DISPLAYSRCBONUS)))

override DISPLAYSRCBONUS	:= \
	door_management \
	door_movements \
	frame_display \
	image_function \
	image_utils \
	inputs_define \
	lantern_hud \
	lantern_hud_drawing \
	load_images \
	lst_int \
	minimap \
	minimap_drawing \
	mlx_loop \
	mlx_main_loop \
	monster \
	mouse_hook \
	overlay \
	player \
	player_facing \
	ray_check \
	render_calcul \
	ray_check_init \
	hit_object \
	transparency \
	render_one_ray \
	monster_direction \
	player_direction \
	set_hit_tab \
	timer \
	torch \
	window_start \
	util_hit \

SRCBONUS += $(addprefix $(THREADDIR), $(addsuffix .c, $(THREADSRC)))

override THREADSRC	:= \
	threads_init \
	threads_utils \

SRCBONUS += $(addprefix $(SOUNDDIR), $(addsuffix .c, $(SOUNDSRC)))

override SOUNDSRC	:= \
	bluetooth_detection \
	bluetooth_utils \
	cleanup_sound \
	init_sound \
	load_sound \
	play_sound \
	process_utils \
