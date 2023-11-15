#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <ctype.h>
#include <unistd.h>

#define ARQUIVO_CSV "pokedex.csv"

//===============================================================================================//

// Estrutura para representar as escolhas do usuário
typedef struct {
    int numero[3];
    char nome[3][30];
    char tipo1[3][15];
    char tipo2[3][15];
    int statusTotal[3];
    int hp[3];
    int ataque[3];
    int defesa[3];
    int atqSpec[3];
    int defSpec[3];
    int velocidade[3];
    int geracao[3];
    int lendario[3];
    char cor[3][15];
    float altura[3];
    float peso[3];
    int taxadeCap[3];
    int xp[3];
} Escolha;

//===============================================================================================//

// Estrutura para representar os dados de uma linha do CSV
typedef struct {
    int numero;
    char nome[30];
    char tipo1[15];
    char tipo2[15];
    int statusTotal;
    int hp;
    int ataque;
    int defesa;
    int atqSpec;
    int defSpec;
    int velocidade;
    int geracao;
    int lendario;
    char cor[15];
    float altura;
    float peso;
    int taxadeCap;
    int xp;
    int evolucao;
    int preEvolucao;
} RegistroCSV;

//===============================================================================================//

// Estrutura para representar a mochila do usuário
typedef struct {
    int posicaoMochila[6];
    int numero[6];
    char nome[6][30];
    char tipoUm[6][15];
    char tipoDois[6][15];
    int statusTotal[6];
    int ataque[6];
    int defesa[6];
    int atqSpec[6];
    int defSpec[6];
    int velocidade[6];
    int geracao[6];
    int lendario[6];
    char cor[6][15];
    float altura[6];
    float peso[6];
    int taxadeCap[6];
    int evolucao[6];
    int preEvolucao[6];
    int xp[6];
    int pokeball;
    int greatball;
    int ultraball;
    int masterball;
} Mochila;

//===============================================================================================//

// Estrutura para representar a coleção completa de Pokémon do usuário
typedef struct {
    int posicaoColecao[100];
    int numero[100];
    char nome[100][30];
    char tipoUm[100][15];
    char tipoDois[100][15];
    int statusTotal[100];
    int ataque[100];
    int defesa[100];
    int atqSpec[100];
    int defSpec[100];
    int velocidade[100];
    int geracao[100];
    int lendario[100];
    char cor[100][15];
    float altura[100];
    float peso[100];
    int taxadeCap[100];
    int evolucao[100];
    int preEvolucao[100];
    int xp[100];
} Colecao;

//===============================================================================================//

// Função para inicializar os dados da mochila do usuário
void inicializarMochila(Mochila *mochila) {
    // Loop para inicializar cada slot da mochila
    for (int i = 0; i < 6; ++i) {
        // Inicializa os campos individuais de cada Pokémon na mochila
        mochila->posicaoMochila[i] = 0;
        mochila->numero[i] = 0;
        strcpy(mochila->nome[i], "");
        strcpy(mochila->tipoUm[i], "");
        strcpy(mochila->tipoDois[i], "");
        mochila->statusTotal[i] = 0;
        mochila->ataque[i] = 0;
        mochila->defesa[i] = 0;
        mochila->atqSpec[i] = 0;
        mochila->defSpec[i] = 0;
        mochila->velocidade[i] = 0;
        mochila->geracao[i] = 0;
        mochila->lendario[i] = 0;
        strcpy(mochila->cor[i], "");
        mochila->altura[i] = 0.0;
        mochila->peso[i] = 0.0;
        mochila->taxadeCap[i] = 0;
        mochila->evolucao[i] = 0.0;
        mochila->preEvolucao[i] = 0.0;
        mochila->xp[i] = 0;
    }

    // Inicializa o número de cada tipo de Pokébola na mochila
    mochila->pokeball = 10;
    mochila->greatball = 10;
    mochila->ultraball = 10;
    mochila->masterball = 10;
}

//===============================================================================================//

