/*
 * utn.c
 *
 *  Created on: 12 may. 2021
 *      Author: Luk
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

static int getInt(int* pResultado);
static int esNumerica(char* cadena,int limite);
static int getString(char* cadena,int longitud);
static int getFloat(float* pResultado);

static int getNombre(char* pResultado,int longitud);
static int esNombre(char* cadena,int limite);
static int getCuit(char* str,int len);
static int getDni(char* pResultado, int longitud);
static int isValidCuit(char* str,int len);

static int getInt(int* pResultado)
{
	int retorno=-1;
	char bufferString[50];
	if(pResultado!=NULL&&
	   getString(bufferString,sizeof(bufferString))==0&&
	   esNumerica(bufferString,sizeof(bufferString)))
	{
		retorno=0;
		*pResultado=atoi(bufferString);
	}
	return retorno;
}
static int esNumerica(char* cadena,int limite)
{
	int retorno=-1;//ERROR
	int i=0;

	if(cadena!=NULL&&limite>0)
	{
		retorno=1;//VERDADERO
		for(i=0;i<limite&&cadena[i]!='\0';i++)
		{
			if(i==0&&(cadena[i]=='+'||cadena[i]=='-'))
			{
				continue;
			}
			if(cadena[i]>'9'||cadena[i]<'0')
			{
				retorno=0;
				break;
			}
		}
	}

	return retorno;
}

static int getString(char* cadena,int longitud)
{
	int retorno=-1;
	char bufferString[4000];
	if(cadena!=NULL&& longitud>0)
	{
		fflush(stdin);
		if(fgets(bufferString,sizeof(bufferString),stdin)!=NULL)
		{
			if(bufferString[strlen(bufferString)-1]=='\n')
			{
				bufferString[strlen(bufferString)-1]='\0';
			}
			if(strlen(bufferString)<=longitud)
			{
				strncpy(cadena,bufferString,longitud);
				retorno=0;
			}
		}

	}
	return retorno;
}
int utn_getNumero(int* pResultado, char* mensaje, char* mensajeError, int minimo, int maximo, int reintentos)
{
	int retorno = -1;
	int bufferInt;
	if(pResultado != NULL && mensaje != NULL && mensajeError != NULL && minimo <= maximo && reintentos >= 0)
	{
		do
		{
			printf("%s",mensaje);
			if(getInt(&bufferInt)==0&&bufferInt >= minimo && bufferInt <= maximo)
			{
				*pResultado = bufferInt;
				retorno = 0;
				break;
			}
			printf("%s",mensajeError);
			reintentos--;

		}while(reintentos >= 0);
	}
	return retorno;
}
int utn_getString(char* pResultado,int longitud, char* mensaje, char* mensajeError, int reintentos)
{
	int retorno=-1;
	char bufferString[4000];

	while(reintentos>=0)
	{
		reintentos--;
		printf("%s",mensaje);
		if(getString(bufferString,sizeof(bufferString))==0)
		{
			strncpy(pResultado,bufferString,longitud);
			retorno=0;
			break;
		}
		printf("%s",mensajeError);
	}

	return retorno;
}

/* \brief Obtiene un string valido como nombre
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \return Retorna 0 (EXITO) si se obtiene un nombre y -1 (ERROR) si no
 */
static int getNombre(char* pResultado, int longitud)
{
    int retorno=-1;
    char buffer[4096];

    if(pResultado != NULL)
    {
    	if(	getString(buffer,sizeof(buffer))==0 &&
    		esNombre(buffer,sizeof(buffer)) &&
			strnlen(buffer,sizeof(buffer))<longitud)
    	{
    		strncpy(pResultado,buffer,longitud);
			retorno = 0;
		}
    }
    return retorno;
}

/* \brief Verifica si la cadena ingresada es un nombre valido
 * \param cadena Cadena de caracteres a ser analizada
 * \return Retorna 1 (verdadero) si la cadena es valida y 0 (falso) si no lo es
 */
