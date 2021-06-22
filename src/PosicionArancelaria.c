/*
 * PosicionArancelaria.c
 *
 *  Created on: 22 jun. 2021
 *      Author: Luk
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PosicionArancelaria.h"
#include "utn.h"
#include "LinkedList.h"

PosicionArancelaria* pa_new(void)
{
	return (PosicionArancelaria*) malloc(sizeof(PosicionArancelaria));
}

PosicionArancelaria* pa_newParam(int idPA, char nomenclaturaArancelaria, float porcentajeDelSeguro,
		float porcentajeImportacion,float porcentajeTasaEstadistica, char tipoDeLicencia)
{
	PosicionArancelaria* auxPA = pa_new();
	if(auxPA != NULL)
	{
		if  (pa_setNomenclaturaArancelaria(auxPA,nomenclaturaArancelaria) < 0 ||
			 pa_setPorcentajeDelSeguro(auxPA,porcentajeDelSeguro) < 0 ||
			 pa_setPorcentajeImportacion(auxPA,porcentajeImportacion) < 0 ||
			 pa_setPorcentajeTasaEstadistica(auxPA,porcentajeTasaEstadistica) < 0 ||
			 pa_setTipoDeLicencia(auxPA,tipoDeLicencia) < 0 ||
			 pa_setId(auxPA,idPA) < 0 )
		{
			articulo_delete(auxPA);
			auxPA = NULL;
		}
	}
	return auxPA;
}

PosicionArancelaria* pa_add(int idPosicionArancelaria){
	PosicionArancelaria* auxPA;
	char nomenclaturaArancelaria[250];
	float porcentajeDelSeguro;
	float porcentajeImportacion;
	float porcentajeTasaEstadistica;
	int tipoDeLicencia;

	if(!utn_isValidAlphaNumericCode(nomenclaturaArancelaria,250,"\nIngrese nomenclatura arancelaria: ","Error") &&
	   !utn_getFloat(&porcentajeDelSeguro,"\nIngrese porcentaje del seguro: ","Error", 0, 999999, 2) &&
	   !utn_getFloat(&porcentajeImportacion,"\nIngrese porcentaje de importacion: ","Error", 0, 999999, 2) &&
	   !utn_getFloat(&porcentajeTasaEstadistica,"\nIngrese porcentaje de tasa estadistica: ","Error", 0, 999999, 2) &&
	   !utn_getInt(&tipoDeLicencia,"Ingrese tipo de licencia(1-Automatico,2-No automatico): ","Error", 1, 2, 2)){

		auxPA= pa_new();

		if(!posArancelaria_setIdPosArancelaria(auxPA, idPosicionArancelaria) &&
		   !posArancelaria_setNomenclatura(auxPA, nomenclaturaArancelaria) &&
		   !posArancelaria_setPorcentajeSeguro(auxPA, porcentajeDelSeguro) &&
		   !posArancelaria_setPorcentajeImportacion(auxPA, porcentajeImportacion) &&
		   !posArancelaria_setTasaEStadistica(auxPA, porcentajeTasaEstadistica) &&
		   !posArancelaria_setTipoLicencia(auxPA, tipoDeLicencia)){
			return auxPA;
		}else{
			pa_delete(auxPA);
			auxPA = NULL;
		}
	}
return auxPA;
}

int pa_delete(PosicionArancelaria* this)
{
	int retorno = -1;
	if(this != NULL)
	{
		free(this);
		retorno = 0;
	}
	return retorno;
}

int pa_setNomenclaturaArancelaria(PosicionArancelaria* this, char* nomenclaturaArancelaria)
{
    int retorno = 0;
    if(this != NULL && nomenclaturaArancelaria != NULL)
    {
        strcpy(this->nomenclaturaArancelaria, nomenclaturaArancelaria);
        retorno = 1;
    }
    return retorno;
}

int pa_getNomenclaturaArancelaria(PosicionArancelaria* this, char* nomenclaturaArancelaria)
{
    int retorno = 0;
    if(this != NULL && nomenclaturaArancelaria != NULL)
    {
        strcpy(nomenclaturaArancelaria, this->nomenclaturaArancelaria);
        retorno = 1;
    }
    return retorno;
}

int pa_setTipoDeLicencia(PosicionArancelaria* this, int tipoDeLicencia)
{
    int retorno = 0;
    if(this != NULL && tipoDeLicencia != NULL)
    {
        strcpy(this->tipoDeLicencia, tipoDeLicencia);
        retorno = 1;
    }
    return retorno;
}

int pa_getTipoDeLicencia(PosicionArancelaria* this, int* tipoDeLicencia)
{
    int retorno = 0;
    if(this != NULL && tipoDeLicencia != NULL)
    {
        strcpy(tipoDeLicencia, this->tipoDeLicencia);
        retorno = 1;
    }
    return retorno;
}

int pa_setPorcentajeDelSeguro(PosicionArancelaria* this, float porcentajeDelSeguro)
{
    int retorno = 0;
    if(this != NULL && porcentajeDelSeguro > 0)
    {
        this->porcentajeDelSeguro = porcentajeDelSeguro;
        retorno = 1;
    }
    return retorno;
}

int pa_getPorcentajeDelSeguro(PosicionArancelaria* this, float* porcentajeDelSeguro)
{
    int retorno = 0;
    if(this != NULL)
    {
        *porcentajeDelSeguro = this->porcentajeDelSeguro;
        retorno = 1;
    }
    return retorno;
}

int pa_setPorcentajeImportacion(PosicionArancelaria* this, float porcentajeImportacion)
{
    int retorno = 0;
    if(this != NULL && porcentajeImportacion > 0)
    {
        this->porcentajeImportacion = porcentajeImportacion;
        retorno = 1;
    }
    return retorno;
}

int pa_getPorcentajeImportacion(PosicionArancelaria* this, float* porcentajeImportacion)
{
    int retorno = 0;
    if(this != NULL)
    {
        *porcentajeImportacion = this->porcentajeImportacion;
        retorno = 1;
    }
    return retorno;
}

int pa_setPorcentajeTasaEstadistica(PosicionArancelaria* this, float porcentajeTasaEstadistica)
{
    int retorno = 0;
    if(this != NULL && porcentajeTasaEstadistica > 0)
    {
        this->porcentajeTasaEstadistica = porcentajeTasaEstadistica;
        retorno = 1;
    }
    return retorno;
}

int pa_getPorcentajeTasaEstadistica(PosicionArancelaria* this, float* porcentajeTasaEstadistica)
{
    int retorno = 0;
    if(this != NULL)
    {
        *porcentajeTasaEstadistica = this->porcentajeTasaEstadistica;
        retorno = 1;
    }
    return retorno;
}
