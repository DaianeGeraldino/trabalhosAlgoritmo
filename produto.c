#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "produto.h"
#include <time.h>

Produto produtos[MAX_PRODUTOS];
int qtdProdutos = 0;

void carregarProdutos() {
	system("cls");
    FILE *f = fopen(ARQ_PRODUTOS, "r");
    if (!f) {
        printf("Arquivo de produtos nao encontrado. Iniciando novo estoque.\n");
        return;
    }

    qtdProdutos = 0;
    while(fscanf(f, "%d;%49[^;];%29[^;];%d;%f\n", 
            &produtos[qtdProdutos].codigo,
            produtos[qtdProdutos].nome,
            produtos[qtdProdutos].marca,
            &produtos[qtdProdutos].quantidade,
            &produtos[qtdProdutos].preco) == 5) {
        qtdProdutos++;
        if (qtdProdutos >= MAX_PRODUTOS) break;
    }
    fclose(f);
}

void salvarProdutos() {
	system("cls");
	int i;
    FILE *f = fopen(ARQ_PRODUTOS, "w");
    if (!f) {
        printf("Erro ao abrir arquivo para salvar produtos!\n");
        return;
    }

    for(i = 0; i < qtdProdutos; i++) {
        fprintf(f, "%d;%s;%s;%d;%.2f\n", 
            produtos[i].codigo,
            produtos[i].nome,
            produtos[i].marca,
            produtos[i].quantidade,
            produtos[i].preco);
    }

    fclose(f);
}

int buscarProdutoPorCodigo(int codigo) {
	int i;
    for(i = 0; i < qtdProdutos; i++) {
        if (produtos[i].codigo == codigo) return i;
    }
    return -1;
}

void cadastrarProduto() {
    system("cls");
	FILE *f = fopen(ARQ_PRODUTOS, "a+");
    if (!f) {
        printf("Erro ao abrir arquivo para cadastro de produto!\n");
        return;
    }

    Produto novo;
    char buffer[100];


    static int inicializado = 0;
    if (!inicializado) {
        srand((unsigned)time(NULL)); 
        // unsigned: Faz a fun??o n?o inicializar mais de uma vez para n?o correr o risco de gerar n?meros/c?digos repetidos
        inicializado = 1;
    }

    
    int codigoExiste;
    do {
        novo.codigo = rand() % 9000 + 1000;

        
        rewind(f);
        // rewind: Faz cursor/ponteiro voltar ao inicio do arquivo
        Produto temp;
        codigoExiste = 0;
        while (fscanf(f, "%d;%49[^;];%29[^;];%d;%f\n",
                      &temp.codigo, temp.nome, temp.marca,
                      &temp.quantidade, &temp.preco) == 5) {
            if (temp.codigo == novo.codigo) {
                codigoExiste = 1;
                break;
            }
        }
    } while (codigoExiste);

    printf("\nCadastro de Produto\n");
    printf("C?digo gerado: %d\n", novo.codigo);

    printf("Nome: ");
    scanf(" %[^\n]", buffer);
    strcpy(novo.nome, buffer);
    //  strcpy: Copia o texto string para o buffer

    printf("Marca: ");
    scanf(" %[^\n]", buffer);
    strcpy(novo.marca, buffer);

    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);

    printf("Pre?o unit?rio: ");
    scanf("%f", &novo.preco);

  
    fprintf(f, "%d;%s;%s;%d;%.2f\n",
            novo.codigo, novo.nome, novo.marca,
            novo.quantidade, novo.preco);

    fclose(f);
    printf("Produto cadastrado com sucesso!\n");
}



void alterarProduto() {
    system("cls");
	int codigo;
	int escolha;
    printf("Digite o codigo do produto a alterar: ");
    scanf("%d", &codigo);

    int pos = buscarProdutoPorCodigo(codigo);
    if (pos == -1) {
        printf("Produto nao encontrado!\n");
        return;
    }

    printf("Produto encontrado: %s - %s\n", produtos[pos].nome, produtos[pos].marca);
    
   	printf("Alterar:\n1 - Quantidade\n2 - Preco\nEscolha: ");
   	scanf("%d", &escolha);

    getchar(); 

    if (escolha == 1) {
        printf("Digite nova quantidade (atual %d): ", produtos[pos].quantidade);
    	scanf("%d", &produtos[pos].quantidade);
    } else if (escolha == 2) {
        printf("Digite novo preco unitario (atual %.2f): ", produtos[pos].preco);
    	scanf("%f", &produtos[pos].preco);
    } else {
        printf("Opcao invalida!\n");
        return;
    }
    
    salvarProdutos();
    printf("Produto alterado com sucesso!\n");
}

