/*
 * TransporteMar.c
 *
 *  Created on: 22 jun. 2021
 *      Author: Luk
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"
#include "LinkedList.h"
#include "TransporteMar.h"

TransporteMar* tm_new(void){
	return (TransporteMar*) malloc(sizeof(TransporteMar));
}
TransporteMar* tm_newParam(int idTranspMaritimo,float metrosCubicos, float precioPorMetroCubico){
	TransporteMar* auxTranspMaritimo = tm_new();
	if(auxTranspMaritimo!=NULL){
		if(tm_setMetrosCubicos(auxTranspMaritimo, metrosCubicos)<0 ||
			tm_setPrecioPorMetroCubico(auxTranspMaritimo, precioPorMetroCubico)<0){

			tm_delete(auxTranspMaritimo);
			auxTranspMaritimo=NULL;
		}
	}
	return auxTranspMaritimo;
}
TransporteMar* tm_add(){
	TransporteMar* auxTrMaritimo;
	float metrosCubicos;
	float precioPorMetroCubico;

	if(!utn_getFloat(&metrosCubicos,"\nIngrese los metros Cubicos:","Error",1,999999, 2) &&
	   !utn_getFloat(&precioPorMetroCubico,"\nIngrese el precio por metro Cubico:","Error",1,999999, 2)){

		auxTrMaritimo = tm_new();

		if(!tm_setMetrosCubicos(auxTrMaritimo, metrosCubicos) &&
			!tm_setPrecioPorMetroCubico(auxTrMaritimo, precioPorMetroCubico)){

			return auxTrMaritimo;
		}
		else
		{
			tm_delete(auxTrMaritimo);
			auxTrMaritimo = NULL;
		}
	}
	return auxTrMaritimo;
}
int tm_delete(TransporteMar* this){
	int retorno = -1;
	if(this != NULL)
	{
		free(this);
		retorno = 0;
	}
	return retorno;
}
int tm_setId(TransporteMar* this, int idTranspMaritimo){
	int retorno = -1;
	if(this != NULL)
	{
		this->idTranspMaritimo = idTranspMaritimo;
		retorno = 0;
	}
	return retorno;
}
int tm_getId(TransporteMar* this,int* flagError){
	*flagError = -1;
	int auxIdTrMaritimo = -1;
	if(this != NULL && flagError != NULL )
	{
		auxIdTrMaritimo=this->metrosCubicos;
		*flagError = 0;
	}
	return auxIdTrMaritimo;
}
int tm_setMetrosCubicos(TransporteMar* this, float metrosCubicos){
	int retorno = -1;
	if(this != NULL)
	{
		this->metrosCubicos = metrosCubicos;
		retorno = 0;
	}
	return retorno;
}
float tm_getMetrosCubicos(TransporteMar* this,int* flagError){
	*flagError = -1;
	float auxMetrosCubicos = -1;
	if(this != NULL && flagError != NULL )
	{
		auxMetrosCubicos=this->metrosCubicos;
		*flagError = 0;
	}
	return auxMetrosCubicos;
}

int tm_setPrecioPorMetroCubico(TransporteMar* this, float precioPorMetroCubico){
	int retorno = -1;
	if(this != NULL)
	{
		this->precioPorMetroCubico = precioPorMetroCubico;
		retorno = 0;
	}
	return retorno;
}
float tm_getPrecioPorMetroCubico(TransporteMar* this,int* flagError){
	*flagError = -1;
	float auxPrecioPorMetroCubico = -1;
	if(this != NULL && flagError != NULL )
	{
		auxPrecioPorMetroCubico=this->precioPorMetroCubico;
		*flagError = 0;
	}
	return auxPrecioPorMetroCubico;
}
