
#include <stdio.h> //Fornece funções para entrada e saída, como printf e scanf
#include <string.h> //Contém funções para manipulação de strings, como strlen e strcpy
#include <ctype.h>  // Oferece funções para classificação e conversão de caracteres, como toupper e isdigit
#include <stdlib.h> // Inclui funções utilitárias, como alocação de memória (malloc), conversão de números e controle do programa (exit)
#include <time.h>  // Disponibiliza funções para trabalhar com data e hora, como time e difftime
#define MAX_PERGUNTAS 50 // Altera a quantidade de perguntas máximas do quiz

// Agrupando os dados 
typedef struct {
    char pergunta[256];
    char alternativas[4][128];
    char respostaCorreta; 
    
} Pergunta;
void exibirMenu();
int escolherNivel();
int carregarPerguntas(Pergunta perguntas[], int *total);
void embaralharPerguntas(Pergunta perguntas[], int total);
void exibirPergunta(Pergunta p);
int verificarResposta(Pergunta p, char resposta);
int jogarQuiz(Pergunta perguntas[], int total, int nRodada);
void salvarNoRanking(const char *nome, int pontos, int total);
void verRanking();

// Menu principal
void exibirMenu() {
    printf("\n=== QUIZ: MITOLOGIA BRASILEIRA ===\n");
    printf("1 - Iniciar Quiz\n");
    printf("2 - Ver Pontuação da última rodada\n");
    printf("3 - Ver Ranking\n");
    printf("4 - Sair\n\n");
    printf("Escolha uma opção: ");
}

// Menu de níveis que retorna número de perguntas
int escolherNivel() {
    int nivel = 0;
    printf("\nEscolha o nível:\n");
    printf("1 - Fácil (3 perguntas)\n");
    printf("2 - Médio (5 perguntas)\n");
    printf("3 - Difícil (8 perguntas)\n");
    printf("Opção: ");
    if (scanf("%d", &nivel) != 1) {
        return 3;
    }
    if (nivel == 1) return 3;
    if (nivel == 2) return 5;
    return 8;
}

 //Tenta carregar de 'perguntas.csv'. Se falhar, usa o banco interno.
int carregarPerguntas(Pergunta perguntas[], int *total) {
    FILE *f = fopen("perguntas.csv", "r");
    char linha[1024];
    int count = 0;

    if (f) {
        while (fgets(linha, sizeof(linha), f) && count < MAX_PERGUNTAS) {
            // Remove \r\n
            linha[strcspn(linha, "\r\n")] = '\0';
            
            // Pula linhas vazias
            if (strlen(linha) == 0) continue;

            // Quebra de linha ';'
            char *tok = strtok(linha, ";"); 
            if (!tok) continue;
            strncpy(perguntas[count].pergunta, tok, sizeof(perguntas[count].pergunta) - 1);
            perguntas[count].pergunta[sizeof(perguntas[count].pergunta) - 1] = '\0';

            int campos_validos = 1;
            for (int i = 0; i < 4; i++) {
                tok = strtok(NULL, ";");
                if (!tok) { 
                    campos_validos = 0;
                    break;
                }
                strncpy(perguntas[count].alternativas[i], tok, sizeof(perguntas[count].alternativas[i]) - 1);
                perguntas[count].alternativas[i][sizeof(perguntas[count].alternativas[i]) - 1] = '\0';
            }

            if (!campos_validos) continue;

            tok = strtok(NULL, ";");
            if (!tok) continue;
            perguntas[count].respostaCorreta = (char)tolower((unsigned char)tok[0]);

            count++;
        }
        fclose(f);
        *total = count;
        if (count > 0) return 1; // O arquivo carregou com sucesso
    } 

    // Banco de perguntas interno (8 perguntas)
    Pergunta interno[] = {                                         
        {                     
            "Quem usa um gorro vermelho e tem uma perna só, pregando peças em quem desrespeita a natureza?",
            {"Curupira", "Saci", "Caipora", "Iara"}, 'b'
        },
        {                    
            "Guardião das florestas, conhecido por ter os pés virados para trás e confundir caçadores.",
            {"Cuca", "Mula sem Cabeça", "Curupira", "Caipora"}, 'c'
        },
        {
            "Figura ligada aos rios, conhecida por encantar pessoas com sua voz.",
            {"Mula sem Cabeça", "Iara", "Boitatá", "Boto cor-de-rosa"}, 'b'
        },
        {
            "Ser de fogo associado à proteção das matas contra queimadas.",
            {"Boitatá", "Cuca", "Saci", "Curupira"}, 'a'
        },
        {
            "Personagem que assusta crianças, frequentemente retratada como uma bruxa.",
            {"Iara", "Cuca", "Caipora", "Mula sem Cabeça"}, 'b'
        },
        {
            "Ser do folclore que caça à noite e protege os animais da mata.",
            {"Caipora", "Curupira", "Boitatá", "Saci"}, 'a'
        },
        {
            "Personagem que solta fogo pelas narinas e não tem cabeça.",
            {"Mula sem Cabeça", "Cuca", "Boitatá", "Curupira"}, 'a'
        },
        {
            "Qual deles é conhecido por pregar travessuras e fazer redemoinhos?",
            {"Boitatá", "Saci", "Iara", "Caipora"}, 'b'
        },
        {
            "Quem é retratada como bruxa em algumas histórias, antagonista do Sítio do Picapau Amarelo?",
            {"Cuca", "Iara", "Mula sem Cabeça", "Caipora"}, 'a'
        },
        {
            "Qual criatura é associada ao fogo serpenteante que percorre campos?",
            {"Boitatá", "Curupira", "Saci", "Iara"}, 'a'
        }
    };
    int nInterno = sizeof(interno) / sizeof(interno[0]);
    for (int i = 0; i < nInterno; i++) perguntas[i] = interno[i];
    *total = nInterno;
    return 0; 
}