// Função para inicializar os dados da coleção de Pokémon do usuário
void inicializarColecao(Colecao *colecao) {
    // Loop para inicializar cada slot da coleção
    for (int i = 0; i < 100; ++i) {
        // Inicializa os campos individuais de cada Pokémon na coleção
        colecao->posicaoColecao[i] = 0;
        colecao->numero[i] = 0;
        strcpy(colecao->nome[i], "");
        strcpy(colecao->tipoUm[i], "");
        strcpy(colecao->tipoDois[i], "");
        colecao->statusTotal[i] = 0;
        colecao->ataque[i] = 0;
        colecao->defesa[i] = 0;
        colecao->atqSpec[i] = 0;
        colecao->defSpec[i] = 0;
        colecao->velocidade[i] = 0;
        colecao->geracao[i] = 0;
        colecao->lendario[i] = 0;
        strcpy(colecao->cor[i], "");
        colecao->altura[i] = 0.0;
        colecao->peso[i] = 0.0;
        colecao->taxadeCap[i] = 0;
        colecao->evolucao[i] = 0;
        colecao->preEvolucao[i] = 0;
        colecao->xp[i] = 0;
    }
}

//===============================================================================================//

// Função para calcular a média da experiência (xp) dos Pokémon na mochila
RegistroCSV calcularMedia(Mochila *mochila, RegistroCSV *registro) {
    RegistroCSV resultado;

    // Inicializa o acumulador de xp e o contador de Pokémon na mochila
    resultado.xp = 0;
    int contador = 0;

    // Loop para percorrer cada slot da mochila
    for (int i = 0; i < 6; i++) {
        // Verifica se o Pokémon na posição i possui xp não nula
        if (mochila->xp[i] != 0) {
            contador++; // Incrementa o contador se xp não for zero
        }

        resultado.xp += mochila->xp[i]; // Acumula o xp do Pokémon na posição i
    }

    // Calcula a média da experiência arredondando para o inteiro mais próximo
    resultado.xp = round(resultado.xp / contador);
    
    // Atualiza o campo xp no registro passado por referência
    registro->xp = resultado.xp;

    return resultado;
}

// Função para contar o número de linhas em um arquivo CSV
int contarLinhas() {
    FILE *arquivo;
    int numLinhas = 0;
    char caractere;

    // Abrir o arquivo em modo de leitura
    arquivo = fopen(ARQUIVO_CSV, "r");

    // Verificar se o arquivo foi aberto com sucesso
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", ARQUIVO_CSV);
        return -1; // Retornar um valor negativo para indicar erro
    }

    // Contar o número de linhas no arquivo
    while ((caractere = fgetc(arquivo)) != EOF) {
        if (caractere == '\n') {
            numLinhas++;
        }
    }

    // Fechar o arquivo
    fclose(arquivo);

    return numLinhas;
}

//===============================================================================================//

// Função para ler uma linha aleatória de um arquivo CSV e exibir os detalhes do Pokémon encontrado
void lerLinhaAleatoria(RegistroCSV *registro, int numLinhas, Mochila *mochila) {
    // Abrir o arquivo CSV em modo de leitura
    FILE *arquivo = fopen("pokedex.csv", "r");
    if (arquivo == NULL) {
        printf("Falha ao abrir o arquivo.\n");
        exit(EXIT_FAILURE);
    }

    // Gerar um índice aleatório para selecionar uma linha no arquivo
    srand((unsigned int)time(NULL));
    int linhaAleatoria = rand() % (numLinhas + 1);
    int linhaAtual = 0;

    // Reposicionar o indicador de posição do arquivo para o início
    rewind(arquivo);

    // Pular linhas até chegar à linha aleatória
    while (linhaAtual < linhaAleatoria) {
        char caractere = fgetc(arquivo);
        if (caractere == '\n') {
            linhaAtual++;
        }
    }

    // Ler os dados da linha aleatória para a estrutura de registro
    if (fscanf(arquivo, "%d ,%s ,%s ,%s ,%d ,%d ,%d ,%d ,%d ,%d ,%d ,%d ,%d ,%s ,%f ,%f ,%d",
               &registro->numero, registro->nome, registro->tipo1, registro->tipo2, &registro->statusTotal, &registro->hp,
               &registro->ataque, &registro->defesa, &registro->atqSpec, &registro->defSpec, &registro->velocidade, &registro->geracao,
               &registro->lendario, registro->cor, &registro->altura, &registro->peso, &registro->taxadeCap)) {

        sleep(1); // Esperar por 1 segundo (opcional)
        calcularMedia(mochila, registro); // Calcular a média da experiência (xp) e atualizar o registro
        printf("================================================================\n");
        printf("\nPokemon encontrado!!!\n");
        sleep(2); // Esperar por 2 segundos (opcional)
        
        // Exibir detalhes do Pokémon encontrado
        printf("\nPokémon para captura:\n");
        printf("Número: %d\n", registro->numero);
        printf("Nome: %s\n", registro->nome);
        printf("Tipo 1: %s\n", registro->tipo1);
        printf("Tipo 2: %s\n", registro->tipo2);
        printf("Status Total: %d\n", registro->statusTotal);
        printf("HP: %d\n", registro->hp);
        printf("Ataque: %d\n", registro->ataque);
        printf("Defesa: %d\n", registro->defesa);
        printf("Ataque Especial: %d\n", registro->atqSpec);
        printf("Defesa Especial: %d\n", registro->defSpec);
        printf("Velocidade: %d\n", registro->velocidade);
        printf("Geração: %d\n", registro->geracao);
        printf("Lendário: %d\n", registro->lendario);
        printf("Cor: %s\n", registro->cor);
        printf("Altura: %.2f\n", registro->altura);
        printf("Peso: %.2f\n", registro->peso);
        printf("Taxa de Captura: %d\n", registro->taxadeCap);
        printf("Level: %d\n", registro->xp);
        printf("================================================================\n");
    }

    // Fechar o arquivo
    fclose(arquivo);
}