void excluirProduto() {
    system("cls");
	int codigo, achou = 0;
    printf("Digite o codigo do produto a excluir: ");
    scanf("%d", &codigo);

    FILE *f = fopen(ARQ_PRODUTOS, "r");
    FILE *temp = fopen("temp.txt", "w");

    Produto p;
    while (fscanf(f, "%d;%49[^;];%29[^;];%d;%f\n",
                  &p.codigo, p.nome, p.marca, &p.quantidade, &p.preco) == 5) {
        if (p.codigo != codigo) {
            fprintf(temp, "%d;%s;%s;%d;%.2f\n",
                    p.codigo, p.nome, p.marca, p.quantidade, p.preco);
        } else {
            achou = 1;
        }
    }

    fclose(f);
    fclose(temp);

    remove(ARQ_PRODUTOS);
    rename("temp.txt", ARQ_PRODUTOS);

    if (achou)
        printf("Produto excluido com sucesso!\n");
    else
        printf("Produto nao encontrado!\n");
}

void listarProdutos() {
    system("cls");
	int escolha;
    int i;
    char filtro[50];

    printf("Listar por:\n1 - Nome\n2 - Marca\nEscolha: ");
    scanf("%d", &escolha);

    getchar(); 

    if (escolha == 1) {
        printf("Digite o nome do produto para listar: ");
        fgets(filtro, 50, stdin);
    } else if (escolha == 2) {
        printf("Digite a marca do produto para listar: ");
        fgets(filtro, 50, stdin);
    } else {
        printf("Opcao invalida!\n");
        return;
    }
    filtro[strcspn(filtro, "\n")] = 0;

    printf("\nProdutos encontrados:\n");
    int encontrou = 0;
    for(i = 0; i < qtdProdutos; i++) {
        if ((escolha == 1 && strcmp(produtos[i].nome, filtro) == 0) || // 0 == 0
        //str = string; cmp = compara??o; compara nome ou marca ao filtro, se as strings forem iguais equivalem a 0
            (escolha == 2 && strcmp(produtos[i].marca, filtro) == 0)) { 
            printf("Codigo: %d | Nome: %s | Marca: %s | Quantidade: %d | Preco: %.2f\n",
                produtos[i].codigo, produtos[i].nome, produtos[i].marca,
                produtos[i].quantidade, produtos[i].preco);
            encontrou = 1;
        }
    }
    if (!encontrou) {
        printf("Nenhum produto encontrado com esse criterio.\n");
    }
}

void relatorioQuantidadeTotal() {
    system("cls");
	int escolha;
    int i;
    char filtro[50];

    printf("Relatorio quantidade total em estoque por:\n1 - Nome\n2 - Marca\nEscolha: ");
    scanf("%d", &escolha);
    getchar();

    if (escolha == 1) {
        printf("Digite o nome do produto: ");
        fgets(filtro, 50, stdin);
    } else if (escolha == 2) {
        printf("Digite a marca do produto: ");
        fgets(filtro, 50, stdin);
    } else {
        printf("Opcao invalida!\n");
        return;
    }
    filtro[strcspn(filtro, "\n")] = 0;

    int totalQtd = 0;
    for(i = 0; i < qtdProdutos; i++) {
        if ((escolha == 1 && strcmp(produtos[i].nome, filtro) == 0) ||
            (escolha == 2 && strcmp(produtos[i].marca, filtro) == 0)) {
            totalQtd += produtos[i].quantidade;
        }
    }

    printf("Quantidade total em estoque: %d unidades\n", totalQtd);
}

void relatorioValorEstoque() {
    system("cls");
	int escolha;
    int i;
    char filtro[50];

    printf("Relatorio valor total em estoque por:\n1 - Nome\n2 - Marca\nEscolha: ");
    scanf("%d", &escolha);
    getchar();

    if (escolha == 1) {
        printf("Digite o nome do produto: ");
        fgets(filtro, 50, stdin);
    } else if (escolha == 2) {
        printf("Digite a marca do produto: ");
        fgets(filtro, 50, stdin);
    } else {
        printf("Opcao invalida!\n");
        return;
    }
    filtro[strcspn(filtro, "\n")] = 0;

    float valorTotal = 0;
    for(i = 0; i < qtdProdutos; i++) {
        if ((escolha == 1 && strcmp(produtos[i].nome, filtro) == 0) ||
            (escolha == 2 && strcmp(produtos[i].marca, filtro) == 0)) {
            valorTotal += produtos[i].quantidade * produtos[i].preco;
        }
    }

    printf("Valor total do estoque: R$ %.2f\n", valorTotal);
}

