/**
 * #################################
 * # Esqueleto do processador em C #
 * #################################
 */

#include <stdint.h>
#include <stdio.h>

uint8_t mem[256] = {0};
uint8_t reg[4] = {0};
uint8_t pc = 0, zf = 0, running = 1;
int ciclo = 0;

void fetch(uint8_t *op, uint8_t *a, uint8_t *b) {
  *op = mem[pc];
  *a = mem[pc + 1];
  *b = mem[pc + 2];
  pc += 3;
}

void decode_execute(uint8_t op, uint8_t a, uint8_t b) {
  switch (op) {
  case 0x01:
    reg[a] = mem[b];
    break;

  case 0x02:
    mem[b] = reg[a];
    break;

  case 0x03:
    reg[a] = reg[a] + reg[b];
    break;

  case 0x04:
    reg[a] = reg[a] - reg[b];
    break;

  case 0x05:
    reg[a] = b;
    break;

  case 0x06:
    zf = (reg[a] == reg[b]) ? 1 : 0;
    break;

  case 0x07:
    pc = a;
    break;

  case 0x08:
    if (zf)
      pc = a;
    break;

  case 0x09:
    if (!zf)
      pc = a;
    break;

  case 0x0A:
    running = 0;
    break;
  }
}

void trace(uint8_t op, uint8_t a, uint8_t b) {
  const char *nomes[] = {"",    "LOAD", "STORE", "ADD", "SUB", "MOV",
                         "CMP", "JMP",  "JZ",    "JNZ", "HALT"};

  printf("Ciclo %d: %-5s %d,%d | R0=%3d R1=%3d"
         " R2=%3d R3=%3d | PC=%3d ZF=%d\n",
         ciclo, nomes[op], a, b, reg[0], reg[1], reg[2], reg[3], pc, zf);
}