//===============================================================================================//

// Função para calcular a probabilidade de captura
double calcularProbabilidadeCaptura(int taxaDeCaptura, double multiplicador) {
    // Se o multiplicador for zero, a probabilidade é sempre 100%
    if (multiplicador == 0.0) {
        return 1.0;
    }

    // Fórmula para calcular a probabilidade usando a fórmula de captura Pokémon
    double alpha = log(0.2) / -255;
    double probabilidade = 1 - exp(-alpha * taxaDeCaptura * multiplicador);
    return probabilidade;
}

//===============================================================================================//

// Função para realizar a captura com 3 chances
void capturarPokemon(RegistroCSV *registro, Mochila *mochila, Colecao *colecao) {
    int tentativas = 3;

    // Loop para realizar até 3 tentativas de captura
    while (tentativas > 0) {
        sleep(1);
        printf("\nVocê tem %d pokeballs, %d greatballs, %d ultraballs, %d masterballs\n", mochila->pokeball, mochila->greatball, mochila->ultraball, mochila->masterball);
        char tipoBola;
        printf("\nVocê tem %d tentativas para capturar o Pokémon!\n", tentativas);
        printf("\nEscolha uma pokebola: pokeball (P), greatball (G), ultraball (U), masterball (M): ");
        scanf(" %c", &tipoBola);

        // Variável para armazenar a quantidade de bolas disponíveis e o multiplicador de captura
        int *quantidadeBola;
        double multiplicador = 1.0;

        // Determina a bola escolhida e seu multiplicador associado
        switch (tipoBola) {
            case 'P':
            case 'p':
                quantidadeBola = &mochila->pokeball;
                break;
            case 'G':
            case 'g':
                quantidadeBola = &mochila->greatball;
                multiplicador = 1.5;
                break;
            case 'U':
            case 'u':
                quantidadeBola = &mochila->ultraball;
                multiplicador = 2.0;
                break;
            case 'M':
            case 'm':
                quantidadeBola = &mochila->masterball;
                multiplicador = 0.0; // Masterball sempre captura com sucesso
                break;
            default:
                printf("Tipo de bola inválido.\n");
                continue; // Reinicia o loop para uma nova tentativa
        }

        // Verifica se há bolas disponíveis do tipo escolhido
        if (*quantidadeBola <= 0) {
            printf("Você não tem mais %s.\n", tipoBola == 'P' || tipoBola == 'p' ? "pokeballs" : (tipoBola == 'G' || tipoBola == 'g' ? "greatballs" : (tipoBola == 'U' || tipoBola == 'u' ? "ultraballs" : "masterballs")));
            tentativas--;
            printf("\nVocê tem %d tentativas para capturar o Pokémon!\n", tentativas);
            continue; // Reinicia o loop para uma nova tentativa
        }

        // Utiliza uma bola da mochila
        (*quantidadeBola)--;

        sleep(1);
        printf("\nCapturando Pokémon (Tentativa %d)...\n", 4 - tentativas);
        double probabilidade = calcularProbabilidadeCaptura(registro->taxadeCap, multiplicador);
        printf("\nA probabilidade de sucesso na captura é: %.2f%%\n", probabilidade * 100);

        // Simulação da captura
        int resultadoCaptura = rand() % 101;

        // Verifica se a captura foi bem-sucedida
        if (resultadoCaptura <= probabilidade * 100) {
            printf("Você capturou %s!\n", registro->nome);

            int i;

            // Adiciona o Pokémon à mochila
            for (i = 1; i < 6; ++i) {
                if (mochila->posicaoMochila[i] == 0) {
                    mochila->posicaoMochila[i] = i + 1;
                    mochila->numero[i] = registro->numero;
                    strcpy(mochila->nome[i], registro->nome);
                    strcpy(mochila->tipoUm[i], registro->tipo1);
                    strcpy(mochila->tipoDois[i], registro->tipo2);
                    mochila->statusTotal[i] = registro->statusTotal;
                    mochila->ataque[i] = registro->ataque;
                    mochila->defesa[i] = registro->defesa;
                    mochila->atqSpec[i] = registro->atqSpec;
                    mochila->defSpec[i] = registro->defSpec;
                    mochila->velocidade[i] = registro->velocidade;
                    mochila->geracao[i] = registro->geracao;
                    mochila->lendario[i] = registro->lendario;
                    strcpy(mochila->cor[i], registro->cor);
                    mochila->altura[i] = registro->altura;
                    mochila->peso[i] = registro->peso;
                    mochila->taxadeCap[i] = registro->taxadeCap;
                    mochila->xp[i] = registro->xp;
                    break;
                }
            }

            // Adiciona o Pokémon à coleção se a mochila estiver cheia
            if (i == 6) {
                for (i = 0; i < 100; ++i) {
                    if (colecao->posicaoColecao[i] == 0) {
                        colecao->posicaoColecao[i] = i + 1;
                        colecao->numero[i] = registro->numero;
                        strcpy(colecao->nome[i], registro->nome);
                        strcpy(colecao->tipoUm[i], registro->tipo1);
                        strcpy(colecao->tipoDois[i], registro->tipo2);
                        colecao->statusTotal[i] = registro->statusTotal;
                        colecao->ataque[i] = registro->ataque;
                        colecao->defesa[i] = registro->defesa;
                        colecao->atqSpec[i] = registro->atqSpec;
                        colecao->defSpec[i] = registro->defSpec;
                        colecao->velocidade[i] = registro->velocidade;
                        colecao->geracao[i] = registro->geracao;
                        colecao->lendario[i] = registro->lendario;
                        strcpy(colecao->cor[i], registro->cor);
                        colecao->altura[i] = registro->altura;
                        colecao->peso[i] = registro->peso;
                        colecao->taxadeCap[i] = registro->taxadeCap;
                        colecao->xp[i] = registro->xp;
                        break;
                    }
                }
            }

            return; // A captura foi bem-sucedida, a função encerra
        } else {
            printf("A captura do Pokémon %s falhou.\n", registro->nome);
            tentativas--;
            sleep(1);
            printf("\nVocê ainda tem %d tentativas para capturar o Pokémon!\n", tentativas);
        }
    }

    printf("Suas tentativas acabaram. O Pokémon %s escapou!\n", registro->nome);
}

