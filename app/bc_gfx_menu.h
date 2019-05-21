#ifndef _BC_GFX_MENU_H
#define _BC_GFX_MENU_H

#include <bc_gfx.h>

//! @addtogroup bc_gfx_menut bc_gfx_menut
//! @brief Graphics Menu Component
//! @{

typedef struct
{
    const char *label;
    void (*on_enter)(void *param);
    void *param;

} bc_gfx_menu_item_t;

//! @brief Instance

typedef struct
{
    bc_gfx_t *_gfx;
    const bc_gfx_menu_item_t *_items;
    size_t _length;
    uint32_t _color_background;
    uint32_t _color;
    const bc_font_t *_font;
    size_t _selected;
    int _max_width;

} bc_gfx_menu_t;

void bc_gfx_menu_init(bc_gfx_menu_t *self, const bc_gfx_menu_item_t *items, size_t length, bc_gfx_t *gfx);

void bc_gfx_menu_up(bc_gfx_menu_t *self);

void bc_gfx_menu_down(bc_gfx_menu_t *self);

void bc_gfx_menu_enter(bc_gfx_menu_t *self);

void bc_gfx_menu_draw(bc_gfx_menu_t *self, int left, int top, int width);

//! @}

#endif //_BC_GFX_MENU_H
