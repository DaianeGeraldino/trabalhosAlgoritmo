#include <stdio.h>
#include "utils.h"

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void menu() {
    printf("\n=== SISTEMA DE CADASTRO DE ALUNOS ===\n");
    printf("1. Cadastrar aluno\n");
    printf("2. Listar todos os alunos\n");
    printf("3. Relatorio por turma\n");
    printf("4. Relatorio individual\n");
    printf("5. Listar alunos por turma\n");
    printf("0. Sair\n");
    printf("Escolha uma opcao: ");
}