//===============================================================================================//

// Função para mostrar os Pokémon na mochila
void mostrarMochila(Mochila *mochila) {
    printf("\nPokémons na Mochila:\n");
    sleep(1);

    // Itera sobre os slots da mochila
    for (int i = 0; i < 6; ++i) {
        // Verifica se o slot contém um Pokémon
        if (mochila->numero[i] != 0) {
            printf("\n================================================================\n");
            printf("Pokemon posição %d\n", mochila->posicaoMochila[i]);
            printf("Nome: %s\n", mochila->nome[i]);
            printf("Número na Pokedex: %d\n", mochila->numero[i]);
            printf("Tipo Um: %s\n", mochila->tipoUm[i]);
            printf("Tipo Dois: %s\n", mochila->tipoDois[i]);
            printf("Status Total: %d\n", mochila->statusTotal[i]);
            printf("Ataque: %d\n", mochila->ataque[i]);
            printf("Defesa: %d\n", mochila->defesa[i]);
            printf("AtqSpec: %d\n", mochila->atqSpec[i]);
            printf("DefSpec: %d\n", mochila->defSpec[i]);
            printf("Velocidade: %d\n", mochila->velocidade[i]);
            printf("Geração: %d\n", mochila->geracao[i]);
            printf("Lendario: %d\n", mochila->lendario[i]);
            printf("Cor: %s\n", mochila->cor[i]);
            printf("Altura: %.2f\n", mochila->altura[i]);
            printf("Peso: %.2f\n", mochila->peso[i]);
            printf("Taxa de Captura: %d\n", mochila->taxadeCap[i]);
            printf("Level: %d\n", mochila->xp[i]);
        }
    }

    sleep(1);
    // Mostra a quantidade de diferentes tipos de Pokébolas disponíveis
    printf("Quantidade de Pokébolas: %d\n", mochila->pokeball);
    printf("Quantidade de Greatballs: %d\n", mochila->greatball);
    printf("Quantidade de Ultraballs: %d\n", mochila->ultraball);
    printf("Quantidade de Masterballs: %d\n", mochila->masterball);
}

