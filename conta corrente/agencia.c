#include "agencia.h"
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

// Imprime Agencia
void imprimeAg(Agencia *func) {
    printf("**********************************************");
    printf("\nCodigo Agencia:");
    printf("%d", func->cod);
    printf("\nNome: ");
    printf("%s", func->nomeAg);
    printf("\nGerente: ");
    printf("%s", func->gerente);
    printf("\n**********************************************");
}

// Cria Agencia. Lembrar de usar free(func)
Agencia *agencia(int cod, char *nomeAg, char *gerente) {
    Agencia *func = (Agencia *) malloc(sizeof(agencia));
    //inicializa espaço de memória com ZEROS
    if (func) memset(func, 0, sizeof(Agencia));
    //copia valores para os campos de func
    func->cod = cod;
    strcpy(func->nomeAg, nomeAg);
    strcpy(func->gerente, gerente);
    return func;
}

// Salva Agencia no arquivo out, na posicao atual do cursor
void salvaAg(Agencia *func, FILE *out) {
    fwrite(&func->cod, sizeof(int), 1, out);
    //func->nome ao invés de &func->nome, pois string já é ponteiro
    fwrite(func->nomeAg, sizeof(char), sizeof(func->nomeAg), out);
    fwrite(func->gerente, sizeof(char), sizeof(func->gerente), out);
}

// Le um Agencia do arquivo in na posicao atual do cursor
// Retorna um ponteiro para Agencia lido do arquivo
Agencia *le(FILE *in) {
    Agencia *func = (Agencia *) malloc(sizeof(Agencia));
    if (0 >= fread(&func->cod, sizeof(int), 1, in)) {
	free(func);
	return NULL;
    }
    fread(func->nomeAg, sizeof(char), sizeof(func->nomeAg), in);
    fread(func->gerente, sizeof(char), sizeof(func->gerente), in);
    return func;
}

// Retorna tamanho do Agencia em bytes
int tamanhoAg() {
    return sizeof(int)  //cod
            + sizeof(char) * 50 //nome
            + sizeof(char) * 50 ;//gerente
}