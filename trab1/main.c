#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int matricula;
    char nome[50];
    char turma[6];
    float nota[4];
} aluno;

int verificaMatricula(FILE *pont_arquiv, int matricula) {
    aluno a;
    rewind(pont_arquiv);

    while (fscanf(pont_arquiv, "%d;%49[^;];%4[^;];%f;%f;%f;%f\n", 
                  &a.matricula, a.nome, a.turma, 
                  &a.nota[0], &a.nota[1], &a.nota[2], &a.nota[3]) == 7) {
        if (a.matricula == matricula) {
            return 1;
        }
    }
    return 0;
}

void cadastro(FILE *pont_arquiv) {
    aluno aluno;
    int i;

    printf("Digite a matricula do aluno: \n");
    scanf("%d", &aluno.matricula);
    getchar();

    if (verificaMatricula(pont_arquiv, aluno.matricula)) {
        printf("Erro: matrícula já cadastrada!\n");
        return;
    }

    printf("Digite o nome do aluno: \n");
    fgets(aluno.nome, sizeof(aluno.nome), stdin);
    aluno.nome[strcspn(aluno.nome, "\n")] = '\0';

    printf("Digite a turma do aluno: \n");
    fgets(aluno.turma, sizeof(aluno.turma), stdin);
    aluno.turma[strcspn(aluno.turma, "\n")] = '\0';

    for (i = 0; i < 4; i++) {
        printf("Digite a nota %d do aluno: \n", i + 1);
        scanf("%f", &aluno.nota[i]);
    }

    fprintf(pont_arquiv, "%d;%s;%s;%.2f;%.2f;%.2f;%.2f\n", 
            aluno.matricula, aluno.nome, aluno.turma, 
            aluno.nota[0], aluno.nota[1], aluno.nota[2], aluno.nota[3]);

    fflush(pont_arquiv);
    printf("Aluno cadastrado com sucesso!\n");
}

void listar(FILE *pont_arquiv) {
    aluno a;
    rewind(pont_arquiv);

    printf("** Lista de Alunos **\n");

    while (fscanf(pont_arquiv, "%d;%49[^;];%4[^;];%f;%f;%f;%f\n", 
                  &a.matricula, a.nome, a.turma, 
                  &a.nota[0], &a.nota[1], &a.nota[2], &a.nota[3]) == 7) {
        printf("Matrícula: %d\n", a.matricula);
        printf("Nome: %s\n", a.nome);
        printf("Turma: %s\n", a.turma);
        printf("Notas: %.2f, %.2f, %.2f, %.2f\n\n", 
                a.nota[0], a.nota[1], a.nota[2], a.nota[3]);
    }
}

int main() {
    FILE *pont_arquiv;
    int opcao;

    pont_arquiv = fopen("arquivo_cadastro.txt", "a+");
    if (pont_arquiv == NULL) {
        printf("Erro na abertura do arquivo!\n");
        exit(1);
    }

    do {
        printf("** MENU **\n");
        printf("1 - Cadastrar aluno\n");
        printf("2 - Listar alunos\n");
        printf("0 - Encerrar programa\n");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                cadastro(pont_arquiv);
                break;
            case 2:
                listar(pont_arquiv);
                break;
            case 0:
                printf("Encerrando programa...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    fclose(pont_arquiv);
    return 0;
}
