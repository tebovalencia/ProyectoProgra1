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

COORD GetConsoleCursorPosition(HANDLE hConsoleOutput) {
    CONSOLE_SCREEN_BUFFER_INFO cbsi;
    if (GetConsoleScreenBufferInfo(hConsoleOutput, &cbsi)) {
        return cbsi.dwCursorPosition;
    } else {
        // La función falló. Llama a GetLastError() para obtener más detalles.
        COORD invalid = { -1, -1 };
        return invalid;
    }
}

void posicionCursor(int x, int y)
{
    int a,b;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD cursorPos = GetConsoleCursorPosition(hConsole);

    if (cursorPos.X==0 && x==-1 ){
        a=100;
    }
    else
    a=cursorPos.X+x;

    if (cursorPos.Y==3 && y==-1){
        b=30;
    }
    else
    b=cursorPos.Y+y;

    if (a>100){
        a=a-100;
    }
    if (b>30){
        b=b-30;
    }
    COORD pos = {a, b};

    SetConsoleCursorPosition(hConsole, pos);
    //WriteConsole(hConsole, "Hello", 5, NULL, NULL);
}

void figuras(int F)
{
    int i,j;

    switch(F)
    {
    case 1:
             for (i=1; i<=5 ; i++)
            {
             for (j=1;j<=5;j++)
             {
                 cout<<"+";
             }
             posicionCursor(-5,1);
            }
            break;

    case 2:
            for (i=1; i<=4;i++)
            {
                for (j=0; j<i; j++)
                {
                    cout<<"+";
                }
                posicionCursor(-i,1);
            }
            break;
    default: cout<<"Ninguna figura seleccionada";break;

    }

}

void operadores(char tecla)
{
    switch (tecla)
    {
        case 27: break;
        case 77: posicionCursor(1,0);break;
        case 72: posicionCursor(0,-1);break;
        case 80: posicionCursor(0,1);break;
        case 75: posicionCursor(-1,0);break;
        case 113: figuras(1);break;
        case 119: figuras(2);break;
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
    gotoxy(50,0);cout<<"Menu"<<endl;
    gotoxy(30,1);cout<<"Esc: Salir,   q:Triangulo    w:Cuadrado   e:Circulo"<<endl;

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






