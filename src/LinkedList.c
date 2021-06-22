#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"


static Node* getNode(LinkedList* this, int nodeIndex);
static int addNode(LinkedList* this, int nodeIndex,void* pElement);

/** \brief Crea un nuevo LinkedList en memoria de manera dinamica
 *
 *  \param void
 *  \return LinkedList* Retorna (NULL) en el caso de no conseguir espacio en memoria
 *                      o el puntero al espacio reservado
 */
LinkedList* ll_newLinkedList(void)
{
    LinkedList* this= NULL;
    this = (LinkedList*) malloc(sizeof(LinkedList));

    if(this != NULL)
	{
		this->size = 0;
		this->pFirstNode = NULL;
	}

    return this;
}

/** \brief Retorna la cantidad de elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna (-1) si el puntero es NULL o la cantidad de elementos de la lista
 *
 */
int ll_len(LinkedList* this)
{
    int returnAux = -1;

    if(this != NULL)
	{
		returnAux = this->size;
	}

    return returnAux;
}


/** \brief  Obtiene un nodo de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pNode) Si funciono correctamente
 *
 */
static Node* getNode(LinkedList* this, int nodeIndex)
{
	Node* pAuxNode = NULL;
	int i;
	if(this != NULL && nodeIndex < ll_len(this) && nodeIndex >= 0)
	{
		pAuxNode = this->pFirstNode;
		for(i=0;i<nodeIndex;i++)
		{
			pAuxNode = pAuxNode->pNextNode;
		}
	}

	return pAuxNode;
}

/** \brief  Permite realizar el test de la funcion getNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pElement) Si funciono correctamente
 *
 */
Node* test_getNode(LinkedList* this, int nodeIndex)
{
    return getNode(this, nodeIndex);
}


/** \brief Agrega y enlaza un nuevo nodo a la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
static int addNode(LinkedList* this, int nodeIndex,void* pElement)
{
	int retorno = -1;
	Node* newNode = NULL;
	Node* previousNode = NULL;

	if(this != NULL  && nodeIndex <= ll_len(this) && nodeIndex >= 0)
	{
		newNode = (Node*) malloc(sizeof(Node));
		previousNode = getNode(this, nodeIndex-1);

		if(newNode != NULL)
		{
			newNode->pNextNode = NULL;
			newNode->pElement = pElement;

			if(nodeIndex == 0)
			{
				newNode->pNextNode = this->pFirstNode;
				this->pFirstNode = newNode;
			}
			else if(previousNode != NULL)
			{
				newNode->pNextNode = previousNode->pNextNode;
				previousNode->pNextNode = newNode;
			}

			this->size ++;
			retorno = 0;
		}
	}

	return retorno;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
  * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int test_addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    return addNode(this,nodeIndex,pElement);
}


/** \brief  Agrega un elemento a la lista
 * \param pList LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento a ser agregado
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_add(LinkedList* this, void* pElement)
{
	int retorno = -1;
	if(this != NULL)
	{
		if(!addNode(this, ll_len(this), pElement))
			retorno = 0;
	}
	return retorno;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a obtener
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_get(LinkedList* this, int index)
{
	void* retorno = NULL;
	Node* auxNode = NULL;
	if(this != NULL && index < ll_len(this) && index >= 0)
	{
		auxNode = getNode(this, index);
		retorno = auxNode->pElement;
	}
	return retorno;
}


/** \brief Modifica un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a modificar
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_set(LinkedList* this, int index,void* pElement)
{
	int retorno = -1;
	Node* pAuxNode = NULL;
	if(this != NULL && index < ll_len(this) && index >= 0)
	{
		pAuxNode = getNode(this, index);

		if(pAuxNode != NULL)
		{
			pAuxNode->pElement = pElement;
			retorno = 0;
		}

	}
	return retorno;
}


/** \brief Elimina un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a eliminar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_remove(LinkedList* this,int index)
{
	int retorno = -1;
	Node* auxNode = NULL;
	Node* previousNode = NULL;
	if(this != NULL && index < ll_len(this) && index >= 0)
	{
	   auxNode = getNode(this, index);
	   previousNode = getNode(this, index-1);

	   if(auxNode != NULL)
	   {
		   if(index == 0)
		   {
			   this->pFirstNode = auxNode->pNextNode;
		   }
		   else if(previousNode != NULL)
		   {
			   previousNode->pNextNode = auxNode->pNextNode;
		   }

		   free(auxNode);
		   this->size --;
		   retorno = 0;
	   }
	}
	return retorno;
}


/** \brief Elimina todos los elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_clear(LinkedList* this)
{
	int returnAux = -1;
	if(this!=NULL)
	{
		for(int i = 0;i<ll_len(this);i++)
		{
			if(ll_remove(this,i) == 0)
			{
				returnAux = 0;
			}
			else
			{
				returnAux = -1;
				break;
			}
		}
	}
	return returnAux;
}


/** \brief Elimina todos los elementos de la lista y la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_deleteLinkedList(LinkedList* this)
{
	int returnAux = -1;
	if(this != NULL)
	{
		if(ll_clear(this)==0)
		{
			free(this);
			returnAux = 0;
		}
	}
	return returnAux;
}

/** \brief Busca el indice de la primer ocurrencia del elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        (indice del elemento) Si funciono correctamente
 *
 */