//===============================================================================================//

// Função para mostrar os Pokémon na coleção
void mostrarColecao(Colecao *colecao) {
    printf("\nPokémons na Coleção:\n");
    sleep(1);

    // Itera sobre os slots da coleção
    for (int i = 0; i < 100; ++i) {
        // Verifica se o slot contém um Pokémon
        if (colecao->posicaoColecao[i] != 0) {
            printf("\n================================================================\n");
            printf("Pokemon posição %d\n", colecao->posicaoColecao[i]);
            printf("Nome: %s\n", colecao->nome[i]);
            printf("Número na Pokedex: %d\n", colecao->numero[i]);
            printf("Tipo Um: %s\n", colecao->tipoUm[i]);
            printf("Tipo Dois: %s\n", colecao->tipoDois[i]);
            printf("Status Total: %d\n", colecao->statusTotal[i]);
            printf("Ataque: %d\n", colecao->ataque[i]);
            printf("Defesa: %d\n", colecao->defesa[i]);
            printf("AtqSpec: %d\n", colecao->atqSpec[i]);
            printf("DefSpec: %d\n", colecao->defSpec[i]);
            printf("Velocidade: %d\n", colecao->velocidade[i]);
            printf("Geração: %d\n", colecao->geracao[i]);
            printf("Lendario: %d\n", colecao->lendario[i]);
            printf("Cor: %s\n", colecao->cor[i]);
            printf("Altura: %.2f\n", colecao->altura[i]);
            printf("Peso: %.2f\n", colecao->peso[i]);
            printf("Taxa de Captura: %d\n", colecao->taxadeCap[i]);
            printf("Level: %d\n", colecao->xp[i]);
        }
    }
}

//===============================================================================================//

// Função para verificar e mostrar a mochila com opção de visualização
void verificarMostrarMochila(Mochila *mochila) {
    char resposta;
    int respostaValida = 0;

    do {
        printf("\n================================================================\n");
        printf("\nDeseja ver a mochila? (S para Sim, N para Não): ");
        scanf(" %c", &resposta);

        if (resposta == 'S' || resposta == 's') {
            mostrarMochila(mochila);
            respostaValida = 1; // A resposta é válida, podemos sair do loop
        } else if (resposta == 'N' || resposta == 'n') {
            printf("Você escolheu não ver a mochila.\n");
            respostaValida = 1; // A resposta é válida, podemos sair do loop
        } else {
            printf("Resposta inválida. Por favor, insira S ou N.\n");
        }
    } while (!respostaValida);
}

//===============================================================================================//

// Função para verificar e mostrar a coleção com opção de visualização
void verificarMostrarColecao(Colecao *colecao) {
    char resposta;
    int respostaValida = 0;

    do {
        printf("================================================================\n");
        printf("Deseja ver a coleção? (S para Sim, N para Não): ");
        scanf(" %c", &resposta);

        if (resposta == 'S' || resposta == 's') {
            mostrarColecao(colecao);
            respostaValida = 1; // A resposta é válida, podemos sair do loop
        } else if (resposta == 'N' || resposta == 'n') {
            printf("Você escolheu não ver a coleção.\n");
            respostaValida = 1; // A resposta é válida, podemos sair do loop
        } else {
            printf("Resposta inválida. Por favor, insira S ou N.\n");
        }
    } while (!respostaValida);
}

