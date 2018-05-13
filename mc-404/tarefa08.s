@@ Tarefa 08
@@ William Gonçalves da Cruz, 188671

  .global _start

  .set IRQ, 0x6
  .set FIQ, 0x7
  .set STACK, 0x8000000             @ Posição inicial da pilha

  .org IRQ*4
  b button_press
  b timer_tick                      @ Configura as interupções

  .align 2
read_keyboard:
  ldr r1, =KEYBOARD_STATE
  ldr r1, [r1]
  cmp r1, #0
  beq read_keyboard                 @ Espera um clique do teclado acontecer

  ldr r1, =KEYBOARD_DATA            @ Devolve em r1 o valor digitado
  ldr r1, [r1]
  bx lr                             @ Retorna do procedimento

write_next_digit:
  ldr r2, =digits
  ldrb r2, [r2, r1]                 @ Salva em r2 o dígito representativo do número teclado

  ldr r0, actual_digit              @ Descobre a casa decimal na qual se deve escrever
  str r2, [r0]                      @ Escreve no mostrador da casa decimal o dígito

  sub r0, #1                        @ Diminue o valor para o mostrador da próxima casa

  ldr r2, =UNIT_DIGIT
  cmp r0, r2                        @ Compara a casa decimal atual com as das unidadesCa
  ldrcc r0, =THOUSAND_DIGIT         @ Caso seja menor, volta para milhares

  ldr r2, =actual_digit
  str r0, [r2]                      @ Salva a próxima casa decimal
  bx lr

button_press:
  ldr r8, =safe_state
  ldr r9, =SAFE_CLOSED_WAITING
  strb r9, [r8]                     @ Fecha o cofre no clique do botao

  ldr r8, =LEDS
  ldr r9, =GREEN
  str r9, [r8]                      @ Muda o led para verde, mostrar que espera uma senha

  movs pc, lr

timer_tick:
  movs pc, lr

_start:
  mov sp, #STACK                    @ Inicializa a pilha

  ldr r0, =THOUSAND_DIGIT
  ldr r1, =actual_digit
  str r0, [r1]                      @ Iniciliza a posição de dígito atual do mostrador

  ldr r0, =safe_state
  ldr r1, =SAFE_OPEN
  strb r1, [r0]                     @ Inicializa estado do cofre

  mov r0, #0x10
  bic r0, r0, #(IRQ+FIQ)            @ Habilita interrupções
  msr cpsr,r0                       @ Move processador para modo usuário

waiting_close_safe_loop:
  ldr r1, =SAFE_OPEN
  ldr r0, safe_state
  cmp r0, r1
  beq waiting_close_safe_loop       @ Continua em loop enquanto o estado do cofre é aberto

loop:
  bl read_keyboard
  bl write_next_digit
  b loop                            @ Espera a senha ser digitada

  mov r0, #0                        @ status -> 0
  mov r7, #1                        @ exit is syscall #1
  swi #0x55                         @ invoke syscall

safe_state: .skip 1
actual_digit: .skip 4

digits:
  .byte 0x7E,0x30,0x6D,0x79,0x33,0x5B,0x5F,0x70,0x7F,0x7B

.equ RED, 0x02
.equ GREEN, 0x01                    @ Cores para os leds

.equ LEDS, 0x090000                 @ Endereço para os LEDS

.equ UNIT_DIGIT, 0xa0000            @ Endereço do dígito das unidades
.equ THOUSAND_DIGIT, 0xa0003        @ Endereço do dígito dos milhares

.equ KEYBOARD_DATA, 0xb0001
.equ KEYBOARD_STATE, 0xb0000        @ Dados teclado

.equ TIMER, 0xc0000                 @ Endereço timer
.equ BUTTON, 0xd0000                @ Endereço botão

.equ SAFE_OPEN, 0x00
.equ SAFE_CLOSED_LOCKED, 0x01
.equ SAFE_CLOSED_WAITING, 0x02
