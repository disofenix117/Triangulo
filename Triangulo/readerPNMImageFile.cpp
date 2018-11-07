/*
Rutinas para la lectura de imagenes en formato pnm (P3)
M�s informaci�n de la estructura del archivo en
https://en.wikipedia.org/wiki/Netpbm_format

Wilson Javier Sarmiento, 2015
Universidad Militar Nueva Granada
Bogot� D.C. Colombia
*/

#include "readerPNMImageFile.h"
#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>

//--------------------------------------------------------------------------------
/*
Funci�n de verificaci�n de un archivo PNM.
Permite verificar si un archivo determinado
es un archivo de imagen digital PNM.
La verificaci�n consiste en leer y comparar los dos
primeros caracteres del archivo con la palabra clave P3.
Si el archivo es correcto, se lee el alto y el acho de
la imagen y se retornan sus valores en los par�metros
H y W.

La funci�n retorna true s� el archivo es correcto,
y false	en otro caso.

Par�metros:
fileName, nombre del archivo.
H, variable donde se recibe el alto de la imagen.
H, variable donde se recibe el ancho de la imagen.
*/
bool checkPNMFile(char* fileName, int* H, int * W)
{
	std::ifstream ifs(fileName);
	if (!ifs.is_open())
		return false; // El archivo no se puede leer.

					  // Variable para la lectura de datos.
	char* line = new char[1024];

	// Se lee la palabra clave la cual debe ser P3.
	ifs.getline(line, 1024);
	line[2] = 0; // Se corta la cadena para minimizar errores en la comparaci�n.

				 // Se verifica la palabra clave.
	if (strcmp(line, "P3\0") == 0)
	{
		// Flujo de lectura de datos en memoria
		std::istringstream ifstr;

		// Se ignoran los comentarios
		ifs.getline(line, 1024);
		while (line[0] == '#')
		{
			ifs.getline(line, 1024);
		}

		// Se lee la l�nea que tiene irformaci�n del ancho y alto de la imagen
		// Se lee desde memoria
		const std::string strLineHW(line);
		ifstr.str(strLineHW);
		ifstr >> (*W);
		ifstr >> (*H);

		ifs.close();
		return true;
	}
	else
	{
		// El archivo no es P3
		ifs.close();
		return false;
	}
}
//--------------------------------------------------------------------------------
/*
Funci�n de lectura de un archivo PNM.

La funci�n retorna true s� el archivo es correcto,
y false	en otro caso.

Par�metros:
fileName, nombre del archivo.
Image, matriz de enteros de [alto][ancho][3] donde
se va almacenar la imagen.
*/
bool readPNMFile(char* fileName, int*** Image)
{

	std::ifstream ifs(fileName);
	if (!ifs.is_open())
		return false; // El archivo no se puede leer.

					  // Variable para la lectura de datos.
	char* line = new char[1024];

	// Se consulta el tama�o del archivo
	ifs.seekg(0, ifs.end);
	std::streamsize bufferSize = ifs.tellg();
	ifs.seekg(0);

	// Se lee la palabra clave la cual debe ser P3.
	ifs.getline(line, 1024);
	line[2] = 0; // Se corta la cadena para minimizar errores en la comparaci�n.

				 // Se verifica la palabra clave.
	if (strcmp(line, "P3\0") == 0)
	{
		int h, w;
		int imax;

		// Flujo de lectura de datos en memoria
		std::istringstream ifstr;

		// Se ignoran los comentarios
		line[0] = '#';
		while (line[0] == '#')
		{
			ifs.getline(line, 1024);
		}

		// Se lee la l�nea que tiene irformaci�n del ancho y alto de la imagen
		// Se lee desde memoria
		const std::string strLineHW(line);
		ifstr.str(strLineHW);
		ifstr >> w;
		ifstr >> h;
		ifstr.clear();

		// Se ignoran los comentarios
		ifs.getline(line, 1024);
		while (line[0] == '#')
		{
			ifs.getline(line, 1024);
		}
		// Se lee la l�nea que tiene irformaci�n el m�ximo valor de intensidad
		// Se lee desde memoria
		const std::string strImax(line);
		ifstr.str(strImax);
		ifstr >> imax;
		ifstr.clear();

		// Se lee el resto del archivo, en paquetes de 1024 caracteres
		std::filebuf*	buffer = ifs.rdbuf();
		char* data = new char[w*h * 50];//[bufferSize];
		char* pdata = (char*)data;

		// Se procede a hacer la lectura por paquetes
		std::streamsize readed = 1024;
		int allreader = 0;
		while (readed == 1024)
		{
			readed = buffer->sgetn(pdata, 1024);
			if (readed != 1024)
				allreader = readed;

			pdata += readed;
			allreader += readed;
		}
		// Toda la informaci�n esta en memoria, el archivo puede ser cerrado
		ifs.close();

		// Se realiza la lectura del bufer en memoria		
		const std::string strData(data);
		ifstr.str(strData);

		// Se almacena en el arreglo donde va a quedar la im�gen
		int hi, wi;
		int cdata;
		for (hi = 0; hi<h; hi++)
		{
			for (wi = 0; wi<w; wi++)
			{
				// Cada entrada es un valor R, G, B de un pixel
				ifstr >> Image[hi][wi][0];
				ifstr >> Image[hi][wi][1];
				ifstr >> Image[hi][wi][2];
			}
		}

		//Fin de la lectura.

		return true;
	}
	else
	{
		// El archivo no es P3
		ifs.close();
		return false;
	}
}
//-------------------------------------------------------------------------------rdbuf