//===============================================================================================//

// Função principal para jogar Pokémon, permitindo procurar e capturar Pokémon aleatórios
void jogarPokemon(RegistroCSV *registro, Mochila *mochila, Colecao *colecao, int numLinhas) {
    char escolha, jogarNovamente;

    do {
        do {
            sleep(2);
            printf("\n\nProcurar Pokemon? (S/N): ");
            scanf(" %c", &escolha);
            escolha = toupper(escolha);

            if (escolha != 'S' && escolha != 'N') {
                printf("Opção inválida. Por favor, escolha S ou N.\n");
            }

        } while (escolha != 'S' && escolha != 'N');

        if (escolha == 'S') {
            // Procura e captura um Pokémon aleatório
            lerLinhaAleatoria(registro, numLinhas, mochila);
            capturarPokemon(registro, mochila, colecao);
            
            // Mostra a mochila e a coleção após a captura
            verificarMostrarMochila(mochila);
            verificarMostrarColecao(colecao);

            // Pergunta se deseja jogar novamente
            printf("\nDeseja jogar novamente? (S/N): ");
            scanf(" %c", &jogarNovamente);
            jogarNovamente = toupper(jogarNovamente);

        } else {
            printf("\nVocê optou por não jogar Pokémon. Até a próxima!\n");
            jogarNovamente = 'N';  // Garante que o loop seja encerrado se o usuário optar por não jogar
        }

    } while (jogarNovamente == 'S');
}

//===============================================================================================//

