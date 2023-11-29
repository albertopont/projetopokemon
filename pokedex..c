#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Definição da estrutura Pokemon que armazenará as informações de cada Pokémon
typedef struct {
    int numero;
    char nome[30];
    char tipoUm[15];
    char tipoDois[15];
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
    int evolucao;
    int preEvolucao;
} Pokemon;

// Função para ler os dados do arquivo CSV e armazenar em um array de structs Pokemon
void arquivoR(Pokemon **pokemon, int *numAloc) {

    // Abre o arquivo CSV para leitura
    FILE *arquivo = fopen("pokedex.csv", "r");
    if (arquivo == NULL) {
        printf("Falha ao abrir o arquivo.\n");
        exit(EXIT_FAILURE);
    }

    // Ignora a primeira linha (cabeçalho) do arquivo CSV
    fscanf(arquivo, "%*[^\n]\n");

    // Inicializa o array de Pokemon com capacidade inicial de 10
    int capacidade = 10; 
    *pokemon = malloc(capacidade * sizeof(Pokemon));
    if (*pokemon == NULL) {
        printf("Falha ao alocar memória.\n");
        exit(EXIT_FAILURE);
    }
    
    // Inicializa o contador de elementos alocados
    *numAloc = 0;

    // Loop para ler os dados do arquivo CSV e armazenar no array de Pokemon
    while (fscanf(arquivo, "%d ,%29[^,] ,%14[^,] ,%14[^,] ,%d ,%d ,%d ,%d ,%d ,%d ,%d ,%d ,%d ,%14[^,] ,%f ,%f ,%d",
                  &(*pokemon)[*numAloc].numero, (*pokemon)[*numAloc].nome,
                  (*pokemon)[*numAloc].tipoUm, (*pokemon)[*numAloc].tipoDois,
                  &(*pokemon)[*numAloc].statusTotal, &(*pokemon)[*numAloc].hp,
                  &(*pokemon)[*numAloc].ataque, &(*pokemon)[*numAloc].defesa,
                  &(*pokemon)[*numAloc].atqSpec, &(*pokemon)[*numAloc].defSpec,
                  &(*pokemon)[*numAloc].velocidade, &(*pokemon)[*numAloc].geracao,
                  &(*pokemon)[*numAloc].lendario, (*pokemon)[*numAloc].cor,
                  &(*pokemon)[*numAloc].altura, &(*pokemon)[*numAloc].peso,
                  &(*pokemon)[*numAloc].taxadeCap) != EOF) {

        // Incrementa o contador de elementos alocados
        (*numAloc)++;

        // Verifica se a capacidade do array precisa ser aumentada
        if (*numAloc >= capacidade) {
            capacidade *= 2;
            
            // Realoca memória para o array de Pokemon
            *pokemon = realloc(*pokemon, capacidade * sizeof(Pokemon));
            if (*pokemon == NULL) {
                printf("Falha ao realocar memória.\n");
                exit(EXIT_FAILURE);
            }
        }
    }

    // Fecha o arquivo após a leitura
    fclose(arquivo);
}

// Função para listar todos os Pokémon presentes na Pokedex
void listarGeral(Pokemon *pokemon, int numAloc) {

    // Chama a função arquivoR para ler os dados do arquivo CSV e preencher a estrutura Pokemon
    arquivoR(&pokemon, &numAloc);

    // Loop para imprimir as informações de cada Pokémon na Pokedex
    for (int i = 0; i < numAloc; i++) {
        // Imprime os detalhes de cada Pokémon formatado
        printf("Pokémon: %d, %s, %s, %s, %d, %d, %d, %d, %d, %d, %d, %d, %d, %s, %.2f, %.2f, %d.\n",
            pokemon[i].numero, pokemon[i].nome, pokemon[i].tipoUm, pokemon[i].tipoDois,
            pokemon[i].statusTotal, pokemon[i].hp, pokemon[i].ataque, pokemon[i].defesa,
            pokemon[i].atqSpec, pokemon[i].defSpec, pokemon[i].velocidade, pokemon[i].geracao,
            pokemon[i].lendario, pokemon[i].cor, pokemon[i].altura, pokemon[i].peso,
            pokemon[i].taxadeCap);
    }

    // Libera a memória alocada para o array de Pokemon
    free(pokemon);
}


