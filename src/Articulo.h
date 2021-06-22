/*
 * Articulo.h
 *
 *  Created on: 17 jun. 2021
 *      Author: Luk
 */

#ifndef ARTICULO_H_
#define ARTICULO_H_

typedef struct{
	char nombre[20];
	char codigoAlfaNumerico[30];
	int idArticulo;
	char descripcion[50];
	char paisFabricacion[20];
	float valorFOB;
	float pesoKg;
	float altoCm;
	float anchoCm;
	float profundidadCm;
	int idPosicionArancelaria;
}Articulo;

Articulo* articulo_new(void);
Articulo* articulo_newParam(int idArticulo,char* nombre,char* codigoAlfaNumerico,char* descripcion,
		char* paisFabricacion,float valorFOB,float pesoKg,float altoCm,float anchoCm,float profundidadCm,int idPosicionArancelaria);

int articulo_delete(Articulo* this);

int articulo_setNombre(Articulo* this, char* nombre);
char* articulo_getNombre(Articulo* this,int* flagError);

int articulo_setDescrpcion(Articulo* this, char* descripcion);
char* articulo_getDescripcion(Articulo* this,int* flagError);

int articulo_setPaisFabricacion(Articulo* this, char* paisFabricacion);
char* articulo_getPaisFabricacion(Articulo* this,int* flagError);

int articulo_setValorFOB(Articulo* this, float valorFOB);
int articulo_getValorFOB(Articulo* this, int* flagError);

int articulo_setId(Articulo* this, int idEmpleado);
int* articulo_getId(Articulo* this,int* flagError);

int articulo_setCodigoAlfanumerico(Articulo* this, char* codigoAlfaNumerico);
int articulo_getCodigoAlfanumerico(Articulo* this, int* flagError);

int articulo_setPesoKg(Articulo* this, float pesoKg);
float* articulo_getPesoKg(Articulo* this,int* flagError);

int articulo_setAltoCm(Articulo* this, float altoCm);
float* articulo_getAltoCm(Articulo* this,int* flagError);

int articulo_setAnchoCm(Articulo* this, float anchoCm);
float* articulo_getAnchoCm(Articulo* this,int* flagError);

int articulo_setProfundidadCm(Articulo* this, float profundidadCm);
float* articulo_getProfundidadCm(Articulo* this,int* flagError);

#endif /* ARTICULO_H_ */
