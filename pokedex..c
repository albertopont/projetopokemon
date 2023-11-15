#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//POKEDEX
typedef struct{
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


void arquivoR(Pokemon **pokemon, int *numAloc){

    FILE *arquivo = fopen("pokedex.csv", "r");
    if(arquivo == NULL){
        printf("Falha ao abrir o arquivo.\n");
        exit(EXIT_FAILURE);
    }

    fscanf(arquivo, "%*[^\n]\n");
    int capacidade = 10; 
    *pokemon = malloc(capacidade * sizeof(Pokemon));
    if (*pokemon == NULL) {
        printf("Falha ao alocar memória.\n");
        exit(EXIT_FAILURE);
    }
    
    *numAloc = 0;
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

        (*numAloc)++;

        if (*numAloc >= capacidade) {
            capacidade *= 2;
            *pokemon = realloc(*pokemon, capacidade * sizeof(Pokemon));
            if (*pokemon == NULL) {
                printf("Falha ao realocar memória.\n");
                exit(EXIT_FAILURE);
            }
        }
    }

    fclose(arquivo);
}

void listarGeral(Pokemon *pokemon, int numAloc){

    arquivoR(&pokemon, &numAloc);

    for (int i = 0; i < numAloc; i++) {
            printf("Pokémon: %d, %s, %s, %s, %d, %d, %d, %d, %d, %d, %d, %d, %d, %s, %.2f, %.2f, %d.\n",
                pokemon[i].numero, pokemon[i].nome, pokemon[i].tipoUm, pokemon[i].tipoDois,
                pokemon[i].statusTotal, pokemon[i].hp, pokemon[i].ataque, pokemon[i].defesa,
                pokemon[i].atqSpec, pokemon[i].defSpec, pokemon[i].velocidade, pokemon[i].geracao,
                pokemon[i].lendario, pokemon[i].cor, pokemon[i].altura, pokemon[i].peso,
                pokemon[i].taxadeCap);
    }
    free(pokemon);
}

void listarGeracao(Pokemon *pokemon, int numAloc, int *geracaoDesejada){
    arquivoR(&pokemon, &numAloc);

    printf("Digite a geração que você deseja ver listada:");
    scanf("%d", geracaoDesejada);

    int indefinido = 0;

        for (int i = 0; i < numAloc; i++) {
            if(pokemon[i].geracao == *geracaoDesejada){
            printf("Pokémon: %d, %s, %s, %s, %d, %d, %d, %d, %d, %d, %d, %d, %d, %s, %.2f, %.2f, %d.\n",
                pokemon[i].numero, pokemon[i].nome, pokemon[i].tipoUm, pokemon[i].tipoDois,
                pokemon[i].statusTotal, pokemon[i].hp, pokemon[i].ataque, pokemon[i].defesa,
                pokemon[i].atqSpec, pokemon[i].defSpec, pokemon[i].velocidade, pokemon[i].geracao,
                pokemon[i].lendario, pokemon[i].cor, pokemon[i].altura, pokemon[i].peso,
                pokemon[i].taxadeCap);
                indefinido++;
        } 
    }

    if(indefinido){
            printf("Não há uma geração correspondente.\n");
    } 
}


void listarTipo(Pokemon *pokemon, int numAloc, char *tipoDesejado){
    arquivoR(&pokemon, &numAloc);

    printf("Digite o tipo que você deseja ver listado:");
    scanf("%s", tipoDesejado);

    for (int i = 0; i < numAloc; i++){
        if (strcmp(pokemon[i].tipoUm, tipoDesejado) == 0 || strcmp(pokemon[i].tipoDois, tipoDesejado) == 0) {
            printf("Pokémon: %d, %s, %s, %s, %d, %d, %d, %d, %d, %d, %d, %d, %d, %s, %.2f, %.2f, %d.\n",
                pokemon[i].numero, pokemon[i].nome, pokemon[i].tipoUm, pokemon[i].tipoDois,
                pokemon[i].statusTotal, pokemon[i].hp, pokemon[i].ataque, pokemon[i].defesa,
                pokemon[i].atqSpec, pokemon[i].defSpec, pokemon[i].velocidade, pokemon[i].geracao,
                pokemon[i].lendario, pokemon[i].cor, pokemon[i].altura, pokemon[i].peso,
                pokemon[i].taxadeCap);
        }
    }
}

