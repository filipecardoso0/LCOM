#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"

int counter = 0; 
int hook_id = 0; 

/*
Altera a frequência do timer.
Deve ler o RBC de modo a que não altere os 4 LSB's da control word que correspondem aos de mode e para definir o BCD/Binary (modo de contagem).

Como?

Verificar se a frequência de input não excede a default (TIMER_FREQ);

Verificar se TIMER_FREQ/freq gera overflow, pois pode exceder os 16 bits;

Obter o LSB e o MSB da frequência de input com o util_get_LSB e util_get_MSB, respetivamente;

Obter a control word:

Criar um status register (st) vazio;

Obter a configuração do timer com timer_get_conf(timer, st);

& lógico do st com o 0x0F para preservar o LSB; (linha 53)

| lógico para inicializar o LSB seguido do MSB da control word; (linha 54)

---

Switch case para obter a control word do timer (TIMER_SEL1 -> Timer 1, TIMER_SEL2 -> Timer 2);

Escrever a control word para a porta da control word, com o sys_outb (linha 71);

Escrever para uma variável o LSB da frequência e depois o MSB com o sys_outb (linhas 73 e 74);

Libertar o espaço alocado para o st;
*/
int (timer_set_frequency)(uint8_t timer, uint32_t freq) {

  uint8_t*  st = (uint8_t*) malloc(sizeof(uint8_t));
  uint8_t target, ctrl_wrd, freq_lsb, freq_msb;
  uint16_t new_freq;
  uint32_t check_freq; 

  if (freq > TIMER_FREQ) return 1;
  
  check_freq = TIMER_FREQ / freq;
    
  if(check_freq > UINT16_MAX) return 1;
  else new_freq = check_freq;

  if (util_get_LSB(new_freq, &freq_lsb)) return 1;
  if (util_get_MSB(new_freq, &freq_msb)) return 1;
  
  if (timer_get_conf(timer, st)) return 1;

  ctrl_wrd = *st & 0x0F;
  ctrl_wrd |= TIMER_LSB_MSB;

  switch(timer){
    case 0: target = TIMER_0; break;
    case 1: target = TIMER_1; 
            ctrl_wrd |= TIMER_SEL1; break;
    case 2: target = TIMER_2; 
            ctrl_wrd |= TIMER_SEL2; break; 
    default: return 1;
  }

  if (sys_outb(TIMER_CTRL, ctrl_wrd)) return 1;

  if (sys_outb(target, (uint32_t) freq_lsb)) return 1;
  if (sys_outb(target, (uint32_t) freq_msb)) return 1;

  free(st);

  return 0;
}

int (timer_subscribe_int)(uint8_t *bit_no) {
  *bit_no = hook_id; 

  if (sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &hook_id) != OK) return 1;

  return 0;
}

int (timer_unsubscribe_int)() {

  if (sys_irqrmpolicy(&hook_id) != OK) return 1;

  return 0;
}

void (timer_int_handler)() {
  counter++;
}


/*
Lê a configuração do timer, ou seja, o status register, através do read-back command;

Como? Escrever a control word na variável control_word;

Mandar para o TIMER_CTRL a control_word (linha 90);

Ler o status register do timer:
Switch case com as macros dos 3 timers,

Chamar o util_sys_inb para ler a porta do timer e mandar o status register para a st que tem 8 bits (sys_inb só lê para 32 bits);

*/

int (timer_get_conf)(uint8_t timer, uint8_t *st) {
  uint8_t control_word, timer_aux;

  // Escrever a control word na variável control_word;  
  
  control_word = TIMER_RB_CMD | TIMER_RB_SEL(timer) | TIMER_RB_COUNT_; 


  if(sys_outb(TIMER_CTRL, control_word)) return 1; 


//Ler o status register do timer;
  switch (timer) {
    
    case 0: timer_aux = TIMER_0; break;
    case 1: timer_aux = TIMER_1; break;
    case 2: timer_aux = TIMER_2; break;
    default: return 1;

  }
  if (util_sys_inb(timer_aux, st)) return 1;

  return 0;
  
}

/*
Mostra a configuração do timer, ou seja, mostra de forma legível o campo a visualizar, lido através do RBC.

Como?

Criar uma instância union timer_status_field_val para obter a configuração do timer;

Switch case com o field dado e recolher as informações, através das operações bitwise com o status register;

Fazer timer_print_config(timer, field, timer_conf);
*/

int (timer_display_conf)(uint8_t timer, uint8_t st,
                        enum timer_status_field field) {

  union timer_status_field_val timer_conf; 
  
  //Mostrar o campo a printar;
  switch (field) {
    case tsf_all: timer_conf.byte = st; break;
    case tsf_initial: timer_conf.in_mode = ((BIT(5) & st) | (BIT(4) & st)) >> 4; break;
    case tsf_mode: timer_conf.count_mode = ((BIT(3) & st) | (BIT(2) & st) | (BIT(1) & st)) >> 1;break;
    case tsf_base: timer_conf.bcd = BIT(0) & st; break;
  }

  if (timer_print_config(timer, field, timer_conf)) return 1; 

  return 0;
}
