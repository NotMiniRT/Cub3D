#include "common.h"
#include "fuel_bar.h"
#include "image_b.h"
#include "minimap.h"
#include "mlx.h"
#include "structs_b.h"
#include "torch.h"

bool	overlay(t_main_struct *main_struct)
{
	if (!display_hud(main_struct)
		|| !display_minimap(main_struct)
		|| !display_torch(main_struct))
		return (false);
	return (true);
}
