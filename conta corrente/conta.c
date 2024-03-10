#include "conta.h"
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

// Imprime Conta
void imprimeConta(Conta *func) {
    printf("**********************************************");
    printf("\nCodigo Conta Corrente: ");
    printf("%d", func->codContaCorrente);
    printf("\nCodigo Agencia: ");
    printf("%d", func->codAgencia);
    printf("\nSalario: ");
    printf("%4.2f", func->salario);
    printf("\n**********************************************");
}

// Cria Conta. Lembrar de usar free(func)
Conta *conta(int codContaCorrente, int codAgencia, double salario) {
    Conta *func = (Conta *) malloc(sizeof(Conta));
    //inicializa espaço de memória com ZEROS
    if (func) memset(func, 0, sizeof(Conta));
    //copia valores para os campos de func
    func->codContaCorrente = codContaCorrente;
    func->codAgencia = codAgencia;
    func->salario = salario;
    return func;
}

// Salva conta no arquivo out, na posicao atual do cursor
void salvaConta(Conta *func, FILE *out) {
    fwrite(&func->codContaCorrente, sizeof(int), 1, out);
    fwrite(&func->codAgencia, sizeof(int), 1, out);
    fwrite(&func->salario, sizeof(double), 1, out);
}

// Le uma conta do arquivo in na posicao atual do cursor
// Retorna um ponteiro para conta lido do arquivo
Conta *leConta(FILE *in) {
    Conta *func = (Conta *) malloc(sizeof(Conta));
    if (0 >= fread(&func->codContaCorrente, sizeof(int), 1, in)
        ||
        0 >= fread(&func->codAgencia, sizeof(int), 1, in)
    ) {
	free(func);
	return NULL;
    }
    fread(&func->salario, sizeof(double), 1, in);
    return func;
}

// Retorna tamanho do funcionario em bytes
int tamanhoConta() {
    return sizeof(int)  //codContaCorrente
            + sizeof(int) //CodAgencia
            + sizeof(double); //salario
}