void inserir(Pokemon *pokemon){
    FILE *arquivo = fopen("pokedex.csv", "a");
    if(arquivo == NULL){
        printf("Falha ao abrir o arquivo.\n");
        exit(EXIT_FAILURE);
    }

    
    pokemon->numero = 722;
    printf("Digite o nome do pokémon a ser inserido:");
    scanf("%s", pokemon->nome);
    printf("Digite o tipo do pokémon a ser inserido:");
    scanf("%s", pokemon->tipoUm);
    printf("Digite o segundo tipo do pokémon a ser inserido:");
    scanf("%s", pokemon->tipoDois);
    printf("Digite o HP do pokémon a ser inserido:");
    scanf("%d", &pokemon->hp);
    while(pokemon->hp > 300){
        printf("O valor digitado torna seu pokémon OVERPOWERED, digite novamente um número entre 0 e 300: ");
        scanf("%d", &pokemon->hp);
    }
    printf("Digite o ataque do pokémon a ser inserido:");
    scanf("%d", &pokemon->ataque);
    while(pokemon->ataque > 300){
        printf("O valor digitado torna seu pokémon OVERPOWERED, digite novamente um número entre 0 e 300: ");
        scanf("%d", &pokemon->ataque);
    }
    printf("Digite a defesa do pokémon a ser inserido:");
    scanf("%d", &pokemon->defesa);
    while(pokemon->defesa > 300){
        printf("O valor digitado torna seu pokémon OVERPOWERED, digite novamente um número entre 0 e 300: ");
        scanf("%d", &pokemon->defesa);
    }
    printf("Digite o ataque especial do pokémon a ser inserido:");
    scanf("%d", &pokemon->atqSpec);
    while(pokemon->atqSpec > 300){
        printf("O valor digitado torna seu pokémon OVERPOWERED, digite novamente um número entre 0 e 300: ");
        scanf("%d", &pokemon->atqSpec);
    }
    printf("Digite a defesa especial do pokémon a ser inserido:");
    scanf("%d", &pokemon->defSpec);
    while(pokemon->defSpec > 300){
        printf("O valor digitado torna seu pokémon OVERPOWERED, digite novamente um número entre 0 e 300: ");
        scanf("%d", &pokemon->defSpec);
    }
    printf("Digite a velocidade do pokémon a ser inserido:");
    scanf("%d", &pokemon->velocidade);
    while(pokemon->velocidade > 300){
        printf("O valor digitado torna seu pokémon OVERPOWERED, digite novamente um número entre 0 e 300: ");
        scanf("%d", &pokemon->velocidade);
    }
    pokemon->statusTotal = pokemon->hp + pokemon->ataque + pokemon->defesa + pokemon->atqSpec + pokemon->defSpec + pokemon->velocidade;
    pokemon->geracao = 9;
    pokemon->lendario = 0;
    printf("Digite a cor do pokémon a ser inserido:");
    scanf("%s", pokemon->cor);
    printf("Digite a altura do pokémon a ser inserido:");
    scanf("%f", &pokemon->altura);
    printf("Digite o peso do pokémon a ser inserido:");
    scanf("%f", &pokemon->peso);
    printf("Digite a taxa de captura do pokémon a ser inserido:");
    scanf("%d", &pokemon->taxadeCap);
    while(pokemon->taxadeCap >= 255 && pokemon->taxadeCap <= 0){
        printf("O valor digitado é inválido digite entre 0 a 255: ");
        scanf("%d", &pokemon->taxadeCap);
    }
    fprintf(arquivo, "\n%6d ,%11s ,%8s ,%8s ,%6d ,%4d ,%6d ,%6d ,%15d ,%15d ,%10d ,%7d ,%8d ,%7s ,%8f ,%7f ,%12d", pokemon->numero, pokemon->nome, pokemon->tipoUm, pokemon->tipoDois, pokemon->statusTotal, pokemon->hp, pokemon->ataque, pokemon->defesa, pokemon->atqSpec, pokemon->defSpec, pokemon->velocidade, pokemon->geracao, pokemon->lendario, pokemon->cor, pokemon->altura, pokemon->peso, pokemon->taxadeCap);
       
    fclose(arquivo);
} 

