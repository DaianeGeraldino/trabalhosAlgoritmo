#include <stdio.h>
#include "aluno.h"

void menu() {
    printf("\n=== MENU ===\n");
    printf("1. Cadastrar aluno\n");
    printf("2. Listar todos os alunos\n");
    printf("3. Relatorio por turma\n");
    printf("4. Relatorio individual\n");
    printf("5. Listar alunos por turma\n");
    printf("0. Sair\n");
    printf("Escolha: ");
}

int main() {
    int opcao;
    do {
        menu();
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1: {
                FILE *arquivo = fopen("alunos.txt", "a");
                if (!arquivo) {
                    printf("Erro ao abrir arquivo.\n");
                    break;
                }
                cadastrarAluno(arquivo);
                fclose(arquivo);
                break;
            }
            case 2: mostrarDados(); break;
            case 3: relatorioTurma(); break;
            case 4: relatorioAluno(); break;
            case 5: listarAlunosPorTurma(); break;
            case 0: printf("Encerrando...\n"); break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}
