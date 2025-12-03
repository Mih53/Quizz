#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char pergunta[200];
    char alternativas[4][50];
    char respostaCorreta; 

} Pergunta;

void exibirMenu() {
    printf("\n QUIZ MITOLOGIA BRASILEIRA\n");
    printf("1 - Iniciar Quiz\n");
    printf("2 - Ver Pontuação\n");
    printf("3 - Sair\n \n");
    printf("Escolha uma opção: ");
}

void exibirPergunta(Pergunta p) {
    printf("\n%s\n", p.pergunta);
    printf("A) %s\n", p.alternativas[0]);
    printf("B) %s\n", p.alternativas[1]);
    printf("C) %s\n", p.alternativas[2]);
    printf("D) %s\n", p.alternativas[3]);
    printf("Escolha (A/B/C/D): \n");
}

int verificarResposta(Pergunta p, char resposta) {
    if (resposta == p.respostaCorreta) {
        return 1; 
    }
   resposta = tolower(resposta);
    return 0; 
}

int main() {
    int opcao;
    int pontuacao = 0;
    char resposta;

    Pergunta perguntas[2] = {
        {
            "Quem usa um gorro vermelho e só tem uma perna só? Se não respeitar a natureza, ele pode pregar peças nas pessoas.",
            {"Curupira", "Saci", "Caipora", "Iara"},
            'b'
        },
        {
            "Qual personagem protege as florestas e tem pés virados para trás? Ele é conhecido por confundir caçadores.",
            {"Cuca", "Mula sem Cabeça", "Curupira", "Caipora"},
            'c'
        }
    };

    do {
        exibirMenu();
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                printf("\n Será que você conehce a mitologia brasileira? \n");
                pontuacao = 0;
                for (int i = 0; i < 2; i++) {
                    exibirPergunta(perguntas[i]);
                    scanf(" %c", &resposta); 
                    if (verificarResposta(perguntas[i], resposta)) {
                        printf(" Acertouuu :)\n");
                        pontuacao++;
                    } else {
                        printf("\n Errou! Resposta correta: %c\n", perguntas[i].respostaCorreta);
                    }
                }
                printf("\n Sua pontuação final é: %d/%d\n", pontuacao, 2);
                break;

            case 2:
                printf("\n Sua pontuação da última rodada é: %d/%d \n", pontuacao, 2);
                break;

            case 3:
                printf("\n Tchau tchau \n");
                break;

            default:
                printf("\n Opss, tente novamente, opção inválida!\n");
        }
    } while(opcao != 3);

    return 0;
}

