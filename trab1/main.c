#include <stdio.h>
#include <stdlib.h>

typedef struct {
	
	int matricula;
	char nome[50];
	char turma[5];
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
	
		printf("**MENU** \n");
		printf("1 - cadastrar aluno \n");
		printf("0 - encerrar programa \n");
		scanf("%d", &opcao);
		getchar();
		
		switch (opcao) {
			
			case 1:
				cadastro(pont_arquiv);
				break;
			
			case 0:
				printf("Encerrando programa... \n");
				break;
		}
		
	} while (opcao != 0);
	
	fclose(pont_arquiv);
		
	return 0;
}