int ll_indexOf(LinkedList* this, void* pElement)
{
	int retorno = -1;
	Node* auxNode = NULL;
	if(this != NULL)
	{
		for(int i=0; i < ll_len(this); i++)
		{
			auxNode = getNode(this, i);
			if(auxNode != NULL && auxNode->pElement == pElement)
			{
				retorno = i;
				break;
			}
		}
	}
	return retorno;
}

/** \brief Indica si la lista esta o no vacia
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si la lista NO esta vacia
                        ( 1) Si la lista esta vacia
 *
 */
int ll_isEmpty(LinkedList* this)
{
	int retorno = -1;
	if(this != NULL)
	{
		if(this->size == 0)
		{
			retorno = 1;
		}
		else
		{
			retorno = 0;
		}
	}
	return retorno;
}

/** \brief Inserta un nuevo elemento en la lista en la posicion indicada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo elemento
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_push(LinkedList* this, int index, void* pElement)
{
	int retorno = -1;
	if(this != NULL  && index <= ll_len(this) && index >= 0)
	{
		if(addNode(this, index, pElement) == 0)
			retorno = 0;
	}
	return retorno;
}


/** \brief Elimina el elemento de la posicion indicada y retorna su puntero
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento eliminar
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_pop(LinkedList* this,int index)
{
	void* returnAux = NULL;
	Node* auxNode = NULL;
	if(this != NULL  && index < ll_len(this) && index >= 0)
	{
		returnAux = ll_get(this, index);

		auxNode = getNode(this, index);
		if(auxNode != NULL)
		{
			free(auxNode);
			this->size --;
		}
	}
	return returnAux;
}


/** \brief  Determina si la lista contiene o no el elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero del elemento a verificar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 1) Si contiene el elemento
                        ( 0) si No contiene el elemento
*/
int ll_contains(LinkedList* this, void* pElement)
{
	int returnAux = -1;
	if(this != NULL)
	{
		if(ll_indexOf(this, pElement) >= 0)
		{
			returnAux = 1;
		}
		else
		{
			returnAux = 0;
		}
	}
	return returnAux;
}

/** \brief  Determina si todos los elementos de la lista (this2)
            estan contenidos en la lista (this)
 *
 * \param this LinkedList* Puntero a la lista
 * \param this2 LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si alguno de los punteros a las listas son NULL
                        ( 1) Si los elementos de (this2) estan contenidos en la lista (this)
                        ( 0) si los elementos de (this2) NO estan contenidos en la lista (this)
*/
int ll_containsAll(LinkedList* this,LinkedList* this2)
{
	int returnAux = -1;
	int counter = 0;
	if(this != NULL && this2 != NULL)
	{
		if(ll_len(this) >= ll_len(this2))
		{
			for(int i=0; i < ll_len(this); i++)
			{
				if(ll_contains(this, ll_get(this2, i)) == 1)
				{
					counter ++;
				}
			}

			if(counter == ll_len(this2))
			{
				returnAux = 1;
			}
			else
			{
				returnAux = 0;
			}
		}
		else
		{
			returnAux = 0;
		}
	}
	return returnAux;
}

