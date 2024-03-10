#include <stdio.h>
#include <stdlib.h>
#include "agencia.h"
#include "conta.h"
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

// void le_segunda_agencia(FILE *in) {
//     printf("\n\nLendo segunda agencia do arquivo...\n\n");
//     //tamanho() indica quantos bytes vamos pular, o que aqui é igual ao tamanho de um registro 
//     //(vamos pular o primeiro e nos posicionar no início do segundo)
//     //** ATENÇÃO: não usar sizeof(Funcionario), pois ele pode retornar valor maior que o tamanho ocupado em disco, 
//     //            devido a alinhamento automático (ver https://en.wikipedia.org/wiki/Data_structure_alignment))

//     //utilizando aqui o seek_set
//     //ao final, o cursor estará posicionado em 0 + tamanho() +1
//     fseek(in, tamanhoAg(), SEEK_SET);
//     Agencia *f = le(in);
//     if (f != NULL) {
//         imprimeAg(f);
//         free(f);
//     }
// }

// void adiciona_agencia(FILE *in) {
//     printf("\n\nAdicionando agencia no final do arquivo...\n\n");
//     //pula 5 registros para posicionar no início do final do arquivo
//     fseek(in, tamanhoAg() * 5, SEEK_SET);
//     Agencia *f = agencia(6, "Itau", "teste");
//     salvaAg(f, in);
//     free(f);
    
//     //lê funcionário que acabou de ser gravado
//     //posiciona novamente o cursor no início desse registro
//     fseek(in, tamanhoAg() * 5, SEEK_SET);
//     Agencia *f6 = le(in);
//     if (f6 != NULL) {
//         imprimeAg(f6);
//         free(f6);
//     }    
// }

// void sobrescreve_quarta_agencia(FILE *in) {
//     printf("\n\nSobrescrevendo quarta agencia do arquivo...\n\n");
//     //pula primeiros 3 registros para posicionar no início do quarto registro
//     fseek(in, tamanhoAg() * 3, SEEK_SET);
//     Agencia *f4 = agencia(7, "Bradesco", "Catarina");
//     salvaAg(f4, in);
//     free(f4);
    
//     //lê funcionário que acabou de ser gravado
//     //posiciona novamente o cursor no início desse registro
//     fseek(in, tamanhoAg() * 3, SEEK_SET);
//     Agencia *f = le(in);
//     if (f != NULL) {
//         imprimeAg(f);
//         free(f);
//     }
// }

void CadastrarConta(FILE *out) {
    int codContaCorrente, codAgencia;
    double salario;

    printf("Digite o codigo da conta corrente: ");
    scanf("%d", &codContaCorrente);

    printf("Digite o codigo da agencia: ");
    scanf("%d", &codAgencia);

    printf("Digite o salario: ");
    scanf("%lf", &salario);

    //criando uma conta com os dados do usuario.
    Conta *nova_conta = conta(codContaCorrente, codAgencia, salario);

    // Salva a nova conta no arquivo
    salvaConta(nova_conta, out);
    free(nova_conta);

    printf("Conta cadastrada com sucesso!\n");
}

void CadastrarAgencia(FILE *out) {
    int cod;
    char nomeAg[50];
    char gerente[50];

    printf("Digite o codigo da Agencia: ");
    scanf("%d", &cod);

    printf("Digite o nome da Agencia: ");
    scanf("%s", nomeAg);

    printf("Digite o gerente: ");
    scanf("%s", gerente);

    //criando uma conta com os dados do usuario.
    Agencia *nova_agencia = agencia(cod, nomeAg, gerente);

    // Salva a nova conta no arquivo
    salvaAg(nova_agencia, out);
    free(nova_agencia);

    printf("Agencia cadastrada com sucesso!\n");
}

void LerContas(FILE *in) {
    printf("\n\nLendo Contas do arquivo...\n\n");
    rewind(in);
    Conta *c;
    while ((c = leConta(in)) != NULL) {
        imprimeConta(c);
        free(c);
    }
}

void LerAgencias(FILE *in) {
    printf("\n\nLendo agencias do arquivo...\n\n");
    rewind(in);
    Agencia *f;
    while ((f = le(in)) != NULL) {
        imprimeAg(f);
        free(f);
    }
}

void Sair() {
    printf("Saindo...\n");
    exit(0);
}


void main(int argc, char** argv) {
    //declara ponteiro para arquivo
    FILE *out;
    //abre arquivo

    if (((out = fopen("agencia.dat", "w+b")) == NULL) || ((out = fopen("conta.dat", "w+b")) == NULL)) {
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }
    else {
        int continuar=1;

        do
        {
            printf("\n\tMenu\n\n");
            printf("1. Cadastrar - Conta\n");
            printf("2. Cadastrar - Agencia\n");
            printf("3. Ler - Contas\n");
            printf("4. Ler - Agencias\n");
            printf("5. Sair\n");
            printf("\n");

            scanf("%d", &continuar);
            system("cls || clear");

            switch(continuar)
            {
                case 1:
                    CadastrarConta(out);
                    break;

                case 2:
                    CadastrarAgencia(out);
                    break;

                case 3:
                    LerContas(out);
                    break;

                case 4:
                    LerAgencias(out);
                    break;

                case 5:
                    Sair();
                    break;

                default:
                    printf("Digite uma opcao valida\n");
            }
    } while(continuar);
        fclose(out);    
    }
}

