#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <conio.h>
#include <windows.h>

using namespace std;

void gotoxy(int x, int y)
{
COORD coordinate;
coordinate.X = x;
coordinate.Y = y;
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinate);
}

void operadores(char tecla)
{
    switch (tecla)
    {
        case 27: break;
        case 77: cout<<"Es la tecla derecha"<<endl;break;
        case 72: cout<<"Es la tecla arriba"<<endl;break;
        case 80: cout<<"Es la tecla abajo"<<endl;break;
        case 75: cout<<"Es la tecla izquierda"<<endl;break;
    }
}

int main()
{

                            // Obtener el handle de la ventana de la consola
                            HWND window = GetConsoleWindow();

                            // Definir nuevo ancho y alto para la ventana
                            int nuevoAncho = 800; // Ancho en píxeles
                            int nuevoAlto = 600;  // Alto en píxeles

                            // Establecer el tamaño de la ventana
                            SetWindowPos(window, HWND_TOP, 0, 0, nuevoAncho, nuevoAlto, SWP_NOMOVE);


    char tecla;
    cout << "Presiona una tecla..." << endl;

    while(true) {
        if (_kbhit()) { // Si se presiona una tecla
            tecla = _getch(); // Captura la tecla presionada
            operadores(tecla);
            if (tecla == 27) { // Si la tecla es ESC
                break; // Salir del bucle
            }
        }
    }

    return 0;
}