// Função para listar os Pokémon de uma geração específica
void listarGeracao(Pokemon *pokemon, int numAloc, int *geracaoDesejada) {
    // Chama a função arquivoR para ler os dados do arquivo CSV e preencher a estrutura Pokemon
    arquivoR(&pokemon, &numAloc);

    // Solicita ao usuário a geração desejada
    printf("Digite a geração que você deseja ver listada:");
    scanf("%d", geracaoDesejada);

    // Variável para verificar se há Pokémon na geração desejada
    int indefinido = 0;

    // Loop para percorrer os Pokémon e imprimir os da geração desejada
    for (int i = 0; i < numAloc; i++) {
        if (pokemon[i].geracao == *geracaoDesejada) {
            // Imprime os detalhes de cada Pokémon formatado
            printf("Pokémon: %d, %s, %s, %s, %d, %d, %d, %d, %d, %d, %d, %d, %d, %s, %.2f, %.2f, %d.\n",
                pokemon[i].numero, pokemon[i].nome, pokemon[i].tipoUm, pokemon[i].tipoDois,
                pokemon[i].statusTotal, pokemon[i].hp, pokemon[i].ataque, pokemon[i].defesa,
                pokemon[i].atqSpec, pokemon[i].defSpec, pokemon[i].velocidade, pokemon[i].geracao,
                pokemon[i].lendario, pokemon[i].cor, pokemon[i].altura, pokemon[i].peso,
                pokemon[i].taxadeCap);
            indefinido++;
        } 
    }

    // Se não houver Pokémon na geração desejada, imprime uma mensagem informativa
    if (indefinido) {
        printf("Não há uma geração correspondente.\n");
    } 
}

// Função para listar os Pokémon de um tipo específico
void listarTipo(Pokemon *pokemon, int numAloc, char *tipoDesejado) {
    // Chama a função arquivoR para ler os dados do arquivo CSV e preencher a estrutura Pokemon
    arquivoR(&pokemon, &numAloc);

    // Solicita ao usuário o tipo desejado
    printf("Digite o tipo que você deseja ver listado:");
    scanf("%s", tipoDesejado);

    // Loop para percorrer os Pokémon e imprimir os do tipo desejado
    for (int i = 0; i < numAloc; i++) {
        if (strcmp(pokemon[i].tipoUm, tipoDesejado) == 0 || strcmp(pokemon[i].tipoDois, tipoDesejado) == 0) {
            // Imprime os detalhes de cada Pokémon formatado
            printf("Pokémon: %d, %s, %s, %s, %d, %d, %d, %d, %d, %d, %d, %d, %d, %s, %.2f, %.2f, %d.\n",
                pokemon[i].numero, pokemon[i].nome, pokemon[i].tipoUm, pokemon[i].tipoDois,
                pokemon[i].statusTotal, pokemon[i].hp, pokemon[i].ataque, pokemon[i].defesa,
                pokemon[i].atqSpec, pokemon[i].defSpec, pokemon[i].velocidade, pokemon[i].geracao,
                pokemon[i].lendario, pokemon[i].cor, pokemon[i].altura, pokemon[i].peso,
                pokemon[i].taxadeCap);
        }
    }
}

