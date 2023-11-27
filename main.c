#include <stdio.h>
#include <string.h>
#include <openssl/aes.h>
#include <openssl/rand.h>

#define KEY_SIZE 256
#define BLOCK_SIZE 16

// Definindo a estrutura para armazenar os dados da indústria
struct Industria {
    char responsavel[100];
    char nomeEmpresa[100];
    char cnpj[15];
    char razaoSocial[100];
    char nomeFantasia[100];
    char telefone[15];
    char endereco[200];
    char email[100];
    char dataAbertura[11];
    // Outros dados relevantes para cadastro podem ser adicionados aqui
};

// Estrutura para armazenar dados criptografados
struct CryptoData {
    unsigned char encryptedData[256]; // Tamanho arbitrário, ajuste conforme necessário
};

// Função para gerar uma chave aleatória
void generateKey(unsigned char *key) {
    RAND_bytes(key, KEY_SIZE / 8);
}

// Função para criptografar os dados usando AES
void encrypt(const unsigned char *plaintext, int plaintext_len, const unsigned char *key, unsigned char *ciphertext) {
    AES_KEY aesKey;
    AES_set_encrypt_key(key, KEY_SIZE, &aesKey);
    AES_encrypt(plaintext, ciphertext, &aesKey);
}

// Função para descriptografar os dados usando AES
void decrypt(const unsigned char *ciphertext, int ciphertext_len, const unsigned char *key, unsigned char *plaintext) {
    AES_KEY aesKey;
    AES_set_decrypt_key(key, KEY_SIZE, &aesKey);
    AES_decrypt(ciphertext, plaintext, &aesKey);
}

// Função para salvar dados criptografados em um arquivo
void salvarDados(struct CryptoData *cryptoData) {
    FILE *arquivo;
    arquivo = fopen("dados.dat", "wb");
    fwrite(cryptoData, sizeof(struct CryptoData), 1, arquivo);
    fclose(arquivo);
}

// Função para ler dados criptografados de um arquivo
void lerDados(struct CryptoData *cryptoData) {
    FILE *arquivo;
    arquivo = fopen("dados.dat", "rb");
    fread(cryptoData, sizeof(struct CryptoData), 1, arquivo);
    fclose(arquivo);
}

// Função para realizar o login
int realizarLogin() {
    char usuario[20];
    char senha[20];

    printf("===== Tela de Login =====\n");
    printf("Informe o usuário: ");
    scanf("%s", usuario);

    printf("Informe a senha: ");
    scanf("%s", senha);

    // Lógica simples de autenticação (usuário e senha hardcoded)
    if (strcmp(usuario, "admin") == 0 && strcmp(senha, "senha123") == 0) {
        printf("Login bem-sucedido!\n");
        return 1; // Retorna 1 para indicar que o login foi bem-sucedido
    } else {
        printf("Usuário ou senha incorretos. Tente novamente.\n");
        return 0; // Retorna 0 para indicar que o login falhou
    }
}

// Função para exibir o menu principal
void exibirMenu(struct Industria *industria, unsigned char *encryptionKey);

// Função para exibir o menu inicial
void exibirMenuInicial() {
    printf("\n===== Menu Inicial =====\n");
    printf("1. Cadastro de Indústria\n");
    printf("2. Relatórios\n");
    printf("3. Sair\n");
}

// Função para processar a escolha do menu
void processarEscolhaMenu(struct Industria *industria, unsigned char *encryptionKey, int escolha);

// Função para exibir relatórios
void exibirRelatorios(struct Industria *industria, unsigned char *encryptionKey);

// Função para salvar relatórios em arquivo TXT
void salvarRelatorioEmArquivo(int escolhaRelatorio, struct Industria *industria, unsigned char *encryptionKey);

// Função para cadastrar os dados da indústria
void cadastrarIndustria(struct Industria *industria, unsigned char *encryptionKey) {
    printf("\nCadastro da Indústria\n");

    printf("Responsável: ");
    scanf("%s", industria->responsavel);

    printf("Nome da Empresa: ");
    scanf("%s", industria->nomeEmpresa);

    printf("CNPJ: ");
    scanf("%s", industria->cnpj);

    printf("Razão Social: ");
    scanf("%s", industria->razaoSocial);

    printf("Nome Fantasia: ");
    scanf("%s", industria->nomeFantasia);

    printf("Telefone: ");
    scanf("%s", industria->telefone);

    printf("Endereço: ");
    scanf("%s", industria->endereco);

    printf("Email: ");
    scanf("%s", industria->email);

    printf("Data de Abertura: ");
    scanf("%s", industria->dataAbertura);

    // Adicione aqui as instruções para os demais campos do cadastro

    // Criptografar os dados sensíveis antes de salvar
    struct CryptoData cryptoData;
    encrypt((const unsigned char *)industria, sizeof(struct Industria), encryptionKey, cryptoData.encryptedData);

    salvarDados(&cryptoData);

    printf("\nCadastro concluído com sucesso!\n");

    // Gera relatórios
    gerarRelatorio(industria, encryptionKey);
}

