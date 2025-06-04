#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

typedef struct {
    int matricula;
    char nome[50];
    char turma[6];
    float nota[4];
} Aluno;

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void cadastrarAluno(FILE *arquivo) {
    Aluno aluno;
    
    printf("\n--- CADASTRO DE ALUNO ---\n");
    
    printf("Matricula: ");
    scanf("%d", &aluno.matricula);
    limparBuffer();
    
    printf("Nome: ");
    fgets(aluno.nome, 50, stdin);
    aluno.nome[strcspn(aluno.nome, "\n")] = '\0';
    
    printf("Turma: ");
    fgets(aluno.turma, 6, stdin);
    aluno.turma[strcspn(aluno.turma, "\n")] = '\0';
    
    printf("Digite as 4 notas:\n");
    for(int i = 0; i < 4; i++) {
        printf("Nota %d: ", i+1);
        scanf("%f", &aluno.nota[i]);
    }
    limparBuffer();
    
    fprintf(arquivo, "%d;%s;%s;%.2f;%.2f;%.2f;%.2f\n", 
            aluno.matricula, aluno.nome, aluno.turma, 
            aluno.nota[0], aluno.nota[1], aluno.nota[2], aluno.nota[3]);
    
    printf("\n✓ Aluno cadastrado com sucesso!\n");
}

void mostrarDados() {
    FILE *arquivo = fopen("alunos.txt", "r");
    if (arquivo == NULL) {
        printf("\nErro: Nenhum dado cadastrado ainda.\n");
        return;
    }

    printf("\n--- TODOS OS ALUNOS ---\n");
    printf("MATRICULA | %-30s | TURMA | NOTAS\n", "NOME");
    printf("----------|-------------------------------|-------|----------------\n");

    char linha[200];
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        Aluno a;
        sscanf(linha, "%d;%[^;];%[^;];%f;%f;%f;%f",
               &a.matricula, a.nome, a.turma,
               &a.nota[0], &a.nota[1], &a.nota[2], &a.nota[3]);

        printf("%9d | %-30s | %-5s | %.1f, %.1f, %.1f, %.1f\n",
               a.matricula, a.nome, a.turma,
               a.nota[0], a.nota[1], a.nota[2], a.nota[3]);
    }
    fclose(arquivo);
    printf("\n");
}

void relatorioTurma() {
    char turma[6];
    printf("\nTurma para relatorio: ");
    fgets(turma, 6, stdin);
    turma[strcspn(turma, "\n")] = '\0';

    FILE *arquivo = fopen("alunos.txt", "r");
    if (arquivo == NULL) {
        printf("Nenhum aluno cadastrado.\n");
        return;
    }

    int count = 0;
    float somaMedias = 0, maiorNota = -1, menorNota = 11;
    char linha[200];

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        Aluno a;
        sscanf(linha, "%d;%[^;];%[^;];%f;%f;%f;%f",
               &a.matricula, a.nome, a.turma,
               &a.nota[0], &a.nota[1], &a.nota[2], &a.nota[3]);

        if (strcmp(a.turma, turma) == 0) {
            float media = (a.nota[0] + a.nota[1] + a.nota[2] + a.nota[3]) / 4;
            somaMedias += media;
            count++;

            for (int i = 0; i < 4; i++) {
                if (a.nota[i] > maiorNota) maiorNota = a.nota[i];
                if (a.nota[i] < menorNota) menorNota = a.nota[i];
            }
        }
    }
    fclose(arquivo);

    if (count > 0) {
        printf("\nRELATORIO DA TURMA %s\n", turma);
        printf("Alunos: %d\n", count);
        printf("Media geral: %.2f\n", somaMedias / count);
        printf("Maior nota: %.2f\n", maiorNota);
        printf("Menor nota: %.2f\n", menorNota);
    } else {
        printf("Nenhum aluno encontrado na turma %s\n", turma);
    }
}

void relatorioAluno() {
    int matricula;
    printf("\nMatricula para relatorio: ");
    scanf("%d", &matricula);
    limparBuffer();

    FILE *arquivo = fopen("alunos.txt", "r");
    if (arquivo == NULL) {
        printf("Nenhum aluno cadastrado.\n");
        return;
    }

    int encontrado = 0;
    char linha[200];

    while (fgets(linha, sizeof(linha), arquivo) != NULL && !encontrado) {
        Aluno a;
        sscanf(linha, "%d;%[^;];%[^;];%f;%f;%f;%f",
               &a.matricula, a.nome, a.turma,
               &a.nota[0], &a.nota[1], &a.nota[2], &a.nota[3]);

        if (a.matricula == matricula) {
            float media = (a.nota[0] + a.nota[1] + a.nota[2] + a.nota[3]) / 4;
            float maior = a.nota[0], menor = a.nota[0];
            
            for (int i = 1; i < 4; i++) {
                if (a.nota[i] > maior) maior = a.nota[i];
                if (a.nota[i] < menor) menor = a.nota[i];
            }

            printf("\nRELATORIO DO ALUNO\n");
            printf("Nome: %s\n", a.nome);
            printf("Turma: %s\n", a.turma);
            printf("Notas: %.1f, %.1f, %.1f, %.1f\n", 
                   a.nota[0], a.nota[1], a.nota[2], a.nota[3]);
            printf("Media: %.2f\n", media);
            printf("Maior nota: %.1f\n", maior);
            printf("Menor nota: %.1f\n", menor);
            
            encontrado = 1;
        }
    }

    if (!encontrado) {
        printf("Aluno com matricula %d nao encontrado.\n", matricula);
    }
    fclose(arquivo);
}

void menu() {
    printf("\n=== SISTEMA DE CADASTRO ===\n");
    printf("1. Cadastrar aluno\n");
    printf("2. Listar todos os alunos\n");
    printf("3. Relatorio por turma\n");
    printf("4. Relatorio individual\n");
    printf("0. Sair\n");
    printf("Escolha uma opcao: ");
}

int main() {
    FILE *arquivo = fopen("alunos.txt", "a+");
    if (arquivo == NULL) {
        printf("Erro ao criar arquivo de dados.\n");
        return 1;
    }

    int opcao;
    do {
        menu();
        scanf("%d", &opcao);
        limparBuffer();

        switch(opcao) {
            case 1:
                cadastrarAluno(arquivo);
                break;
            case 2:
                mostrarDados();
                break;
            case 3:
                relatorioTurma();
                break;
            case 4:
                relatorioAluno();
                break;
            case 0:
                printf("Encerrando o sistema...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    fclose(arquivo);
    return 0;
}
