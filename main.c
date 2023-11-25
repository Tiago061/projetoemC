#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct{
    char nomeDeUsuario[50];
    char senhaDoUsuario[50];
    char cpfDoUsuario[50];
    char emailDoUsuario[50];
    char dataDeNascimento[15];

} Cliente;


void criptografarSenha(char *senha){
    while(*senha) {
        (*senha)++;
        senha++;
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


void cadastrarUsuario(Cliente **clientes, int *numClientes){
    Cliente novoCliente;

    printf("Nome de usuário: ");
    scanf("%s", novoCliente.nomeDeUsuario);

    printf("Senha: ");
    scanf("%s", novoCliente.senhaDoUsuario);
    criptografarSenha(novoCliente.senhaDoUsuario);

    printf("E-mail: ");
    scanf("%s", novoCliente.emailDoUsuario);

    printf("CPF: ");
    scanf("%s", novoCliente.cpfDoUsuario);

    printf("Data de Nascimento: ");
    scanf("%s", novoCliente.dataDeNascimento);

    (*numClientes)++;
    *clientes = (Cliente *)realloc(*clientes, (*numClientes) * sizeof(Cliente));
    if (*clientes == NULL){
        fprintf(stderr, "Erro ao alocar memória. \n");
        exit(EXIT_FAILURE);
    }
    (*clientes)[*numClientes - 1] = novoCliente;

    printf("Usuário cadastrado com sucesso!\n");

}

int fazerLogin(Cliente *clientes, int numClientes){
    char nomeDeUsuario[50];
    char senha[50];

    printf("Usuário: ");
    scanf("%s", nomeDeUsuario);

    printf("Senha: ");
    scanf("%s", senha);
    criptografarSenha(senha);

    for(int i = 0; i < numClientes; i++) {
        if(strcmp(clientes[i].nomeDeUsuario, nomeDeUsuario) == 0 &&
        strcmp(clientes[i].senhaDoUsuario, senha) == 0){
            printf("Login bem-sucedido!\n");
            return 1;
}
    }
    printf("Nome de usuário ou senha incorretos.\n");
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
    Cliente *clientes = NULL;
    int numClientes = 0;
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
                fazerLogin(clientes, numClientes);
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

    free(clientes);

    return 0;
}
