/*
 * PosicionArancelaria.h
 *
 *  Created on: 20 jun. 2021
 *      Author: Luk
 */

#ifndef POSICIONARANCELARIA_H_
#define POSICIONARANCELARIA_H_

typedef struct{
	int idPA;
	char nomenclaturaArancelaria[50];
	float porcentajeDelSeguro;
	float porcentajeImportacion;
	float porcentajeTasaEstadistica;
	int tipoDeLicencia[30];
}PosicionArancelaria;

PosicionArancelaria* pa_new(void);
PosicionArancelaria* pa_newParam(int idPA, char nomenclaturaArancelaria, float porcentajeDelSeguro,
		float porcentajeImportacion,float porcentajeTasaEstadistica, char tipoDeLicencia);

PosicionArancelaria* pa_add(int idPosicionArancelaria)

int pa_delete(PosicionArancelaria* this);

int pa_setNomenclaturaArancelaria(PosicionArancelaria* this, char* nomenclaturaArancelaria);
int pa_getNomenclaturaArancelaria(PosicionArancelaria* this, char* nomenclaturaArancelaria);

int pa_setPorcentajeDelSeguro(PosicionArancelaria* this, float porcentajeDelSeguro);
int pa_getPorcentajeDelSeguro(PosicionArancelaria* this, float* porcentajeDelSeguro);

int pa_setPorcentajeImportacion(PosicionArancelaria* this, float porcentajeImportacion);
int pa_getPorcentajeImportacion(PosicionArancelaria* this, float* porcentajeImportacion);

int pa_setPorcentajeTasaEstadistica(PosicionArancelaria* this, float porcentajeTasaEstadistica);
int pa_getPorcentajeTasaEstadistica(PosicionArancelaria* this, float* porcentajeTasaEstadistica);

int pa_setTipoDeLicencia(PosicionArancelaria* this, int tipoDeLicencia);
int pa_getTipoDeLicencia(PosicionArancelaria* this, int* tipoDeLicencia);

#endif /* POSICIONARANCELARIA_H_ */
