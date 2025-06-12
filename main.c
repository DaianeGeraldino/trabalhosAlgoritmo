#include <stdio.h>
#include "produto.h"

int main() {
    int opcao;

    carregarProdutos();

    do {
        printf("\n--- Sistema de Controle de Estoque ---\n");
        printf("1 - Cadastrar Produto\n");
        printf("2 - Alterar Produto\n");
        printf("3 - Excluir Produto\n");
        printf("4 - Listar Produtos\n");
        printf("5 - Relatorio Quantidade Total\n");
        printf("6 - Relatorio Valor em Estoque\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: cadastrarProduto(); break;
            case 2: alterarProduto(); break;
            case 3: excluirProduto(); break;
            case 4: listarProdutos(); break;
            case 5: relatorioQuantidadeTotal(); break;
            case 6: relatorioValorEstoque(); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opcao invalida!\n");
        }

    } while(opcao != 0);

    return 0;
}
