/*
 * Calculos.h
 *
 *  Created on: 22 jun. 2021
 *      Author: Luk
 */

#ifndef CALCULOS_H_
#define CALCULOS_H_

float calculo_precioFinalTransporteMaritimo(TransporteMar trMaritimo,Articulo* pArticulo,
		PosicionArancelaria* pPosArancelaria,float* precioFinalMaritimo);
float cal_precioFinalTransporteAereo(TransporteAereo trAereo,Articulo* pArticulo,PosicionArancelaria* pPosArancelaria,float* precioFinalAereo);
float cal_baseImponibleTransporteMaritimo(Articulo* pArticulo,TransporteMar trMaritimo,PosicionArancelaria* pPosArancelaria,float* baseImponibleMaritima);
float cal_seguro(Articulo* pArticulo,PosicionArancelaria* pPosArancelaria,float* seguro);
float cal_proporcionalMaritimo(Articulo* pArticulo,TransporteMar transporteMaritimo, float* propMaritimo);
float cal_volumenCubico(Articulo* pArticulo, float* volumenArticulo);
float cal_porcentajeImportacion(PosicionArancelaria* pPosicionArancelaria,float baseImponible ,float* importacionFinal);
float cal_porcentajeTasaEstadistica(PosicionArancelaria* pPosArancelaria,float baseImponible ,float* tasaFinal);
float cal_baseImponibleAereo(Articulo* pArticulo,TransporteAereo trAereo,PosicionArancelaria* pPosicionArancelaria,float* baseImponibleAereo);

#endif /* CALCULOS_H_ */
