#include <bc_gfx_menu.h>
#include <bc_system.h>

void bc_gfx_menu_init(bc_gfx_menu_t *self, const bc_gfx_menu_item_t *items, size_t length, bc_gfx_t *gfx)
{
    self->_gfx = gfx;
    self->_items = items;
    self->_length = length;
    self->_color_background = 0;
    self->_color = 1;
    self->_font = &bc_font_ubuntu_24;
    self->_selected = 0;
    self->_max_width = 0;

    bc_gfx_set_font(self->_gfx, self->_font);

    int width;

    for (size_t i = 0; i < self->_length; i++)
    {
        width = bc_gfx_calc_string_width(self->_gfx, (char *) self->_items[i].label);

        if (width > self->_max_width)
        {
            self->_max_width = width;
        }
    }
}

void bc_gfx_menu_up(bc_gfx_menu_t *self)
{
    self->_selected = (self->_selected == 0) ? self->_length - 1 : self->_selected - 1;
}

void bc_gfx_menu_down(bc_gfx_menu_t *self)
{
    if(++self->_selected == self->_length)
    {
        self->_selected = 0;
    }
}

void bc_gfx_menu_enter(bc_gfx_menu_t *self)
{
    if (self->_items[self->_selected].on_enter != NULL)
    {
        self->_items[self->_selected].on_enter(self->_items[self->_selected].param);
    }
}

void bc_gfx_menu_draw(bc_gfx_menu_t *self, int left, int top, int width)
{
    bc_system_pll_enable();

//    bc_gfx_caps_t caps = bc_gfx_get_caps(self->_gfx);

    bc_gfx_set_font(self->_gfx, self->_font);

    int font_height = self->_font->chars[0].image->heigth;

    for (size_t i = 0; i < self->_length; i++)
    {
        if (self->_selected == i)
        {
            bc_gfx_draw_fill_rectangle(self->_gfx, left, top, width, top + font_height, self->_color);

            bc_gfx_draw_string(self->_gfx, left, top, (char *) self->_items[i].label, self->_color_background);
        }
        else
        {
            bc_gfx_draw_string(self->_gfx, left, top, (char *) self->_items[i].label, self->_color);
        }

        top += font_height;
    }

    bc_system_pll_disable();
}
