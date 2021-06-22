/*
 ============================================================================
 Name        : Segundo_Parcial.c
 Author      : Luca
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "Dictionary.h"
#include "controller.h"
#include "articulo.h"
#include "transporteMar.h"
#include "transporteAereo.h"
#include "utn.h"

int main(void) {
    int option;
    Dictionary* articulos = dict_new(0);
    Dictionary* PosicionArancelaria = dict_new(0);
    TransporteAereo transporteAereo;
	TransporteMar transporteMaritimo;

    if(!controller_initAll(articulos, PosicionArancelaria, &transporteMaritimo, &transporteAereo))
    {
        do{
    		printf("\n                  MENU                     \n"
    				"1-Listar valor de transporte por Articulo.\n"
    				"2-Alta articulos.\n"
    				"3-Modificar articuloss.\n"
    				"4-Baja articulos.\n"
    				"5-Listar articulos.\n"
    				"6-Ordenar articulos por nombre.\n"
    				"7-Mostrar precios de transporte.\n"
    				"8-Salir.\n");
    		utn_getInt(&option,"\nIngrese una opcion: ","Error",1,8,2);
			switch(option)
			{
				case 1:
					controller_ListArticuloConPreciosDeTransporte(articulos, PosicionArancelaria, transporteMaritimo);
					break;
				case 2:
					controller_addArticulo(articulos,PosicionArancelaria);
					break;
				case 3:
					controller_editArticulo(articulos,PosicionArancelaria);
					break;
				case 4:
					controller_removeArticulo(articulos);
					break;
				case 5:
					controller_ListArticulo(articulos);
					break;
				case 6:
					controller_sortArticulo(articulos);
					break;
				case 7:
					controller_ListTransporteMaritimo(transporteMaritimo);
					controller_ListTransporteAereo(transporteAereo);
					break;
			}
        }while(option != 8);
    }

    return 0;
}