int main() {

  /*
   * ==========================================
   * CARREGAMENTO DOS DADOS
   * ==========================================
   *
   * Array:
   * 3, 7, 2, 5, 1, 8, 4, 6
   *
   * Os dados devem ficar em 0x10 até 0x17.
   */

  mem[0x10] = 3;
  mem[0x11] = 7;
  mem[0x12] = 2;
  mem[0x13] = 5;
  mem[0x14] = 1;
  mem[0x15] = 8;
  mem[0x16] = 4;
  mem[0x17] = 6;


  /*
   * ==========================================
   * DESVIO PARA O PROGRAMA
   * ==========================================
   *
   * O programa começa em 0x30 para não
   * sobrescrever os dados armazenados em
   * 0x10 até 0x17.
   *
   * 0x07 = JMP
   * 0x30 = endereço de destino
   * 0x00 = segundo operando não utilizado
   */

  mem[0x00] = 0x07;
  mem[0x01] = 0x30;
  mem[0x02] = 0x00;


  /*
   * ==========================================
   * PROGRAMA DO SOMATÓRIO
   * ==========================================
   *
   * R0 = acumulador da soma
   * R1 = valor atual do array
   *
   * Resultado final:
   * R0 = 36
   *
   * Cada instrução ocupa 3 posições de memória.
   */


  /* 0x30: MOV R0, 0
   * R0 = 0
   */
  mem[0x30] = 0x05;
  mem[0x31] = 0x00;
  mem[0x32] = 0x00;


  /* 0x33: LOAD R1, 0x10
   * R1 = MEM[0x10] = 3
   */
  mem[0x33] = 0x01;
  mem[0x34] = 0x01;
  mem[0x35] = 0x10;


  /* 0x36: ADD R0, R1
   * R0 = R0 + R1
   */
  mem[0x36] = 0x03;
  mem[0x37] = 0x00;
  mem[0x38] = 0x01;


  /* 0x39: LOAD R1, 0x11
   * R1 = MEM[0x11] = 7
   */
  mem[0x39] = 0x01;
  mem[0x3A] = 0x01;
  mem[0x3B] = 0x11;


  /* 0x3C: ADD R0, R1
   * R0 = R0 + R1
   */
  mem[0x3C] = 0x03;
  mem[0x3D] = 0x00;
  mem[0x3E] = 0x01;


  /* 0x3F: LOAD R1, 0x12
   * R1 = MEM[0x12] = 2
   */
  mem[0x3F] = 0x01;
  mem[0x40] = 0x01;
  mem[0x41] = 0x12;


  /* 0x42: ADD R0, R1 */
  mem[0x42] = 0x03;
  mem[0x43] = 0x00;
  mem[0x44] = 0x01;


  /* 0x45: LOAD R1, 0x13
   * R1 = MEM[0x13] = 5
   */
  mem[0x45] = 0x01;
  mem[0x46] = 0x01;
  mem[0x47] = 0x13;


  /* 0x48: ADD R0, R1 */
  mem[0x48] = 0x03;
  mem[0x49] = 0x00;
  mem[0x4A] = 0x01;


  /* 0x4B: LOAD R1, 0x14
   * R1 = MEM[0x14] = 1
   */
  mem[0x4B] = 0x01;
  mem[0x4C] = 0x01;
  mem[0x4D] = 0x14;


  /* 0x4E: ADD R0, R1 */
  mem[0x4E] = 0x03;
  mem[0x4F] = 0x00;
  mem[0x50] = 0x01;


  /* 0x51: LOAD R1, 0x15
   * R1 = MEM[0x15] = 8
   */
  mem[0x51] = 0x01;
  mem[0x52] = 0x01;
  mem[0x53] = 0x15;


  /* 0x54: ADD R0, R1 */
  mem[0x54] = 0x03;
  mem[0x55] = 0x00;
  mem[0x56] = 0x01;


  /* 0x57: LOAD R1, 0x16
   * R1 = MEM[0x16] = 4
   */
  mem[0x57] = 0x01;
  mem[0x58] = 0x01;
  mem[0x59] = 0x16;


  /* 0x5A: ADD R0, R1 */
  mem[0x5A] = 0x03;
  mem[0x5B] = 0x00;
  mem[0x5C] = 0x01;


  /* 0x5D: LOAD R1, 0x17
   * R1 = MEM[0x17] = 6
   */
  mem[0x5D] = 0x01;
  mem[0x5E] = 0x01;
  mem[0x5F] = 0x17;


  /* 0x60: ADD R0, R1 */
  mem[0x60] = 0x03;
  mem[0x61] = 0x00;
  mem[0x62] = 0x01;


  /*
   * ==========================================
   * ARMAZENAMENTO DO RESULTADO
   * ==========================================
   *
   * 0x02 = STORE
   * R0 -> MEM[0x20]
   *
   * Resultado esperado: 36
   */

  /* 0x63: STORE R0, 0x20 */
  mem[0x63] = 0x02;
  mem[0x64] = 0x00;
  mem[0x65] = 0x20;


  /* 0x66: HALT */
  mem[0x66] = 0x0A;
  mem[0x67] = 0x00;
  mem[0x68] = 0x00;


  /*
   * ==========================================
   * EXECUÇÃO DA MINICPU
   * ==========================================
   */

  while (running && pc < 256) {
    uint8_t op, a, b;

    ciclo++;

    fetch(&op, &a, &b);
    decode_execute(op, a, b);
    trace(op, a, b);
  }


  /*
   * ==========================================
   * VALIDAÇÃO DO RESULTADO
   * ==========================================
   */

  printf("\n====================================\n");
  printf("Resultado final: MEM[0x20] = %d\n", mem[0x20]);
  printf("Resultado esperado: 36\n");

  if (mem[0x20] == 36) {
    printf("VALIDACAO: OK - soma correta!\n");
  } else {
    printf("VALIDACAO: ERRO - soma incorreta!\n");
  }

  printf("====================================\n");

  return 0;
}
