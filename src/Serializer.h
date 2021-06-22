/*
 * Serializer.h
 *
 *  Created on: 22 jun. 2021
 *      Author: Luk
 */

#ifndef SERIALIZER_H_
#define SERIALIZER_H_

int serializer_ArticuloToText(FILE* pFile , Dictionary* pDictArticulo);
int serializer_posicionArancelariaToText(FILE* pFile , Dictionary* pDictPosicionArancelaria);
int serializer_transporteMaritimoToText(FILE* pFile ,TransporteMar* transporteMaritimo);
int serializer_transporteAereoToText(FILE* pFile ,TransporteAereo* transporteAereo);

#endif /* SERIALIZER_H_ */
