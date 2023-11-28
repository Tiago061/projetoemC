#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CLIENTES 100
#define KEY_SHIFT 3

struct Industria {
    char responsavel[100];
    char nomeEmpresa[100];
    char cnpj[15];
    char razaoSocial[100];
    char telefone[15];
    char endereco[200];
    char email[100];
    char dataAbertura[11];
    float insumosTratadosSemestral;
    float gastosMensais;
};

struct CryptoData {
    char encryptedData[sizeof(struct Industria)];
};

void criptografar(struct Industria *dados, int shift) {
    int i;

    for (i = 0; i < sizeof(struct Industria); i++) {
        if (dados->responsavel[i] != '\0') {
            dados->responsavel[i] += shift;
        }

        if (dados->nomeEmpresa[i] != '\0') {
            dados->nomeEmpresa[i] += shift;
        }

        if (dados->cnpj[i] != '\0') {
            dados->cnpj[i] += shift;
        }
    }
}

void descriptografar(struct Industria *dados, int shift) {
    int i;

    for (i = 0; i < sizeof(struct Industria); i++) {
        if (dados->responsavel[i] != '\0') {
            dados->responsavel[i] -= shift;
        }

        if (dados->nomeEmpresa[i] != '\0') {
            dados->nomeEmpresa[i] -= shift;
        }

        if (dados->cnpj[i] != '\0') {
            dados->cnpj[i] -= shift;
        }
    }
}

void salvarDados(struct CryptoData *cryptoData) {
    FILE *arquivo;
    arquivo = fopen("dados.dat", "wb");
    fwrite(cryptoData, sizeof(struct CryptoData), 1, arquivo);
    fclose(arquivo);
}

void lerDados(struct CryptoData *cryptoData) {
    FILE *arquivo;
    arquivo = fopen("dados.dat", "rb");
    fread(cryptoData, sizeof(struct CryptoData), 1, arquivo);
    fclose(arquivo);
}

int realizarLogin() {
    char usuario[20];
    char senha[20];

    printf("===== Tela de Login =====\n");
    printf("Informe o usuário: ");
    scanf("%s", usuario);

    printf("Informe a senha: ");
    scanf("%s", senha);

    if (strcmp(usuario, "unip") == 0 && strcmp(senha, "1234") == 0) {
        printf("Login bem-sucedido!\n");
        return 1;
    } else {
        printf("Usuário ou senha incorretos. Tente novamente.\n");
        return 0;
    }
}

void gerarRelatorio(struct Industria *industria);
void exibirMenu(struct Industria *industria);
void exibirMenuInicial();
void processarEscolhaMenu(struct Industria *industria, int escolha);
void exibirRelatorios(struct Industria *industria);
void salvarRelatorioEmArquivo(int escolhaRelatorio, struct Industria *industria);
void cadastrarIndustria(struct Industria *industria);
void atualizarDadosMensais(struct Industria *industria);
float calcularTotalInsumosTratados(struct Industria *industria);
float calcularTotalGastosMensais(struct Industria *industria);

void cadastrarIndustria(struct Industria *industria) {
    printf("\nCadastro da Indústria\n");

    printf("Responsável: ");
    scanf("%s", industria->responsavel);

    printf("Nome da Empresa: ");
    scanf("%s", industria->nomeEmpresa);

    printf("CNPJ: ");
    scanf("%s", industria->cnpj);

    printf("Razão Social: ");
    scanf("%s", industria->razaoSocial);

    printf("Telefone: ");
    scanf("%s", industria->telefone);

    printf("Endereço:\n");
    printf("Endereço(Completo):");
    scanf(" %99[^\n]", industria->endereco);

    printf("Email: ");
    scanf("%s", industria->email);

    printf("Data de Abertura: ");
    scanf("%s", industria->dataAbertura);

    criptografar(industria, KEY_SHIFT);

    struct CryptoData cryptoData;
    memcpy(cryptoData.encryptedData, industria, sizeof(struct Industria));

    salvarDados(&cryptoData);

    printf("\nCadastro concluído com sucesso!\n");
}