static int esNombre(char* cadena,int longitud)
{
	int i=0;
	int retorno = 1;

	if(cadena != NULL && longitud > 0)
	{
		for(i=0 ; cadena[i] != '\0' && i < longitud; i++)
		{
			if((cadena[i] < 'A' || cadena[i] > 'Z' ) && (cadena[i] < 'a' || cadena[i] > 'z' ))
			{
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}

/* \brief Solicita un nombre al usuario, luego de verificarlo devuelve el resultado
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \param longitud Es la longitud del array resultado
 * \param mensaje Es el mensaje a ser mostrado
 * \param mensajeError Es el mensaje de Error a ser mostrado
 * \param reintentos Cantidad de reintentos
 * \return Retorna 0 si se obtuvo el nombre y -1 si no se obtuvo
 */
int utn_getNombre(char* pResultado, int longitud,char* mensaje, char* mensajeError, int reintentos)
{
	char bufferString[4096];
	int retorno = -1;
	while(reintentos>=0)
	{
		reintentos--;
		printf("%s",mensaje);
		if(getNombre(bufferString,sizeof(bufferString)) == 0 && strnlen(bufferString,sizeof(bufferString)) < longitud )
		{
			strncpy(pResultado,bufferString,longitud);
			retorno = 0;
			break;
		}
		printf("%s",mensajeError);
	}
	return retorno;
}
int utn_getNumeroFloat(float* pResultado, char* mensaje, char* mensajeError, float minimo, float maximo, int reintentos)
{
	int retorno = -1;
	float bufferFloat;
	if(pResultado != NULL && mensaje != NULL && mensajeError != NULL && minimo <= maximo && reintentos >= 0)
	{
		do
		{
			printf("%s",mensaje);
			if(getFloat(&bufferFloat)==0&&bufferFloat >= minimo && bufferFloat <= maximo)
			{
				*pResultado = bufferFloat;
				retorno = 0;
				break;
			}
			printf("%s",mensajeError);
			reintentos--;

		}while(reintentos >= 0);
	}
	return retorno;
}
static int getFloat(float* pResultado)
{
	int retorno=-1;
	char bufferString[50];
	if(pResultado!=NULL&&
	   getString(bufferString,sizeof(bufferString))==0&&
	   esNumerica(bufferString,sizeof(bufferString)))
	{
		retorno=0;
		*pResultado=atof(bufferString);
	}
	return retorno;
}

int utn_getCuit(char* pResultado,int longitud, char* mensaje, char* mensajeError, int reintentos)
{
	int retorno=-1;
		char bufferString[4000];

		while(reintentos>=0)
		{
			reintentos--;
			printf("%s",mensaje);
			if(getCuit(bufferString,longitud)&& isValidCuit(bufferString,longitud))
			{
				strncpy(pResultado,bufferString,longitud);
				retorno=0;
				break;
			}
			printf("%s",mensajeError);
		}

		return retorno;
}
static int getCuit(char* str,int len)
{
	 int retorno=-1;
	    char buffer[4096];

	    if(str != NULL)
	    {
	    	if(	getString(buffer,sizeof(buffer))==0 &&
	    		esNumerica(buffer,sizeof(buffer)) &&
				strnlen(buffer,sizeof(buffer))<len)
	    	{
	    		strncpy(str,buffer,len);
				retorno = 0;
			}
	    }
	    return retorno;
}

static int isValidCuit(char* str,int len)
{
	int retorno=-1;
	int i;
	if(str != NULL)
	{
		for(i=0 ; str[i] != '\0' && i < len; i++)
		{
			if(str[i] < '0' || str[i] > '9' || str[2]=='-' || str[11]=='-')
			{
				retorno = 0;
				break;
			}
		}
	}

	return retorno;
}

/**
 * \brief Obtiene un string valido como DNI
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \return Retorna 0 (EXITO) si se obtiene un dni y -1 (ERROR) si no
 *
 */
static int getDni(char* pResultado, int longitud)
{
    int retorno=-1;
    char buffer[4096];

    if(pResultado != NULL)
    {
    	if(	getString(buffer,sizeof(buffer))==0 &&
    		esNumerica(buffer,sizeof(buffer)) &&
			strnlen(buffer,sizeof(buffer))<longitud)
    	{
    		strncpy(pResultado,buffer,longitud);
			retorno = 0;
		}
    }
    return retorno;
}

/* \brief Solicita un DNI al usuario, luego de verificarlo devuelve el resultado
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \param longitud Es la longitud del array resultado
 * \param mensaje Es el mensaje a ser mostrado
 * \param mensajeError Es el mensaje de Error a ser mostrado
 * \param reintentos Cantidad de reintentos
 * \return Retorna 0 si se obtuvo el dni y -1 si no
 *
 */
int utn_getDni(char* pResultado, int longitud,char* mensaje, char* mensajeError, int reintentos)
{
	char bufferString[4096];
	int retorno = -1;
	while(reintentos>=0)
	{
		reintentos--;
		printf("%s",mensaje);
		if(getDni(bufferString,sizeof(bufferString)) == 0 && strnlen(bufferString,sizeof(bufferString)) < longitud )
		{
			strncpy(pResultado,bufferString,longitud);
			retorno = 0;
			break;
		}
		printf("%s",mensajeError);
	}
	return retorno;
}
