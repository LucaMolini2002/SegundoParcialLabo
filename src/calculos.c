/*
 * calculos.c
 *
 *  Created on: 22 jun. 2021
 *      Author: Luk
 */

#include <stdio.h>
#include <stdlib.h>
#include "utn.h"
#include "articulo.h"
#include "posicionArancelaria.h"
#include "parser.h"
#include "transporteAereo.h"
#include "transporteMar.h"
#include "calculos.h"
#include "LinkedList.h"
#include "Dictionary.h"

float cal_precioFinalTransporteMaritimo(TransporteMar transporteMaritimo,Articulo* pArticulo,PosicionArancelaria* pPosicionArancelaria,float* precioFinalMaritimo)
{
	float importacionFinalMaritimo;
	float baseImponibleMaritimo;
	float tasaFinalMaritimo;

	calculo_baseImponibleMaritimo(pArticulo, transporteMaritimo, pPosicionArancelaria, &baseImponibleMaritimo);
	calcular_porcentajeImportacion(pPosicionArancelaria, baseImponibleMaritimo, &importacionFinalMaritimo);
	calcular_porcentajeTasa(pPosicionArancelaria, baseImponibleMaritimo, &tasaFinalMaritimo);

	*precioFinalMaritimo= baseImponibleMaritimo+ importacionFinalMaritimo+ tasaFinalMaritimo;

	return *precioFinalMaritimo;
}
float cal_precioFinalTransporteAereo(TransporteAereo trAereo,Articulo* pArticulo,PosicionArancelaria* pPosArancelaria,float* precioFinalAereo)
{
	float baseImponibleAerea;
	float importacionFinalAereo;
	float tasaFinalAereo;
	int flagError;


	calculo_baseImponibleAereo(pArticulo, trAereo, pPosArancelaria, &baseImponibleAerea);
	calcular_porcentajeImportacion(pPosArancelaria, baseImponibleAerea, &importacionFinalAereo);
	calcular_porcentajeTasa(pPosArancelaria, baseImponibleAerea, &tasaFinalAereo);

	*precioFinalAereo= baseImponibleAerea+ importacionFinalAereo+ tasaFinalAereo;

	return *precioFinalAereo;
}
float cal_baseImponibleTransporteMaritimo(Articulo* pArticulo,TransporteMar trMaritimo,PosicionArancelaria* pPosArancelaria,float* baseImponibleMaritima)
{
	int flagError;
	float seguro;
	float propMaritimo;
	float valorFOB;

	cal_seguro(pArticulo, pPosArancelaria, &seguro);
	cal_propMaritimo(pArticulo, trMaritimo, &propMaritimo);
	valorFOB= articulo_getFob(pArticulo, &flagError);

	*baseImponibleMaritima= valorFOB + seguro + propMaritimo;

	return 0;
}
float cal_seguro(Articulo* pArticulo,PosicionArancelaria* pPosArancelaria,float* seguro)
{

	float porcSeguro;
	float valorFOB;
	int flagError;
	porcSeguro= pa_getPorcentajeSeguro(pPosArancelaria, &flagError);
	valorFOB= articulo_getFob(pArticulo, &flagError);
	*seguro=(porcSeguro*valorFOB)/100;
	return *seguro;
}
float cal_proporcionalMaritimo(Articulo* pArticulo,TransporteMar transporteMaritimo, float* propMaritimo)
{
	int flag;
	float metrosCubicos;
	float precioPorMetroCubico;
	float volumenArt;
	float precioFinal;

	metrosCubicos= tm_getMetrosCubicos(&transporteMaritimo, &flag);
	precioPorMetroCubico= tm_getPrecioPorMetroCubico(&transporteMaritimo, &flag);

	precioFinal=metrosCubicos/precioPorMetroCubico;
	cal_volumenCubico(pArticulo, &volumenArt);
	*propMaritimo= volumenArt*precioFinal;

	return *propMaritimo;
}
float cal_volumenCubico(Articulo* pArticulo, float* volumenArticulo)
{
	int flagError;
	float anchoCm;
	float altoCm;
	float profundidadCm;
	altoCm= articulo_getAlto(pArticulo, &flagError);
	anchoCm= articulo_getAncho(pArticulo, &flagError);
	profundidadCm= articulo_getProfundidad(pArticulo, &flagError);
	*volumenArticulo= (altoCm*anchoCm*profundidadCm)/(100*100*100);
	return *volumenArticulo;
}
float cal_porcentajeImportacion(PosicionArancelaria* pPosicionArancelaria,float baseImponible ,float* importacionFinal){

	float porcentajeImportacion;
	int flag;

	porcentajeImportacion= posArancelaria_getPorcentajeImportacion(pPosicionArancelaria, &flag);

	*importacionFinal= (porcentajeImportacion * baseImponible)/100;

	return *importacionFinal;
}
float cal_porcentajeTasaEstadistica(PosicionArancelaria* pPosArancelaria,float baseImponible ,float* tasaFinal)
{

	float porcentajeTasaEstadistica;
	int flagError;

	porcentajeTasaEstadistica= pa_getTasaEStadistica(pPosArancelaria, &flagError);
	*tasaFinal= (porcentajeTasaEstadistica * baseImponible)/100;
	return *tasaFinal;
}
float cal_baseImponibleAereo(Articulo* pArticulo,TransporteAereo trAereo,PosicionArancelaria* pPosicionArancelaria,float* baseImponibleAereo)
{
	int flagError;
	float seguro;
	float propAereo;
	float valorFOB;

	cal_seguro(pArticulo, pPosicionArancelaria, &seguro);
	//cal_proporcionAereo();
	valorFOB= articulo_getvalorFOB(pArticulo, &flagError);

	*baseImponibleAereo= valorFOB + seguro + propAereo;

	return 0;
}
float cal_proporcionAereo()
{
	return 1;
}
float cal_precioPesoVolumetrico()
{

	return 1;
}
float cal_precioPesoReal()
{

	return 1;
}