// Função para inserir um novo Pokémon no arquivo CSV
void inserir(Pokemon *pokemon) {
    // Abre o arquivo CSV no modo de escrita no final (append)
    FILE *arquivo = fopen("pokedex.csv", "a");
    if (arquivo == NULL) {
        printf("Falha ao abrir o arquivo.\n");
        exit(EXIT_FAILURE);
    }

    // Solicita ao usuário os dados do novo Pokémon
    printf("Digite o número, necessita ser maior que 750: ");
    scanf("%d", &pokemon->numero);
    
    // Solicita e valida o nome do Pokémon
    printf("Digite o nome do pokémon a ser inserido:");
    scanf("%s", pokemon->nome);

    // Solicita e valida o tipo do Pokémon
    printf("Digite o tipo do pokémon a ser inserido:");
    scanf("%s", pokemon->tipoUm);

    // Solicita e valida o segundo tipo do Pokémon
    printf("Digite o segundo tipo do pokémon a ser inserido:");
    scanf("%s", pokemon->tipoDois);

    // Solicita e valida o HP do Pokémon
    printf("Digite o HP do pokémon a ser inserido:");
    scanf("%d", &pokemon->hp);
    while (pokemon->hp > 200) {
        printf("O valor digitado torna seu pokémon OVERPOWERED, digite novamente um número entre 0 e 300: ");
        scanf("%d", &pokemon->hp);
    }

    // Solicita e valida os atributos de ataque, defesa, ataque especial, defesa especial e velocidade
    // Certifica-se de que os valores não tornam o Pokémon overpower
    printf("Digite o ataque do pokémon a ser inserido:");
    scanf("%d", &pokemon->ataque);
    while (pokemon->ataque > 200) {
        printf("O valor digitado torna seu pokémon OVERPOWERED, digite novamente um número entre 0 e 300: ");
        scanf("%d", &pokemon->ataque);
    }

    printf("Digite a defesa do pokémon a ser inserido:");
    scanf("%d", &pokemon->defesa);
    while (pokemon->defesa > 200) {
        printf("O valor digitado torna seu pokémon OVERPOWERED, digite novamente um número entre 0 e 300: ");
        scanf("%d", &pokemon->defesa);
    }

    printf("Digite o ataque especial do pokémon a ser inserido:");
    scanf("%d", &pokemon->atqSpec);
    while (pokemon->atqSpec > 200) {
        printf("O valor digitado torna seu pokémon OVERPOWERED, digite novamente um número entre 0 e 300: ");
        scanf("%d", &pokemon->atqSpec);
    }

    printf("Digite a defesa especial do pokémon a ser inserido:");
    scanf("%d", &pokemon->defSpec);
    while (pokemon->defSpec > 200) {
        printf("O valor digitado torna seu pokémon OVERPOWERED, digite novamente um número entre 0 e 300: ");
        scanf("%d", &pokemon->defSpec);
    }

    printf("Digite a velocidade do pokémon a ser inserido:");
    scanf("%d", &pokemon->velocidade);
    while (pokemon->velocidade > 200) {
        printf("O valor digitado torna seu pokémon OVERPOWERED, digite novamente um número entre 0 e 300: ");
        scanf("%d", &pokemon->velocidade);
    }

    // Calcula e preenche o status total do Pokémon
    pokemon->statusTotal = pokemon->hp + pokemon->ataque + pokemon->defesa + pokemon->atqSpec + pokemon->defSpec + pokemon->velocidade;

    // Preenche automaticamente a geração e se o Pokémon é lendário
    pokemon->geracao = 9;
    pokemon->lendario = 0;

    // Solicita e valida a cor do Pokémon
    printf("Digite a cor do pokémon a ser inserido:");
    scanf("%s", pokemon->cor);

    // Solicita e valida a altura do Pokémon
    printf("Digite a altura do pokémon a ser inserido:");
    scanf("%f", &pokemon->altura);

    // Solicita e valida o peso do Pokémon
    printf("Digite o peso do pokémon a ser inserido:");
    scanf("%f", &pokemon->peso);

    // Solicita e valida a taxa de captura do Pokémon
    printf("Digite a taxa de captura do pokémon a ser inserido:");
    scanf("%d", &pokemon->taxadeCap);
    while (pokemon->taxadeCap >= 255 && pokemon->taxadeCap <= 0) {
        printf("O valor digitado é inválido digite entre 0 a 255: ");
        scanf("%d", &pokemon->taxadeCap);
    }

    // Escreve os dados do novo Pokémon no arquivo CSV
    fprintf(arquivo, "\n%6d ,%11s ,%8s ,%8s ,%6d ,%4d ,%6d ,%6d ,%15d ,%15d ,%10d ,%7d ,%8d ,%7s ,%8f ,%7f ,%12d",
            pokemon->numero, pokemon->nome, pokemon->tipoUm, pokemon->tipoDois, pokemon->statusTotal, pokemon->hp,
            pokemon->ataque, pokemon->defesa, pokemon->atqSpec, pokemon->defSpec, pokemon->velocidade, pokemon->geracao,
            pokemon->lendario, pokemon->cor, pokemon->altura, pokemon->peso, pokemon->taxadeCap);

    // Fecha o arquivo
    fclose(arquivo);
}