// Embaralha as perguntas
void embaralharPerguntas(Pergunta perguntas[], int total) {
    for (int i = total - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Pergunta tmp = perguntas[i];
        perguntas[i] = perguntas[j];
        perguntas[j] = tmp;
    }
}

void exibirPergunta(Pergunta p) {
    printf("\n%s\n", p.pergunta);
    printf("A) %s\n", p.alternativas[0]);
    printf("B) %s\n", p.alternativas[1]);
    printf("C) %s\n", p.alternativas[2]);
    printf("D) %s\n", p.alternativas[3]);
    printf("Escolha (A/B/C/D): ");
}

int verificarResposta(Pergunta p, char resposta) {
    resposta = (char)tolower((unsigned char)resposta);
    return (resposta == p.respostaCorreta) ? 1 : 0;
}

// Executa uma rodada com nRodada perguntas (após embaralhar)
int jogarQuiz(Pergunta perguntas[], int total, int nRodada) {
    int pontuacao = 0;
    char resposta;

    if (nRodada > total) nRodada = total;

    printf("\nVamos começar! Boa sorte!\n");

    for (int i = 0; i < nRodada; i++) {
        exibirPergunta(perguntas[i]);
        if (scanf(" %c", &resposta) != 1) {
            printf("Opss, entrada inválida, tente novamente!\n");
            continue;
        }
        if (verificarResposta(perguntas[i], resposta)) {
            printf("Resposta Corrata :) \n");
            pontuacao++;
        } else {
            char corretaMaiuscula = (char)toupper((unsigned char)perguntas[i].respostaCorreta);
            printf("Opss, resposta errada :( \n A resposta correta é: %c\n", corretaMaiuscula);
        }
    }

    printf("\n Sua pontuação desta rodada é: %d/%d\n", pontuacao, nRodada);
    return pontuacao;
}

void salvarNoRanking(const char *nome, int pontos, int total) {
    FILE *f = fopen("ranking.txt", "a");
    if (!f) {
        printf("Desculpe, não foi possível salvar a pontuação no ranking\n");
        return;
    }

    // Salvar data e hora atual no ranking
    time_t agora = time(NULL);
    struct tm *tm_info = localtime(&agora);
    char data[32];
    strftime(data, sizeof(data), "%Y-%m-%d %H:%M", tm_info);

    fprintf(f, "%s;%d;%d;%s\n", nome, pontos, total, data);
    fclose(f);
    printf("Oba, sua pontuação foi salva no ranking!\n");
}

void verRanking() {
    FILE *f = fopen("ranking.txt", "r");
    if (!f) {
        printf("\n Ainda não há ranking salvo, jogue para salvar!\n");
        return;
    }
    char linha[256];
    //Posição no ranking, 1º, 2º, 3º, etc...
    int pos = 1;
    printf("\n RANKING \n");
    while (fgets(linha, sizeof(linha), f)) {

        linha[strcspn(linha, "\r\n")] = '\0';
        char nome[64] = "", data[64] = "";
        int pontos = 0, total = 0;
        char *tok = strtok(linha, ";");
        if (tok) strncpy(nome, tok, sizeof(nome));
        tok = strtok(NULL, ";");
        if (tok) pontos = atoi(tok);
        tok = strtok(NULL, ";");
        if (tok) total = atoi(tok);
        tok = strtok(NULL, ";");
        if (tok) strncpy(data, tok, sizeof(data));

        printf("%2d) %-15s  %2d/%-2d  (%s)\n", pos++, nome, pontos, total, data);
    }
    fclose(f);
}

// Função principal
int main() {
    srand((unsigned)time(NULL));

    Pergunta perguntas[MAX_PERGUNTAS];
    int totalPerguntas = 0;
    int usouArquivo = carregarPerguntas(perguntas, &totalPerguntas);

   if (usouArquivo) {
        printf("Perguntas carregadas de 'perguntas.csv' (%d).\n", totalPerguntas);
    } else {
        printf("Usando banco interno de perguntas (%d).\n", totalPerguntas);
    }

    int opcao;
    int pontuacaoUltimaRodada = 0;
    int totalUltimaRodada = 0;

    do {
        exibirMenu();
        if (scanf("%d", &opcao) != 1) {
            printf("\nEntrada inválida. Encerrando.\n");
            break;
        }

        switch (opcao) {
            case 1: {
                int nRodada = escolherNivel();
                // Embaralha antes de jogar
                embaralharPerguntas(perguntas, totalPerguntas);
                pontuacaoUltimaRodada = jogarQuiz(perguntas, totalPerguntas, nRodada);
                totalUltimaRodada = nRodada;

                //Pergunta nome para ranking
                char nome[64];
                printf("\nDigite seu nome (sem espaços, ex.: Milena): ");
                scanf("%63s", nome);
                salvarNoRanking(nome, pontuacaoUltimaRodada, totalUltimaRodada);
                break;
            }
            case 2:
                if (totalUltimaRodada > 0) {
                    printf("\nPontuação da última rodada: %d/%d\n",
                           pontuacaoUltimaRodada, totalUltimaRodada);
                } else {
                    printf("\nAinda não há rodada registrada.\n");
                }
                break;

            case 3:
                verRanking();
                break;
                
            case 4:
                printf("\nTchau tchau!\n");
                break;

            default:
                printf("\nOpção inválida! Tente novamente.\n");
        }
    } while (opcao != 4);

    return 0;
}
                

