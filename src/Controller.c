/*
 * Controller.c
 *
 *  Created on: 22 jun. 2021
 *      Author: Luk
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"
#include "articulo.h"
#include "posicionArancelaria.h"
#include "transporteMar.h"
#include "transporteAereo.h"
#include "calculos.h"
#include "controller.h"
#include "LinkedList.h"
#include "Dictionary.h"
#include "parser.h"
#include "serializer.h"

int idArtMax=0;
int idPosArancelariaMax=0;
int controller_generateArticuloId()
{
	idArtMax+=1;
	return idArtMax;
}
int controller_generatePosicionArancelariaId()
{
	idPosArancelariaMax+=1;

	return idPosArancelariaMax;
}

int controller_initAll(Dictionary* pDictArticulo,Dictionary* pDictPosicionArancelaria,TransporteMar* transporteMaritimo, TransporteAereo* transporteAereo)
{
	int retorno=-1;

	if(!controller_loadArticulosFromText("articulos.txt",pDictArticulo) &&
	   !controller_loadPosicionArancelariaFromText("posicionArancelaria.txt", pDictPosicionArancelaria) &&
	   !controller_loadTransporteMaritimoFromText("transporteMaritimo.txt", transporteMaritimo) &&
	   !controller_loadTransporteAereoFromText("transporteAereo.txt", transporteAereo))
	{
		retorno=0;
	}
return retorno;
}

int controller_loadArticulosFromText(char* path ,Dictionary* pDictArt)
{
	FILE *pFile;
	int retFuncionId;
	int retorno=-1;

	pFile=fopen(path,"r");
	if(path !=NULL && pFile!=NULL && pDictArt!=NULL)
	{
		retFuncionId=parser_ArticulosFromText(pFile, pDictArt);
		if(!retFuncionId)
		{
			idArtMax=retFuncionId;
			retorno=0;
			printf("Carga realizada con exito. \n");
		}
	}
	else
	{
		printf("No se pudo abrir el archivo. ");
	}
	fclose(pFile);
    return retorno;
}

int controller_addArticle(Dictionary* pArrayListArticles,Dictionary* pDictPosArancelaria)
{
	Articulo* pArticulo;
	int idArticulo;
	int flag;
	int lenList;
	int idPosArancelaria;
	int retorno=-1;

	if(pArrayListArticles!=NULL)
	{
		idArticulo= controller_generateArticuloId();
		pArticulo= articulo_add(idArticulo);
		if(pArticulo!=NULL)
		{
			lenList= controller_ListPosicionArancelaria(pDictPosArancelaria);
			if(lenList>0)
			{
				utn_getInt(&idPosArancelaria,"Ingrese la posicion arancelaria: \n","Error \n",1,lenList,2);
				articulo_setIdPosArancelaria(pArticulo, idPosArancelaria);
				if(!dict_insert(pArrayListArticles,articulo_getCodigo(pArticulo, &flag),pArticulo))
				{
					controller_saveArticuloAsText("articulos.txt", pArrayListArticles);
					retorno=0;
				}
			}
		}
	}
	else
	{
		printf("Error");
	}

    return retorno;
}

int controller_editArticle(Dictionary* pArrayListArticles,Dictionary* pDictPosArancelaria)
{
	char codigo[25];
	Articulo* pArticulo;
	char nombre[25];
	char descripcion[250];
	char paisFabricacion[25];
	float fob;
	float pesoKg;
	float ancho;
	float alto;
	float profundidad;
	int lenList;
	int idPosArancelaria;

	if(pArrayListArticles!=NULL){
		if(!utn_getString(codigo,25,"\nIngrese el codigo del producto a modificar: ","Error")){
			pArticulo= dict_get(pArrayListArticles, codigo);

			if(pArticulo!=NULL)
			{
				if(!utn_isValidName(nombre,25,"\nIngrese nombre del Producto: ","Error") &&
				   !utn_isValidName(descripcion,250,"\nIngrese descripcion del Producto: ","Error") &&
				   !utn_isValidName(paisFabricacion,25,"\nIngrese pais de fabricacion: ","error") &&
				   !utn_getFloat(&fob,"\nIngrese valor Fob: ","Error", 0,999999,2) &&
				   !utn_getFloat(&pesoKg,"\nIngrese peso en Kg: ","Error", 0,999999,2) &&
				   !utn_getFloat(&ancho,"\nIngrese ancho en cm: ","Error", 0,999999,2) &&
				   !utn_getFloat(&alto,"\nIngrese alto en cm: ","Error", 0,999999,2) &&
				   !utn_getFloat(&profundidad,"\nIngrese profundidad en cm: ","Error", 0,999999,2))
				{

					lenList= controller_ListPosArancelaria(pDictPosArancelaria);
					if(lenList>0)
					{
						utn_getInt(&idPosArancelaria,"\nIngrese la posicion arancelaria que desee: ","Error",1,lenList,2);
						articulo_setIdPosArancelaria(pArticulo, idPosArancelaria);
					}

					if(	!articulo_setNombre(pArticulo,nombre) &&
						!articulo_setDescripcion(pArticulo,descripcion) &&
						!articulo_setPaisFabricacion(pArticulo,paisFabricacion) &&
						!articulo_setFob(pArticulo,fob) &&
						!articulo_setPesoKg(pArticulo,pesoKg) &&
						!articulo_setAncho(pArticulo,ancho) &&
						!articulo_setAlto(pArticulo,alto) &&
						!articulo_setProfundidad(pArticulo,pesoKg))
					{
						controller_saveArticuloAsText("articulos.txt", pArrayListArticles);
						printf("\nArticulo modificado exitosamente.");
						return 0;
					}
				}
			}else{
				printf("\nCodigo no encontrado.");
			}
		}
	}
    return 1;
}

int controller_removeArticle(Dictionary* pArrayListArticles)
{
	Articulo* pArticulo;
	char codigo[25];

	if(pArrayListArticles!=NULL){
		if(!utn_getString(codigo,25,"\nIngrese el codigo del Producto a eliminar: ","Error", 2)){

			pArticulo= dict_get(pArrayListArticles, codigo);

			if(pArticulo!=NULL){
				articulo_delete(pArticulo);
				dict_remove(pArrayListArticles, codigo);
				controller_saveArticuloAsText("articulos.txt", pArrayListArticles);
				printf("Se elimino el articulo con exito. \n");
			}else{
				printf("No se encontro el codigo. \n");
			}
		}
	}
    return 1;
}

int controller_ListArticcle(Dictionary* pArrayListArticles)
{
	int flagError;
	Articulo* pArticulo;
	LinkedList* listArticulo;

	listArticulo=dict_getValues(pArrayListArticles);

	if(pArrayListArticles!=NULL && listArticulo!=NULL)
	{
		printf("Nombre, CodigoAlfaNumerico, Descripcion,PaisDeFabricacion,valorFOB,PesoKG,Ancho,Alto,Profundidad, PosArancelaria\n");

		for(int i=0; i< ll_len(listArticulo);i++)
		{
			pArticulo=(Articulo*)ll_get(listArticulo, i);
			printf("\n%s,%s,%s,%s,%.2f,%.2f,%.2f,%.2f,%.2f,%d",
					articulo_getNombre(pArticulo, &flagError),
					articulo_getCodigo(pArticulo, &flagError),
					articulo_getDescripcion(pArticulo, &flagError),
					articulo_getPaisFabricacion(pArticulo, &flagError),
					articulo_getFob(pArticulo, &flagError),
					articulo_getPesoKg(pArticulo, &flagError),
					articulo_getAncho(pArticulo, &flagError),
					articulo_getAlto(pArticulo, &flagError),
					articulo_getProfundidad(pArticulo, &flagError),
					articulo_getIdPosArancelaria(pArticulo, &flagError));
		}
		ll_deleteLinkedList(listArticulo);
	}
    return 1;
}

int controller_sortArticcle(Dictionary* pArrayListArticles)
{

	LinkedList* listArticulo;
	int option;
	if(pArrayListArticles!=NULL)
	{
		listArticulo=dict_getValues(pArrayListArticles);
		if(listArticulo!=NULL)
		{
			if(!ll_sort(listArticulo, articulo_compareByNombre, 1))
			{
				controller_ListArticuloList(listArticulo);
			}
		}
		ll_deleteLinkedList(listArticulo);
	}
	return 0;
}

int controller_buscarArticulo(Dictionary* pDictPosicionArancelaria,Dictionary* pDictArticulo, TransporteAereo transporteAereo,TransporteMar transporteMaritimo)
{

	char codigoAlfaNumerico[25];
	Articulo* pArticulo;
	PosicionArancelaria* pPosicionArancelaria;
	int idPosicionArancelariaArticulo;
	char idPosArancelariaArticuloSrt[30];

	float precioFinalMaritimo;
	float precioFinalAereo;

	int retorno=-1;
	int flagError;

	if(pDictArticulo!=NULL){
		if(!utn_isValidAlphaNumericCode(codigoAlfaNumerico,25,"Ingrese el codigo del Producto: \n","Error\n")){
			pArticulo=(Articulo*)dict_get(pDictArticulo, codigoAlfaNumerico);


			if(pArticulo!=NULL){

				idPosicionArancelariaArticulo=articulo_getIdPosArancelaria(pArticulo, &flagError);

				snprintf(idPosArancelariaArticuloSrt,sizeof(idPosArancelariaArticuloSrt),"%d",idPosicionArancelariaArticulo);
				pPosicionArancelaria=(PosicionArancelaria*)dict_get(pDictPosicionArancelaria, idPosArancelariaArticuloSrt);

				cal_precioFinalTransporteMaritimo(transporteMaritimo, pArticulo, pPosicionArancelaria, &precioFinalMaritimo);
				cal_precioFinalTransporteAereo(transporteAereo, pArticulo, pPosicionArancelaria, &precioFinalAereo);

				printf("Nombre, Codigo, Descripcion,PaisFabricacion,Fob,PesoKG,Ancho,Alto,Profundidad, PosArancelaria, CostoFinalMaritimo, CostoFinalAereo\n");

				printf("\n%s,%s,%s,%s,%.2f,%.2f,%.2f,%.2f,%.2f,%d,%.2f,%.2f",
						articulo_getNombre(pArticulo, &flagError),
						articulo_getDescripcion(pArticulo, &flagError),
						articulo_getPaisFabricacion(pArticulo, &flagError),
						articulo_getValorFOB(pArticulo, &flagError),
						articulo_getCodigoAlfaNumerico(pArticulo, &flagError),
						articulo_getPesoKg(pArticulo, &flagError),
						articulo_getAnchoCm(pArticulo, &flagError),
						articulo_getAltoCm(pArticulo, &flagError),
						articulo_getProfundidadCm(pArticulo, &flagError),
						articulo_getIdPosicionArancelaria(pArticulo, &flagError),
						precioFinalMaritimo,precioFinalAereo);
				retorno=0;

			}
		}
	}
    return retorno;
}

int controller_saveArticuloAsText(char* path , Dictionary* pListArticulo)
{
	FILE *pFile;
	int retorno=-1;
	pFile=fopen(path,"w+");
	if(pFile!=NULL){
		if(!serializer_ArticuloToText(pFile, pListArticulo))
		{
			retorno=0;
		}
	}
	fclose(pFile);
    return retorno;
}

int controller_loadPosicionArancelariaFromText(char* path , Dictionary* pDictPosArancelaria)
{
	FILE *pFile;
	int retId;
	int retorno=-1;

	pFile=fopen(path,"r");
	if(path !=NULL && pFile!=NULL && pDictPosArancelaria!=NULL)
	{
		retId=parser_posicionArancelariaFromText(pFile, pDictPosArancelaria);
		if(retId>0)
		{
			printf("Carga realizada\n");
			idPosArancelariaMax=retId;
			retorno=0;
		}
	}
	else
	{
		printf("No se pudo abrir el archivo");
	}
	fclose(pFile);

    return retorno;
}

int controller_addPosicionArancelaria(Dictionary* pDictPosArancelaria)
{
	PosicionArancelaria* pPosicionArancelaria;
	char idPosicionArancelariaStr[20];
	int idPosicionArancelaria;
	if(pDictPosArancelaria!=NULL){
		idPosicionArancelaria= controller_generatePosArancelariaId();
		pPosicionArancelaria= posArancelaria_add(idPosicionArancelaria);

		if(pPosicionArancelaria!=NULL){
			snprintf(idPosicionArancelariaStr,sizeof(idPosicionArancelariaStr),"%d",idPosicionArancelaria);
			if(!dict_insert(pDictPosArancelaria,idPosicionArancelariaStr,pPosicionArancelaria)){
				controller_savePosicionArancelariaAsText("posicionArancelaria.txt", pDictPosArancelaria);
				printf("\Se agrego con exito. \n");
			}
		}
	}else{
		printf("Error");
	}

    return 1;
}

int controller_editPosicionArancelaria(Dictionary* pDictPosArancelaria)
{
	PosicionArancelaria* pPosicionArancelaria;
	int idPosArancelaria;
	char idposArancelariaStr[20];
	char nomenclatura[250];
	float porcentajeSeguro;
	float porcentajeImportacion;
	float tasaEstadistica;
	int tipoLicencia;


	if(pDictPosArancelaria!=NULL){
		if(!utn_getInt(&idPosArancelaria,"Ingrese el id de posicion Arancelaria a modificar: ","Error",0,10,2)){

			snprintf(idposArancelariaStr,sizeof(idposArancelariaStr),"%d",idPosArancelaria);
			pPosicionArancelaria= dict_get(pDictPosArancelaria, idposArancelariaStr);

			if(pPosicionArancelaria!=NULL){
				if(	!utn_isValidAlphaNumericCode(nomenclatura,250,"\nIngrese nomeclatura: ","Error") &&
					!utn_getFloat(&porcentajeSeguro,"\nIngrese el porcentaje del Seguro: ","Error", 0,50000,2) &&
					!utn_getFloat(&porcentajeImportacion,"\nIngrese el porcentaje de importacion: ","Error", 0,50000,2) &&
					!utn_getFloat(&tasaEstadistica,"\nIngrese el porcentaje de tasa de estadistica: ","Error", 0,50000,2) &&
					!utn_getInt(&tipoLicencia,"Ingrese el tipo de licencia(1-Automatica,2-No Automatica): ","Error", 1,2, 2)){

					if(!pa_setNomenclatura(pPosicionArancelaria, nomenclatura) &&
					   !pa_setPorcentajeSeguro(pPosicionArancelaria, porcentajeSeguro) &&
					   !pa_setPorcentajeImportacion(pPosicionArancelaria, porcentajeImportacion) &&
					   !pa_setTasaEStadistica(pPosicionArancelaria, tasaEstadistica) &&
					   !pa_setTipoLicencia(pPosicionArancelaria, tipoLicencia)){

						printf("La modificacion se realizo con exito. \n");
						controller_savePosicionArancelariaAsText("posicionArancelaria.txt", pDictPosArancelaria);
						return 0;
					}
				}
			}
		}
	}
    return 1;
}

int controller_removePosicionArancelaria(Dictionary* pDictPosicionArancelaria)
{
	PosicionArancelaria* pPosicionArancelaria;
	int idPosicionArancelaria;
	char idposicionArancelariaStr[20];
	if(pDictPosicionArancelaria!=NULL)
	{
		if(!utn_getInt(&idPosicionArancelaria,"Ingrese ID de la posicion arancelaria a eliminar. ","Error",0,100,2))
		{
			snprintf(idposicionArancelariaStr,sizeof(idposicionArancelariaStr),"%d",idPosicionArancelaria);
			pPosicionArancelaria= dict_get(pDictPosicionArancelaria, idposicionArancelariaStr);
			if(pPosicionArancelaria!=NULL)
			{
				posArancelaria_delete(pPosicionArancelaria);
				dict_remove(pDictPosicionArancelaria, idposicionArancelariaStr);
				controller_savePosicionArancelariaAsText("posicionArancelaria.txt", pDictPosicionArancelaria);
				printf("Se elimino con exito. \n");
			}
			else
			{
				printf("No se encontro el ID. \n");
			}
		}
	}
    return 1;
}

int controller_ListPosicionArancelaria(Dictionary* pDictPosicionArancelaria)
{
	int flagError;
	int lenList=0;

	LinkedList* listaPosicionArancelaria;
	PosicionArancelaria* pPosicionArancelaria;
	listaPosicionArancelaria=dict_getValues(pDictPosicionArancelaria);
	if(pDictPosicionArancelaria!=NULL && listaPosicionArancelaria!=NULL)
	{
		printf("\nIdPosicionArancelaria, NomenclaturaArancelaria, PorcentajeDelSeguro,PorcentajeImportacion,PorcentajetasaEstadistica,TipoLicencia");
		lenList=ll_len(listaPosicionArancelaria);
		if(lenList>0)
		{
			for(int i=0; i< lenList;i++)
			{
				pPosicionArancelaria=ll_get(listaPosicionArancelaria, i);
				printf("\n%d) %s,%.2f,%.2f,%.2f,%d",
						pa_getIdPosArancelaria(pPosicionArancelaria, &flagError),
						pa_getNomenclatura(pPosicionArancelaria, &flagError),
						pa_getPorcentajeSeguro(pPosicionArancelaria, &flagError),
						pa_getPorcentajeImportacion(pPosicionArancelaria, &flagError),
						pa_getTasaEstadistica(pPosicionArancelaria, &flagError),
						pa_getTipoDeLicencia(pPosicionArancelaria, &flagError));
			}
		}
		ll_deleteLinkedList(listaPosicionArancelaria);
	}
    return lenList;
}

int controller_savePosicionArancelariaAsText(char* path , Dictionary* pDictPosicionArancelaria)
{
	FILE *pFile;
	int retorno=-1;
	pFile=fopen(path,"w+");
	if(pFile!=NULL){
		if(!serializer_posicionArancelariaToText(pFile, pDictPosicionArancelaria))
		{
			retorno=0;
		}
	}
	fclose(pFile);
    return retorno;
}

int controller_loadTransporteMaritimoFromText(char* path,TransporteMar* transporteMaritimo)
{
	FILE *pFile;
	int retFuncion;
	int retorno=-1;

	pFile=fopen(path,"r");
	if(path !=NULL && pFile!=NULL){

		retFuncion= parser_transporteMaritimoFromText(pFile ,transporteMaritimo);

		if(!retFuncion)
		{
				printf("\nCarga realizada");
				retorno=0;
		}
	}
	else
	{
		printf("No se pudo abrir e archivo \n");
	}
	fclose(pFile);
    return retorno;
}

int controller_saveTransporteMaritimoAsText(char* path ,TransporteMar* transporteMaritimo)
{
	int ret=-1;
	FILE *pFile;

	pFile=fopen(path,"w+");
	if(pFile!=NULL){
		if(!serializer_trMaritimoToText(pFile, transporteMaritimo)){
			ret=0;
		}
	}
	fclose(pFile);
    return ret;
}

int controller_loadTransporteAereoFromText(char* path , TransporteAereo* transporteAereo)
{
	FILE *pFile;
	int retornoFuncion;
	int retorno=-1;

	pFile=fopen(path,"r");
	if(path !=NULL && pFile!=NULL)
	{
		retornoFuncion= parser_transporteAereoFromText(pFile ,transporteAereo);
		if(!retornoFuncion)
		{
				printf("Carga realizada con exito. \n");
				retorno=0;
		}
	}else{
		printf("No se pudo abrir el archivo. \n");
	}
	fclose(pFile);

    return retorno;
}

int controller_ListTransporteAereo(TransporteAereo transporteAereo)
{
	printf("\nTransporte Aereo\n\metrosCubicos -- PrecioPorKg");
	printf("\t %.2f \t %.2f \n",transporteAereo.metrosCubicos,transporteAereo.precioPorKg);
	return 0;
}

int controller_saveTransporteAereoAsText(char* path ,TransporteAereo* transporteAereo)
{
	int ret=-1;
	FILE *pFile;
	pFile=fopen(path,"w+");
	if(pFile!=NULL)
	{
		if(!serializer_transporteAereoToText(pFile, transporteAereo))
		{
			ret=0;
		}
	}
	fclose(pFile);
    return ret;
}

int controller_ListArticuloConPreciosDeTransporte(Dictionary* pDictArticulo,Dictionary* pDictPosicionArancelaria, TransporteMar transporteMaritimo, TransporteAereo transporteAereo)
{
	int flagError;
	Articulo* pArticulo;
	LinkedList* listArticulo;
	PosicionArancelaria* pPosArancelaria;
	LinkedList* listPosArancelaria;
	int  idPosArancelariaDeArticulo;
	float precioFinalMaritimo;
	float precioFinalAereo;

	listArticulo=dict_getValues(pDictArticulo);
	listPosArancelaria=dict_getValues(pDictPosicionArancelaria);

	if(pDictArticulo!=NULL && listArticulo!=NULL){
		printf("Nombre, Codigo, Descripcion, PaisFabricacion, Fob, PesoKG, Ancho, Alto, Profundidad, PosArancelaria, CostoFinalMaritimo, CostoFinalAereo\n");

		for(int i=0; i< ll_len(listArticulo);i++){
			pArticulo=(Articulo*)ll_get(listArticulo, i);
			idPosArancelariaDeArticulo=articulo_getIdPosArancelaria(pArticulo, &flagError);
			pPosArancelaria=ll_get(listPosArancelaria,idPosArancelariaDeArticulo-1);
			cal_precioFinalTransporteMaritimo(transporteMaritimo, pArticulo, pPosArancelaria, &precioFinalMaritimo);
			cal_precioFinalTransporteAereo(transporteAereo, pArticulo, pPosArancelaria, &precioFinalAereo);

			printf("\n%s, %s, %s, %s, %.2f, %.2f, %.2f, %.2f, %.2f, %d, %.2f, %.2f",
					articulo_getNombre(pArticulo, &flagError),
					articulo_getDescripcion(pArticulo, &flagError),
					articulo_getPaisFabricacion(pArticulo, &flagError),
					articulo_getCodigoAlfaNumerico(pArticulo, &flagError),
					articulo_getValorFOB(pArticulo, &flagError),
					articulo_getPesoKg(pArticulo, &flagError),
					articulo_getAnchoCm(pArticulo, &flagError),
					articulo_getAltoCm(pArticulo, &flagError),
					articulo_getProfundidadCm(pArticulo, &flagError),
					articulo_getIdPosicionArancelaria(pArticulo, &flagError),
					precioFinalMaritimo,precioFinalAereo);
		}
		ll_deleteLinkedList(listArticulo);
	}
    return 1;
}