void pesquisar(Pokemon *pokemon){
    
    FILE *arquivo = fopen("pokedex.csv", "r");
    if(arquivo == NULL){
        printf("Falha ao abrir o arquivo.\n");
        exit(EXIT_FAILURE);
    }
    char pokemonPesquisado[30]; //Variável que será utilizada para inserir o nome do pokémon pesquisado
    int verificador = 0;  //Variável contadora para verificar se o pokémon está ou não registrado

    printf("Digite o nome do pokémon que você deseja pesquisar: ");
    scanf("%s", pokemonPesquisado);
    
   fscanf(arquivo, "%*[^\n]\n"); 
   while (fscanf(arquivo, "%d ,%s ,%s ,%s ,%d ,%d ,%d ,%d ,%d ,%d ,%d ,%d ,%d ,%s ,%f ,%f ,%d", &pokemon->numero, pokemon->nome, pokemon->tipoUm, pokemon->tipoDois, &pokemon->statusTotal, &pokemon->hp, &pokemon->ataque, &pokemon->defesa, &pokemon->atqSpec, &pokemon->defSpec, &pokemon->velocidade, &pokemon->geracao, &pokemon->lendario, pokemon->cor, &pokemon->altura, &pokemon->peso, &pokemon->taxadeCap) != EOF){
       if(strcmp(pokemon->nome, pokemonPesquisado) == 0){
            verificador = 1;
            break;
        } 
    }

    if(verificador){
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
    
    fclose(arquivo);
}

void excluir(Pokemon *pokemon){
    FILE *arquivoOriginal = fopen("pokedex.csv", "r");
    if(arquivoOriginal == NULL){
        printf("Falha ao abrir o arquivo.\n");
        exit(EXIT_FAILURE);
    } 

    FILE *arquivoTemporario = fopen("pokedextemp.csv", "w");
    if(arquivoTemporario == NULL){
        printf("Falha ao abrir o arquivo.\n");
        fclose(arquivoOriginal);
        exit(EXIT_FAILURE);
    }

    int pokemonRemovido;
    printf("Digite o número do pokémon a ser removido: ");
    scanf("%d", &pokemonRemovido);

    while (fscanf(arquivoOriginal, "%d ,%s ,%s ,%s ,%d ,%d ,%d ,%d ,%d ,%d ,%d ,%d ,%d ,%s ,%f ,%f ,%d", &pokemon->numero, pokemon->nome, pokemon->tipoUm, pokemon->tipoDois, &pokemon->statusTotal, &pokemon->hp, &pokemon->ataque, &pokemon->defesa, &pokemon->atqSpec, &pokemon->defSpec, &pokemon->velocidade, &pokemon->geracao, &pokemon->lendario, pokemon->cor, &pokemon->altura, &pokemon->peso, &pokemon->taxadeCap) != EOF){
        if(pokemon->numero != pokemonRemovido){
            fscanf(arquivoOriginal, "%*[^\n]\n");
        }
    }

    fclose(arquivoOriginal);
    fclose(arquivoTemporario);

    if (remove("pokedex.csv") == 0) {
        if (rename("pokedextemp.csv", "pokedex.csv") != 0) {
            printf("Failed to rename the temporary file.\n"); }
    } else {
        printf("Failed to remove the original file.\n");
    }

}

void alterar(Pokemon *pokemon) {
    FILE *arquivoOriginal = fopen("pokedex.csv", "r");
    if (arquivoOriginal == NULL) {
        printf("Erro ao abrir arquivo!\n");
        exit(1);
    }

    FILE *arquivoTemporario = fopen("pokedextemp.csv", "w");
    if (arquivoTemporario == NULL) {
        printf("Erro ao abrir arquivo!\n");
        exit(1);
    }

    int pokemonDesejado;
    printf("Digite o número do pokémon que você deseja alterar: ");
    scanf("%d", &pokemonDesejado);

    while (fscanf(arquivoOriginal, "%d ,%s ,%s ,%s ,%d ,%d ,%d ,%d ,%d ,%d ,%d ,%d ,%d ,%s ,%f ,%f ,%d",
                  &pokemon->numero, pokemon->nome, pokemon->tipoUm, pokemon->tipoDois, &pokemon->statusTotal,
                  &pokemon->hp, &pokemon->ataque, &pokemon->defesa, &pokemon->atqSpec, &pokemon->defSpec,
                  &pokemon->velocidade, &pokemon->geracao, &pokemon->lendario, pokemon->cor,
                  &pokemon->altura, &pokemon->peso, &pokemon->taxadeCap) != EOF) {
        fscanf(arquivoOriginal, "%*[^\n]\n");

        if (pokemon->numero == pokemonDesejado) {
            pokemon->numero = pokemon->numero;
            printf("Digite o nome do pokémon: ");
            scanf("%s", &pokemon->nome);
            printf("Digite o primeiro tipo do pokémon: ");
            scanf("%s", &pokemon->tipoUm);
            printf("Digite segundo do pokémon: ");
            scanf("%s", &pokemon->tipoDois);
            printf("Digite o HP do pokémon: ");
            scanf("%d", pokemon->hp);
            printf("Digite o ATAQUE do pokémon: ");
            scanf("%d", pokemon->ataque);
            printf("Digite a DEFESA do pokémon: ");
            scanf("%d", pokemon->defesa);
            printf("Digite o ATAQUE ESPECIAL do pokémon: ");
            scanf("%d", pokemon->atqSpec);
            printf("Digite o DEFESA ESPECIAL do pokémon: ");
            scanf("%d", pokemon->defSpec);
            printf("Digite o HP do pokémon: ");
            scanf("%d", pokemon->velocidade);
            pokemon->geracao = 10;
            pokemon->lendario = 0;
            printf("Digite a cor do pokémon: ");
            scanf("%d", &pokemon->cor);
            pokemon->altura = 1.79;
            pokemon->peso = 80;
            pokemon->taxadeCap = 100;

            fprintf(arquivoTemporario, "%d ,%s ,%s ,%s ,%d ,%d ,%d ,%d ,%d ,%d ,%d ,%d ,%d ,%s ,%.2f ,%.2f ,%d\n",
                    pokemon->numero, pokemon->nome, pokemon->tipoUm, pokemon->tipoDois, pokemon->statusTotal,
                    pokemon->hp, pokemon->ataque, pokemon->defesa, pokemon->atqSpec, pokemon->defSpec,
                    pokemon->velocidade, pokemon->geracao, pokemon->lendario, pokemon->cor,
                    pokemon->altura, pokemon->peso, pokemon->taxadeCap);
        } else {
            fprintf(arquivoTemporario, "%d ,%s ,%s ,%s ,%d ,%d ,%d ,%d ,%d ,%d ,%d ,%d ,%d ,%s ,%.2f ,%.2f ,%d\n",
                    pokemon->numero, pokemon->nome, pokemon->tipoUm, pokemon->tipoDois, pokemon->statusTotal,
                    pokemon->hp, pokemon->ataque, pokemon->defesa, pokemon->atqSpec, pokemon->defSpec,
                    pokemon->velocidade, pokemon->geracao, pokemon->lendario, pokemon->cor,
                    pokemon->altura, pokemon->peso, pokemon->taxadeCap);
        }
    }

    fclose(arquivoOriginal);
    fclose(arquivoTemporario);

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
    inserir(&pokemon);
    break;

    case 3:
    excluir(&pokemon);
    break;

    case 4:
    pesquisar(&pokemon);
    break;

    case 5:
    alterar(&pokemon);
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
