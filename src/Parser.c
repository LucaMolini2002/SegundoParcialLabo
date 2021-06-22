/*
 * Parser.c
 *
 *  Created on: 21 jun. 2021
 *      Author: Luk
 */

#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Articulo.h"
#include "utn.h"
#include "TransporteMar.h"
#include "TransporteAereo.h"

/** \brief Parsea los datos los datos de los articulos desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListArticles LinkedList*
 * \return int retorna la cant de articulos que se cargaron
 *
 */
int parser_ArticlesFromText(FILE* pFile , LinkedList* pArrayListArticles)
{
	int retorno=-1;
	Articulo* pAuxArticle;
	char idStr[50],nombre[128],descripcion[128],paisFabricacion[128],codigoAlfanumerico[128],
	valorFOBstr[50],pesoKgStr[50],altoCmStr[50],anchoCmStr[50],profundidadCmStr[50],volumenStr,
	valorMaritimoStr[50],valorAereoStr[50],valorAereoFinalStr[50],valorMaritimoFinalStr[50];
	int id;
	float valorFOB,pesoKg,altoCm,anchoCm,profundidadCm,volumen,valorMaritimo,valorAereo,valorAereoFinal,valorMaritimoFinal;

	int idMax=0;

	if(pFile !=NULL)
	{
		do
		{

			if(fscanf(pFile,"%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n",
					idStr,nombre,descripcion,paisFabricacion,codigoAlfanumerico,valorFOBstr,pesoKgStr,
					altoCmStr,anchoCmStr,profundidadCmStr,volumenStr,valorMaritimoStr,valorAereoStr,valorAereoFinalStr,valorMaritimoFinalStr)==15)
			{
				id=atoi(idStr);
				valorFOB=atof(valorFOBstr);
				pesoKg=atof(pesoKgStr);
				altoCm=atof(altoCmStr);
				anchoCm=atof(anchoCmStr);
				profundidadCm=atof(profundidadCmStr);
				volumen=atof(volumenStr);
				valorMaritimo=atof(valorMaritimoStr);
				valorAereo=atof(valorAereoStr);
				valorAereoFinal=atof(valorAereoFinalStr);
				valorMaritimoFinal=atof(valorMaritimoFinalStr);
				if(id>idMax)
				{
					idMax=id;
				}
			}
			else
			{
				break;
			}
			pAuxArticle=articulo_newParam(id,nombre,descripcion,paisFabricacion,codigoAlfanumerico,valorFOB,pesoKg,altoCm,anchoCm,profundidadCm,volumen,valorMaritimo,valorAereo,valorAereoFinal,valorMaritimoFinal);
			if(pAuxArticle!=NULL)
			{
				ll_add(pArrayListArticles, pAuxArticle);
			}
		}while(!feof(pFile));
			retorno = idMax;
	}
	return retorno;
}

int parser_PosicionArancelariaFromText(FILE* pFile , Dictionary* pDictPosicionArancelaria)
{
	PosicionArancelaria* pPosicionArancelaria;
	int retorno=-1;
	int idMax=0;
	char idPosisionArancelariaStr[128], nomenclaturaStr[128], porcentajeSeguroStr[128], porcentajeImportacionStr[128],tasaEstadisticaStr[128], tipoLicenciaStr[128];
	int idPosicionArancelaria;
	float porcentajeSeguro;
	float porcentajeImportacion;
	float tasaEstadistica;
	int tipoLicencia;
	int flag=0;

	if(pFile !=NULL)
	{
		do{

			if(fscanf(pFile,"%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n",
					idPosisionArancelariaStr,nomenclaturaStr,
					porcentajeSeguroStr, porcentajeImportacionStr,
					tasaEstadisticaStr,tipoLicenciaStr)==6)
			{
				if(flag!=0)
				{
					idPosicionArancelaria=atoi(idPosisionArancelariaStr);
					porcentajeSeguro=atof(porcentajeSeguroStr);
					porcentajeImportacion=atof(porcentajeImportacionStr);
					tasaEstadistica=atof(tasaEstadisticaStr);
					tipoLicencia=atof(tipoLicenciaStr);
					if(idPosicionArancelaria>idMax)
					{
						idMax=idPosicionArancelaria;
					}
					pPosicionArancelaria=pa_newParam(idPosicionArancelaria, nomenclaturaStr, porcentajeSeguro, porcentajeImportacion, tasaEstadistica, tipoLicencia);
					if(pPosicionArancelaria!=NULL)
					{
						dict_insert(pDictPosicionArancelaria, idPosisionArancelariaStr, pPosicionArancelaria);
					}
				}
			}
			flag=1;
		}while(!feof(pFile));
		return idMax;
	}
	return -1;

}
int parser_transporteMaritimoFromText(FILE* pFile , TransporteMar* pTrasporteMaritimo)
{
	int flag=0;
	int retorno=-1;
	char idTransporteMaritimoStr[15],metrosCubicosStr[250],precioPorMetroCubicoStr[250];
	int idTransporteMaritimo;
	float metrosCubicos;
	float precioPorMetroCubico;


	if(pFile !=NULL){
		do{

			if(fscanf(pFile,"%[^,],%[^,],%[^\n]\n",idTransporteMaritimoStr,metrosCubicosStr,precioPorMetroCubicoStr)==3){
				if(flag!=0){

					idTransporteMaritimo=atoi(idTransporteMaritimoStr);
					metrosCubicos=atof(metrosCubicosStr);
					precioPorMetroCubico=atof(precioPorMetroCubicoStr);

					tm_setId(pTrasporteMaritimo, idTransporteMaritimo);
					tm_setMetrosCubicos(pTrasporteMaritimo, metrosCubicos);
					tm_setPrecioPorMetroCubico(pTrasporteMaritimo, precioPorMetroCubico);
					retorno=0;
				}
			}
			flag=1;
		}while(!feof(pFile));

	}
	return retorno;
}
int parser_transporteAereoFromText(FILE* pFile , TransporteAereo* pTransporteAereo)
{
	int flag=0;
	int retorno=-1;
	char idTrAereoStr[15],metrosCubicosStr[250],precioPorKgStr[250];
	int idTransporteAereo;
	float metrosCubicos;
	float precioPorKg;


	if(pFile !=NULL)
	{
		do{
			if(fscanf(pFile,"%[^,],%[^,],%[^\n]\n",idTrAereoStr,metrosCubicosStr,precioPorKgStr)==3){
				if(flag!=0)
				{
					idTransporteAereo=atoi(idTrAereoStr);
					metrosCubicos=atof(metrosCubicosStr);
					precioPorKg=atof(precioPorKgStr);
					ta_setId(pTransporteAereo,idTransporteAereo);
					ta_setMetrosCubicos(pTransporteAereo, metrosCubicos);
					ta_setPrecioPorKg(pTransporteAereo, precioPorKg);
					retorno=0;
				}
			}
			flag=1;
		}while(!feof(pFile));
	}
	return retorno;
}
