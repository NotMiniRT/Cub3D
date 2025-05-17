#include "structs.h"
#include "common.h"
#include "image.h"
#include "mlx.h"
#include "minimap.h"
#include "fuel_bar.h"

bool	overlay(t_main_struct *main_struct)
{
	if (display_hud(main_struct) && display_minimap(main_struct))
		return (false);
	return (true);
}
