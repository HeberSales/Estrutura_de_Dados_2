#ifndef AGENCIA_H
#define AGENCIA_H

#include <stdlib.h>
#include <stdio.h>

typedef struct Agencia {
    int cod;
    char nomeAg[50];
    char gerente[50];
} Agencia;

// Imprime funcionario
void imprimeAg(Agencia *func);

// Cria Agencia. Lembrar de usar free(agencia)
Agencia *agencia(int cod, char *nomeAg, char *gerente);

// Salva funcionario no arquivo out, na posicao atual do cursor
void salvaAg(Agencia *func, FILE *out);

// Le um funcionario do arquivo in na posicao atual do cursor
// Retorna um ponteiro para funcionario lido do arquivo
Agencia *le(FILE *in);

// Retorna tamanho do funcionario em bytes
int tamanhoAg();

#endif