// Função para pesquisar um Pokémon no arquivo CSV
void pesquisar(Pokemon *pokemon) {
    // Abre o arquivo CSV no modo de leitura
    FILE *arquivo = fopen("pokedex.csv", "r");
    if (arquivo == NULL) {
        printf("Falha ao abrir o arquivo.\n");
        exit(EXIT_FAILURE);
    }

    char pokemonPesquisado[30]; // Variável que será utilizada para inserir o nome do pokémon pesquisado
    int verificador = 0;       // Variável contadora para verificar se o pokémon está ou não registrado

    // Solicita ao usuário o nome do pokémon que deseja pesquisar
    printf("Digite o nome do pokémon que você deseja pesquisar: ");
    scanf("%s", pokemonPesquisado);

    // Ignora a primeira linha do arquivo (cabeçalho)
    fscanf(arquivo, "%*[^\n]\n");

    // Loop para percorrer o arquivo e encontrar o Pokémon pesquisado
    while (fscanf(arquivo, "%d ,%s ,%s ,%s ,%d ,%d ,%d ,%d ,%d ,%d ,%d ,%d ,%d ,%s ,%f ,%f ,%d", &pokemon->numero, pokemon->nome, pokemon->tipoUm, pokemon->tipoDois, &pokemon->statusTotal, &pokemon->hp, &pokemon->ataque, &pokemon->defesa, &pokemon->atqSpec, &pokemon->defSpec, &pokemon->velocidade, &pokemon->geracao, &pokemon->lendario, pokemon->cor, &pokemon->altura, &pokemon->peso, &pokemon->taxadeCap) != EOF){
        if (strcmp(pokemon->nome, pokemonPesquisado) == 0) {
            verificador = 1;
            break;
        } 
    }

    // Se o Pokémon foi encontrado, exibe suas informações
    if (verificador) {
        printf("Número: %d\n", pokemon->numero);
        printf("Nome: %s\n", pokemon->nome);
        printf("Tipos: %s e %s\n", pokemon->tipoUm, pokemon->tipoDois);
        printf("Status total: %d\n", pokemon->statusTotal);
        printf("Ataque: %d\n", pokemon->ataque);
        printf("Defesa: %d\n", pokemon->defesa);
        printf("Ataque especial: %d\n", pokemon->atqSpec);
        printf("Defesa especial: %d\n", pokemon->defSpec);
        printf("Velocidade: %d\n", pokemon->velocidade);
        printf("Altura: %.2f\n", pokemon->altura);
        printf("Peso: %.2f\n", pokemon->peso);
        printf("Taxa de captura: %d\n", pokemon->taxadeCap);
    } else {
        printf("O pokémon pesquisado ainda não foi capturado ou não existe.\n");
    } 
    
    // Fecha o arquivo
    fclose(arquivo);
}


