/*6) Considere a funcaox abaixo. O que essa função faz? Escreva 
uma função não-recursiva que resolve o mesmo problema
int funcaox(int a){
 if(a <= 0) return 0;
 else return a + funcaox(a-1);
}//funcaox
*/

#include <stdio.h>
#include <stdlib.h>

int funcaoNaoRecursiva(int a) {
    int soma = 0;
    while (a > 0) {
        soma += a;
        a--;
    }
    return soma;
}

int main() {
    int numero;

    printf("Digite um numero inteiro positivo: ");
    scanf("%d", &numero);

    if (numero < 0) {
        printf("Digite um número inteiro positivo.\n");
    } else {
        int resultado = funcaoNaoRecursiva(numero);
        printf("A soma dos numeros de %d ate 1 e: %d\n", numero, resultado);
    }

    return 0;
}