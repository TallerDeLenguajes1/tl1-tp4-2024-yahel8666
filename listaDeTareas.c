#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 200

typedef struct Nodo {
    Tarea T;
    Nodo *Siguiente;
} Nodo;

typedef struct Tarea {
    int TareaID;//Numérico autoincremental comenzando en 1000
    char *Descripcion;
    int Duracion; // entre 10 – 100
} Tarea;

Nodo* crearLista();
Tarea crearTarea(int *id); //creo solamente una tarea
Nodo* crearNuevoNodo(int *d); //creo un nuevo nodo con la tarea cargada 
void insertarNodo(Nodo**cabeceraPendientes, Nodo*nuevoNodo); // inserto ese nodo con la tarea en la lista de pendientes. 
void moverTareas(Nodo** c1, Nodo**c2);
void mostrarListas(Nodo** c1, Nodo** c2);
void BuscarTareaPorId(Nodo**c1, Nodo**c2);
void mostrarTareaPorPalabra(Nodo**c1, Nodo**c2);
void liberarMemoria(Nodo**cabeceraLista);
int main ()
{
    //variables: 
    char opcion; int id=1000; int opcion1;

    //creo las cabeceras de cada lista. Ahora están vacías. 
    Nodo * cabeceraRealizadas = crearLista();
    Nodo * cabeceraPendientes = crearLista();
 
    puts("\n--MENÚ--\n");
    do
    {
        printf("\nElija una opcion: \n");
        printf("\n 1) Agregar una Tarea a Lista de Pendientes \n");         
        printf("\n2)Mover una Tarea de Pendientes a Realizada\n");
        printf("\n3)Mostrar ambas listas de tareas");
        printf("\n4)Buscar la tarea por id\n");
        printf("\n5)Buscar la tarea por palabra clave.\n");       
        printf("\n6)Salir \n");
        scanf("%c", &opcion);
        getchar();
        switch (opcion)
        {
        case 1:
        do
        {
            Nodo * nuevoNodo = crearNuevoNodo(&id); //creo un nuevo nodo con una tarea cargada. 
            insertarNodo(&cabeceraPendientes, nuevoNodo);

            puts("\nTarea agregada");
            puts("\nDeseas agregar otra Tarea Pendiente:");
                puts("1) Si");
                puts("0) No");
                getchar();
                scanf("%d", &opcion1);
        } while (opcion1 == 1);
            break;
        case 2: 
            moverTareas(&cabeceraPendientes, &cabeceraRealizadas); 
            break;
        case 3:
            mostrarListas(&cabeceraPendientes, &cabeceraRealizadas);
            break;
        case 4:
            mostrarTareaPorId(&cabeceraPendientes, &cabeceraRealizadas);
            break;
        case 5:
            mostrarTareaPorPalabra(&cabeceraPendientes, &cabeceraRealizadas);
            break;
        default:
            break;
        }
    } while (opcion != 6);

    /*ahora tengo que eliminar la memoria de las descripciones 
    de cada tarea*/

    liberarMemoria(&cabeceraPendientes);
    liberarMemoria(&cabeceraRealizadas);
    
    return 0;
}

Nodo*crearLista()
{
    return NULL;   
}

Tarea crearTarea(int *id)
{
    Tarea nuevaTarea;
    nuevaTarea.TareaID = (*id)++;

    char *buff = (char *)malloc(sizeof(char)*MAX);     
    printf("Ingrese la descripción de la tarea: \n");
    gets(buff);

    nuevaTarea.Descripcion = (char*)malloc(strlen(buff)+1); 

    /*Copio en nuevaTarea.Descripcion, lo que se guardó en el buff*/
    strcpy(nuevaTarea.Descripcion, buff);
    nuevaTarea.Duracion = rand()%91 + 10;

    free(buff);

    return nuevaTarea;
}

Nodo *crearNuevoNodo(int* id)
{
    //reservo memoria para el nuevo nodo 
    Nodo* nuevoNodo =(Nodo*) malloc(sizeof(Nodo));
    nuevoNodo->T = crearTarea(id); 
    nuevoNodo->Siguiente = NULL;

    return nuevoNodo;
}

//lo inserto al comienzo
void insertarNodo(Nodo **cabeceraPendientes, Nodo * nuevoNodo)
{
    /*
        (*cabeceraPendientes) es la cabeza de mi lista 
    */
    nuevoNodo->Siguiente = *cabeceraPendientes;
    *cabeceraPendientes = nuevoNodo;
}

