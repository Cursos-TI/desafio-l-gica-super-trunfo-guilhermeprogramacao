#include <stdio.h>
#include <string.h>

struct Carta {
    char nomePais[50];
    int populacao;
    float area;
    float pib;
    int pontosTuristicos;
    float densidadeDemografica;
};

// Função para exibir o menu de seleção de atributos
void exibirMenu(int atributoBloqueado) {
    printf("\nEscolha um atributo:\n");
    if (atributoBloqueado != 1) printf("1 - População\n");
    if (atributoBloqueado != 2) printf("2 - Área\n");
    if (atributoBloqueado != 3) printf("3 - PIB\n");
    if (atributoBloqueado != 4) printf("4 - Pontos Turísticos\n");
    if (atributoBloqueado != 5) printf("5 - Densidade Demográfica\n");
}

// Função para obter valor do atributo selecionado
float obterValor(struct Carta c, int atributo) {
    switch (atributo) {
        case 1: return (float)c.populacao;
        case 2: return c.area;
        case 3: return c.pib;
        case 4: return (float)c.pontosTuristicos;
        case 5: return c.densidadeDemografica;
        default: return 0;
    }
}

// Função para exibir o nome do atributo
const char* nomeAtributo(int codigo) {
    switch (codigo) {
        case 1: return "População";
        case 2: return "Área";
        case 3: return "PIB";
        case 4: return "Pontos Turísticos";
        case 5: return "Densidade Demográfica";
        default: return "Desconhecido";
    }
}

int main() {
    // Duas cartas pré-definidas
    struct Carta carta1 = {"Brasil", 203000000, 8515767.0, 22000.0, 25};
    struct Carta carta2 = {"Argentina", 45000000, 2780400.0, 5000.0, 12};

    carta1.densidadeDemografica = carta1.populacao / carta1.area;
    carta2.densidadeDemografica = carta2.populacao / carta2.area;

    int atributo1, atributo2;

    // Escolha do primeiro atributo
    exibirMenu(0);
    printf("Escolha o primeiro atributo para comparação: ");
    scanf("%d", &atributo1);
    while (atributo1 < 1 || atributo1 > 5) {
        printf("Opção inválida. Escolha novamente: ");
        scanf("%d", &atributo1);
    }

    // Escolha do segundo atributo, bloqueando o primeiro
    exibirMenu(atributo1);
    printf("Escolha o segundo atributo para comparação: ");
    scanf("%d", &atributo2);
    while (atributo2 < 1 || atributo2 > 5 || atributo2 == atributo1) {
        printf("Opção inválida ou repetida. Escolha novamente: ");
        scanf("%d", &atributo2);
    }

    // Obtenção dos valores
    float valor1_carta1 = obterValor(carta1, atributo1);
    float valor1_carta2 = obterValor(carta2, atributo1);

    float valor2_carta1 = obterValor(carta1, atributo2);
    float valor2_carta2 = obterValor(carta2, atributo2);

    // Aplicando regra da densidade (menor vence), os outros (maior vence)
    int ponto_carta1 = 0, ponto_carta2 = 0;

    if (atributo1 == 5) { // Densidade demográfica
        ponto_carta1 += (valor1_carta1 < valor1_carta2) ? 1 : (valor1_carta2 < valor1_carta1 ? 0 : 0);
        ponto_carta2 += (valor1_carta2 < valor1_carta1) ? 1 : (valor1_carta1 < valor1_carta2 ? 0 : 0);
    } else {
        ponto_carta1 += (valor1_carta1 > valor1_carta2) ? 1 : (valor1_carta2 > valor1_carta1 ? 0 : 0);
        ponto_carta2 += (valor1_carta2 > valor1_carta1) ? 1 : (valor1_carta1 > valor1_carta2 ? 0 : 0);
    }

    if (atributo2 == 5) {
        ponto_carta1 += (valor2_carta1 < valor2_carta2) ? 1 : (valor2_carta2 < valor2_carta1 ? 0 : 0);
        ponto_carta2 += (valor2_carta2 < valor2_carta1) ? 1 : (valor2_carta1 < valor2_carta2 ? 0 : 0);
    } else {
        ponto_carta1 += (valor2_carta1 > valor2_carta2) ? 1 : (valor2_carta2 > valor2_carta1 ? 0 : 0);
        ponto_carta2 += (valor2_carta2 > valor2_carta1) ? 1 : (valor2_carta1 > valor2_carta2 ? 0 : 0);
    }

    float soma_carta1 = valor1_carta1 + valor2_carta1;
    float soma_carta2 = valor1_carta2 + valor2_carta2;

    printf("\n====== RESULTADO DA COMPARAÇÃO ======\n");
    printf("Carta 1 - %s:\n", carta1.nomePais);
    printf("  %s: %.2f\n", nomeAtributo(atributo1), valor1_carta1);
    printf("  %s: %.2f\n", nomeAtributo(atributo2), valor2_carta1);
    printf("  Soma total: %.2f\n", soma_carta1);

    printf("\nCarta 2 - %s:\n", carta2.nomePais);
    printf("  %s: %.2f\n", nomeAtributo(atributo1), valor1_carta2);
    printf("  %s: %.2f\n", nomeAtributo(atributo2), valor2_carta2);
    printf("  Soma total: %.2f\n", soma_carta2);

    printf("\n==== VENCEDOR ====\n");
    if (soma_carta1 > soma_carta2) {
        printf("Vencedor: %s!\n", carta1.nomePais);
    } else if (soma_carta2 > soma_carta1) {
        printf("Vencedor: %s!\n", carta2.nomePais);
    } else {
        printf("Empate!\n");
    }

    return 0;
}
