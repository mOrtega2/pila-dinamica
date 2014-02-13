#include <stdio.h>
#include <stdlib.h>

#define TODO_BIEN 1
#define SIN_MEMORIA 0
#define PILA_VACIA 0
#define CON_MSJ 1
#define TAM 15

typedef struct
{
    int edad;
    char nom[TAM];
    char ape[TAM];
    float prom;

}t_dato;

typedef struct s_nodo
{
    t_dato dato;
    struct s_nodo* sig;
}t_nodo;

typedef t_nodo* t_pila;

void crearPila(t_pila* );
int pilaVacia(const t_pila* );
int pilaLLena(const t_pila* );
int verTope(const t_pila* , t_dato* );
int apilar(t_pila* , const t_dato* );
int desapilar(t_pila* , t_dato* );
void vaciarPila(t_pila* );
int elegirMenu();
void ingresarDatos(t_dato*);
void guardarEnArchivo(t_pila *, t_dato *);
void sacarDeArchivo(t_pila *, t_dato *);
int abrirArchivo(FILE **, const char *, const char *, int);
void mostrarArchivo(t_dato *);

int main()
{
    int opcion;
    t_pila pila;
    t_dato dato;

    opcion = elegirMenu();

while(opcion!=0)

{

    switch(opcion)
        {
            case 1:
                crearPila(&pila);

                break;

            case 2:
                if(pilaVacia(&pila))
                   printf("La pila esta vacia");

                break;

            case 3:
                if(pilaLLena(&pila))
                 printf("La pila esta llena");

                break;

            case 4:

                if(verTope(&pila, &dato))
                {
                    printf("%d", dato.edad);
                    puts(dato.nom);
                    puts(dato.ape);
                    printf("%f", dato.prom);
                }
                else
                {
                    printf("No hay tope");
                }
                break;

            case 5:

                ingresarDatos(&dato);

                if(apilar(&pila, &dato))
                   printf("Apilo");
                else
                   printf("No pudo apilar");

                break;

            case 6:

                if(desapilar(&pila, &dato))
                    printf("Desapilo");
                else
                    printf("No pudo desapilar");

                break;

            case 7:

                vaciarPila(&pila);

                break;

            case 8:

                guardarEnArchivo(&pila, &dato);

                break;

            case 9:

                mostrarArchivo(&dato);

                break;

            case 0:
                printf("Ha decidido salir");

                break;
            default:

                printf("Numero no valido");
                break;
        }

opcion = elegirMenu();

}

return 0;
}

int elegirMenu()
{
     int opcion;
     printf("**********MENU DE OPCIONES**********\n \
1- Crear Pila\n \
2- Pila Vacia\n \
3- Pila LLena\n \
4- Ver tope de pila\n \
5- Apilar\n \
6- Desapilar\n \
7- Vaciar pila\n \
8- Guardar en Archivo\n \
0- Salir\n \
INGRESE EL NUMERO DE OPCION: ");

      scanf("%d",&opcion);
      return opcion;

}

int abrirArchivo(FILE **pf, const char *nombre, const char *mod, int conSin)
{
    *pf=fopen(nombre, mod);
    if((*pf)==NULL)
    {
        if(conSin== CON_MSJ)
        {
            printf("ERROR abriendo %s con modo %s", nombre, mod);
        }
        return 0;
    }
    return 1;
}

void crearPila(t_pila* pp)
{
    (*pp) = NULL;
}

int pilaVacia(const t_pila* pp)
{
    return (*pp) == NULL;



}

int pilaLLena(const t_pila* pp)
{
    void* aux = malloc(sizeof(t_dato));
    free(aux);

    return aux== NULL;
}

int verTope(const t_pila* pp, t_dato* pd)
{

    if((*pp) == NULL)
       return PILA_VACIA;

    *pd = (*pp)->dato;
    return TODO_BIEN;
}

int apilar(t_pila* pp, const t_dato* pd)
{
    t_nodo* nue = (t_nodo*)malloc(sizeof(t_nodo));

    if(nue == NULL)
        return SIN_MEMORIA;

    nue->dato = *pd;
    nue->sig = *pp;
    *pp = nue;

    return TODO_BIEN;
}

int desapilar(t_pila* pp, t_dato* pd)
{
    if((*pp)== NULL)
      return PILA_VACIA;

    t_nodo* aux = *pp ;

    *pp = aux->sig;
    *pd = aux->dato;

    free(aux);

    return TODO_BIEN;
}

void vaciarPila(t_pila* pp)
{
    while((*pp)!=NULL)
    {
        t_nodo* aux = *pp ;
        *pp = (*pp)->sig;
        free(aux);
    }

}

void ingresarDatos(t_dato* pd)
{
    printf("Edad: \n");
    scanf("%d", &pd->edad);
    fflush(stdin);
    printf("Nombre: \n");
    gets(pd->nom);
    fflush(stdin);
    printf("Apellido: \n");
    gets(pd->ape);
    fflush(stdin);
    printf("Promedio: \n");
    scanf("%f", &pd->prom);
    fflush(stdin);

}

void guardarEnArchivo(t_pila *pp, t_dato *pd)
{
    FILE *pf;
    abrirArchivo(&pf, "ArchivoBin", "w+ b", CON_MSJ);
    while(!(pilaVacia(pp)))
    {
        desapilar(pp, pd);
        fwrite(pd, sizeof(t_dato), 1, pf);
    }
}

void mostrarArchivo(t_dato *pd)
{
    FILE *pf;
    abrirArchivo(&pf, "ArchivoBin", "w+ b", CON_MSJ);
    while(!feof(pf))
    {
        fread(pd, sizeof(t_dato), 1, pf);
        printf("%d \n", pd -> edad);
        puts(pd -> nom);
        puts(pd -> ape);
        printf("%f \n", pd ->prom);
    }
}