// Função para excluir um Pokémon do arquivo CSV
void excluir(Pokemon *pokemon) {
    // Abre o arquivo original para leitura
    FILE *arquivoOriginal = fopen("pokedex.csv", "r");
    if (arquivoOriginal == NULL) {
        printf("Falha ao abrir o arquivo.\n");
        exit(EXIT_FAILURE);
    } 

    // Abre um arquivo temporário para escrita
    FILE *arquivoTemporario = fopen("pokedextemp.csv", "w");
    if (arquivoTemporario == NULL) {
        printf("Falha ao abrir o arquivo.\n");
        fclose(arquivoOriginal);
        exit(EXIT_FAILURE);
    }

    int pokemonRemovido;
    printf("Digite o número do pokémon a ser removido: ");
    scanf("%d", &pokemonRemovido);

    // Lê e escreve a primeira linha do arquivo (cabeçalho)
    char linha[1024];
    fgets(linha, sizeof(linha), arquivoOriginal);
    fprintf(arquivoTemporario, "%s", linha);

    // Loop para copiar todos os Pokémon do arquivo original para o arquivo temporário, exceto o Pokémon a ser removido
    while (fscanf(arquivoOriginal, "%d ,%s ,%s ,%s ,%d ,%d ,%d ,%d ,%d ,%d ,%d ,%d ,%d ,%s ,%f ,%f ,%d",
                  &pokemon->numero, pokemon->nome, pokemon->tipoUm, pokemon->tipoDois, &pokemon->statusTotal,
                  &pokemon->hp, &pokemon->ataque, &pokemon->defesa, &pokemon->atqSpec, &pokemon->defSpec,
                  &pokemon->velocidade, &pokemon->geracao, &pokemon->lendario, pokemon->cor,
                  &pokemon->altura, &pokemon->peso, &pokemon->taxadeCap) != EOF) {
        if (pokemon->numero != pokemonRemovido) {
            // Se o Pokémon não for o removido, escreve no arquivo temporário
            fprintf(arquivoTemporario, "%d ,%s ,%s ,%s ,%d ,%d ,%d ,%d ,%d ,%d ,%d ,%d ,%d ,%s ,%.2f ,%.2f ,%d\n",
                    pokemon->numero, pokemon->nome, pokemon->tipoUm, pokemon->tipoDois, pokemon->statusTotal,
                    pokemon->hp, pokemon->ataque, pokemon->defesa, pokemon->atqSpec, pokemon->defSpec,
                    pokemon->velocidade, pokemon->geracao, pokemon->lendario, pokemon->cor,
                    pokemon->altura, pokemon->peso, pokemon->taxadeCap);
        }
    }

    // Fecha os arquivos
    fclose(arquivoOriginal);
    fclose(arquivoTemporario);

    // Remove o arquivo original e renomeia o arquivo temporário para o nome original
    if (remove("pokedex.csv") == 0) {
        if (rename("pokedextemp.csv", "pokedex.csv") != 0) {
            printf("Falha ao renomear o arquivo temporário.\n");
        }
    } else {
        printf("Falha ao renomear ao arquivo original.\n");
    }
}

// Função para alterar os dados de um Pokémon no arquivo CSV
void alterar(Pokemon *pokemon) {
    // Abre o arquivo original para leitura
    FILE *arquivoOriginal = fopen("pokedex.csv", "r");
    if (arquivoOriginal == NULL) {
        printf("Erro ao abrir arquivo!\n");
        exit(1);
    }

    // Abre um arquivo temporário para escrita
    FILE *arquivoTemporario = fopen("pokedextemp.csv", "w");
    if (arquivoTemporario == NULL) {
        printf("Erro ao abrir arquivo!\n");
        exit(1);
    }

    int pokemonDesejado;
    printf("Digite o número do pokémon que você deseja alterar: ");
    scanf("%d", &pokemonDesejado);

    // Loop para copiar todos os Pokémon do arquivo original para o arquivo temporário, realizando alterações no Pokémon desejado
    while (fscanf(arquivoOriginal, "%d ,%s ,%s ,%s ,%d ,%d ,%d ,%d ,%d ,%d ,%d ,%d ,%d ,%s ,%f ,%f ,%d",
                  &pokemon->numero, pokemon->nome, pokemon->tipoUm, pokemon->tipoDois, &pokemon->statusTotal,
                  &pokemon->hp, &pokemon->ataque, &pokemon->defesa, &pokemon->atqSpec, &pokemon->defSpec,
                  &pokemon->velocidade, &pokemon->geracao, &pokemon->lendario, pokemon->cor,
                  &pokemon->altura, &pokemon->peso, &pokemon->taxadeCap) != EOF) {
        fscanf(arquivoOriginal, "%*[^\n]\n");

        // Se o Pokémon desejado for encontrado, solicita novos dados e escreve no arquivo temporário
        if (pokemon->numero == pokemonDesejado) {  
            // Solicita novos dados para o Pokémon
            printf("Digite o número do pokémon (De preferência sendo igual o que você digitou para alterar): ");
            scanf("%d", &pokemon->numero);
            printf("Digite o nome do pokémon: ");
            scanf("%s", pokemon->nome);
            printf("Digite o primeiro tipo do pokémon: ");
            scanf("%s", pokemon->tipoUm);
            printf("Digite o segundo tipo do pokémon: ");
            scanf("%s", pokemon->tipoDois);
            printf("Digite o HP do pokémon: ");
            scanf("%d", &pokemon->hp);
           scanf("%d", &pokemon->ataque);
            printf("Digite a DEFESA do pokémon: ");
            scanf("%d", &pokemon->defesa);
            printf("Digite o ATAQUE ESPECIAL do pokémon: ");
            scanf("%d", &pokemon->atqSpec);
            printf("Digite o DEFESA ESPECIAL do pokémon: ");
            scanf("%d", &pokemon->defSpec);
            printf("Digite o HP do pokémon: ");
            scanf("%d", &pokemon->velocidade);
            printf("Digite a cor do pokémon: ");
            scanf("%s", &pokemon->cor);

            // Define valores padrão para os atributos não solicitados
            pokemon->geracao = 10;
            pokemon->lendario = 0;
            pokemon->altura = 2;
            pokemon->peso = 80;
            pokemon->taxadeCap = 100;

            // Escreve os novos dados no arquivo temporário
            fprintf(arquivoTemporario, "%d ,%s ,%s ,%s ,%d ,%d ,%d ,%d ,%d ,%d ,%d ,%d ,%d ,%s ,%.2f ,%.2f ,%d\n",
                    pokemon->numero, pokemon->nome, pokemon->tipoUm, pokemon->tipoDois, pokemon->statusTotal,
                    pokemon->hp, pokemon->ataque, pokemon->defesa, pokemon->atqSpec, pokemon->defSpec,
                    pokemon->velocidade, pokemon->geracao, pokemon->lendario, pokemon->cor,
                    pokemon->altura, pokemon->peso, pokemon->taxadeCap);
        } else {
            // Se o Pokémon não for o desejado, escreve no arquivo temporário sem alterações
            fprintf(arquivoTemporario, "%d ,%s ,%s ,%s ,%d ,%d ,%d ,%d ,%d ,%d ,%d ,%d ,%d ,%s ,%.2f ,%.2f ,%d\n",
                    pokemon->numero, pokemon->nome, pokemon->tipoUm, pokemon->tipoDois, pokemon->statusTotal,
                    pokemon->hp, pokemon->ataque, pokemon->defesa, pokemon->atqSpec, pokemon->defSpec,
                    pokemon->velocidade, pokemon->geracao, pokemon->lendario, pokemon->cor,
                    pokemon->altura, pokemon->peso, pokemon->taxadeCap);
        }
    }

    // Fecha os arquivos
    fclose(arquivoOriginal);
    fclose(arquivoTemporario);

    // Remove o arquivo original e renomeia o arquivo temporário para o nome original
    remove("pokedex.csv");
    rename("pokedextemp.csv", "pokedex.csv");
}