//desvinculo un nodo de c1 para vincularlo a c2. 
void moverTareas(Nodo** c1, Nodo ** c2)
{
    int idBuscado;
    printf(" \n Ingrese el id de la tarea: "); 
    scanf("%d", &idBuscado);

    Nodo* actual = *c1; 
    Nodo * anterior = NULL;

    while (actual && actual->T.TareaID!= idBuscado)
    {

        anterior = actual; 
        actual = actual->Siguiente;
    }
    if(actual == NULL)
    {
        printf("\n Tarea no encontrada ");
    } else {
        if(anterior == NULL)
        {
            *c1 = actual->Siguiente;
        } else
        {
            anterior->Siguiente = actual->Siguiente;
        }
        actual->Siguiente = *c2; 
        *c2 = actual; 
    }
}

void mostrarListas(Nodo** c1, Nodo** c2)
{
    Nodo *auxC1 = *c1; 
    Nodo *auxC2 = *c2;

    printf("\n -- Tareas Pendientes -- \n");
    /*Va a iterar siempre que no llegue a NULL*/
    while (auxC1 )
    {
        printf(" \n %s", auxC1->T.Descripcion);
        auxC1 = auxC1->Siguiente;
    }

    printf("\n -- Tareas Realizadas-- \n");
    /*Va a iterar siempre que no llegue a NULL*/
    while (auxC2)
    {
        printf(" \n %s", auxC2->T.Descripcion);
        auxC2 = auxC2->Siguiente;
    }
}

void BuscarTareaPorId(Nodo**c1, Nodo**c2)
{
    Nodo * auxC1 = *c1; 
    Nodo * auxC2 = *c2;
    int idBuscado; 

    printf("\n Ingrese el id de la tarea buscada: "); 
    scanf("%d", &idBuscado);

    /*Busco si la tarea está en la lista de Pendientes.*/
    while (auxC1 && auxC1->T.TareaID != idBuscado)
    {
        auxC1 = auxC1->Siguiente;
    }
    /*Si la encontré (Si auxC1 != NULL), muestro el resultado*/
    if (auxC1)
    {
        printf("\n Tarea encontrada en la lista de Pendientes: ");
        printf("\n Descripcion de la tarea: %s", auxC1->T.Descripcion);
        printf("\n Duración de la tarea: %d", auxC1->T.Duracion);
    } else{

        /*Busco si la tarea está en la lista de Realizadas.*/
        while (auxC2 && auxC2->T.TareaID != idBuscado)
        {
            auxC2 = auxC2->Siguiente;
        }
        /*Si la encontré (Si auxC2 != NULL), muestro el resultado*/
        if (auxC2)
        {
            printf("\n Tarea encontrada en la lista de Pendientes: ");
            printf("\n Descripcion de la tarea: %s", auxC2->T.Descripcion);
            printf("\n Duración de la tarea: %d", auxC2->T.Duracion);
        }
    }
    if (auxC1==NULL && auxC2==NULL)
    {
        printf("\n No existe tarea con ese ID");
    }
}

void mostrarTareaPorPalabra(Nodo**c1, Nodo**c2)
{
    char * buff = (char *)malloc(sizeof(char)*MAX); //libero memoria al final de la funcion. 
    printf("\n Ingrese la palabra clave: ");
    gets(buff);

    char * palabra = (char*)malloc((strlen(buff)+1)*sizeof(char));
    strcpy(palabra, buff);
    fflush(stdin);

    Nodo*auxC1 = *c1; 
    Nodo*auxC2= *c2;
    

    while (auxC1 && strstr(auxC1->T.Descripcion, palabra)==NULL)
    {
        auxC1 = auxC1->Siguiente; 
    } 
    if (auxC1)
    {
        printf("\n Tarea Encontrada en la lista de Pendientes: "); 
        printf("\n Descripción de la tarea: %s", auxC1->T.Descripcion); 
        printf("\n Id de la tarea: %d", auxC1->T.TareaID); 
        printf("\n Duracion de la tarea: %d", auxC1->T.Duracion); 
    } else {
        /*Sino, buscamos en la lista de tareas Realizadas*/
        while (auxC2 && strstr(auxC2->T.Descripcion, palabra)==NULL)
        {
            auxC2 = auxC2->Siguiente; 
        } if (auxC2)
        {
            printf("\n Tarea Encontrada en la lista de Realizadas: "); 
            printf("\n Descripción de la tarea: %s", auxC2->T.Descripcion); 
            printf("\n Id de la tarea: %d", auxC2->T.TareaID); 
            printf("\n Duracion de la tarea: %d", auxC2->T.Duracion);         
        }
    }
    if (!auxC1 && !auxC2)
    {
        printf("\n No existe la tarea ");
    }

    free(buff);
    free(palabra);
}

void liberarMemoria(Nodo **cabeceraLista)
{
    Nodo*temp; 
    if (*cabeceraLista)
    {
        temp = *cabeceraLista;
        *cabeceraLista = (*cabeceraLista)->Siguiente; 
        free(temp->T.Descripcion);
        free(temp);
        /*La función free(temp) libera la memoria apuntada 
        por el puntero temp, es decir, elimina el nodo al
        que apunta temp en la lista enlazada.*/
    }
}
