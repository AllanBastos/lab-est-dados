/*****************************************************************************
 * Instituto Federal de Educação Ciência e Tecnologia da Paraíba			 
 * Campus Campina Grande													 
 * Curso Superior em Engenharia da Computação								 
 * Professor: Cesar Vasconcelos												 
 * 																			 
 * Copyright - Cesar Vasconcelos											 
 * Este marerial foi elaborado apenas para ser utilizado pelos alunos da 	 
 * disciplina Estruturas de Dados, do curso de Eng. da Computação do IFPB.	 
 * 																			 
 * Nenhuma parte deste material pode ser reproduzida ou transmitida			 
 * de qualquer modo ou por qualquer meio sem prévia autorização do 			 
 * autor e sem lhe ser dado o devido crédito.								 
 * **************************************************************************/


/*************** Área de dados do TAD Lista Duplamente Encadeada *********************/
#include "listadupenc.h"
#include <stdio.h>
#include <stdlib.h>

//----------------------------------------------------------------------

// funções auxiliares que apenas fatoram código comum as sub-rotinas...
TListaDupEnc aloca();

//----------------------------------------------------------------------

//*************** Implementação do TAD Lista Dup. Encadeada ***********//


/* Criar uma lista duplamente encadeada vazia
 * Parâmetros: o ponteiro que representa "a cabeça" da lista 
 * (por referência)
 */
void criarLista( TListaDupEnc *lista ){ *lista = NULL; }


/* Verificar se a lista está (ou não) vazia
 * Parâmetros: o ponteiro que representa "a cabeça" da lista (por valor)
 */
int listaVazia( TListaDupEnc lista ){ return lista == NULL; }


/* Verificar a quantidade de elementos na lista
 * Parâmetros: o ponteiro que representa a cabeça da lista (por valor)
 */
int tamanhoLista( TListaDupEnc lista ){
	int tamanho = 0;
	while( lista != NULL ) {
    	lista = lista->prox;
        tamanho++;
    }
    return tamanho;
}

/*  Buscar um elemento mediante sua posição na lista
 *  Parâmetros: lista = a lista dup. encadeada
 *              posicao = posição na qual se deseja buscar o elemento
 *              dado = passagem por referência "retornando" o elem. desejado
 *  Retorno: 1 em caso de sucesso ou 0, no caso de posição inválida
 */
int elementoNaPosicao( TListaDupEnc lista, int posicao, int* dado ){
	int posicaoAtual = 1;
	
    // se lista está vazia ou posição inválida
    if ( listaVazia( lista ) || posicao <= 0 
              || posicao > tamanhoLista( lista ) ) return 0;
    
    while ( ( lista != NULL ) && ( posicaoAtual < posicao ) ){
    	lista = lista->prox;
        posicaoAtual++;
    }
    *dado = lista->dado;
    return 1;
}

/* Obter a posição de um elemento na lista dup. encadeada
 * Parâmetros: lista = a lista dup. encadeada
 *             elemento = o dado a ser pesquisado na lista
 * Retorno: a posição do elemento em caso de sucesso ou 0 caso contrário
 */
int posicaoDoElemento( TListaDupEnc lista, int dado ){
    int posicao = 1;

    while ( lista != NULL ) {
    	// testar se o dado � igual ao campo de informação do nó...
    	if ( dado == lista->dado )	return posicao;
    	
    	lista = lista->prox;
    	posicao++;
    }
    return 0;
}

/* Inserir um elemento na lista mediante uma posição
 * Parâmetros: lista = a lista dup. encadeada
 *             elemento = o dado a ser inserido
 *             posicao = posição na qual se deseja inserir o elemento
 * Retorno: 1 em caso de sucesso ou 0, caso contrário
 */
int inserirElemento( TListaDupEnc* lista, int posicao, int dado ){
	TListaDupEnc novo = NULL, aux = NULL;
    int contador = 1;
    
    // inserção em uma lista que está vazia
    if( listaVazia( *lista ) ) {
    	// se a lista está vazia, só é possível inserir na posição 1
        if( posicao != 1 ) return 0;
		// alocar o no e testar pra ver se tudo correu bem
        if( ( novo = aloca() ) == NULL ) return 0;

        novo->dado = dado;
        novo->prox = NULL;
        novo->ant = NULL;
        *lista = novo;
        return 1;
    }

	// inserção na primeira posição em uma lista não vazia
    if( posicao == 1 ){
    	// alocar o no e testar pra ver se tudo correu bem
        if( ( novo = aloca() ) == NULL ) return 0;

        novo->dado = dado;
        novo->prox = *lista; // faz novo nó "conectar-se" ao primeiro
        novo->ant = NULL;
        (*lista)->ant = novo;
        *lista = novo;
        return 1;
    }

    // inserção após a primeira posição e em uma lista não vazia
    aux = *lista;

	// uma estratégia é fazer aux parar uma posição "antes" da real posição
	while( ( contador < posicao -1 ) && ( aux != NULL ) ) {
    	aux = aux->prox;
        contador++;
    }

    // só por garantia, vou testar se posição 
	// foi maior que o esperado (é inválida)
    if( aux == NULL ) return 0;

    // alocar o novo nó
    if( ( novo = aloca() ) == NULL ) return 0;

    novo->dado = dado;
    novo->prox = aux->prox;
    novo->ant = aux;

    // cenário de inserção entre dois elementos existentes
    if( aux->prox != NULL ) aux->prox->ant = novo;

    aux->prox = novo;
    return 1;
}

/* Remover um elemento da lista mediante sua posição
 * Parâmetros: lista = a lista dup. encadeada
 * 			   dado = passagem por referência "retornando" o elem. removido
 *             posicao = posição na qual se deseja remover o elemento
 * Retorno: 1 em caso de sucesso ou 0, caso contrário
 */
int removerElemento( TListaDupEnc* lista, int posicao, int *dado ){
	TListaDupEnc aux = NULL;
    int contador = 1;

    if ( listaVazia( *lista ) ) return 0;

    // faz aux apontar para o primeiro elemento
    aux = *lista;

    // aux deve "parar" sobre o nó a ser removido
    while( ( contador < posicao ) && ( aux != NULL ) ){
    	aux = aux->prox;
        contador++;
    }
    // se a posição foi maior que o esperado
    if ( aux == NULL ) return 0;

 	// guardar o dado antes de "apagar" o nó da memória
    *dado = aux->dado;

    // primeiro nó da lista?
    if( posicao == 1 ){
    	*lista = aux->prox;
        // deve-se testar se há mais de um elemento na lista
        if( aux->prox != NULL )	aux->prox->ant = NULL;
    } else {
    	// se não é o último nó...
        if( aux->prox != NULL ) aux->prox->ant = aux->ant;

        aux->ant->prox = aux->prox;
    }
    // remover, aqui, implica em desalocar memória
    free( aux );
    return 1;
}

/* Exibir todos os elementos da lista
 * Parâmetros: lista = a lista encadeada
 */
void imprimir ( TListaDupEnc lista ){
	printf( "\nLista: ( ");

	for( ;!listaVazia( lista ); lista = lista->prox )
	    printf("%d ", lista->dado );

	printf( ")" );
}

// alocar um novo nó na memória do computador
// função utilitária usada para fatorar código comum
TListaDupEnc aloca(){ return (no*) malloc( sizeof( no ) ); }