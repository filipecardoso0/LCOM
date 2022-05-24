#include "graphics_card.h"

static void *video_mem;
static unsigned h_res;
static unsigned v_res;
static unsigned bits_per_pixel;
static unsigned bytes_per_pixel;

static uint8_t red_mask;
static uint8_t green_mask;
static uint8_t blue_mask;

void *(vg_init)(uint16_t mode) {

    struct minix_mem_range mr;
    int r;

    if (OK != (r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr)))
        panic("sys_privctl (ADD_MEM) failed: %d\n", r);
    vbe_mode_info_t mode_info;
    vbe_get_mode_info(mode, &mode_info);
    h_res = mode_info.XResolution;
    v_res = mode_info.YResolution;
    bits_per_pixel = mode_info.BitsPerPixel;
    bytes_per_pixel = (mode_info.BitsPerPixel + mode_info.BitsPerPixel % 8) / 8;
    unsigned vram_base = (phys_bytes)mode_info.PhysBasePtr;
    unsigned vram_size = h_res * v_res * bytes_per_pixel;

    red_mask = mode_info.RedMaskSize;
    green_mask = mode_info.GreenMaskSize;
    blue_mask = mode_info.BlueMaskSize;

    mr.mr_base = vram_base;
    mr.mr_limit = vram_base + vram_size;
    
    if (OK != (r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr)))
        panic("sys_privctl (ADD_MEM) failed: %d\n", r);
    
    video_mem = vm_map_phys(SELF, (void*)mr.mr_base, (h_res * v_res * bytes_per_pixel));
    if (video_mem == MAP_FAILED)
        panic("couldn’t map video memory");

    reg86_t reg86;
    memset(&reg86, 0, sizeof(reg86));
    reg86.ax = SET_VBE_MODE;
    reg86.bx = BIT(14) | mode;
    reg86.intno = BIOS_VIDEO_SERVICES;
    if (sys_int86(&reg86) != OK) {
        printf("set_vbe_mode: sys_int86() failed \n");
        return NULL;
    }
    return video_mem;
}

int(vg_draw_pixel)(uint16_t x, uint16_t y, uint32_t color) {
    if (x < h_res && y < v_res) {
      char* init_address = (char*)video_mem + (y * h_res + x) * bytes_per_pixel;

      memcpy(init_address, &color, bytes_per_pixel);
      
      return 0;
    }
    return 1;
}

int(vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color) {
    for (unsigned int i = x; i < (x + len); i++)
        if (vg_draw_pixel(i, y, color)) return 1;
    return 0;
}

int(vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color) {
    for (unsigned int i = y; i < y + height; i++)
        if (vg_draw_hline(x, i, width, color)) return 1;
    return 0;
}

int draw_pattern(uint16_t mode, uint8_t no_rectangles, uint32_t first, uint8_t step) {
    uint16_t rec_width = h_res / no_rectangles;
    uint16_t rec_height = v_res / no_rectangles;

    uint32_t color, red, green, blue;

    for (uint8_t col = 0; col < no_rectangles; col++) {
        for (uint8_t row = 0; row < no_rectangles; row++) {
            if (mode == MODE_INDEXED){
                color = (first + (row * no_rectangles + col) * step) % (1 << bits_per_pixel);
            } else {
                red = (GET_RED(first) + col*step) % (1 << red_mask);
                green = (GET_GREEN(first) + row*step) % (1 << green_mask);
                blue = (GET_BLUE(first) + (col+row)*step) % (1 << blue_mask);
                color = SET_COLOR(red, green, blue);
            }
            if (vg_draw_rectangle(col * rec_width, row * rec_height, rec_width, rec_height, color)) return 1;
        }
    }

    return 0;

}

int xpm_draw(uint8_t* map, uint16_t x, uint16_t y, uint16_t width, uint16_t height) {
    for (uint16_t i = 0; i < width; i++) {
        for (uint16_t j = 0; j < height; j++) {
            if (vg_draw_pixel(x, y, map[i + j * width])) return 1;
        }
    }
    return 0;
}