/** \brief Crea y retorna una nueva lista con los elementos indicados
 *
 * \param pList LinkedList* Puntero a la lista
 * \param from int Indice desde el cual se copian los elementos en la nueva lista
 * \param to int Indice hasta el cual se copian los elementos en la nueva lista (no incluido)
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                o (si el indice from es menor a 0 o mayor al len de la lista)
                                o (si el indice to es menor o igual a from o mayor al len de la lista)
                         (puntero a la nueva lista) Si ok
*/
LinkedList* ll_subList(LinkedList* this,int from,int to)
{
    LinkedList* cloneArray = NULL;
    if(this != NULL && from < ll_len(this) && from >= 0 && to <= ll_len(this) && to > from)
	{
		cloneArray = ll_newLinkedList();
		if(cloneArray != NULL)
		{
			for(int i=from; i < to; i++)
			{
				ll_add(cloneArray, ll_get(this, i));
			}
		}
	}
    return cloneArray;
}



/** \brief Crea y retorna una nueva lista con los elementos de la lista pasada como parametro
 *
 * \param pList LinkedList* Puntero a la lista
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                (puntero a la nueva lista) Si ok
*/
LinkedList* ll_clone(LinkedList* this)
{
    LinkedList* arrayClonado = NULL;
    if(this != NULL)
    	arrayClonado = ll_subList(this, 0, ll_len(this));

    return arrayClonado;
}


/** \brief Ordena los elementos de la lista utilizando la funcion criterio recibida como parametro
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \param order int  [1] Indica orden ascendente - [0] Indica orden descendente
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
                                ( 0) Si ok
 */
int ll_sort(LinkedList* this, int (*pFunc)(void* ,void*), int order)
{
    int returnAux =-1;
    void* auxElement = NULL;
	Node* auxNodeI = NULL;
	Node* auxNodeJ = NULL;
	int len;
	if(this != NULL && pFunc != NULL && (order == 1 || order == 0))
	{
		len = ll_len(this);

		for(int i=0; i < len-1; i++)
		{
			for(int j=i+1; j < len; j++)
			{
				auxNodeI = getNode(this, i);
				auxNodeJ = getNode(this, j);
				if(auxNodeI != NULL && auxNodeJ != NULL)
				{
					if(pFunc(auxNodeI->pElement, auxNodeJ->pElement) && order)
					{
						auxElement = auxNodeI->pElement;
						auxNodeI->pElement = auxNodeJ->pElement;
						auxNodeJ->pElement = auxElement;
					}
					else if(pFunc(auxNodeI->pElement, auxNodeJ->pElement) == -1 && !order)
					{
						auxElement = auxNodeI->pElement;
						auxNodeI->pElement = auxNodeJ->pElement;
						auxNodeJ->pElement = auxElement;
					}
				}
			}
		}
		returnAux = 0;
	}
    return returnAux;

}

void* ll_getNext(LinkedList* this, int isFirst)
{
	void* returnAux = NULL;
	static Node* pNodeAux = NULL;
	if(this != NULL)
	{
		if(isFirst)
		{
			pNodeAux = getNode(this,0);
			if(pNodeAux != NULL)
			{
				returnAux = pNodeAux->pElement;
			}
		}
		else
		{
			if(pNodeAux != NULL)
			{
				pNodeAux = pNodeAux->pNextNode;
				if(pNodeAux != NULL)
				{
					returnAux = pNodeAux->pNextNode;
				}
			}
		}
	}
	return returnAux;
}
/*
static Node* buscar(LinkedList* this, int (*FuncionBuscar)(void*))
{
	Node* pAuxNode = NULL;
	int i;

	if(this != NULL && FuncionBuscar != NULL)
	{
		pAuxNode = this->pFirstNode;
		while(pAuxNode != NULL)
		{
			if(FuncionBuscar(pAuxNode->pElement) == 1)
			{
				break;
			}
			pAuxNode = pAuxNode->pNextNode;
		}
	}
	return pAuxNode;
}
*/
