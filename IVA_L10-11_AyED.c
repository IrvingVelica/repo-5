/* Fecha de creacion: 19 de Octubre del 2018  Fecha de Modificacion:  21 de Octubre del 2018 */
/* Autor: Irving Velica Adame*/
/* Descripcion:  Practica 10-11 de Tablas Hash */
/* Nombre Archivo: IVA_L10-11_AyED.c*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <math.h>
#define TAM 211

typedef struct _tdato{
	int dato;
	struct _tdato *sig;
}stdato;
typedef stdato *Tdato ;

void AsignarKey( Tdato Arreglo[] );
void LoadThash();
Tdato DeleteThash( Tdato lista, int num );
Tdato FindThash( Tdato lista , int num );
Tdato GenDatoValor( int valor );

int main (){
	int num, choose, op=0, flag=0, pos;
	Tdato key[ TAM ], temp, lista;
	char search;
	printf("\t\t   Algoritmos practica #10-11 \n \n");
	AsignarKey( key );
	do{
    printf("\t\t  M  A  I  N       M  E  N  U \n");
    printf("1) Cargar tabla Hash \n");
    printf("2) Eliminar valor \n");
    printf("3) Buscar \n");
    printf("4) Salir \n");
    scanf( "%d",&choose );
    switch( choose )
	{
    	case 1:
    	LoadThash( key );
    	flag=1;
    	break;
    	case 2:
    	if ( flag==0 )
    	{
    		printf("No se ha cargado ninguna tabla \n");
		}
		else
		{
			num = leenum( 0, 1000, "Ingrese la numero que desea borrar \n", "Error, dato invalido" );
			pos = num % TAM ;
            temp = DeleteThash( key [ pos ], num );
            if ( temp )
            {
				printf( " Dato eliminado correctamente \n") ;
			}
			else if( temp == NULL )
			{
				printf( "No existe el dato \n" );
			}
		}
    	break;
    	case 3:
    	if ( flag==0 )
    	{
    		printf("No se ha cargado ninguna tabla \n");
		}
		else
		{
			num = leenum( 0, 1000, "Ingrese la numero que desea buscar \n", "Error, dato invalido" );
			pos = num % TAM ;
            temp = FindThash( key [ pos ], num );
            if( temp )
            {
				printf( "| numero encontrado en la lista |\n") ;
            	printf( "| Posicion | %3d | Valor | %3d |\n", pos, temp->dato ) ;
			}
			else if( temp == NULL )
			{
				printf( "No existe el dato \n" );
			}
		}
    	break;
    	case 4:
    	printf("THE END? \n");
    	op=1;
    	break;
    	default:
    	printf("Opcion no valida \n");
    	break;
    	
	}
	system("pause");
	system("CLS");
	}
	while( op != 1 );
	return 0;
}

void AsignarKey( Tdato Arreglo[] )
{
    int i ;
    for( i = 0 ; i<TAM ; i++ )
        {
            Arreglo[ i ] = NULL ;
        }
}

void LoadThash( Tdato key[] ){
	FILE *fa;
	Tdato temp = NULL;
	int valor, pos;
    fa=fopen("numeros.txt","r");
    int feof(FILE *fa);
    if ( fa )
    {
    	printf("Leyendo datos del archivo ...\n");
    	while( !feof( fa) )
    	{
    		 fscanf( fa , "%d" , &valor ) ;
                pos = valor % TAM ;
                printf( "| Posicion | %3d | Valor | %3d |\n", pos, valor ) ;
                temp = GenDatoValor( valor ) ;
                if( !key[ pos ] )
                    {
                        key[ pos ] = temp ;
                    }
                    else
					{
                        temp->sig = key[ pos ] ;
                        key[ pos ] = temp ;
                        temp = NULL ;
					}
		}
		printf("\n\t Archivo leido correctamente \n");
	}
	else
	{
		printf("El archivo no pudo ser leido \n");
	}
    fclose(fa);
}

Tdato DeleteThash( Tdato lista, int num ){
	Tdato nodo=NULL, temp= NULL;
	temp = lista;
	if ( temp )
	{
		if(temp->dato == num )
		{
			temp = temp->sig;
			return temp;
		}
		else
		{
			while( temp!=NULL && temp->dato <= num )
			{
				if( (temp->sig)->dato == num )
				{
					nodo=temp->sig;
					temp->sig = nodo->sig;
					nodo->sig=NULL;
					return nodo;
				}
				temp = temp->sig;
			}
		}
	}
	return nodo = NULL;
}

Tdato FindThash( Tdato lista , int num ){
	Tdato temp ;
    temp = lista ;
    do
        {
            if( temp->dato >= num )
                {
                	if( temp->dato == num )
                	{
                		return temp;
					}
					return temp=NULL;
                }
            temp = temp->sig ;
        } while( temp ) ;
    return temp = NULL ;
}


int leenum(int ri, int rs, char *msg, char *msgError){
	char xnum[30];
	int num;
	do
	{
		puts(msg);
		fflush(stdin);
		gets(xnum);
		num = atoi(xnum);
		if (num<ri || num>rs)
		{
			puts(msgError);
			system("pause");
		}
	} while (num<ri || num>rs);
	return num;
}

Tdato GenDatoValor( int valor )
{
	Tdato temp ;
	temp = ( Tdato )malloc( sizeof( stdato ) ) ;
	temp->dato = valor ;
	return temp ;
}
