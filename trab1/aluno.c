#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aluno.h"
#include "utils.h"

int matriculaExiste(const char *filename, int matricula) {
    FILE *arquivo = fopen(filename, "r");
    if (!arquivo) return 0;
    
    char linha[200];
    while (fgets(linha, sizeof(linha), arquivo)) {
        int m;
        sscanf(linha, "%d", &m);
        if (m == matricula) {
            fclose(arquivo);
            return 1;
        }
    }
    fclose(arquivo);
    return 0;
}

void cadastrarAluno(FILE *arquivo) {
    Aluno aluno;
    printf("\n--- CADASTRO DE ALUNO ---\n");

    do {
        printf("Matricula: ");
        scanf("%d", &aluno.matricula);
        limparBuffer();

        if (matriculaExiste("alunos.txt", aluno.matricula)) {
            printf("Erro: Matricula ja existe.\n");
        } else break;
    } while (1);

    printf("Nome: ");
    fgets(aluno.nome, sizeof(aluno.nome), stdin);
    aluno.nome[strcspn(aluno.nome, "\n")] = '\0';

    printf("Turma: ");
    fgets(aluno.turma, sizeof(aluno.turma), stdin);
    aluno.turma[strcspn(aluno.turma, "\n")] = '\0';

    printf("Digite as 4 notas:\n");
    for (int i = 0; i < 4; i++) {
        do {
            printf("Nota %d (0 a 10): ", i + 1);
            scanf("%f", &aluno.nota[i]);
            if (aluno.nota[i] < 0 || aluno.nota[i] > 10) {
                printf("Erro: A nota deve estar entre 0 e 10.\n");
            }
        } while (aluno.nota[i] < 0 || aluno.nota[i] > 10);
    }

    fprintf(arquivo, "%d;%s;%s;%.2f;%.2f;%.2f;%.2f;\n",
            aluno.matricula, aluno.nome, aluno.turma,
            aluno.nota[0], aluno.nota[1], aluno.nota[2], aluno.nota[3]);

    fflush(arquivo);

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
