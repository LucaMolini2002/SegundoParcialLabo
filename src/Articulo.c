/*
 * Articulo.c
 *
 *  Created on: 21 jun. 2021
 *      Author: Luk
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Articulo.h"
#include "utn.h"
#include "LinkedList.h"

Articulo* articulo_new(void)
{
	return (Articulo*) malloc(sizeof(Articulo));
}

Articulo* articulo_newParam(int idArticulo,char* nombre,char* codigoAlfaNumerico,char* descripcion,
		char* paisFabricacion,float valorFOB,float pesoKg,float altoCm,float anchoCm,float profundidadCm,int idPosicionArancelaria)
{
	Articulo* auxArticulo = articulo_new();
	if(auxArticulo!= NULL)
	{
		if  ( 	articulo_setIdArticulo(auxArticulo,idArticulo) < 0 ||
				articulo_setNombre(auxArticulo,nombre) < 0 ||
				articulo_setCodigo(auxArticulo,codigoAlfaNumerico) < 0 ||
				articulo_setDescripcion(auxArticulo,descripcion) < 0 ||
				articulo_setPaisFabricacion(auxArticulo,paisFabricacion) < 0 ||
				articulo_setFob(auxArticulo,valorFOB) < 0 ||
				articulo_setPesoKg(auxArticulo,pesoKg) <0 ||
				articulo_setAlto(auxArticulo,altoCm) <0 ||
				articulo_setAncho(auxArticulo,anchoCm) <0 ||
				articulo_setProfundidad(auxArticulo,profundidadCm) <0 ||
				articulo_setIdPosArancelaria(auxArticulo, idPosicionArancelaria) < 0) //falta id pos aranceleria
		{
			articulo_delete(auxArticulo);
			auxArticulo = NULL;
		}
	}
	return auxArticulo;
}

int articulo_delete(Articulo* this)
{
	int retorno = -1;
	if(this != NULL)
	{
		free(this);
		retorno = 0;
	}
	return retorno;
}

Articulo* articulo_add(int idArticulo)
{
	int retorno=-1;
	char nombre[25];
	char codigoAlfaNumerico[25];
	char descripcion[250];
	char paisFabricacion[25];
	float valorFOB;
	float pesoKg;
	float altoCm;
	float anchoCm;
	float profundidadCm;

		if(!utn_getNombre(nombre, 25, "Ingrese nombre del Producto: \n","Error") &&
		   !utn_isValidAlphaNumericCode(codigoAlfaNumerico,25,"Ingrese el codigo del Producto: \n","Error") &&
		   !utn_getNombre(descripcion,250,"Ingrese descripcion del Producto: \n","Error") &&
		   !utn_getString(paisFabricacion,25,"Ingrese pais de fabricacion: \n","error") &&
		   !utn_getFloat(&valorFOB,"Ingrese valor Fob: \n","Error", 0.0,99999.9,2) &&
		   !utn_getFloat(&pesoKg,"Ingrese valor peso en Kg: \n","Error\n", 0.0,99999.9,2) &&
		   !utn_getFloat(&altoCm,"Ingrese valor alto en cm: \n","Error\n",  0.0,99999.9,2) &&
		   !utn_getFloat(&anchoCm,"Ingrese valor ancho en cm: \n","Error\n",  0.0,99999.9,2) &&
		   !utn_getFloat(&profundidadCm,"Ingrese valor profundidad en cm: \n","Error\n", 0.0,99999.9,2))
		{

		    Articulo* auxArticulo= articulo_new();

			if( 	!articulo_setId(auxArticulo,idArticulo) &&
					!articulo_setNombre(auxArticulo,nombre) &&
					!articulo_setCodigoAlfaNumerico(auxArticulo,codigoAlfaNumerico) &&
					!articulo_setDescripcion(auxArticulo,descripcion) &&
					!articulo_setPaisFabricacion(auxArticulo,paisFabricacion) &&
					!articulo_setValorFOB(auxArticulo,valorFOB) &&
					!articulo_setPesoKg(auxArticulo,pesoKg) &&
					!articulo_setAnchoCm(auxArticulo,anchoCm) &&
					!articulo_setAltoCm(auxArticulo,altoCm) &&
					!articulo_setProfundidadCm(auxArticulo,profundidadCm))
			{
				retorno = auxArticulo;
			}
			else
			{
				articulo_delete(auxArticulo);
			}
		}
	return NULL;
}

int articulo_setNombre(Articulo* this, char* nombre)
{
    int retorno = 0;
    if(this != NULL && nombre != NULL)
    {
        strcpy(this->nombre, nombre);
        retorno = 1;
    }
    return retorno;
}

char* articulo_getNombre(Articulo* this,int* flagError)
{
	*flagError = -1;
	char* auxNombre= NULL;
	if(this != NULL && flagError != NULL )
	{
		auxNombre = this->nombre;
		*flagError = 0;
	}
	return auxNombre;
}

int articulo_setValorFOB(Articulo* this, float valorFOB)
{
	int retorno = 0;
	if(this != NULL && valorFOB > 0 )
	{
		this->valorFOB = valorFOB;
		retorno = 1;
	}
	return retorno;
}

int articulo_getValorFOB(Articulo* this, int* flagError)
{
	*flagError = -1;
	int* aux= NULL;
	if(this != NULL && flagError != NULL )
	{
		aux = this->valorFOB;
		*flagError = 0;
	}
	return aux;
}

int articulo_setCodigoAlfanumerico(Articulo* this, char* codigoAlfaNumerico)
{
	int retorno = 0;
	if(this != NULL && codigoAlfaNumerico != NULL)
	{
		strcpy(this->codigoAlfaNumerico, codigoAlfaNumerico);
		retorno = 1;
	}
	return retorno;
}

int articulo_getCodigoAlfanumerico(Articulo* this, int* flagError)
{
	*flagError = -1;
	char* auxcodigoAlfaNumerico= NULL;
	if(this != NULL && flagError != NULL )
	{
		auxcodigoAlfaNumerico = this->codigoAlfaNumerico;
		*flagError = 0;
	}
	return auxcodigoAlfaNumerico;
}

int articulo_setId(Articulo* this, int id)
{
    int retorno = 0;
    if(this != NULL && id > 0 && id <= 2000)
    {
        this->idArticulo = id;
        retorno = 1;
    }
    return retorno;
}

int* articulo_getId(Articulo* this,int* flagError)
{
	*flagError = -1;
	int* aux= NULL;
	if(this != NULL && flagError != NULL )
	{
		aux = this->idArticulo;
		*flagError = 0;
	}
	return aux;
}

int articulo_setDescripcion(Articulo* this, char* descripcion)
{
    int retorno = 0;
    if(this != NULL && descripcion != NULL)
    {
        strcpy(this->descripcion, descripcion);
        retorno = 1;
    }
    return retorno;
}

char* articulo_getDescripcion(Articulo* this,int* flagError)
{
	*flagError = -1;
	char* auxDescripcion= NULL;
	if(this != NULL && flagError != NULL )
	{
		auxDescripcion = this->descripcion;
		*flagError = 0;
	}
	return auxDescripcion;
}

int articulo_setPaisFabricacion(Articulo* this, char* paisFabricacion)
{
    int retorno = 0;
    if(this != NULL && paisFabricacion != NULL)
    {
        strcpy(this->paisFabricacion, paisFabricacion);
        retorno = 1;
    }
    return retorno;
}

char* articulo_getPaisFabricacion(Articulo* this,int* flagError)
{
	*flagError = -1;
	char* auxPaisFabricacion= NULL;
	if(this != NULL && flagError != NULL )
	{
		auxPaisFabricacion = this->paisFabricacion;
		*flagError = 0;
	}
	return auxPaisFabricacion;
}

int articulo_setPesoKg(Articulo* this, float pesoKg)
{
    int retorno = 0;
    if(this != NULL && pesoKg > 0 )
    {
        this->pesoKg = pesoKg;
        retorno = 1;
    }
    return retorno;
}

float* articulo_getPesoKg(Articulo* this,int* flagError)
{
	*flagError = -1;
	float* aux= NULL;
	if(this != NULL && flagError != NULL )
	{
		aux = this->pesoKg;
		*flagError = 0;
	}
	return aux;
}

int articulo_setAltoCm(Articulo* this, float altoCm)
{
    int retorno = 0;
    if(this != NULL && altoCm > 0 )
    {
        this->altoCm = altoCm;
        retorno = 1;
    }
    return retorno;
}

float* articulo_getAltoCm(Articulo* this,int* flagError)
{
	*flagError = -1;
	float* aux= NULL;
	if(this != NULL && flagError != NULL )
	{
		aux = this->altoCm;
		*flagError = 0;
	}
	return aux;
}

int articulo_setAnchoCm(Articulo* this, float anchoCm)
{
    int retorno = 0;
    if(this != NULL && anchoCm > 0 )
    {
        this->anchoCm = anchoCm;
        retorno = 1;
    }
    return retorno;
}

float* articulo_getAnchoCm(Articulo* this,int* flagError)
{
	*flagError = -1;
	float* aux= NULL;
	if(this != NULL && flagError != NULL )
	{
		aux = this->anchoCm;
		*flagError = 0;
	}
	return aux;
}

int articulo_setProfundidadCm(Articulo* this, float profundidadCm)
{
    int retorno = 0;
    if(this != NULL && profundidadCm > 0 )
    {
        this->profundidadCm = profundidadCm;
        retorno = 1;
    }
    return retorno;
}

float* articulo_getProfundidadCm(Articulo* this,int* flagError)
{
	*flagError = -1;
	float* aux= NULL;
	if(this != NULL && flagError != NULL )
	{
		aux = this->profundidadCm;
		*flagError = 0;
	}
	return aux;
}

int articulo_compareByNombre(void* art1, void* art2)
{
	int retorno=-1;
	int flagError;
	Articulo* articulo1 = NULL;
	Articulo* articulo2 = NULL;
	articulo1=(Articulo*)art1;
	articulo2=(Articulo*)art2;
	if(strcmp(articulo_getNombre(articulo1, &flagError),articulo_getNombre(articulo2, &flagError))>0)
	{
		retorno=1;
	}
	return retorno;
}




