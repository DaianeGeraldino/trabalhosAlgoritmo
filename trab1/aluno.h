#ifndef ALUNO_H
#define ALUNO_H

typedef struct {
    int matricula;
    char nome[50];
    char turma[6];
    float nota[4];
} Aluno;

int matriculaExiste(const char *filename, int matricula);
void cadastrarAluno(FILE *arquivo);
void mostrarDados();

#endif