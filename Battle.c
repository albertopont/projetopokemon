#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_POKEMONS 721
#define TAMANHO_MAX_LINHA 1024

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

////////////////////////////////////////// VINCULA A STRUCT COM A ARQUIVO //////////////////////////////////////////////////////////////

void Vincular_Pokedex_Struct(Pokemon pokedex[], char *arquivoPokedex) {
    FILE *file = fopen(arquivoPokedex, "r");

    if (file == NULL) {
        printf("\nNão foi possível abrir o arquivo.\n");
        exit(1);
    }

    char linha[TAMANHO_MAX_LINHA];
    int linhaAtual = 0;

    while (fgets(linha, sizeof(linha), file)) {
        if (linhaAtual == 0) {
            // Ignora a primeira linha de cabeçalho.
            linhaAtual++;
            continue;
        }

        char *token;
        int col = 0;
        token = strtok(linha, ",");

        while (token != NULL) {
            // Remover espaços em branco no início e no final da string
            char *trimmed = token;
            while (*trimmed == ' ' || *trimmed == '\t') {
                trimmed++;
            }

            size_t len = strlen(trimmed);
            while (len > 0 && (trimmed[len - 1] == ' ' || trimmed[len - 1] == '\t' || trimmed[len - 1] == '\n')) {
                trimmed[--len] = '\0';
            }

            switch (col) {
                case 0:
                    pokedex[linhaAtual - 1].numero = atoi(trimmed);
                    break;
                case 1:
                    strncpy(pokedex[linhaAtual - 1].nome, trimmed, sizeof(pokedex[linhaAtual - 1].nome));
                    break;
                case 2:
                    strncpy(pokedex[linhaAtual - 1].tipoUm, trimmed, sizeof(pokedex[linhaAtual - 1].tipoUm));
                    break;
                case 3:
                    strncpy(pokedex[linhaAtual - 1].tipoDois, trimmed, sizeof(pokedex[linhaAtual - 1].tipoDois));
                    break;
                case 4:
                    pokedex[linhaAtual - 1].statusTotal = atoi(trimmed);
                    break;
                case 5:
                    pokedex[linhaAtual - 1].hp = atoi(trimmed);
                    break;
                case 6:
                    pokedex[linhaAtual - 1].ataque = atoi(trimmed);
                    break;
                case 7:
                    pokedex[linhaAtual - 1].defesa = atoi(trimmed);
                    break;
                case 8:
                    pokedex[linhaAtual - 1].atqSpec = atoi(trimmed);
                    break;
                case 9:
                    pokedex[linhaAtual - 1].defSpec = atoi(trimmed);
                    break;
                case 10:
                    pokedex[linhaAtual - 1].velocidade = atoi(trimmed);
                    break;
                case 11:
                    pokedex[linhaAtual - 1].geracao = atoi(trimmed);
                    break;
                case 12:
                    pokedex[linhaAtual - 1].lendario = atoi(trimmed);
                    break;
                case 13:
                    strncpy(pokedex[linhaAtual - 1].cor, trimmed, sizeof(pokedex[linhaAtual - 1].cor));
                    break;
                case 14:
                    pokedex[linhaAtual - 1].altura = atof(trimmed);
                    break;
                case 15:
                    pokedex[linhaAtual - 1].peso = atof(trimmed);
                    break;
                case 16:
                    pokedex[linhaAtual - 1].taxadeCap = atoi(trimmed);
                    break;
                case 17:
                    pokedex[linhaAtual - 1].evolucao = atoi(trimmed);
                    break;
                case 18:
                    pokedex[linhaAtual - 1].preEvolucao = atoi(trimmed);
                    break;
            }

            token = strtok(NULL, ",");
            col++;
        }

        linhaAtual++;
    }

    fclose(file);
}

///////////////////////////////////////////////// FUNCAO PARA CALCULAR A EFETIVIDADE DO ATCK ////////////////////////////////////////