void atualizarDadosMensais(struct Industria *industria) {
    printf("\nAtualização Mensal\n");

    printf("Quantidade de Resíduos Ambientais Tratados: ");
    scanf("%f", &industria->insumosTratadosSemestral);

    printf("Valor Estimado de Custo: ");
    scanf("%f", &industria->gastosMensais);

    printf("\nAtualização concluída com sucesso!\n");

    gerarRelatorio(industria);
}

float calcularTotalInsumosTratados(struct Industria *industria) {
    return industria->insumosTratadosSemestral;
}

float calcularTotalGastosMensais(struct Industria *industria) {
    return industria->gastosMensais;
}
void exibirMenuInicial() {
    printf("\n===== Menu Inicial =====\n");
    printf("1. Cadastro de Indústria\n");
    printf("2. Atualização Mensal\n");
    printf("3. Relatórios\n");
    printf("4. Sair\n");
}

void gerarRelatorio(struct Industria *industria) {
    printf("\nGerando Relatórios Individuais\n");

    float totalInsumosTratados = calcularTotalInsumosTratados(industria);
    float totalGastosMensais = calcularTotalGastosMensais(industria);

    printf("Total de Insumos Tratados Semestralmente: %.2f\n", totalInsumosTratados);
    printf("Total de Gastos Mensais: %.2f\n", totalGastosMensais);
}

void exibirRelatorios(struct Industria *industria) {
    printf("\n===== Relatórios =====\n");

    int escolhaRelatorio;
    printf("Escolha o tipo de relatório:\n");
    printf("1. Relatório Individual\n");
    printf("2. Voltar ao Menu Inicial\n");
    printf("Opção: ");
    scanf("%d", &escolhaRelatorio);

    switch (escolhaRelatorio) {
        case 1:
            gerarRelatorio(industria);
            break;
        default:
            printf("Opção inválida. Tente novamente.\n");
            return;
    }

    char salvarRelatorio;
    printf("Deseja salvar o relatório em um arquivo TXT? (S/N): ");
    scanf(" %c", &salvarRelatorio);

    if (salvarRelatorio == 'S' || salvarRelatorio == 's') {
        salvarRelatorioEmArquivo(escolhaRelatorio, industria);
    }
}

void salvarRelatorioEmArquivo(int escolhaRelatorio, struct Industria *industria) {
    FILE *arquivo;
    char nomeArquivo[50];

    printf("Digite o nome do arquivo (inclua a extensão .txt): ");
    scanf("%s", nomeArquivo);

    arquivo = fopen(nomeArquivo, "w");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    fprintf(arquivo, "Relatório:\n");
    fprintf(arquivo, "========================================\n");

    // Escrever o relatório no arquivo
    if (escolhaRelatorio == 1) {
        fprintf(arquivo, "Relatório Individual:\n");
        fprintf(arquivo, "Total de Insumos Tratados Semestralmente: %.2f\n", calcularTotalInsumosTratados(industria));
        fprintf(arquivo, "Total de Gastos Mensais: %.2f\n", calcularTotalGastosMensais(industria));
    } else if (escolhaRelatorio == 2) {
        fprintf(arquivo, "Relatório Global:\n");
    }

    fprintf(arquivo, "========================================\n");
    fclose(arquivo);

    printf("Relatório salvo em %s\n", nomeArquivo);
}



void exibirMenu(struct Industria *industria) {
    int escolha;

    do {
        exibirMenuInicial();
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);

        processarEscolhaMenu(industria, escolha);

    } while (escolha != 4);
}

void processarEscolhaMenu(struct Industria *industria, int escolha) {
    switch (escolha) {
        case 1:
            cadastrarIndustria(industria);
            break;
        case 2:
            atualizarDadosMensais(industria);
            break;
        case 3:
            exibirRelatorios(industria);
            break;
        case 4:
            printf("Saindo do sistema...\n");
            break;
        default:
            printf("Opção inválida. Tente novamente.\n");
    }
}

int main() {
    struct Industria industria;
    struct CryptoData cryptoData;

    int loginSucesso = realizarLogin();

    if (loginSucesso) {
        lerDados(&cryptoData);
        memcpy(&industria, cryptoData.encryptedData, sizeof(struct Industria));
        descriptografar(&industria, KEY_SHIFT);
        exibirMenu(&industria);
    }

    return 0;
}
