#include "xpm.h"

xpm_t* 
xpm_new(xpm_map_t xpm, uint16_t x, uint16_t y) 
{
    xpm_t* new_xpm = (xpm_t*)malloc(sizeof(xpm_t));
    if (new_xpm == NULL) return NULL;

    enum xpm_image_type image_type = XPM_INDEXED;
    xpm_image_t img;
    new_xpm->map = xpm_load(xpm, image_type, &img);

    new_xpm->x = x;
    new_xpm->y = y;
    new_xpm->width = img.width;
    new_xpm->height = img.height;

    return new_xpm;
}

void 
xpm_delete(xpm_t* xpm)
{
    free(xpm->map);
    free(xpm);
}

void 
xpm_set_position(xpm_t* xpm, uint16_t x, uint16_t y)
{
    xpm->x = x;
    xpm->y = y;
}

uint16_t 
xpm_get_width(xpm_t* xpm)
{
    return xpm->width;
}

uint16_t 
xpm_get_height(xpm_t* xpm) 
{
    return xpm->height;
}

int
xpm_draw(xpm_t* xpm)
{
    for (uint16_t i = 0; i < xpm->width; i++) {
        for (uint16_t j = 0; j < xpm->height; j++) {
            if (vg_draw_pixel(xpm->x + i, xpm->y + j, xpm->map[i + j * xpm->width])) return 1;
        }
    }
    return 0;

}