/*
 * Parser.h
 *
 *  Created on: 21 jun. 2021
 *      Author: Luk
 */

#ifndef PARSER_H_
#define PARSER_H_

int parser_ArticlesFromText(FILE* pFile , LinkedList* pArrayListArticles);
int parser_PosicionArancelariaFromText(FILE* pFile , Dictionary* pDictPosicionArancelaria);
int parser_transporteMaritimoFromText(FILE* pFile , TransporteMar* pTrasporteMaritimo);
int parser_transporteAereoFromText(FILE* pFile , TransporteAereo* pTransporteAereo);

#endif /* PARSER_H_ */
