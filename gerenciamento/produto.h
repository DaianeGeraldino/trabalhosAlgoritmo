#ifndef PRODUTO_H
#define PRODUTO_H

#define MAX_PRODUTOS 1000
#define ARQ_PRODUTOS "produtos.txt"


typedef struct {
    int codigo;
    char nome[50];
    char marca[30];
    int quantidade;
    float preco;
} Produto;


void carregarProdutos();
void salvarProdutos();
int buscarProdutoPorCodigo(int codigo);
void cadastrarProduto();
void alterarProduto();
void excluirProduto();
void listarProdutos();
void relatorioQuantidadeTotal();
void relatorioValorEstoque();

#endif