int CalculaEficaciaAtack(Pokemon pokedex[], int NumeroPokemon1, int NumeroPokemon2){

    int Imunidade = 0;
    int Nao_Eficaz_Especial = 100;
    int Nao_Eficaz_Normal = 150;
    int Eficaz = 200;
    int Super_Eficaz_Normal = 300;
    int Hiper_Eficaz_Especial = 500;
    int Vantagens=0;
    int Desvantagens=0;

    ////////////////////////////////////////////////      VANTAGENS    ///////////////////////////////////////////////////////////

    if ((strcmp(pokedex[NumeroPokemon1].tipoUm, "Planta") == 0 || strcmp(pokedex[NumeroPokemon1].tipoDois, "Planta") == 0) &&
    (strcmp(pokedex[NumeroPokemon2].tipoUm, "Terra") == 0 || strcmp(pokedex[NumeroPokemon2].tipoUm, "Pedra") == 0 || strcmp(pokedex[NumeroPokemon2].tipoUm, "Water") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Terra") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Pedra") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Water") == 0)) {

    Vantagens++;

    }

    if ((strcmp(pokedex[NumeroPokemon1].tipoUm, "Fire") == 0 || strcmp(pokedex[NumeroPokemon1].tipoDois, "Fire") == 0) &&
    (strcmp(pokedex[NumeroPokemon2].tipoUm, "Bug") == 0 || strcmp(pokedex[NumeroPokemon2].tipoUm, "Planta") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoUm, "Gelo") == 0 || strcmp(pokedex[NumeroPokemon2].tipoUm, "Aço") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Bug") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Planta") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Gelo") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Aço") == 0)) {
 
    Vantagens++;
 
    }   

    if ((strcmp(pokedex[NumeroPokemon1].tipoUm, "Water") == 0 || strcmp(pokedex[NumeroPokemon1].tipoDois, "Water") == 0) &&
    (strcmp(pokedex[NumeroPokemon2].tipoUm, "Fogo") == 0 || strcmp(pokedex[NumeroPokemon2].tipoUm, "Terra") == 0 || strcmp(pokedex[NumeroPokemon2].tipoUm, "Pedra") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Fogo") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Terra") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Pedra") == 0)) {
 
    Vantagens++;
 
    }

    if ((strcmp(pokedex[NumeroPokemon1].tipoUm, "Electric") == 0 || strcmp(pokedex[NumeroPokemon1].tipoDois, "Electric") == 0) &&
    (strcmp(pokedex[NumeroPokemon2].tipoUm, "Water") == 0 || strcmp(pokedex[NumeroPokemon2].tipoUm, "Voador") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Water") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Voador") == 0)) {
   
    Vantagens++;

    }

    if ((strcmp(pokedex[NumeroPokemon1].tipoUm, "Voador") == 0 || strcmp(pokedex[NumeroPokemon1].tipoDois, "Voador") == 0) &&
    (strcmp(pokedex[NumeroPokemon2].tipoUm, "Inseto") == 0 || strcmp(pokedex[NumeroPokemon2].tipoUm, "Lutador") == 0 || strcmp(pokedex[NumeroPokemon2].tipoUm, "Planta") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Inseto") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Lutador") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Planta") == 0)) {
   
    Vantagens++;
   
    }

    if ((strcmp(pokedex[NumeroPokemon1].tipoUm, "Gelo") == 0 || strcmp(pokedex[NumeroPokemon1].tipoDois, "Gelo") == 0) &&
    (strcmp(pokedex[NumeroPokemon2].tipoUm, "Dragon") == 0 || strcmp(pokedex[NumeroPokemon2].tipoUm, "Voador") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoUm, "Planta") == 0 || strcmp(pokedex[NumeroPokemon2].tipoUm, "Terra") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Dragon") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Voador") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Planta") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Terra") == 0)) {
   
    Vantagens++;

    }

    if ((strcmp(pokedex[NumeroPokemon1].tipoUm, "Pedra") == 0 || strcmp(pokedex[NumeroPokemon1].tipoDois, "Pedra") == 0) &&
    (strcmp(pokedex[NumeroPokemon2].tipoUm, "Inseto") == 0 || strcmp(pokedex[NumeroPokemon2].tipoUm, "Fogo") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoUm, "Voador") == 0 || strcmp(pokedex[NumeroPokemon2].tipoUm, "Gelo") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Inseto") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Fogo") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Voador") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Gelo") == 0)) {
   
    Vantagens++;

    }

    if ((strcmp(pokedex[NumeroPokemon1].tipoUm, "Terra") == 0 || strcmp(pokedex[NumeroPokemon1].tipoDois, "Terra") == 0) &&
    (strcmp(pokedex[NumeroPokemon2].tipoUm, "Eletric") == 0 || strcmp(pokedex[NumeroPokemon2].tipoUm, "Fire") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoUm, "Venenoso") == 0 || strcmp(pokedex[NumeroPokemon2].tipoUm, "Pedra") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoUm, "Aço") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Eletric") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Fire") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Venenoso") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Pedra") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Aço") == 0)) {

    Vantagens++;

    }

    if ((strcmp(pokedex[NumeroPokemon1].tipoUm, "Aço") == 0 || strcmp(pokedex[NumeroPokemon1].tipoDois, "Aço") == 0) &&
    (strcmp(pokedex[NumeroPokemon2].tipoUm, "Fada") == 0 || strcmp(pokedex[NumeroPokemon2].tipoUm, "Gelo") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoUm, "Pedra") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Fada") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Gelo") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Pedra") == 0)) {

    Vantagens++;

    }

    if ((strcmp(pokedex[NumeroPokemon1].tipoUm, "Sombrio") == 0 || strcmp(pokedex[NumeroPokemon1].tipoDois, "Sombrio") == 0) &&
    (strcmp(pokedex[NumeroPokemon2].tipoUm, "Ghost") == 0 || strcmp(pokedex[NumeroPokemon2].tipoUm, "Psychic") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Ghost") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Psychic") == 0)) {
   
    Vantagens++;

    }

    if ((strcmp(pokedex[NumeroPokemon1].tipoUm, "Psychic") == 0 || strcmp(pokedex[NumeroPokemon1].tipoDois, "Psychic") == 0) &&
    (strcmp(pokedex[NumeroPokemon2].tipoUm, "Lutador") == 0 || strcmp(pokedex[NumeroPokemon2].tipoUm, "Venenoso") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Lutador") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Venenoso") == 0)) {
 
    Vantagens++;
 
    }

    if ((strcmp(pokedex[NumeroPokemon1].tipoUm, "Venenoso") == 0 || strcmp(pokedex[NumeroPokemon1].tipoDois, "Venenoso") == 0) &&
    (strcmp(pokedex[NumeroPokemon2].tipoUm, "Fada") == 0 || strcmp(pokedex[NumeroPokemon2].tipoUm, "Planta") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Fada") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Planta") == 0)) {
    
    Vantagens++;
   
    }

    if ((strcmp(pokedex[NumeroPokemon1].tipoUm, "Bug") == 0 || strcmp(pokedex[NumeroPokemon1].tipoDois, "Bug") == 0) &&
    (strcmp(pokedex[NumeroPokemon2].tipoUm, "Sombrio") == 0 || strcmp(pokedex[NumeroPokemon2].tipoUm, "Planta") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoUm, "Psychic") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Sombrio") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Planta") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Psychic") == 0)) {
    
    Vantagens++;

    }

    if ((strcmp(pokedex[NumeroPokemon1].tipoUm, "Fada") == 0 || strcmp(pokedex[NumeroPokemon1].tipoDois, "Fada") == 0) &&
    (strcmp(pokedex[NumeroPokemon2].tipoUm, "Sombrio") == 0 || strcmp(pokedex[NumeroPokemon2].tipoUm, "Dragão") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoUm, "Lutador") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Sombrio") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Dragão") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Lutador") == 0)) {

    Vantagens++;

    }

    if ((strcmp(pokedex[NumeroPokemon1].tipoUm, "Ghost") == 0 || strcmp(pokedex[NumeroPokemon1].tipoDois, "Ghost") == 0) &&
    (strcmp(pokedex[NumeroPokemon2].tipoUm, "Ghost") == 0 || strcmp(pokedex[NumeroPokemon2].tipoUm, "Psychic") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Ghost") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Psychic") == 0)) {

    Vantagens++;

    }

    if ((strcmp(pokedex[NumeroPokemon1].tipoUm, "Dragon") == 0 || strcmp(pokedex[NumeroPokemon1].tipoDois, "Dragon") == 0) &&
    (strcmp(pokedex[NumeroPokemon2].tipoUm, "Dragon") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Dragon") == 0)) {
    
    Vantagens++;
  
    }

    ///////////////////////////////////////// DESVANTAGENS //////////////////////////////////////////////////////////////

    if ((strcmp(pokedex[NumeroPokemon1].tipoUm, "Normal") == 0 || strcmp(pokedex[NumeroPokemon1].tipoDois, "Normal") == 0) &&
    (strcmp(pokedex[NumeroPokemon2].tipoUm, "Lutador") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Lutador") == 0)) {

    Desvantagens++;

    }

    if ((strcmp(pokedex[NumeroPokemon1].tipoUm, "Planta") == 0 || strcmp(pokedex[NumeroPokemon1].tipoDois, "Planta") == 0) &&
        (strcmp(pokedex[NumeroPokemon2].tipoUm, "Bug") == 0 || strcmp(pokedex[NumeroPokemon2].tipoUm, "Fire") == 0 || strcmp(pokedex[NumeroPokemon2].tipoUm, "Voador") == 0 ||
        strcmp(pokedex[NumeroPokemon2].tipoUm, "Gelo") == 0 || strcmp(pokedex[NumeroPokemon2].tipoUm, "Venenoso") == 0 ||
        strcmp(pokedex[NumeroPokemon2].tipoDois, "Bug") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Fire") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Voador") == 0 ||
        strcmp(pokedex[NumeroPokemon2].tipoDois, "Gelo") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Venenoso") == 0)) {

        Desvantagens++;
    }

    if ((strcmp(pokedex[NumeroPokemon1].tipoUm, "Fire") == 0 || strcmp(pokedex[NumeroPokemon1].tipoDois, "Fire") == 0) &&
        (strcmp(pokedex[NumeroPokemon2].tipoUm, "Pedra") == 0 || strcmp(pokedex[NumeroPokemon2].tipoUm, "Terra") == 0 || strcmp(pokedex[NumeroPokemon2].tipoUm, "Water") == 0 ||
        strcmp(pokedex[NumeroPokemon2].tipoDois, "Pedra") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Terra") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Water") == 0)) {
        
        Desvantagens++;
    }

    if ((strcmp(pokedex[NumeroPokemon1].tipoUm, "Water") == 0 || strcmp(pokedex[NumeroPokemon1].tipoDois, "Water") == 0) &&
    (strcmp(pokedex[NumeroPokemon2].tipoUm, "Eletric") == 0 || strcmp(pokedex[NumeroPokemon2].tipoUm, "Planta") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Eletric") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Planta") == 0)) {
   
        Desvantagens++;
    }

    if ((strcmp(pokedex[NumeroPokemon1].tipoUm, "Eletric") == 0 || strcmp(pokedex[NumeroPokemon1].tipoDois, "Eletric") == 0) &&
    (strcmp(pokedex[NumeroPokemon2].tipoUm, "Terra") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Terra") == 0)) {

        Desvantagens++;
    }

    if ((strcmp(pokedex[NumeroPokemon1].tipoUm, "Voador") == 0 || strcmp(pokedex[NumeroPokemon1].tipoDois, "Voador") == 0) &&
    (strcmp(pokedex[NumeroPokemon2].tipoUm, "Eletric") == 0 || strcmp(pokedex[NumeroPokemon2].tipoUm, "Gelo") == 0 || strcmp(pokedex[NumeroPokemon2].tipoUm, "Pedra") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Eletric") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Gelo") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Pedra") == 0)) {
       
        Desvantagens++;
    }

    if ((strcmp(pokedex[NumeroPokemon1].tipoUm, "Gelo") == 0 || strcmp(pokedex[NumeroPokemon1].tipoDois, "Gelo") == 0) &&
    (strcmp(pokedex[NumeroPokemon2].tipoUm, "Lutador") == 0 || strcmp(pokedex[NumeroPokemon2].tipoUm, "Fire") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoUm, "Pedra") == 0 || strcmp(pokedex[NumeroPokemon2].tipoUm, "Aço") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Lutador") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Fire") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Pedra") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Aço") == 0)) {
    
        Desvantagens++;
    }

    if ((strcmp(pokedex[NumeroPokemon1].tipoUm, "Pedra") == 0 || strcmp(pokedex[NumeroPokemon1].tipoDois, "Pedra") == 0) &&
    (strcmp(pokedex[NumeroPokemon2].tipoUm, "Lutador") == 0 || strcmp(pokedex[NumeroPokemon2].tipoUm, "Planta") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoUm, "Terra") == 0 || strcmp(pokedex[NumeroPokemon2].tipoUm, "Aço") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoUm, "Water") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Lutador") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Planta") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Terra") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Aço") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Water") == 0)) {
   
        Desvantagens++;
    }

    if ((strcmp(pokedex[NumeroPokemon1].tipoUm, "Terra") == 0 || strcmp(pokedex[NumeroPokemon1].tipoDois, "Terra") == 0) &&
    (strcmp(pokedex[NumeroPokemon2].tipoUm, "Gelo") == 0 || strcmp(pokedex[NumeroPokemon2].tipoUm, "Planta") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoUm, "Water") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Gelo") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Planta") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Water") == 0)) {
        
        Desvantagens++;
    }

    if ((strcmp(pokedex[NumeroPokemon1].tipoUm, "Aço") == 0 || strcmp(pokedex[NumeroPokemon1].tipoDois, "Aço") == 0) &&
    (strcmp(pokedex[NumeroPokemon2].tipoUm, "Lutador") == 0 || strcmp(pokedex[NumeroPokemon2].tipoUm, "Fire") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoUm, "Terra") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Lutador") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Fire") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Terra") == 0)) {

        Desvantagens++;
    }

    if ((strcmp(pokedex[NumeroPokemon1].tipoUm, "Lutador") == 0 || strcmp(pokedex[NumeroPokemon1].tipoDois, "Lutador") == 0) &&
    (strcmp(pokedex[NumeroPokemon2].tipoUm, "Fada") == 0 || strcmp(pokedex[NumeroPokemon2].tipoUm, "Voador") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoUm, "Psychic") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Fada") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Voador") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Psychic") == 0)) {
        
        Desvantagens++;
    
    }

    if ((strcmp(pokedex[NumeroPokemon1].tipoUm, "Sombrio") == 0 || strcmp(pokedex[NumeroPokemon1].tipoDois, "Sombrio") == 0) &&
    (strcmp(pokedex[NumeroPokemon2].tipoUm, "Bug") == 0 || strcmp(pokedex[NumeroPokemon2].tipoUm, "Fada") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoUm, "Lutador") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Bug") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Fada") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Lutador") == 0)) {

    Desvantagens++;

    }

    if ((strcmp(pokedex[NumeroPokemon1].tipoUm, "Psychic") == 0 || strcmp(pokedex[NumeroPokemon1].tipoDois, "Psychic") == 0) &&
    (strcmp(pokedex[NumeroPokemon2].tipoUm, "Bug") == 0 || strcmp(pokedex[NumeroPokemon2].tipoUm, "Sombrio") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoUm, "Ghost") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Bug") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Sombrio") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Ghost") == 0)) {

    Desvantagens++;

    }

    if ((strcmp(pokedex[NumeroPokemon1].tipoUm, "Venenoso") == 0 || strcmp(pokedex[NumeroPokemon1].tipoDois, "Venenoso") == 0) &&
    (strcmp(pokedex[NumeroPokemon2].tipoUm, "Terra") == 0 || strcmp(pokedex[NumeroPokemon2].tipoUm, "Psychic") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Terra") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Psychic") == 0)) {
    
    Desvantagens++;

    }

    if ((strcmp(pokedex[NumeroPokemon1].tipoUm, "Bug") == 0 || strcmp(pokedex[NumeroPokemon1].tipoDois, "Bug") == 0) &&
    (strcmp(pokedex[NumeroPokemon2].tipoUm, "Fire") == 0 || strcmp(pokedex[NumeroPokemon2].tipoUm, "Voador") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoUm, "Pedra") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Fire") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Voador") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Pedra") == 0)) {
    
        Desvantagens++;
    }

    if ((strcmp(pokedex[NumeroPokemon1].tipoUm, "Fada") == 0 || strcmp(pokedex[NumeroPokemon1].tipoDois, "Fada") == 0) &&
    (strcmp(pokedex[NumeroPokemon2].tipoUm, "Aço") == 0 || strcmp(pokedex[NumeroPokemon2].tipoUm, "Venenoso") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Aço") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Venenoso") == 0)) {
        
        Desvantagens++;
    }

    if ((strcmp(pokedex[NumeroPokemon1].tipoUm, "Ghost") == 0 || strcmp(pokedex[NumeroPokemon1].tipoDois, "Ghost") == 0) &&
    (strcmp(pokedex[NumeroPokemon2].tipoUm, "Ghost") == 0 || strcmp(pokedex[NumeroPokemon2].tipoUm, "Sombrio") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Ghost") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Sombrio") == 0)) {
        
        Desvantagens++;
    }

    if ((strcmp(pokedex[NumeroPokemon1].tipoUm, "Dragon") == 0 || strcmp(pokedex[NumeroPokemon1].tipoDois, "Dragon") == 0) &&
    (strcmp(pokedex[NumeroPokemon2].tipoUm, "Dragon") == 0 || strcmp(pokedex[NumeroPokemon2].tipoUm, "Fada") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoUm, "Gelo") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Dragon") == 0 || strcmp(pokedex[NumeroPokemon2].tipoDois, "Fada") == 0 ||
     strcmp(pokedex[NumeroPokemon2].tipoDois, "Gelo") == 0)) {
        
        Desvantagens++;

    }

                ///////////////////////////////// IMUNIDADE ////////////////////////////////////

        if(strcmp(pokedex[NumeroPokemon1].tipoUm, "Normal") == 0 && strcmp(pokedex[NumeroPokemon2].tipoUm, "Ghost")==0 ){

            return Imunidade;

        }else{
            if(strcmp(pokedex[NumeroPokemon1].tipoUm, "Lutador")==0 && strcmp(pokedex[NumeroPokemon2].tipoUm, "Ghost")==0){

                return Imunidade;

            }else{
                if(strcmp(pokedex[NumeroPokemon1].tipoUm, "Venenoso")==0 && strcmp(pokedex[NumeroPokemon2].tipoUm, "Aço")==0){

                    return Imunidade;

                }else{
                    if(strcmp(pokedex[NumeroPokemon1].tipoUm, "Terra")==0 && strcmp(pokedex[NumeroPokemon2].tipoUm, "Voador")==0){

                        return Imunidade;

                    }else{
                        if(strcmp(pokedex[NumeroPokemon1].tipoUm, "Ghost")==0 && strcmp(pokedex[NumeroPokemon2].tipoUm, "Normal")==0){

                            return Imunidade;

                        }else{
                            if(strcmp(pokedex[NumeroPokemon1].tipoUm, "Eletric")==0 && strcmp(pokedex[NumeroPokemon2].tipoUm, "Terra")==0){

                                return Imunidade;

                            }else{
                                if(strcmp(pokedex[NumeroPokemon1].tipoUm, "Psychic")==0 && strcmp(pokedex[NumeroPokemon2].tipoUm, "Sombrio")==0){

                                    return Imunidade;

                                }else{
                                    if(strcmp(pokedex[NumeroPokemon1].tipoUm,"Dragon")==0 && strcmp(pokedex[NumeroPokemon2].tipoUm, "Fada")==0 ){

                                        return Imunidade;

                                    }else{
                                        if(Vantagens == Desvantagens){

                                            return Eficaz;

                                        }else{
                                            if(Vantagens-Desvantagens>=1){

                                                return Super_Eficaz_Normal;

                                            }else{
                                                if(Vantagens-Desvantagens>=2){

                                                    return Hiper_Eficaz_Especial;

                                                }else{
                                                    if(Desvantagens-Vantagens>=1){

                                                        return Nao_Eficaz_Normal;

                                                    }else{
                                                        if(Desvantagens-Vantagens>=2){

                                                            return Nao_Eficaz_Especial;
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }



    return 0;

}



/////////////////////////////////////////////////// FUNCAO PARA A BATALHA ////////////////////////////////////////////////////////////////

void BatalhaPokemon(Pokemon pokedex[], int NumeroPokemon1, int NumeroPokemon2, int NivelPokemon1, int NivelPokemon2) {

    int Pokemon_Velocidade_Maior;
    int Pokemon_Velocidade_Menor;
    int HP_Pokemon_Velocidade_Maior;
    int HP_Pokemon_Velocidade_Menor;
    int Nivel_Pokemon_Velocidade_Maior;
    int Nivel_Pokemon_Velocidade_Menor;

    int Taxa_Eficacia_Atck;


    printf("\nBATALHA!\n");
    printf("%s VS %s\n", pokedex[NumeroPokemon1].nome, pokedex[NumeroPokemon2].nome);

    if (pokedex[NumeroPokemon1].velocidade > pokedex[NumeroPokemon2].velocidade) {

        printf("%s COMEÇA ATACANDO!\n", pokedex[NumeroPokemon1].nome);

        Pokemon_Velocidade_Maior = NumeroPokemon1;
        Pokemon_Velocidade_Menor = NumeroPokemon2;

        HP_Pokemon_Velocidade_Maior = pokedex[NumeroPokemon1].hp;
        HP_Pokemon_Velocidade_Menor = pokedex[NumeroPokemon2].hp;

        Nivel_Pokemon_Velocidade_Maior = NivelPokemon1;
        Nivel_Pokemon_Velocidade_Menor = NivelPokemon2;

    } else {
        printf("%s COMEÇA ATACANDO!\n", pokedex[NumeroPokemon2].nome);

        Pokemon_Velocidade_Maior = NumeroPokemon2;
        Pokemon_Velocidade_Menor = NumeroPokemon1;

        HP_Pokemon_Velocidade_Maior = pokedex[NumeroPokemon2].hp;
        HP_Pokemon_Velocidade_Menor = pokedex[NumeroPokemon1].hp;

        Nivel_Pokemon_Velocidade_Maior = NivelPokemon2;
        Nivel_Pokemon_Velocidade_Menor = NivelPokemon1;

    }

    while (HP_Pokemon_Velocidade_Maior > 0 && HP_Pokemon_Velocidade_Menor > 0) {

        int ataque, defesa;
        int escolhaAtaque;
        int dano;

        printf("\n%s ATACA\n",pokedex[Pokemon_Velocidade_Maior].nome);

        do {
            printf("Escolha o tipo de ataque (1 para normal, 2 para especial): ");
            scanf("%d", &escolhaAtaque);

            if (escolhaAtaque == 1) {
                ataque = pokedex[Pokemon_Velocidade_Maior].ataque;
                defesa = pokedex[Pokemon_Velocidade_Menor].defesa;
            } else if (escolhaAtaque == 2) {
                ataque = pokedex[Pokemon_Velocidade_Maior].atqSpec;
                defesa = pokedex[Pokemon_Velocidade_Menor].defSpec;
            } else {
                printf("Opção Inválida!\n");
            }
        } while (escolhaAtaque < 1 || escolhaAtaque > 2);

        /////////////////////////// CALCULO DO DANO POKEMON COM VELOCIDADE MAIOR //////////////////////////////////////


        Taxa_Eficacia_Atck = CalculaEficaciaAtack(pokedex,Pokemon_Velocidade_Maior,Pokemon_Velocidade_Menor);

        dano = (((2 * Nivel_Pokemon_Velocidade_Maior + 10) / 250.0) * ((float)ataque / defesa)) * Taxa_Eficacia_Atck;

        if(ataque==pokedex[Pokemon_Velocidade_Maior].atqSpec){

            dano += 5;
        }

        HP_Pokemon_Velocidade_Menor -= dano;


        ///////////////////////////////////////EXIBE A EFICACIA DO ATCK //////////////////////////////////

        if(Taxa_Eficacia_Atck==0){

            printf("\n%s POSSUI IMUNIDADE AO SEU ATAQUE!\n",pokedex[Pokemon_Velocidade_Menor].nome);

        }else{

            if(Taxa_Eficacia_Atck == 100){

                printf("\nATAQUE NÃO EFICAZ!\n");

            }else{
                if(Taxa_Eficacia_Atck==150){

                    printf("\nATAQUE NÃO MUITO EFICAZ!\n");

                }else{
                    if(Taxa_Eficacia_Atck==200){
                        
                    printf("\nATAQUE EFICAZ!\n");

                    }else{
                        if(Taxa_Eficacia_Atck==300){

                        printf("\nATAQUE SUPER EFICAZ!\n");

                        }else{
                            if(Taxa_Eficacia_Atck==500){

                            printf("\nATAQUE HIPER EFICAZ!\n");

                            }
                        }
                    }
                }
                    
            }
        }

        printf("%s ataca %s e causa %d de dano!\n", pokedex[Pokemon_Velocidade_Maior].nome, pokedex[Pokemon_Velocidade_Menor].nome, dano);

        if (HP_Pokemon_Velocidade_Menor <= 0) {
            printf("%s Perdeu!\n", pokedex[Pokemon_Velocidade_Menor].nome);
            break;
        }

        printf("%s tem %d HP restantes.\n", pokedex[Pokemon_Velocidade_Menor].nome, HP_Pokemon_Velocidade_Menor);

        ///////////////////// TURNO DO POKEMON COM VELOCIDADE MENOR //////////////////////////////////

        printf("\n%s ATACA\n",pokedex[Pokemon_Velocidade_Menor].nome);

        do {
            printf("Escolha o tipo de ataque (1 para normal, 2 para especial): ");
            scanf("%d", &escolhaAtaque);

            if (escolhaAtaque == 1) {
                ataque = pokedex[Pokemon_Velocidade_Menor].ataque;
                defesa = pokedex[Pokemon_Velocidade_Maior].defesa;
            } else if (escolhaAtaque == 2) {
                ataque = pokedex[Pokemon_Velocidade_Menor].atqSpec;
                defesa = pokedex[Pokemon_Velocidade_Maior].defSpec;
            } else {
                printf("Opção Inválida!\n");
            }
        } while (escolhaAtaque < 1 || escolhaAtaque > 2);

        //////////////////////////////////////// DANO POKEMON VELOCIDADE MENOR /////////////////////////////////////////

        Taxa_Eficacia_Atck = CalculaEficaciaAtack(pokedex,Pokemon_Velocidade_Menor,Pokemon_Velocidade_Maior);

        dano = (((2 * Nivel_Pokemon_Velocidade_Menor + 10) / 250.0) * ((float)ataque / defesa)) * Taxa_Eficacia_Atck;

        if(ataque==pokedex[Pokemon_Velocidade_Menor].atqSpec){
            
            dano+=5;
        }

        HP_Pokemon_Velocidade_Maior -= dano;


        ///////////////////////////////////////EXIBE A EFICACIA DO ATCK //////////////////////////////////

        if(Taxa_Eficacia_Atck==0){

            printf("\n%s POSSUI IMUNIDADE AO SEU ATAQUE!\n",pokedex[Pokemon_Velocidade_Menor].nome);

        }else{

            if(Taxa_Eficacia_Atck == 100){

                printf("\nATAQUE NÃO EFICAZ!\n");

            }else{
                if(Taxa_Eficacia_Atck==150){

                    printf("\nATAQUE NÃO MUITO EFICAZ!\n");

                }else{
                    if(Taxa_Eficacia_Atck==200){
                        
                    printf("\nATAQUE EFICAZ!\n");

                    }else{
                        if(Taxa_Eficacia_Atck==300){

                        printf("\nATAQUE SUPER EFICAZ!\n");

                        }else{
                            if(Taxa_Eficacia_Atck==500){

                            printf("\nATAQUE HIPER EFICAZ!\n");

                            }
                        }
                    }
                }
                    
            }
        }

        printf("%s ataca %s e causa %d de dano!\n", pokedex[Pokemon_Velocidade_Menor].nome, pokedex[Pokemon_Velocidade_Maior].nome, dano);

        if (HP_Pokemon_Velocidade_Maior <= 0) {
            printf("%s Perdeu!\n", pokedex[Pokemon_Velocidade_Maior].nome);
            break;
        }

        printf("%s tem %d HP restantes.\n", pokedex[Pokemon_Velocidade_Maior].nome, HP_Pokemon_Velocidade_Maior);
    }
}

int main() {

    Pokemon pokedex[MAX_POKEMONS];

    int NumeroPokemon1, NumeroPokemon2;
    int NivelPokemon1, NivelPokemon2;

    Vincular_Pokedex_Struct(pokedex, "pokedex.csv");

    printf("Escolha o primeiro Pokémon (índice de 1 a 721): ");
    scanf("%d", &NumeroPokemon1);

        printf("Escolha o nivel do primeiro Pokémon: ");
        scanf("%d", &NivelPokemon1);

    printf("Escolha o segundo Pokémon (índice de 1 a 721): ");
    scanf("%d", &NumeroPokemon2);

        printf("Escolha o nivel do segundo Pokémon: ");
        scanf("%d", &NivelPokemon2);


    if (NumeroPokemon1 >= 1 && NumeroPokemon1 <= MAX_POKEMONS && NumeroPokemon2 >= 1 && NumeroPokemon2 <= MAX_POKEMONS) {

        BatalhaPokemon(pokedex, NumeroPokemon1 - 1, NumeroPokemon2 - 1, NivelPokemon1, NivelPokemon2); // Subtrai 1 para ajustar o índice do array.

    } else {
        printf("Índices de Pokémon inválidos!\n");
    }

    return 0;
}
