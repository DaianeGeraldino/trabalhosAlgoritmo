#include <stdio.h>
#include <string.h>
#include "aluno.h"
#include "utils.h"

void relatorioTurma() {
    char turma[6];
    printf("\nTurma para relatorio: ");
    fgets(turma, sizeof(turma), stdin);
    turma[strcspn(turma, "\n")] = '\0';

    FILE *arquivo = fopen("alunos.txt", "r");
    if (!arquivo) {
        printf("Nenhum aluno cadastrado.\n");
        return;
    }

    int count = 0;
    float somaMedias = 0, maiorNota = -1, menorNota = 11;
    char linha[200];

    while (fgets(linha, sizeof(linha), arquivo)) {
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
    if (!arquivo) {
        printf("Nenhum aluno cadastrado.\n");
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
            printf("\nRELATORIO DO ALUNO\n");
            printf("Nome: %s\n", a.nome);
            printf("Turma: %s\n", a.turma);
            printf("Notas: %.1f, %.1f, %.1f, %.1f\n", 
                   a.nota[0], a.nota[1], a.nota[2], a.nota[3]);

            float media = (a.nota[0] + a.nota[1] + a.nota[2] + a.nota[3]) / 4;
            printf("Media: %.2f\n", media);

            float maior = a.nota[0], menor = a.nota[0];
            for (int i = 1; i < 4; i++) {
                if (a.nota[i] > maior) maior = a.nota[i];
                if (a.nota[i] < menor) menor = a.nota[i];
            }
            printf("Maior nota: %.1f\n", maior);
            printf("Menor nota: %.1f\n", menor);
            encontrado = 1;
            break;
        }
    }
    if (!encontrado) {
        printf("Aluno com matricula %d nao encontrado.\n", matricula);
    }
    fclose(arquivo);
}

void listarAlunosPorTurma() {
    char turmaBusca[6];
    printf("Digite a turma que deseja listar: ");
    fgets(turmaBusca, sizeof(turmaBusca), stdin);
    turmaBusca[strcspn(turmaBusca, "\n")] = '\0';

    FILE *arquivo = fopen("alunos.txt", "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    char linha[200];
    int encontrou = 0;
    printf("\n--- ALUNOS DA TURMA %s ---\n", turmaBusca);

    while (fgets(linha, sizeof(linha), arquivo)) {
        Aluno a;
        sscanf(linha, "%d;%[^;];%[^;];%f;%f;%f;%f",
               &a.matricula, a.nome, a.turma,
               &a.nota[0], &a.nota[1], &a.nota[2], &a.nota[3]);

        if (strcmp(a.turma, turmaBusca) == 0) {
            printf("Matricula: %d\n", a.matricula);
            printf("Nome: %s\n", a.nome);
            printf("Notas: %.2f, %.2f, %.2f, %.2f\n",
                   a.nota[0], a.nota[1], a.nota[2], a.nota[3]);
            printf("------------------------------\n");
            encontrou = 1;
        }
    }
    if (!encontrou) {
        printf("Nenhum aluno encontrado nessa turma.\n");
    }
    fclose(arquivo);
}