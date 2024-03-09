#include <stdio.h>
#include <stdlib.h>
#include "agencia.h"
//para rodar
//gcc -o main funcionario.c main.c 
//.\main.exe

/*
->Modifique a implementação para lidar com registros de 
conta-corrente

-> Dois arquivos:
    - Agência (Cod, Nome, Gerente)
    - Conta-Corrente (Cod, CodAgencia, Saldo)

-> Usuário deve poder escolher o que quer cadastrar
-> Dados devem ser lidos do teclado
-> Aplicação deve ter opção de Cadastrar, Ler ou Sair

*/

//SEEK_SET: indica o início do arquivo
//SEEK_CUR: indica q o deslocamento sera feito a partir da posição atual do cursor
//SEEK_END: indica q o deslocamento sera feito a partir do final do arquivo
    //podemos usar o seek_end combinado com a função ftell, que retorna a posição atual do cursor em bytes
/*
EXEMPLO: para descobrir o numero de registros q tem no arquivo
--preciso dese para implementar a busca binária
int tamanho_arquivo(FILE *arq){
    fseek(arq, 0, SEEK_END);
    int tam = trunc(ftell(arq) / tamanho());
    return tam;
}
*/

void insere_5_agencias(FILE *out) {
    printf("Inserindo 5 Agencias no arquivo...");

    Agencia *f1 = agencia(1, "Itau", "Heber");
    salvaAg(f1, out);
    free(f1);
    Agencia *f2 = agencia(2, "Santander", "Marcos");
    salvaAg(f2, out);
    free(f2);
    Agencia *f3 = agencia(3, "Itau", "Kevyn");
    salvaAg(f3, out);
    free(f3);
    Agencia *f4 = agencia(4, "Itau", "Sully");
    salvaAg(f4, out);
    free(f4);
    Agencia *f5 = agencia(5, "Santander", "Heber");
    salvaAg(f5, out);
    free(f5);       
}

void le_agencias(FILE *in) {
    printf("\n\nLendo agencias do arquivo...\n\n");
    rewind(in);
    Agencia *f;
    while ((f = le(in)) != NULL) {
        imprimeAg(f);
        free(f);
    }
}

void le_segunda_agencia(FILE *in) {
    printf("\n\nLendo segunda agencia do arquivo...\n\n");
    //tamanho() indica quantos bytes vamos pular, o que aqui é igual ao tamanho de um registro 
    //(vamos pular o primeiro e nos posicionar no início do segundo)
    //** ATENÇÃO: não usar sizeof(Funcionario), pois ele pode retornar valor maior que o tamanho ocupado em disco, 
    //            devido a alinhamento automático (ver https://en.wikipedia.org/wiki/Data_structure_alignment))

    //utilizando aqui o seek_set
    //ao final, o cursor estará posicionado em 0 + tamanho() +1
    fseek(in, tamanhoAg(), SEEK_SET);
    Agencia *f = le(in);
    if (f != NULL) {
        imprimeAg(f);
        free(f);
    }
}

void adiciona_agencia(FILE *in) {
    printf("\n\nAdicionando agencia no final do arquivo...\n\n");
    //pula 5 registros para posicionar no início do final do arquivo
    fseek(in, tamanhoAg() * 5, SEEK_SET);
    Agencia *f = agencia(6, "Itau", "teste");
    salvaAg(f, in);
    free(f);
    
    //lê funcionário que acabou de ser gravado
    //posiciona novamente o cursor no início desse registro
    fseek(in, tamanhoAg() * 5, SEEK_SET);
    Agencia *f6 = le(in);
    if (f6 != NULL) {
        imprimeAg(f6);
        free(f6);
    }    
}

void sobrescreve_quarta_agencia(FILE *in) {
    printf("\n\nSobrescrevendo quarta agencia do arquivo...\n\n");
    //pula primeiros 3 registros para posicionar no início do quarto registro
    fseek(in, tamanhoAg() * 3, SEEK_SET);
    Agencia *f4 = agencia(7, "Bradesco", "Catarina");
    salvaAg(f4, in);
    free(f4);
    
    //lê funcionário que acabou de ser gravado
    //posiciona novamente o cursor no início desse registro
    fseek(in, tamanhoAg() * 3, SEEK_SET);
    Agencia *f = le(in);
    if (f != NULL) {
        imprimeAg(f);
        free(f);
    }
}

void main(int argc, char** argv) {
    //declara ponteiro para arquivo
    FILE *out;
    //abre arquivo
    if ((out = fopen("agencia.dat", "w+b")) == NULL) {
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }
    else {
        //insere funcionários
        insere_5_agencias(out);

        //volta ao início do arquivo e lê os funcionários inseridos
        le_agencias(out);

        //volta ao início do arquivo e lê o segundo funcionário
        le_segunda_agencia(out);

        //grava mais um funcionário no final do arquivo
        adiciona_agencia(out);

        //sobrescreve quarto funcionário
        sobrescreve_quarta_agencia(out);
        
        //lendo o arquivo todo novamente
        le_agencias(out);
        tamanhoAg(out);
        //fecha arquivo
        fclose(out);    
    }
}

