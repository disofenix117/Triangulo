/*
Rutinas para la lectura de imagenes en formato pnm (P3)
M�s informaci�n de la estructura del archivo en
https://en.wikipedia.org/wiki/Netpbm_format

Wilson Javier Sarmiento, 2015
Universidad Militar Nueva Granada
Bogot� D.C. Colombia
*/

#ifndef __readerPNMImageFile__
#define __readerPNMImageFile__

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
bool checkPNMFile(char* fileName, int* H, int * W);
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
bool readPNMFile(char* fileName, int*** Image);
//--------------------------------------------------------------------------------

#endif // __readerPNMImageFile__

