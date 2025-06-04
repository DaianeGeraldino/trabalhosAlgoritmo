#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aluno.h"

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int matriculaExiste(const char *filename, int matricula) {
    FILE *arquivo = fopen(filename, "r");
    if (arquivo == NULL) return 0;

    char linha[200];
    while (fgets(linha, sizeof(linha), arquivo)) {
        int mat;
        sscanf(linha, "%d", &mat);
        if (mat == matricula) {
            fclose(arquivo);
            return 1;
        }
    }

    fclose(arquivo);
    return 0;
}

void cadastrarAluno(FILE *arquivo) {
    Aluno aluno;
    int i;

    printf("\n--- CADASTRO DE ALUNO ---\n");

    do {
        printf("Matricula: ");
        scanf("%d", &aluno.matricula);
        limparBuffer();
        if (matriculaExiste("alunos.txt", aluno.matricula)) {
            printf("Matricula ja existe.\n");
        } else break;
    } while (1);

    printf("Nome: ");
    fgets(aluno.nome, sizeof(aluno.nome), stdin);
    aluno.nome[strcspn(aluno.nome, "\n")] = '\0';

    printf("Turma: ");
    fgets(aluno.turma, sizeof(aluno.turma), stdin);
    aluno.turma[strcspn(aluno.turma, "\n")] = '\0';

    printf("Digite as 4 notas:\n");
    for (i = 0; i < 4; i++) {
        printf("Nota %d: ", i + 1);
        scanf("%f", &aluno.nota[i]);
    }
    limparBuffer();

    fprintf(arquivo, "%d;%s;%s;%.2f;%.2f;%.2f;%.2f\n",
            aluno.matricula, aluno.nome, aluno.turma,
            aluno.nota[0], aluno.nota[1], aluno.nota[2], aluno.nota[3]);

    printf("Aluno cadastrado com sucesso!\n");
}

void mostrarDados() {
    FILE *arquivo = fopen("alunos.txt", "r");
    if (!arquivo) {
        printf("Nenhum dado cadastrado.\n");
        return;
    }

    printf("\n--- TODOS OS ALUNOS ---\n");
    printf("MATRICULA | %-30s | TURMA | NOTAS\n", "NOME");
    printf("----------|-------------------------------|-------|----------------\n");

    char linha[200];
    while (fgets(linha, sizeof(linha), arquivo)) {
        Aluno a;
        sscanf(linha, "%d;%[^;];%[^;];%f;%f;%f;%f",
               &a.matricula, a.nome, a.turma,
               &a.nota[0], &a.nota[1], &a.nota[2], &a.nota[3]);

        printf("%9d | %-30s | %-5s | %.1f, %.1f, %.1f, %.1f\n",
               a.matricula, a.nome, a.turma,
               a.nota[0], a.nota[1], a.nota[2], a.nota[3]);
    }

    fclose(arquivo);
}

void relatorioTurma() {
    char turma[6];
    int i;
    printf("\nTurma para relatorio: ");
    fgets(turma, sizeof(turma), stdin);
    turma[strcspn(turma, "\n")] = '\0';

    FILE *arquivo = fopen("alunos.txt", "r");
    if (!arquivo) {
        printf("Nenhum aluno cadastrado.\n");
        return;
    }

    int count = 0;
    float soma = 0, maior = -1, menor = 11;
    char linha[200];

    while (fgets(linha, sizeof(linha), arquivo)) {
        Aluno a;
        sscanf(linha, "%d;%[^;];%[^;];%f;%f;%f;%f",
               &a.matricula, a.nome, a.turma,
               &a.nota[0], &a.nota[1], &a.nota[2], &a.nota[3]);

        if (strcmp(a.turma, turma) == 0) {
            float media = (a.nota[0] + a.nota[1] + a.nota[2] + a.nota[3]) / 4;
            soma += media;
            count++;
            for (i = 0; i < 4; i++) {
                if (a.nota[i] > maior) maior = a.nota[i];
                if (a.nota[i] < menor) menor = a.nota[i];
            }
        }
    }

    fclose(arquivo);

    if (count > 0) {
        printf("\nTurma %s - Alunos: %d\n", turma, count);
        printf("Media geral: %.2f\n", soma / count);
        printf("Maior nota: %.2f | Menor nota: %.2f\n", maior, menor);
    } else {
        printf("Nenhum aluno encontrado na turma %s\n", turma);
    }
}

void relatorioAluno() {
    int matricula;
    int i;
    printf("\nMatricula do aluno: ");
    scanf("%d", &matricula);
    limparBuffer();

    FILE *arquivo = fopen("alunos.txt", "r");
    if (!arquivo) {
        printf("Arquivo nao encontrado.\n");
        return;
    }

    char linha[200];
    int encontrado = 0;

    while (fgets(linha, sizeof(linha), arquivo)) {
        Aluno a;
        sscanf(linha, "%d;%[^;];%[^;];%f;%f;%f;%f",
               &a.matricula, a.nome, a.turma,
               &a.nota[0], &a.nota[1], &a.nota[2], &a.nota[3]);

        if (a.matricula == matricula) {
            float media = (a.nota[0] + a.nota[1] + a.nota[2] + a.nota[3]) / 4;
            float maior = a.nota[0], menor = a.nota[0];
            for (i = 1; i < 4; i++) {
                if (a.nota[i] > maior) maior = a.nota[i];
                if (a.nota[i] < menor) menor = a.nota[i];
            }

            printf("\nAluno: %s\n", a.nome);
            printf("Turma: %s\n", a.turma);
            printf("Notas: %.1f, %.1f, %.1f, %.1f\n", a.nota[0], a.nota[1], a.nota[2], a.nota[3]);
            printf("Media: %.2f | Maior: %.1f | Menor: %.1f\n", media, maior, menor);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Aluno nao encontrado.\n");
    }

    fclose(arquivo);
}

void listarAlunosPorTurma() {
    char turma[6];
    printf("Digite a turma: ");
    fgets(turma, sizeof(turma), stdin);
    turma[strcspn(turma, "\n")] = '\0';

    FILE *arquivo = fopen("alunos.txt", "r");
    if (!arquivo) {
        printf("Erro ao abrir arquivo.\n");
        return;
    }

    char linha[200];
    int encontrou = 0;

    printf("\n--- Alunos da Turma %s ---\n", turma);

    while (fgets(linha, sizeof(linha), arquivo)) {
        Aluno a;
        sscanf(linha, "%d;%[^;];%[^;];%f;%f;%f;%f",
               &a.matricula, a.nome, a.turma,
               &a.nota[0], &a.nota[1], &a.nota[2], &a.nota[3]);

        if (strcmp(a.turma, turma) == 0) {
            printf("Matricula: %d | Nome: %s\n", a.matricula, a.nome);
            encontrou = 1;
        }
    }

    if (!encontrou) {
        printf("Nenhum aluno encontrado.\n");
    }

    fclose(arquivo);
}
