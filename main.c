#include "main.h"

/*Función que inserta números aleatorios en una lista*/
void inserta_datos_de_prueba(Lista lista);

int cmp_int(const void* a, const void* b) {
	int a_int = *((int*) (((Elemento*) a)->valor));
	int b_int = *((int*) (((Elemento*) b)->valor));
	if (a_int > b_int) {
		return 1;
	} else if (a_int == b_int) {
		return 0;
	}
	return -1;
}

void ordena_lista(Lista lista, int(*cmp)(const void*, const void*)) {
	size_t l = longitud(lista);
	Elemento* arreglo = malloc(sizeof(Elemento)*l);
	Elemento* aux = *lista;
	int i;
	for (i = 0; i < l; i++) {
		arreglo[i] = *aux;
		aux = aux->siguiente;
	}
	qsort(arreglo, l, sizeof(Elemento), *cmp);
	aux = *lista;
	for (i = 0; i < l; i++) {
		aux->valor = arreglo[i].valor;
		aux = aux->siguiente;
	}
}

void borra_lista(Lista lista) {
	Elemento* aux;
	int i;
	for (i = 0; i < longitud(lista); i++) {
		aux = quita_elemento(lista, 0);
		if (aux != NULL) {
			free(aux->valor);
			free(aux);
		}
	}
	free(lista);
}

Elemento* quita_elemento(Lista lista, size_t posicion) {
    if(*lista == NULL || posicion < 0 || posicion >= longitud(lista))
        return NULL;

    if (posicion == 0) {
        Elemento* aux = *lista;
        Elemento* aux2 = aux->siguiente;
        *lista = aux2;
        return aux;
    } else if (posicion == longitud(lista)-1) {
        Elemento *a = *lista;
        int i;
        for(i = 0; i<longitud(lista)-2; i++)
            a = a-> siguiente;
        Elemento *b = a->siguiente;
        Elemento *c = b;
        a->siguiente = NULL;
        return c;
    } else {
        Elemento *a = *lista;
        int i;
        for(i = 0; i<posicion-1; i++)
            a = a-> siguiente;
        Elemento *b = a->siguiente;
        Elemento *c = b;
        a->siguiente = b->siguiente;
        return c;
    }
}

void imprime_lista_int(Lista lista) {
	Elemento* aux = *lista;
	printf("[");
	while (aux) {
		printf("%d", *((int*) aux->valor));
		if (aux->siguiente) {
			printf(", ");
		}
		aux = aux->siguiente;
	}
	printf("]\n");
}

Lista crea_lista() {
	Lista lista = malloc (sizeof(Lista));
	return lista;
}

size_t longitud(Lista lista) {
	Elemento* aux = *lista;
	int longitud = 0;
	while (aux) {
		longitud++;
		aux = aux->siguiente;
	}
	return longitud;
}

int inserta_elemento(Lista lista, void *valor) {
	Elemento* aux = malloc(sizeof(Elemento));
	aux->siguiente = (*lista);
	aux->valor = valor;
	*lista = aux;
	return longitud(lista) + 1;
}

int main()
{
    // Se crea la lista
    Lista lista = crea_lista();
    printf("La lista tiene %d elementos\n", longitud(lista));

    // Se insertan datos de prueba
    inserta_datos_de_prueba(lista);
    printf("La lista tiene %d elementos\n", longitud(lista));

    // Se remueve un elemento de la lista
    Elemento *borrado = quita_elemento(lista, 0);
    if (borrado != NULL) {free(borrado->valor);}
    free(borrado);
    printf("La lista tiene %d elementos\n", longitud(lista));

    // Se remueve un elemento que no existe en la lista
    quita_elemento(lista, longitud(lista));
    printf("La lista tiene %d elementos\n", longitud(lista));

    //Se imprime la lista antes de ordenar
    imprime_lista_int(lista);
    ordena_lista(lista, &cmp_int);

    //Se imprime la lista después de ordenar
    imprime_lista_int(lista);

    //Se libera la memoria ocupada
    borra_lista(lista);
}

void inserta_datos_de_prueba(Lista lista)
{
    srand(time(NULL));
    int *num_a_insertar;
    int indice;
    for (indice = 0; indice < 20; ++indice) {
        num_a_insertar = malloc(sizeof(int));
        *num_a_insertar = rand() % 100;
        inserta_elemento(lista, num_a_insertar);
    };
}