int main(){ 
    Pokemon *pokemon;
    int numAloc;
    char tipoDesejado[15];
    int geracaoDesejada;

    arquivoR(&pokemon, &numAloc);

    int numeroEscolhido;
    int listagem;
    printf("POKÉDEX\n");
    printf("Digite o número correspondente para realizar a função desejada:\n" );
    printf("1 para LISTAR pokémons\n");
    printf("2 para INSERIR um pokémon\n");
    printf("3 para REMOVER um pokémon\n");
    printf("4 para PESQUISAR pokémons\n");
    printf("5 para ALTERAR pokémon\n");
    printf("6 para ENCERRAR o menu\n");
    printf("Número desejado: ");
    scanf("%d", &numeroEscolhido);

    switch (numeroEscolhido){
    case 1:
        printf("Escolha o tipo de listagem que deseja realizar.\n");
        printf("Digite 1 para listar TODOS os pokémons\n");
        printf("Digite 2 para listar pokémons por GERAÇÃO\n");
        printf("Digite 3 para listar pokémons por TIPO\n");
        printf("Número desejado: ");
        scanf("%d", &listagem);

        switch (listagem){
        case 1:
            listarGeral(pokemon, numAloc);
            break;
        
        case 2:
            listarGeracao(pokemon, numAloc, &geracaoDesejada);
            free(pokemon);  
            break;

        case 3:
            listarTipo(pokemon, numAloc, tipoDesejado);
            free(pokemon);  
            break;

        default:
            printf("O valor digitado não está associado a nenhuma opção disponível.");
            break;
        }
        break;
    
    case 2:
    inserir(pokemon);
    break;

    case 3:
    excluir(pokemon);
    break;

    case 4:
    pesquisar(pokemon);
    break;

    case 5:
    alterar(pokemon);
    break;

    case 6:
    exit(1);
    break;

    default:
    printf("O valor digitado não está associado a nenhuma opção disponível.");
    break;
    }

    return 0;
}   

    return 0;
}
