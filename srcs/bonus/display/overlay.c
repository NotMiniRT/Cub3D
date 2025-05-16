#include "structs.h"
#include "common.h"
#include "image.h"
#include "mlx.h"
#include "minimap.h"

bool	overlay(t_main_struct *main_struct)
{
	if (display_minimap(main_struct))
		return (false);
	return (true);
}
