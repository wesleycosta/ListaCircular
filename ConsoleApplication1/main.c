#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	int valor;
}ELEMENTO;

typedef struct
{
	ELEMENTO elemento;
	ELEMENTO *proximo;
	ELEMENTO *anterior;
}ELEMENTO_NO;

typedef struct lista
{
	ELEMENTO_NO *inicio;
	ELEMENTO_NO *fim;
	int totalElementos;
}LISTA;

LISTA* CriarLista()
{
	LISTA *pLista = (LISTA *)malloc(sizeof(LISTA));
	pLista->inicio = 0;
	pLista->fim = NULL;
	pLista->totalElementos = 0;

	return pLista;
}

int ListaVazia(LISTA *pLista)
{
	return !pLista->inicio;
}

// VERIFICA SE DOIS ELEMENTOS S�O IGUAIS
int Igual(ELEMENTO A, ELEMENTO B)
{
	return A.valor == B.valor;
}

// BUSCA UM ELEMENTO DA LISTA, CASA N�O EXISTA RETORNA NULL
ELEMENTO_NO *BuscarElemento(LISTA *pLista, ELEMENTO elemento)
{
	ELEMENTO_NO *pIndex = NULL;
	int index = 0;

	for (pIndex = pLista->fim; index < pLista->totalElementos; pIndex = pIndex->proximo)
	if (Igual(pIndex->elemento, elemento))
		return pIndex;

	return NULL;
}

// INSERE UM NOVO ELEMENTO DA LISTA
int Inserir(LISTA *pLista, ELEMENTO elemento)
{
	ELEMENTO_NO *novoElemento = (ELEMENTO_NO *)malloc(sizeof(ELEMENTO_NO));

	// VERIFICA SE O NOVO ELEMENTO FOI ALOCADO NA MEMORIA
	if (!novoElemento)
		return -1; // ERRO AO ALOCAR O NOVO ELEMENTO
	else
	{
		novoElemento->elemento = elemento;

		// VERIFICA SE A LISTA ESTA VAZIA
		if (ListaVazia(pLista))
		{
			novoElemento->proximo = novoElemento; // O PROXIMO DO NOVO ELEMENTO APONTA PARA O INICIO DA FILA  (NOVO ELEMENTO)
			novoElemento->anterior = novoElemento; // O ANTERIRO DO NOVO ELEMENTO APONTA PARA O FINAL DA FILA (NOVO ELEMENTO)
			pLista->inicio = novoElemento; // INICIO DA FILA RECEBE O NOVO ELEMENTO
		}
		else
		{
			novoElemento->anterior = pLista->fim; // O ANTERIOR DO NOVO ELEMENTO APONTA PARA O ULTIMO ELEMENTO DA FILA
			novoElemento->proximo = pLista->inicio; // O PROXIMO  DO NOVO ELEMENTO APONTA PARA O INICIO DA FILA

			pLista->fim->proximo = novoElemento;   // O PROXIMO DO ULTIMO ELEMNTO APONTA PARA O NOVO ELEMENTO
			pLista->inicio->anterior = novoElemento; // O ANTERIOR DO inicio APONTA PARA O FINAL DA LISTA
		}

		pLista->fim = novoElemento; // fim RECEBE O NOVO ELEMENTO
		return pLista->totalElementos++;
	}
}

// REMOVER UM ELEMENTO DA LISTA
int Remover(LISTA *pLista, ELEMENTO elemento)
{
	ELEMENTO_NO *elementoEncontrado = BuscarElemento(pLista, elemento);

	if (!elementoEncontrado)
		return -1;
	else
	{
		ELEMENTO_NO * elementoAntes = elementoEncontrado->anterior;
		ELEMENTO_NO * elementoDepois = elementoEncontrado->proximo;

		elementoAntes->proximo = elementoEncontrado->proximo;
		elementoDepois->anterior = elementoAntes;

		if (elementoEncontrado == pLista->fim)
		{
			pLista->fim = elementoAntes;
			pLista->inicio->anterior = elementoAntes;
		}
		else if (elementoEncontrado == pLista->inicio)
		{
			pLista->inicio = elementoDepois;
			pLista->fim->proximo = elementoDepois;
		}

		free(elementoEncontrado);
		return pLista->totalElementos--;
	}
}

// ORDERNA A LISTA
void Ordernar(LISTA *pLista)
{
	ELEMENTO_NO *pElAtual;
	ELEMENTO_NO *pElProximo;

	int i = 0, j = 0;

	for (pElAtual = pLista->inicio; i < pLista->totalElementos; pElAtual = pElAtual->proximo)
	{
		for (pElProximo = pElAtual->proximo; j < pLista->totalElementos - 1; pElProximo = pElProximo->proximo)
		{
			if (pElAtual->elemento.valor < pElProximo->elemento.valor)
			{
				ELEMENTO x = pElAtual->elemento;
				pElAtual->elemento = pElProximo->elemento;
				pElProximo->elemento = x;
			}
			j++;
		}

		j = 0; i++;
	}
}

// IMPRIME TODOS OS ELEMENTOS DA LISTA
void Imprimir(LISTA *pLista)
{
	ELEMENTO_NO *pIndex = pLista->fim;
	int index = 0;

	for (pIndex = pLista->inicio; index < pLista->totalElementos; pIndex = pIndex->proximo)
		printf("[%d] - %d \n", index++, pIndex->elemento.valor);
}

void Pause()
{
	printf("\n\nTecle <ENTER> para continuar...");
	getchar();
}

int main()
{
	LISTA *pLista = CriarLista();
	ELEMENTO elemento;
	int i = 0;

	for (i = 10; i > 0; i--)
	{
		elemento.valor = i;
		Inserir(pLista, elemento);
	}

	Imprimir(pLista);

	printf("\n\n");

	elemento.valor = 1;
	Remover(pLista, elemento);
	elemento.valor = 3;
	Remover(pLista, elemento);
	elemento.valor = 4;
	Remover(pLista, elemento);

	Ordernar(pLista);

	Imprimir(pLista);

	Pause();
	return 0;
}