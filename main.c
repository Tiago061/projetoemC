#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void criptografarSenha(char *senha){
    for (int i = 0; senha[i] != '\0'; i++){
        senha[i] += 3;
    }
}


struct Industria{
    char usuario[50];
    char senha[50];
    char nomeResponsavel[50];
    char nomeEmpresa[50];
    char cnpj[15];
    char razaoSocial[50];
    char telefone[15];
    char rua[50];
    char numero[3];
    char bairro[50];
    char cidade[50];
    char estado[3];
    char cep[10];
    char email[50];
    char dataDeAbertura[11];
};


int Login (struct Industria *industria){
    char insiraUsuario[50];
    char insiraSenha[50];

    system("cls");
    printf("Usuário: ");
    scanf("%s", insiraUsuario);

    printf("Senha: ");
    scanf("%s", insiraSenha);

    if(strcmp(insiraUsuario, industria->usuario) == 0 && strcmp(insiraSenha, industria->senha) == 0){
        return 1;
    } else{
        return 0;
    }
}

int industriaExiste( struct Industria *industria, int contIndustria, char *usuario) {
    for (int i = 0; i < contIndustria; i++) {
        if (strcmp(usuario, industria[i].usuario) == 0) {
            return 1;
        }
    }
    return 0;
}



void registrarDados(struct Industria *industria){

    printf("\nSEJA BEM VINDO A SOLUÇÔES AMBIENTAIS");
    printf("\n***************************************");
    printf("\nInforme os dados da Indústria:\n");

    printf(" Nome do Responsável: ");
    scanf("%s", industria->nomeResponsavel);

    printf("Nome da Empresa: ");
    scanf("%s", industria->nomeEmpresa);

    printf("CNPJ: ");
    scanf("%s", industria->cnpj);

    printf("Email: ");
    scanf("%s", industria->email);

    printf("Razão Social: ");
    scanf("%s", industria->razaoSocial);

    printf("Telefone: ");
    scanf("%s", industria->telefone);

    printf("Endereço(Rua): ");
    scanf("%s", industria->rua);

    printf("Número: ");
    scanf("%s", industria->numero);

    printf("Bairro: ");
    scanf("%s", industria->bairro);

    printf("Cidade: ");
    scanf("%s", industria->cidade);

    printf("Sigla do Estado: ");
    scanf("%s", industria->estado);

    printf("CEP: ");
    scanf("%s", industria->cep);

    printf("Data de Abertura: ");
    scanf("%s", industria->dataDeAbertura);
}

int main() {
    struct Industria industria;
    int escolha;

    strcpy(industria.usuario, "usuario");
    strcpy(industria.senha, "senha");
    criptografarSenha(industria.senha);


    do {
        printf("\nEscolha a Opção:\n");
        printf("1 - Login\n");
        printf("2 - Cadastrar dados da Indústria\n");
        printf("3 - Cadastrar novo usuário\n");
        printf("4 - Cadastrar Funcionário\n");
        printf("5 - Verificar e Salvar relatórios\n");
        printf("0 - Sair\n");
        printf("Opção: ");
        scanf("%d", &escolha);


        switch (escolha) {
            case 1:
                if (Login(&industria)) {
                    printf("\nLogin Bem-sucedido!\n");
                } else {
                    printf("\nLogin falhou. Verifique usuário e senha ou cadastra-se\n");
                }
                break;
            case 2:
                registrarDados(&industria);
                break;
            case 3:
                //cadastrar novo usuario
                break;
            case 4:
                //cadastrar funcionário
                break;
            case 5:
                //Verificar e salvar relatórios
                break;
            case 0:
                printf("Saindo do sistema.\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }

    } while(escolha != 0);

    return 0;
}
