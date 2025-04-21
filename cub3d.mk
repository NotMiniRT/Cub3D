override SRCSDIR	:= srcs_mandatory/
override SRCS		= $(addprefix $(SRCSDIR), $(SRC))

override UTILSDIR	:= utils/

SRC	+= $(addsuffix .c, $(MAIN))

override MAIN			:= \
	cub3d \

SRC += $(addprefix $(UTILSDIR), $(addsuffix .c, $(UTILSSRC)))

override UTILSSRC		:= \
	test \
