#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <conio.h>
#include <windows.h>

using namespace std;

//Funcion para para mover el cursor a un punto especifico conociendo las coordenadas
void gotoxy(int x, int y)
{
COORD coordinate;
coordinate.X = x;
coordinate.Y = y;
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinate);
}
//Funcion necesaria para el movimiento paso a paso del cursor
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
//Funcion para mover el cursor a partir de la posicion actual una cantidad deseada y pantalla circular
void posicionCursor(int x, int y)
{
    int a,b;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD cursorPos = GetConsoleCursorPosition(hConsole);

    if (cursorPos.X==0 && x==-1 ){
        a=110;
    }
    else
    a=cursorPos.X+x;

    if (cursorPos.Y==0 && y==-1){
        b=30;
    }
    else
    b=cursorPos.Y+y;

    if (a>110){
        a=a-110;
    }
    if (b>30){
        b=b-30;
    }

    gotoxy(a,b);

}

void figuras(int F)
{
    int i,j,o;

    switch(F)
    {
    case 1:
             for (i=1; i<=4 ; i++)
            {
             for (j=0;j<=4;j++)
             {
                 cout<<".";
             }
             posicionCursor(-j,1);
            }
            break;

    case 2:
            for (i=1; i<=8;)
            {
                for (j=1; j<=i; j++)
                {
                    cout<<".";
                }
                posicionCursor(-i-1,1);

                i=i+2;
            }
            break;

    case 3:
            for (i=1;i<=4;i++)
            {
                for(j=4;j>=1;)
                {
                    cout<<".";
                    j=j-i;
                }
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
        case 59: figuras(1);break; //Triangulo 113
        case 119: figuras(2);break; //Cuadrado
        case 101: figuras(3);break; //Circulo
    }
}

void menu(){
    gotoxy(50,0);cout<<"Menu"<<endl;
    gotoxy(30,1);cout<<"Esc: Salir,   q:Triangulo    w:Cuadrado   e:Circulo"<<endl;
}


int main()
{
        // Variables para almacenar las coordenadas del cursor
    int cursorx = 0, cursory = 0;

    // Estructura para almacenar la posición del cursor
    POINT cursorPos;

                            // Obtener el handle de la ventana de la consola
                            HWND window = GetConsoleWindow();

                            // Definir nuevo ancho y alto para la ventana
                            int nuevoAncho = 800; // Ancho en píxeles
                            int nuevoAlto = 600;  // Alto en píxeles

                            // Establecer el tamaño de la ventana
                            SetWindowPos(window, HWND_TOP, 0, 0, nuevoAncho, nuevoAlto, SWP_NOMOVE);


    int tecla;

    while(true) {
        if (_kbhit()) { // Si se presiona una tecla
            tecla = _getch(); // Captura la tecla presionada
            if (tecla == 0 || tecla == 224) { // Teclas extendidas
                    tecla = _getch();
                    if (tecla == 134){
                            // Obtener la posición del cursor
                            if (GetCursorPos(&cursorPos)) {
                                // Guardar las coordenadas del cursor en las variables
                                cursorx = cursorPos.x;
                                cursory = cursorPos.y;
                                //muestra menu
                                menu();
                                gotoxy(cursorx,cursory);
                            } else {
                                std::cerr << "Error al obtener la posición del cursor." << std::endl;
                            }
                    }
            }
            operadores(tecla);
            if (tecla == 27) { // Si la tecla es ESC
                break; // Salir del bucle
            }
        }
    }

    return 0;
}






