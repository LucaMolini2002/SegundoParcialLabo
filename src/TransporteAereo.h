/*
 * TransporteAereo.h
 *
 *  Created on: 22 jun. 2021
 *      Author: Luk
 */

#ifndef TRANSPORTEAEREO_H_
#define TRANSPORTEAEREO_H_

typedef struct{
	int idTransporteAereo;
	float precioPorKg;
	float metrosCubicos;
}TransporteAereo;

TransporteAereo* ta_new(void);
TransporteAereo* ta_newParam(int idTrAereo,float metrosCubicos, float precioPorKg);
TransporteAereo* ta_add();
int ta_delete(TransporteAereo* this);

int ta_setId(TransporteAereo* this, int idTransporteAereo);
int ta_getId(TransporteAereo* this,int* flagError);

int ta_setMetrosCubicos(TransporteAereo* this, float metrosCubicos);
float ta_getMetrosCubicos(TransporteAereo* this,int* flagError);

int ta_setPrecioPorKg(TransporteAereo* this, float precioPorKg);
float ta_getPrecioPorKg(TransporteAereo* this,int* flagError);


#endif /* TRANSPORTEAEREO_H_ */
