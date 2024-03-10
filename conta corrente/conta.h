#ifndef CONTA_H
#define CONTA_H

#include <stdlib.h>
#include <stdio.h>

typedef struct Conta {
    int codContaCorrente;
    int codAgencia;
    double salario;
} Conta;

// Imprime Conta
void imprimeConta(Conta *func);

// Cria Agencia. Lembrar de usar free(agencia)
Conta *conta(int codContaCorrente, int codAgencia, double salario);

// Salva Conta no arquivo out, na posicao atual do cursor
void salvaConta(Conta *func, FILE *out);

// Le um Conta do arquivo in na posicao atual do cursor
// Retorna um ponteiro para Conta lido do arquivo
Conta *leConta(FILE *in);

// Retorna tamanho do Conta em bytes
int tamanhoConta();

#endif