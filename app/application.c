#include <application.h>
#include <bc_gfx_menu.h>

bc_led_t led;
bc_led_t led_lcd_red;
bc_led_t led_lcd_blue;
bc_led_t led_lcd_green;
bc_gfx_t *gfx;
bc_button_t button;
bc_button_t button_lcd_left;
bc_button_t button_lcd_right;

bc_gfx_menu_t menu;


void lcd_button_left_event_handler(bc_button_t *self, bc_button_event_t event, void *event_param)
{
    if (event == BC_BUTTON_EVENT_CLICK)
    {
        bc_gfx_menu_down(&menu);

        bc_scheduler_plan_now(0);
    }
}

void lcd_button_right_event_handler(bc_button_t *self, bc_button_event_t event, void *event_param)
{
    if (event == BC_BUTTON_EVENT_CLICK)
    {
        bc_scheduler_plan_absolute(0, BC_TICK_INFINITY);

        bc_gfx_menu_enter(&menu);
    }
}

void item_red_led(void *param)
{
    bc_led_pulse(&led_lcd_red, 200);
}

void item_blue_led(void *param)
{
    bc_led_pulse(&led_lcd_blue, 200);
}

void item_green_led(void *param)
{
    bc_led_pulse(&led_lcd_green, 200);
}

void application_init(void)
{
    // Initialize logging
    bc_log_init(BC_LOG_LEVEL_DUMP, BC_LOG_TIMESTAMP_ABS);

    // Initialize button
    bc_button_init(&button, BC_GPIO_BUTTON, BC_GPIO_PULL_DOWN, false);

    // Initialize LED
    bc_led_init(&led, BC_GPIO_LED, false, false);

    // Initialize LCD module
    bc_module_lcd_init();

    // Initialize LCD button left
    bc_button_init_virtual(&button_lcd_left, BC_MODULE_LCD_BUTTON_LEFT, bc_module_lcd_get_button_driver(), false);
    bc_button_set_event_handler(&button_lcd_left, lcd_button_left_event_handler, NULL);

    // Initialize LCD button right
    bc_button_init_virtual(&button_lcd_right, BC_MODULE_LCD_BUTTON_RIGHT, bc_module_lcd_get_button_driver(), false);
    bc_button_set_event_handler(&button_lcd_right, lcd_button_right_event_handler, NULL);

    // Initialize LED on LCD module
    bc_led_init_virtual(&led_lcd_red, BC_MODULE_LCD_LED_RED, bc_module_lcd_get_led_driver(), true);
    bc_led_init_virtual(&led_lcd_blue, BC_MODULE_LCD_LED_BLUE, bc_module_lcd_get_led_driver(), true);
    bc_led_init_virtual(&led_lcd_green, BC_MODULE_LCD_LED_GREEN, bc_module_lcd_get_led_driver(), true);

    gfx = bc_module_lcd_get_gfx();
    // bc_gfx_set_rotation(gfx, BC_GFX_ROTATION_90);

    static const bc_gfx_menu_item_t items[] = {
        {"Red LED", item_red_led, NULL},
        {"Blue LED", item_blue_led, NULL},
        {"Green LED", item_green_led, NULL}
    };

    bc_gfx_menu_init(&menu, items, sizeof(items)/sizeof(items[0]), gfx);

    bc_led_pulse(&led, 2000);
}

void application_task(void)
{

    if (!bc_gfx_display_is_ready(gfx))
    {
        bc_scheduler_plan_current_now();
    }

    bc_system_pll_enable();

    bc_gfx_clear(gfx);

    bc_gfx_menu_draw(&menu, 5, 5, 118);

    bc_gfx_update(gfx);

    bc_system_pll_disable();
}
