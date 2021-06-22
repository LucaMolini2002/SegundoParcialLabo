/*
 * Controller.h
 *
 *  Created on: 22 jun. 2021
 *      Author: Luk
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

int controller_generateArticuloId();
int controller_generatePosicionArancelariaId();
int controller_initAll(Dictionary* pDictArticulo,Dictionary* pDictPosicionArancelaria,TransporteMar* transporteMaritimo, TransporteAereo* transporteAereo);
int controller_loadArticulosFromText(char* path ,Dictionary* pDictArt);
int controller_addArticle(Dictionary* pArrayListArticles,Dictionary* pDictPosArancelaria);
int controller_editArticle(Dictionary* pArrayListArticles,Dictionary* pDictPosArancelaria);
int controller_removeArticle(Dictionary* pArrayListArticles);
int controller_ListArticle(Dictionary* pArrayListArticles);
int controller_sortArticle(Dictionary* pDictArticulo);
int controller_buscarArticulo(Dictionary* pDictPosicionArancelaria,Dictionary* pDictArticulo, TransporteAereo transporteAereo,TransporteMar transporteMaritimo);
int controller_saveArticuloAsText(char* path , Dictionary* pListArticulo);
int controller_loadPosicionArancelariaFromText(char* path , Dictionary* pDictPosArancelaria);
int controller_addPosicionArancelaria(Dictionary* pDictPosArancelaria);
int controller_editPosicionArancelaria(Dictionary* pDictPosArancelaria);
int controller_removePosicionArancelaria(Dictionary* pDictPosicionArancelaria);
int controller_ListPosicionArancelaria(Dictionary* pDictPosicionArancelaria);
int controller_savePosicionArancelariaAsText(char* path , Dictionary* pDictPosicionArancelaria);
int controller_loadTransporteMaritimoFromText(char* path,TransporteMar* transporteMaritimo);
int controller_saveTransporteMaritimoAsText(char* path ,TransporteMar* transporteMaritimo);
int controller_loadTransporteAereoFromText(char* path , TransporteAereo* transporteAereo);
int controller_ListTransporteAereo(TransporteAereo transporteAereo);
int controller_saveTransporteAereoAsText(char* path ,TransporteAereo* transporteAereo);
int controller_ListArticuloConPreciosDeTransporte(Dictionary* pDictArticulo,Dictionary* pDictPosicionArancelaria, TransporteMar transporteMaritimo, TransporteAereo transporteAereo);

#endif /* CONTROLLER_H_ */