// Função para calcular o total de insumos tratados semestralmente
float calcularTotalInsumosTratados(struct Industria *industria) {
    // Lógica para calcular o total de insumos tratados
    // Implemente conforme necessário
    return 1000.0; // Exemplo, substitua pela lógica real
}

// Função para calcular o total de gastos mensais
float calcularTotalGastosMensais(struct Industria *industria) {
    // Lógica para calcular o total de gastos mensais
    // Implemente conforme necessário
    return 5000.0; // Exemplo, substitua pela lógica real
}

// Função para gerar relatórios individuais
void gerarRelatorio(struct Industria *industria, unsigned char *encryptionKey) {
    printf("\nGerando Relatórios Individuais\n");

    // Calcular e exibir relatórios individuais
    float totalInsumosTratados = calcularTotalInsumosTratados(industria);
    float totalGastosMensais = calcularTotalGastosMensais(industria);

    printf("Total de Insumos Tratados Semestralmente: %.2f\n", totalInsumosTratados);
    printf("Total de Gastos Mensais: %.2f\n", totalGastosMensais);
}

// Função para gerar relatórios globais
void gerarRelatorioGlobal(struct Industria *industria, unsigned char *encryptionKey) {
    printf("\nGerando Relatórios Globais\n");

    // Adicione aqui a lógica para gerar relatórios globais
    // Pode incluir informações consolidadas de várias indústrias
    // por exemplo, médias, totais, etc.
}

// Função para exibir relatórios
void exibirRelatorios(struct Industria *industria, unsigned char *encryptionKey) {
    printf("\n===== Relatórios =====\n");

    int escolhaRelatorio;
    printf("Escolha o tipo de relatório:\n");
    printf("1. Relatório Individual\n");
    printf("2. Relatório Global\n");
    printf("3. Voltar ao Menu Inicial\n");
    printf("Opção: ");
    scanf("%d", &escolhaRelatorio);

    switch (escolhaRelatorio) {
        case 1:
            gerarRelatorio(industria, encryptionKey);
            break;
        case 2:
            gerarRelatorioGlobal(industria, encryptionKey);
            break;
        case 3:
            return; // Retorna ao menu inicial
        default:
            printf("Opção inválida. Tente novamente.\n");
            return;
    }

    // Opção de salvar o relatório em arquivo TXT
    char salvarRelatorio;
    printf("Deseja salvar o relatório em um arquivo TXT? (S/N): ");
    scanf(" %c", &salvarRelatorio);

    if (salvarRelatorio == 'S' || salvarRelatorio == 's') {
        salvarRelatorioEmArquivo(escolhaRelatorio, industria, encryptionKey);
    }
}

// Função para salvar relatórios em arquivo TXT
void salvarRelatorioEmArquivo(int escolhaRelatorio, struct Industria *industria, unsigned char *encryptionKey) {
    FILE *arquivo;
    char nomeArquivo[50];

    // Escolher o nome do arquivo
    printf("Digite o nome do arquivo (inclua a extensão .txt): ");
    scanf("%s", nomeArquivo);

    arquivo = fopen(nomeArquivo, "w");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    // Redirecionar a saída para o arquivo
    fclose(stdout);
    fopen(nomeArquivo, "w");

    // Escrever o relatório no arquivo
    if (escolhaRelatorio == 1) {
        gerarRelatorio(industria, encryptionKey);
    } else if (escolhaRelatorio == 2) {
        gerarRelatorioGlobal(industria, encryptionKey);
    }

    // Restaurar a saída padrão
    fclose(stdout);
    fopen("/dev/tty", "w");

    printf("Relatório salvo em %s\n", nomeArquivo);
}

// Função para exibir o menu principal
void exibirMenu(struct Industria *industria, unsigned char *encryptionKey) {
    int escolha;

    do {
        exibirMenuInicial();
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);

        processarEscolhaMenu(industria, encryptionKey, escolha);

    } while (escolha != 3);
}

// Função para processar a escolha do menu
void processarEscolhaMenu(struct Industria *industria, unsigned char *encryptionKey, int escolha) {
    switch (escolha) {
        case 1:
            cadastrarIndustria(industria, encryptionKey);
            break;
        case 2:
            exibirRelatorios(industria, encryptionKey);
            break;
        case 3:
            printf("Saindo do sistema...\n");
            break;
        default:
            printf("Opção inválida. Tente novamente.\n");
    }
}

// Função principal
int main() {
    struct Industria industria;
    struct CryptoData cryptoData;
    unsigned char encryptionKey[KEY_SIZE / 8];

    // Realiza o login
    int loginSucesso = realizarLogin();

    // Se o login for bem-sucedido, permite acessar o sistema
    if (loginSucesso) {
        // Gera uma chave aleatória para criptografia
        generateKey(encryptionKey);

        // Lê dados previamente cadastrados, se existirem
        lerDados(&cryptoData);

        // Descriptografa os dados para exibição ou atualização
        decrypt(cryptoData.encryptedData, sizeof(struct Industria), encryptionKey, (unsigned char *)&industria);

        // Exibe o menu inicial
        exibirMenu(&industria, encryptionKey);
    }

    return 0;
}