void escolhaPokemon(Escolha *escolha, Mochila *mochila) {
    // Abre o arquivo CSV contendo os dados dos Pokémons
    FILE *arquivo = fopen("pokedex.csv", "r");
    if (arquivo == NULL) { // Verifica se houve falha na abertura do arquivo
        printf("Falha ao abrir o arquivo.\n");
        exit(EXIT_FAILURE);
    }

    // Define as linhas dos três primeiros Pokémons na pokedex
    int linhaBulbasaur = 1;
    int linhaCharmander = 4;
    int linhaSquirtle = 7;
    int linhaAtual = 0;

    // Reseta a posição do arquivo para o início
    rewind(arquivo);

    // Pula linhas até a linha do Bulbasaur
    while (linhaAtual < linhaBulbasaur) {
        char caractere = fgetc(arquivo);
        if (caractere == '\n') {
            linhaAtual++;
        }
    }

    // Lê os dados do Bulbasaur do arquivo e preenche a estrutura Escolha
    if (fscanf(arquivo, "%d ,%s ,%s ,%s ,%d ,%d ,%d ,%d ,%d ,%d ,%d ,%d ,%d ,%s ,%f ,%f ,%d",
               &escolha->numero[0], escolha->nome[0], escolha->tipo1[0], escolha->tipo2[0],
               &escolha->statusTotal[0], &escolha->hp[0], &escolha->ataque[0], &escolha->defesa[0],
               &escolha->atqSpec[0], &escolha->defSpec[0], &escolha->velocidade[0], &escolha->geracao[0],
               &escolha->lendario[0], escolha->cor[0], &escolha->altura[0], &escolha->peso[0],
               &escolha->taxadeCap[0])) {

        // Imprime os dados do Bulbasaur na tela
        printf("\n================================================================\n");
        printf("\nPokémon para escolher:\n");
        escolha->xp[0] = 5;
        printf("Número: %d\n", escolha->numero[0]);
        printf("Nome: %s\n", escolha->nome[0]);
        printf("Tipo 1: %s\n", escolha->tipo1[0]);
        printf("Tipo 2: %s\n", escolha->tipo2[0]);
        printf("Status Total: %d\n", escolha->statusTotal[0]);
        printf("HP: %d\n", escolha->hp[0]);
        printf("Ataque: %d\n", escolha->ataque[0]);
        printf("Defesa: %d\n", escolha->defesa[0]);
        printf("Ataque Especial: %d\n", escolha->atqSpec[0]);
        printf("Defesa Especial: %d\n", escolha->defSpec[0]);
        printf("Velocidade: %d\n", escolha->velocidade[0]);
        printf("Geração: %d\n", escolha->geracao[0]);
        printf("Lendário: %d\n", escolha->lendario[0]);
        printf("Cor: %s\n", escolha->cor[0]);
        printf("Altura: %.2f\n", escolha->altura[0]);
        printf("Peso: %.2f\n", escolha->peso[0]);
        printf("Taxa de Captura: %d\n", escolha->taxadeCap[0]);
        printf("Level: %d\n", escolha->xp[0]);
        printf("\n================================================================\n");
    }

    // Reinicializa a variável linhaAtual
    linhaAtual = 0;

    // Reseta a posição do arquivo para o início
    rewind(arquivo);

    // Pula linhas até a linha do Charmander
    while (linhaAtual < linhaCharmander) {
        char caractere = fgetc(arquivo);
        if (caractere == '\n') {
            linhaAtual++;
        }
    }

    // Lê os dados do Charmander do arquivo e preenche a estrutura Escolha
    if (fscanf(arquivo, "%d ,%s ,%s ,%s ,%d ,%d ,%d ,%d ,%d ,%d ,%d ,%d ,%d ,%s ,%f ,%f ,%d",
               &escolha->numero[1], escolha->nome[1], escolha->tipo1[1], escolha->tipo2[1],
               &escolha->statusTotal[1], &escolha->hp[1], &escolha->ataque[1], &escolha->defesa[1],
               &escolha->atqSpec[1], &escolha->defSpec[1], &escolha->velocidade[1], &escolha->geracao[1],
               &escolha->lendario[1], escolha->cor[1], &escolha->altura[1], &escolha->peso[1],
               &escolha->taxadeCap[1])) {

        // Adiciona um delay de 1 segundo
        sleep(1);

        // Preenche o campo de experiência e imprime os dados do Charmander na tela
        escolha->xp[1] = 5;
        printf("Número: %d\n", escolha->numero[1]);
        printf("Nome: %s\n", escolha->nome[1]);
        printf("Tipo 1: %s\n", escolha->tipo1[1]);
        printf("Tipo 2: %s\n", escolha->tipo2[1]);
        printf("Status Total: %d\n", escolha->statusTotal[1]);
        printf("HP: %d\n", escolha->hp[1]);
        printf("Ataque: %d\n", escolha->ataque[1]);
        printf("Defesa: %d\n", escolha->defesa[1]);
        printf("Ataque Especial: %d\n", escolha->atqSpec[1]);
        printf("Defesa Especial: %d\n", escolha->defSpec[1]);
        printf("Velocidade: %d\n", escolha->velocidade[1]);
        printf("Geração: %d\n", escolha->geracao[1]);
        printf("Lendário: %d\n", escolha->lendario[1]);
        printf("Cor: %s\n", escolha->cor[1]);
        printf("Altura: %.2f\n", escolha->altura[1]);
        printf("Peso: %.2f\n", escolha->peso[1]);
        printf("Taxa de Captura: %d\n", escolha->taxadeCap[1]);
        printf("Level: %d\n", escolha->xp[1]);
        printf("\n================================================================\n");
    }

    // Reinicializa a variável linhaAtual
    linhaAtual = 0;

    // Reseta a posição do arquivo para o início
    rewind(arquivo);

    // Pula linhas até a linha do Squirtle
    while (linhaAtual < linhaSquirtle) {
        char caractere = fgetc(arquivo);
        if (caractere == '\n') {
            linhaAtual++;
        }
    }

    // Lê os dados do Squirtle do arquivo e preenche a estrutura Escolha
    if (fscanf(arquivo, "%d ,%s ,%s ,%s ,%d ,%d ,%d ,%d ,%d ,%d ,%d ,%d ,%d ,%s ,%f ,%f ,%d",
               &escolha->numero[2], escolha->nome[2], escolha->tipo1[2], escolha->tipo2[2],
               &escolha->statusTotal[2], &escolha->hp[2], &escolha->ataque[2], &escolha->defesa[2],
               &escolha->atqSpec[2], &escolha->defSpec[2], &escolha->velocidade[2], &escolha->geracao[2],
               &escolha->lendario[2], escolha->cor[2], &escolha->altura[2], &escolha->peso[2],
               &escolha->taxadeCap[2])) {

        // Adiciona um delay de 1 segundo
        sleep(1);

        // Preenche o campo de experiência e imprime os dados do Squirtle na tela
        escolha->xp[2] = 5;
        printf("Número: %d\n", escolha->numero[2]);
        printf("Nome: %s\n", escolha->nome[2]);
        printf("Tipo 1: %s\n", escolha->tipo1[2]);
        printf("Tipo 2: %s\n", escolha->tipo2[2]);
        printf("Status Total: %d\n", escolha->statusTotal[2]);
        printf("HP: %d\n", escolha->hp[2]);
        printf("Ataque: %d\n", escolha->ataque[2]);
        printf("Defesa: %d\n", escolha->defesa[2]);
        printf("Ataque Especial: %d\n", escolha->atqSpec[2]);
        printf("Defesa Especial: %d\n", escolha->defSpec[2]);
        printf("Velocidade: %d\n", escolha->velocidade[2]);
        printf("Geração: %d\n", escolha->geracao[2]);
        printf("Lendário: %d\n", escolha->lendario[2]);
        printf("Cor: %s\n", escolha->cor[2]);
        printf("Altura: %.2f\n", escolha->altura[2]);
        printf("Peso: %.2f\n", escolha->peso[2]);
        printf("Taxa de Captura: %d\n", escolha->taxadeCap[2]);
        printf("Level: %d\n", escolha->xp[2]);
        printf("\n================================================================\n");
    }

    // Reseta a posição do arquivo para o início
    rewind(arquivo);

    // Fecha o arquivo após o uso
    fclose(arquivo);

    // Inicializa a variável de escolha com 0
    int i = 0;

    // Adiciona um delay de 2 segundos para dar um efeito visual
    sleep(2);

    // Imprime mensagem para escolher um Pokémon inicial
    printf("\nEscolha seu Pokémon inicial!\n");

    do {
        // Solicita ao usuário que digite a escolha entre 1 e 3
        printf("\nDigite 1 - Bulbasaur; 2 - Charmander; 3 - Squirtle: ");
        scanf("%d", &i);

        // Verifica se a escolha é inválida e exibe mensagem de erro
        if (i < 1 || i > 3) {
            printf("Opção inválida. Tente novamente.\n");
        }

    } while (i < 1 || i > 3);

    // Exibe a escolha do usuário
    printf("Você escolheu o %s!\n", escolha->nome[i - 1]);

    // Preenche os dados do Pokémon escolhido na mochila
    mochila->posicaoMochila[0] = 1;
    mochila->numero[0] = escolha->numero[i - 1];
    strcpy(mochila->nome[0], escolha->nome[i - 1]);
    strcpy(mochila->tipoUm[0], escolha->tipo1[i - 1]);
    strcpy(mochila->tipoDois[0], escolha->tipo2[i - 1]);
    mochila->statusTotal[0] = escolha->statusTotal[i - 1];
    mochila->ataque[0] = escolha->ataque[i - 1];
    mochila->defesa[0] = escolha->defesa[i - 1];
    mochila->atqSpec[0] = escolha->atqSpec[i - 1];
    mochila->defSpec[0] = escolha->defSpec[i - 1];
    mochila->velocidade[0] = escolha->velocidade[i - 1];
    mochila->geracao[0] = escolha->geracao[i - 1];
    mochila->lendario[0] = escolha->lendario[i - 1];
    strcpy(mochila->cor[0], escolha->cor[i - 1]);
    mochila->altura[0] = escolha->altura[i - 1];
    mochila->peso[0] = escolha->peso[i - 1];
    mochila->taxadeCap[0] = escolha->taxadeCap[i - 1];
    mochila->xp[0] = escolha->xp[i - 1];

    // Adiciona um delay de 2 segundos para dar um efeito visual
    sleep(2);

    // Chama a função para mostrar a mochila
    mostrarMochila(mochila);
}

//===============================================================================================//

int main() {
    // Declaração das estruturas necessárias
    RegistroCSV registro;
    Escolha escolha;
    Mochila mochila;
    Colecao colecao;

    // Conta o número de linhas no arquivo CSV
    int numLinhas = contarLinhas();

    // Inicializa a mochila e a coleção
    inicializarMochila(&mochila);
    inicializarColecao(&colecao);

    // Carrega os dados dos Pokémon disponíveis para escolha
    escolhaPokemon(&escolha, &mochila);

    // Inicia o jogo Pokémon, passando as estruturas necessárias
    jogarPokemon(&registro, &mochila, &colecao, numLinhas);

    // Retorna 0 indicando que o programa foi concluído com sucesso
    return 0;
}
