#include <lcom/lcf.h>
#include <lcom/lab2.h>

#include <stdbool.h>
#include <stdint.h>
#include <lcom/lcf.h>

extern int counter; 


int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  //lcf_trace_calls("/home/lcom/labs/lab2/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  //lcf_log_output("/home/lcom/labs/lab2/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

/*
Ler a configuração de um timer
Como?
Chamar timer_get_conf() seguido do timer_display_conf().

*/
int(timer_test_read_config)(uint8_t timer, enum timer_status_field field) {

  uint8_t st;
  if (timer_get_conf(timer, &st)) return 1;
  if (timer_display_conf(timer, st, field)) return 1;
  return 0;
}

/*
Programa a frequência da geração de interrupts do Timer 0 e testa essa frequência;

Como?

Invocando apenas o timer_set_frequency();

*/
int(timer_test_time_base)(uint8_t timer, uint32_t freq) {

  if(timer_set_frequency(timer, freq)) return 1;
  
  return 0;
}

/*
Testa o interrupt handler do Timer 0;
Subscreve os interrupts do Timer 0 e imprime uma mensagem a cada segundo durante o intervalo de tempo definido em time;

Como?

Criar uma variável que receba o IRQ do timer (irq_set) IRQ's tem 8 bits, neste caso;

Subscrever os interrupts do timer 0 (linha 83);

While loop do Lab:

Mudar a condição (contador de interrupts tem que ser inferior ao intervalo de tempo)-> linha 89

Definir o r para int;

Case:

-> No if:

Invocar o interrupt handler (timer_int_handler);

A cada segundo, imprimir a mensagem (linhas 110 e 111);


Após o While, anular a subscrição dos interrupts (linha 121);
*/

int(timer_test_int)(uint8_t time) {
 
  int ipc_status, r;

  uint8_t irq_set; 

  message msg;

  if (timer_subscribe_int(&irq_set)) return 1;

  while ( counter < time * (int)sys_hz()) {
    if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:			
          if (msg.m_notify.interrupts & BIT(irq_set)) { /* BIT() ATIVA A BITMASK CORRESPONDENTE AO irq_set */ 
            timer_int_handler();

            if(counter % (int) sys_hz() == 0)
              timer_print_elapsed_time();
          }
          break;
      }
    }
  }

  if(timer_unsubscribe_int()) return 1;

  return 0;
}
