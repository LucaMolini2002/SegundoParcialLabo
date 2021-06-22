/*
 * TransporteMar.h
 *
 *  Created on: 22 jun. 2021
 *      Author: Luk
 */

#ifndef TRANSPORTEMAR_H_
#define TRANSPORTEMAR_H_

typedef struct{
	int idTransporteMaritimo;
	float metrosCubicos;
	float precioPorMetroCubico;
}TransporteMar;

TransporteMar* tm_new(void);
TransporteMar* tm_newParam(int idTranspMaritimo,float metrosCubicos, float precioPorMetroCubico);
TransporteMar* tm_add();
int tm_delete(TransporteMar* this);

int tm_setId(TransporteMar* this, int idTranspMaritimo);
int tm_getId(TransporteMar* this,int* flagError);

int tm_setMetrosCubicos(TransporteMar* this, float metrosCubicos);
float tm_getMetrosCubicos(TransporteMar* this,int* flagError);

int tm_setPrecioPorMetroCubico(TransporteMar* this, float precioPorMetroCubico);
float tm_getPrecioPorMetroCubico(TransporteMar* this,int* flagError);

#endif /* TRANSPORTEMAR_H_ */
