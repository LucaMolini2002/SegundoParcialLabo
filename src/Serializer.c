/*
 * Serializer.c
 *
 *  Created on: 22 jun. 2021
 *      Author: Luk
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "Dictionary.h"
#include "articulo.h"
#include "transporteMar.h"
#include "transporteAereo.h"
#include "PosicionArancelaria.h"

int serializer_ArticuloToText(FILE* pFile , Dictionary* pDictArticulo)
{
	Articulo* pArticulo;
	LinkedList* listArticulo;
	int flag;
	int retorno=1;
	listArticulo=dict_getValues(pDictArticulo);
	if(pDictArticulo!=NULL && listArticulo!=NULL){
		fprintf(pFile,"\nNombre, Codigo, Descripcion,PaisFabricacion,Fob,PesoKG,Ancho,Alto,Profundidad, PosArancelaria");
		for(int i=0; i<ll_len(listArticulo);i++){
			pArticulo= ll_get(listArticulo, i);
			if(pArticulo!=NULL){
					fprintf(pFile,"\n%s,%s,%s,%s,%.2f,%.2f,%.2f,%.2f,%.2f,%d",
							articulo_getNombre(pArticulo, &flag),
							articulo_getCodigoAlfaNumerico(pArticulo, &flag),
							articulo_getDescripcion(pArticulo, &flag),
							articulo_getPaisFabricacion(pArticulo, &flag),
							articulo_getValorFOB(pArticulo, &flag),
							articulo_getPesoKg(pArticulo, &flag),
							articulo_getAnchoCm(pArticulo, &flag),
							articulo_getAltoCm(pArticulo, &flag),
							articulo_getProfundidadCm(pArticulo, &flag),
							articulo_getId(pArticulo, &flag));
					retorno=0;
			}
		}
		ll_deleteLinkedList(listArticulo);
	}
	return retorno;
}
int serializer_posicionArancelariaToText(FILE* pFile , Dictionary* pDictPosicionArancelaria)
{
	PosicionArancelaria* pPosicionArancelaria;
	LinkedList* listPosicionArancelaria;
	int flag;
	int retorno=1;
	listPosicionArancelaria=dict_getValues(pDictPosicionArancelaria);
	if(pDictPosicionArancelaria!=NULL && listPosicionArancelaria!=NULL)
	{
		fprintf(pFile,"\nIdPosicionArancelaria, Nomenclatura Arancelaria, PorcentajeSeguro,PorcentajeImportacion,tasaEstadistica,tipoLicencia");
		for(int i=0; i<ll_len(listPosicionArancelaria);i++)
		{
			pPosicionArancelaria= ll_get(listPosicionArancelaria, i);
			if(pPosicionArancelaria!=NULL)
			{
				fprintf(pFile,"\n%d,%s,%.2f,%.2f,%.2f,%d",
						pa_getIdPosArancelaria(pPosicionArancelaria, &flag),
					    pa_getNomenclatura(pPosicionArancelaria, &flag),
					    pa_getPorcentajeSeguro(pPosicionArancelaria, &flag),
					    pa_getPorcentajeImportacion(pPosicionArancelaria, &flag),
					    pa_getTasaEstadistica(pPosicionArancelaria, &flag),
					    pa_getTipoLicencia(pPosicionArancelaria, &flag));
				retorno=0;
			}
		}
		ll_deleteLinkedList(listPosicionArancelaria);
	}
	return retorno;
}
int serializer_transporteMaritimoToText(FILE* pFile ,TransporteMar* transporteMaritimo)
{
	int retorno=-1;
	if(pFile!=NULL)
	{
		fprintf(pFile,"IdTransporteMaritimo, MetrosCubicos, PrecioPorMetroCubico");
		fprintf(pFile,"\n%d,%.2f,%.2f",transporteMaritimo->idTransporteMaritimo,transporteMaritimo->metrosCubicos,transporteMaritimo->precioPorMetroCubico);

		retorno=0;
	}
	return retorno;
}
int serializer_transporteAereoToText(FILE* pFile ,TransporteAereo* transporteAereo)
{
	int retorno=-1;
	if(pFile!=NULL)
	{
		fprintf(pFile,"IdTransporteAereo, MetrosCubicos, PrecioPorKg");
		fprintf(pFile,"\n%d,%.2f,%.2f",transporteAereo->idTransporteAereo,transporteAereo->metrosCubicos,transporteAereo->precioPorKg);
		retorno=0;
	}
	return retorno;
}

