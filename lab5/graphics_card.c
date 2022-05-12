#include "graphics_card.h"

static char *video_mem;
static unsigned h_res;
static unsigned v_res;
static unsigned bits_per_pixel;

int map_mem(uint16_t mode) {

  vbe_mode_info_t mode_info;
  memset(&mode_info, 0, sizeof(mode_info));
  if (vbe_get_mode_info(mode, &mode_info)) return 1;

  h_res = mode_info.XResolution;
  v_res = mode_info.YResolution;
  bits_per_pixel = mode_info.BitsPerPixel;

  struct minix_mem_range mr;
  unsigned int vram_base = mode_info.PhysBasePtr;
  unsigned int vram_size = h_res * v_res * bits_per_pixel;
  int r;

  mr.mr_base = (phys_bytes) vram_base;	
  mr.mr_limit = mr.mr_base + vram_size;  

  if ( OK != (r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr)))
    panic("sys_privctl (ADD_MEM) failed: %d\n", r);

  video_mem = vm_map_phys(SELF, (void *)mr.mr_base, vram_size);

  return 0;
}

int set_graphics_mode(uint16_t mode) {
  
  reg86_t reg86;

  memset(&reg86, 0, sizeof(reg86)); //Inicializar a struct a 0

  reg86.ax = SET_VBE_MODE;
  reg86.bx = BIT(14) | mode;
  reg86.intno = BIOS_VIDEO_SERVICES;
  if ( sys_int86(&reg86) != OK ) {
    printf("set_vbe_mode: sys_int86() failed \n");
    return 1;
  }
  if (reg86.al != VALID_FUNC) return 1;
  if (reg86.ah != SUCCESS_FUNC) return 1;  

  return 0;
}

int draw_rectangle(uint16_t mode, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color) {

  if (map_mem(mode)) return 1;
  if (set_graphics_mode(mode)) return 1;
  if (vg_draw_rectangle(x, y, width, height, color)) return 1;
  if (vg_exit()) return 1;
  return 0;
}

int (vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color) {
  for (int i = x; i < x + len; i++) {
    video_mem[i] = color;
  }
  return 0;
}

int (vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color) {

  for (int i = 0; i < height; i++) {
    if (i == 0 || i == height - 1) {
      if(vg_draw_hline(x, i, width, color)) return 1;
    }
    else {
      if (vg_draw_hline(x, i, 1, color)) return 1;
      if (vg_draw_hline(width - 1, i, 1, color)) return 1;
    }
  }
  return 0;
}
