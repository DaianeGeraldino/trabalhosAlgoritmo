#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	
	int matricula;
	char nome[50];
	char turma[6];
	float nota[4];
	
} aluno;

void cadastro (FILE *pont_arquiv) {
	
	aluno aluno;
	int i;
	
		printf("Digite a matricula do aluno: \n");
		scanf("%d", &aluno.matricula);
		getchar();
		
		printf("Digite o nome do aluno: \n");
		fgets(aluno.nome, sizeof(aluno.nome), stdin);
		
		printf("Digite a turma do aluno: \n");
		fgets(aluno.turma, sizeof(aluno.turma), stdin);
		getchar();
		
		for(i = 0; i < 4; i++) {
			
		printf("Digite a nota do aluno: \n");	
		scanf("%f", &aluno.nota[i]);
	
	}
	
		fprintf(pont_arquiv, "%d;%s;%s;%.2f;%.2f;%.2f;%.2f", aluno.matricula, aluno.nome, aluno.turma, aluno.nota[0], aluno.nota[1], aluno.nota[2], aluno.nota[3]);
		
		printf("aluno cadastrado com sucesso! \n");
}

void mostrarDados() {
    FILE *arquivo;
    char linha[200]; // Tamanho suficiente para uma linha

    arquivo = fopen("arquivo_cadastro.txt", "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para leitura!\n");
        return;
    }

    printf("\n--- DADOS CADASTRADOS ---\n");

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        printf("%s", linha);
    }

    fclose(arquivo);
    printf("\n--------------------------\n");
}

void relatorioTurma() {
    FILE *arquivo;
    char linha[200];
    char turmaBusca[5];
    int count = 0;
    int i;
    float somaMedias = 0, maiorNota = -1, menorNota = 11;

    printf("Digite a turma para o relatório: ");
    fgets(turmaBusca, sizeof(turmaBusca), stdin);

    arquivo = fopen("arquivo_cadastro.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        aluno a;
        sscanf(linha, "%d;%[^;];%[^;];%f;%f;%f;%f",
               &a.matricula, a.nome, a.turma,
               &a.nota[0], &a.nota[1], &a.nota[2], &a.nota[3]);

        if (strncmp(a.turma, turmaBusca, strlen(turmaBusca) - 1) == 0) {
            float media = 0;
            for (i = 0; i < 4; i++) {
                media += a.nota[i];
                if (a.nota[i] > maiorNota) maiorNota = a.nota[i];
                if (a.nota[i] < menorNota) menorNota = a.nota[i];
            }
            media /= 4;
            somaMedias += media;
            count++;
        }
    }

    if (count > 0) {
        printf("\nRelatório da turma %s", turmaBusca);
        printf("Média geral da turma: %.2f\n", somaMedias / count);
        printf("Maior nota da turma: %.2f\n", maiorNota);
        printf("Menor nota da turma: %.2f\n", menorNota);
    } else {
        printf("Nenhum aluno encontrado na turma %s", turmaBusca);
    }

    fclose(arquivo);
}

void relatorioAluno() {
    FILE *arquivo;
    char linha[200];
    int matriculaBusca;
    int achou = 0;
    int i;

    printf("Digite a matrícula do aluno para o relatório: ");
    scanf("%d", &matriculaBusca);
    getchar();

    arquivo = fopen("arquivo_cadastro.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        aluno a;
        sscanf(linha, "%d;%[^;];%[^;];%f;%f;%f;%f",
               &a.matricula, a.nome, a.turma,
               &a.nota[0], &a.nota[1], &a.nota[2], &a.nota[3]);

        if (a.matricula == matriculaBusca) {
            float media = 0, maior = a.nota[0], menor = a.nota[0];
            for (i = 0; i < 4; i++) {
                media += a.nota[i];
                if (a.nota[i] > maior) maior = a.nota[i];
                if (a.nota[i] < menor) menor = a.nota[i];
            }
            media /= 4;

            printf("\nRelatório do aluno %s", a.nome);
            printf("Turma: %s", a.turma);
            printf("Média: %.2f\n", media);
            printf("Maior nota: %.2f\n", maior);
            printf("Menor nota: %.2f\n", menor);
            achou = 1;
            break;
        }
    }

    if (!achou) {
        printf("Aluno com matrícula %d não encontrado.\n", matriculaBusca);
    }

    fclose(arquivo);
}

int main() {
	
	FILE *pont_arquiv;
	int opcao;
	
	pont_arquiv = fopen("arquivo_cadastro.txt", "a+");
	
	if(pont_arquiv == NULL)
	{
		printf("Erro na abertura do arquivo! \n");
		exit(1);
	}
	
	do {
	
		printf("*****MENU***** \n");
		printf("1 - cadastrar aluno \n");
		printf("0 - encerrar programa \n");
		printf("3 - Relatório individual\n");
		printf("4 - Relatório por turma\n");
		scanf("%d", &opcao);
		getchar();
		
		switch (opcao) {
			
			case 1:
				cadastro(pont_arquiv);
				break;
			
			case 0:
				printf("Encerrando programa... \n");
				break;
				
			case 3:
    			relatorioAluno();
    			break;
			
			case 4:
    			relatorioTurma();
    			break;
				
			default:
				printf("Existe isso nao, burro!");
				break;
		}
		
	} while (opcao != 0);
	
	fclose(pont_arquiv);
	
		
	return 0;
}
