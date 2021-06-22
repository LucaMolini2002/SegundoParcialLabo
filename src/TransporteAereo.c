/*
 * TransporteAereo.c
 *
 *  Created on: 22 jun. 2021
 *      Author: Luk
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"
#include "LinkedList.h"
#include "transporteAereo.h"

TransporteAereo* ta_new(void){
	return (TransporteAereo*) malloc(sizeof(TransporteAereo));
}
TransporteAereo* ta_newParam(int idTrAereo,float metrosCubicos, float precioPorKg){
	TransporteAereo* auxTrAereo = ta_new();
	if(auxTrAereo!=NULL){

		if(ta_setMetrosCubicos(auxTrAereo, metrosCubicos)<0 ||
		   ta_setPrecioPorKg(auxTrAereo, precioPorKg)<0)
		{

			ta_delete(auxTrAereo);
			auxTrAereo=NULL;
		}
	}
	return auxTrAereo;
}
TransporteAereo* ta_add(){

	float metrosCubicos;
	float precioPorKg;

	if(!utn_getFloat(&metrosCubicos,"\nIngrese los metros cubicos:","Error",1,999999, 2) &&
	   !utn_getFloat(&precioPorKg,"\nIngrese el precio por Kg:","Error",1,999999, 2)){

		TransporteAereo* auxTrAereo= ta_new();

		if(!ta_setMetrosCubicos(auxTrAereo, metrosCubicos) &&
			!ta_setPrecioPorKg(auxTrAereo, precioPorKg)){

			return auxTrAereo;
		}else{
			ta_delete(auxTrAereo);
		}
	}
	return NULL;
}
int ta_delete(TransporteAereo* this){
	int retorno = -1;
	if(this != NULL)
	{
		free(this);
		retorno = 0;
	}
	return retorno;
}
int ta_setId(TransporteAereo* this, int idTransporteAereo){
	int retorno = -1;
	if(this != NULL)
	{
		this->idTransporteAereo = idTransporteAereo;
		retorno = 0;
	}
	return retorno;
}
int ta_getId(TransporteAereo* this,int* flagError){
	*flagError = -1;
	int auxIdTransporteAereo = -1;
	if(this != NULL && flagError != NULL )
	{
		auxIdTransporteAereo=this->idTransporteAereo;
		*flagError = 0;
	}
	return auxIdTransporteAereo;
}

int ta_setMetrosCubicos(TransporteAereo* this, float metrosCubicos){
	int retorno = -1;
	if(this != NULL)
	{
		this->metrosCubicos = metrosCubicos;
		retorno = 0;
	}
	return retorno;
}
float ta_getMetrosCubicos(TransporteAereo* this,int* flagError){
	*flagError = -1;
	float auxMetrosCubicos = -1;
	if(this != NULL && flagError != NULL )
	{
		auxMetrosCubicos=this->metrosCubicos;
		*flagError = 0;
	}
	return auxMetrosCubicos;
}

int ta_setPrecioPorKg(TransporteAereo* this, float precioPorKg){
	int retorno = -1;
	if(this != NULL)
	{
		this->precioPorKg = precioPorKg;
		retorno = 0;
	}
	return retorno;

}
float ta_getPrecioPorKg(TransporteAereo* this,int* flagError){
	*flagError = -1;
	float auxPrecioPorKg = -1;
	if(this != NULL && flagError != NULL )
	{
		auxPrecioPorKg=this->precioPorKg;
		*flagError = 0;
	}
	return auxPrecioPorKg;
}
