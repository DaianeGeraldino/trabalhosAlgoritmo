#include <stdio.h>
#include "aluno.h"

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
            case 5:
                listarAlunosPorTurma();
                break;
            case 0:
                printf("Encerrando o sistema...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
    fclose(arquivo);
    return 0;
}
