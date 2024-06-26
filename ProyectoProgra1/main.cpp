#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <conio.h>
#include <windows.h>
#include <cmath>
#include <fstream>
#include <string>


using namespace std;

int pantalla[100][6]; //1-Posicion X, 2-Posicion Y, 3-Tecla, 4-Color, 5-Simbolo, 6-tamano
int X=0,Y=0,i=0,j=0, p=0,n=0, s=0; //P se usa para contador de pantalla
int tecla;
int color=0;
int S=0;

void gotoxy(int x, int y);
COORD GetConsoleCursorPosition(HANDLE hConsoleOutput);
void posicionCursor(int x, int y);
void figuras(int F, int n, int S);
void operadorPantalla (int tecla, int X, int Y, int n, int color, int S);
void operadores(char tecla,int n, int S);
void imprimirPantalla();
void menu(int X, int Y);
void colorTexto(int color);
char simbolo(int x);
void exportar();
void importar();

int main()
{
    fflush;
        // Variables para almacenar las coordenadas del cursor
    int cursorx = 0, cursory = 0;
    int tecla;

    // Estructura para almacenar la posici�n del cursor
    POINT cursorPos;

                            // Obtener el handle de la ventana de la consola
                            HWND window = GetConsoleWindow();

                            // Definir nuevo ancho y alto para la ventana
                            int nuevoAncho = 1000; // Ancho en p�xeles
                            int nuevoAlto = 600;  // Alto en p�xeles

                            // Establecer el tama�o de la ventana
                            SetWindowPos(window, HWND_TOP, 0, 0, nuevoAncho, nuevoAlto, SWP_NOMOVE);

        while(true) {
            if (_kbhit()) { // Si se presiona una tecla
                tecla = _getch(); // Captura la tecla presionada
                if (tecla == 0 || tecla == 224) { // Teclas extendidas
                        tecla = _getch();
                        if (tecla == 134){
                                // Obtener la posici�n del cursor
                                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                                COORD cursorPos = GetConsoleCursorPosition(hConsole);
                                    //muestra menu
                                    menu(cursorPos.X,cursorPos.Y);
                                    gotoxy(cursorPos.X,cursorPos.Y);
                                    p=p+1;

                        }
                }
                operadores(tecla,0,0);
                if (tecla == 27) { // Si la tecla es ESC
                    break; // Salir del bucle
                }
            }
        }





    return 0;
}


//Funcion para para mover el cursor a un punto especifico conociendo las coordenadas
void gotoxy(int x, int y)
{
COORD coordinate;
coordinate.X = x;
coordinate.Y = y;
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinate);
}
//Funcion para obtener la posicion del cursor
COORD GetConsoleCursorPosition(HANDLE hConsoleOutput) {
    CONSOLE_SCREEN_BUFFER_INFO cbsi;
    if (GetConsoleScreenBufferInfo(hConsoleOutput, &cbsi)) {
        return cbsi.dwCursorPosition;
    } else {

        COORD invalid = { -1, -1 };
        return invalid;
    }
}
//Funcion para mover el cursor a partir de la posicion actual una cantidad deseada y pantalla circular
void posicionCursor(int x, int y)
{
    int a=0,b=0;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD cursorPos = GetConsoleCursorPosition(hConsole);

    if (cursorPos.X==0 && x==-1 ){
        a=130;

    }
    else
    a=cursorPos.X+x;

    if (cursorPos.Y==0 && y==-1){
        b=34;
    }
    else
    b=cursorPos.Y+y;

    if (a>130){
        a=a-131;
    }
    if (b>34){
        b=b-35;
    }

    gotoxy(a,b);

}

//Funcion para imprimir las figuras deseadas
void figuras(int F, int n, int s)
{
    int i,j,o;

    switch(F)
    {
    case 1:
            //Cuadrado
             for (i=1; i<=n/2 ; i++)
            {
             for (j=0;j<=n;j++)
             {
                 posicionCursor(1,0);
                 cout<<simbolo(s);
                 posicionCursor(-1,0);

             }
             for(o=0;o<=n;o++){
             posicionCursor(-1,0);
             }
             posicionCursor(0,1);
            }
            break;

    case 2:
            //Triangulo
            n=n+2;
            for (i=1; i<=n;)
            {
                for (j=1; j<=i; j++)
                {
                    posicionCursor(1,0);
                    cout<<simbolo(s);
                    posicionCursor(-1,0);
                }

                for(o=0;o<=i;o++){
                     posicionCursor(-1,0);
                     }
                     posicionCursor(0,1);
                i=i+2;
            }
            break;

    case 3:
            //Linea
            for (i=1;i<=n;i++)
            {
                posicionCursor(1,0);
                    cout<<simbolo(s);
                posicionCursor(-1,0);
            }
            break;

    case 4:
            //Cuadrado
             for (i=1; i<=n ; i++)
            {
             for (j=0;j<=n;j++)
             {
                 posicionCursor(1,0);
                 cout<<simbolo(s);
                 posicionCursor(-1,0);

             }
             for(o=0;o<=n;o++){
             posicionCursor(-1,0);
             }
             posicionCursor(0,1);
            }
            break;

    case 5:
            //Circulo
            {
                const int radio = n; // Radio del c�rculo
                const int diametro = 2 * radio; // Di�metro del c�rculo
                const int centerX = radio; // Centro del c�rculo en X
                const int centerY = radio; // Centro del c�rculo en Y
                posicionCursor (-n,-n);
                // Iterar sobre cada punto en la cuadr�cula
                for (int y = 0; y <= diametro; ++y) {
                    for (int x = 0; x <= diametro; ++x) {
                        // Calcular la distancia al centro
                        double distance = sqrt((x - centerX) * (x - centerX) + (y - centerY) * (y - centerY));
                        // Si la distancia est� dentro de un rango del radio, dibujar un asterisco
                        if (abs(distance - radio) < 0.5) {
                            posicionCursor(1,0);
                            cout<<simbolo(s);
                            posicionCursor(-1,0);
                        } else {
                            posicionCursor(1,0);
                            cout << " ";
                            posicionCursor(-1,0);
                        }
                    }
                            for(int m=0; m<= diametro; m++){
                            posicionCursor(-1,0);// Nueva l�nea al final de cada fila
                            }
                            posicionCursor(0,1);
                }
            }
            break;

    case 6:
        {
            int width = 2 * n - 1; // Ancho total del rombo

            // Parte superior del rombo
            for (int i = 0; i < n; ++i) {
                // Espacios antes de los asteriscos
                for (int j = 0; j < n - i - 1; ++j) {
                    posicionCursor(1,0);
                    cout << " ";
                    posicionCursor(-1,0);
                }
                // Asteriscos
                for (int j = 0; j < 2 * i + 1; ++j) {
                    posicionCursor(1,0);
                    cout<<simbolo(s);
                    posicionCursor(-1,0);
                }

                for (int l=0; l<=n-1+i; ++l){
                    posicionCursor(-1,0);
                }

                posicionCursor(0,1);
            }

            // Parte inferior del rombo
            for (int i = n - 2; i >= 0; --i) {
                // Espacios antes de los asteriscos
                for (int j = 0; j < n - i - 1; ++j) {
                    posicionCursor(1,0);
                    cout << " ";
                    posicionCursor(-1,0);
                }
                // Asteriscos
                for (int j = 0; j < 2 * i + 1; ++j) {
                    posicionCursor(1,0);
                    cout<<simbolo(s);
                    posicionCursor(-1,0);
                }
                for (int l=0; l<=n-1+i; ++l){
                    posicionCursor(-1,0);
                }

                posicionCursor(0,1);
            }
        }
        break;

    case 7:
        {
            // Parte superior del hex�gono
            for (int i = 0; i < n; ++i) {
                // Espacios antes de los asteriscos
                for (int j = 0; j < n - i - 1; ++j) {
                    posicionCursor(1,0);
                    cout << " ";
                    posicionCursor(-1,0);
                }
                // Asteriscos
                for (int j = 0; j < n + 2 * i; ++j) {
                    posicionCursor(1,0);
                    cout<<simbolo(s);
                    posicionCursor(-1,0);
                }
                for (int l=0; l<=2*n+i-2; ++l){
                    posicionCursor(-1,0);
                }

                posicionCursor(0,1);
            }

            // Parte central del hex�gono
            for (int i = 0; i < n; ++i) {
                // Asteriscos
                for (int j = 0; j < 3 * n - 2; ++j) {
                    posicionCursor(1,0);
                    cout<<simbolo(s);
                    posicionCursor(-1,0);
                }
                for (int l=0; l<=3*n-3; ++l){
                    posicionCursor(-1,0);
                }

                posicionCursor(0,1);
            }

            // Parte inferior del hex�gono
            for (int i = n - 1; i >= 0; --i) {
                // Espacios antes de los asteriscos
                for (int j = 0; j < n - i - 1; ++j) {
                    posicionCursor(1,0);
                    cout << " ";
                    posicionCursor(-1,0);
                }
                // Asteriscos
                for (int j = 0; j < n + 2 * i; ++j) {
                    posicionCursor(1,0);
                    cout<<simbolo(s);
                    posicionCursor(-1,0);
                }
                for (int l=0; l<=2*n+i-2; ++l){
                    posicionCursor(-1,0);
                }

                posicionCursor(0,1);
            }
        }
        break;

    default: cout<<"Ninguna figura seleccionada";
            break;

    }

}


//Con esta funcion guardare la posicion de todas las figuras en pantalla para luego reimprimirlas para limpiar el menu
void operadorPantalla (int tecla, int X, int Y, int n, int color, int S){

    pantalla[p][1]=X;
    pantalla[p][2]=Y;
    pantalla[p][3]=tecla;
    pantalla[p][4]=color;
    pantalla[p][5]=S;
    pantalla[p][6]=n;
    imprimirPantalla();

}

void imprimirPantalla()
{
    system("cls");
    for (j=0;j<=100;j++){
    gotoxy(pantalla[j][1],pantalla[j][2]);
    colorTexto(pantalla[j][4]);
    operadores(pantalla[j][3],pantalla[j][6],pantalla[j][5]);
    }
}

//Operadores de seleccion de tecla
void operadores(char tecla,int n,int s)
{
    switch (tecla)
    {
        case 27: break;
        case 77: posicionCursor(1,0);break;
        case 72: posicionCursor(0,-1);break;
        case 80: posicionCursor(0,1);break;
        case 75: posicionCursor(-1,0);break;
        case 59: figuras(1,n,s);break; //Cuadrado F1
        case 60: figuras(2,n,s);break; //Triangulo F2
        case 61: figuras(3,n,s);break; //Linea F3
        case 62: figuras(4,n,s);break; //Rectangulo F4
        case 63: figuras(5,n,s);break; //Circulo F5
        case 64: figuras(6,n,s);break; //Rombo F6
        case 65: figuras(7,n,s);break; //Hexagono F7
    }
}

//Funcion de menu
void menu(int X, int Y){

    int i=0;

    reiniciar:
    system("cls");
    gotoxy(70,0);cout<<"Menu"<<endl;
    gotoxy(10,1);cout<<"Esc: Salir - F1:Cuadrado - F2:Triangulo - F3:Linea - F4: Rectangulo - F5: Circulo - F6: Rombo - F7: Hexagono";
    gotoxy(33,2);cout<<"F8:Cambiar caracter - F9:Borrar pantalla - F10:Cambiar color";
    gotoxy(40,3);cout<<"F12:Grabar pantalla - Ctrl+A: Abrir desde archivo ";
    tecla = _getch();

    if (tecla==1){
        importar();

    }

    if (tecla == 0 || tecla == 224) { // Teclas extendidas
        tecla = _getch();

        if (tecla==66){//F8
            system("cls");
            cout<<"Seleccione el caracter que desea usar"<<endl;
            cout<<"1 . (punto)"<<endl;
            cout<<"2 * (asterisco)"<<endl;
            cout<<"3 - (guion)"<<endl;
            cout<<"4 @ (arroba)"<<endl;
            cin>>S;
            goto reiniciar;

        }

        if (tecla==67){//F9
        for (int l=0;l<=100;l++){
            for (int m=1;m<=6;m++){
            pantalla[l][m]=0;}
            p=0;

        }
        system("cls");
        return;
        }

        if (tecla==68){//F10
        system("cls");
        cout<<"Ingrese el color que desea: \n";
        cout<<"1- Azul oscuro \n";
        cout<<"2- Verde oscuro \n";
        cout<<"3- Azul claro \n";
        cout<<"4- Rojo oscuro \n";
        cout<<"5- Morado \n";
        cout<<"6- Amarillo \n";
        cout<<"7- Blanco \n";
        cout<<"8- Gris oscuro \n";
        cout<<"9- Azul claro brillante \n";
        cin>>color;
        goto reiniciar;
        }

        if (tecla==134){
            exportar();
            goto reiniciar;
        }

        system("cls");
        cout<<"Ingrese el tamano de la figura: ";cin>>n;n=n-1;}

    operadorPantalla(tecla,X,Y,n,color,S);

}
void colorTexto(int color) {

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    switch (color)
    {
        case 1: SetConsoleTextAttribute(hConsole, 1);break;
        case 2: SetConsoleTextAttribute(hConsole, 2);break;
        case 3: SetConsoleTextAttribute(hConsole, 3);break;
        case 4: SetConsoleTextAttribute(hConsole, 4);break;
        case 5: SetConsoleTextAttribute(hConsole, 5);break;
        case 6: SetConsoleTextAttribute(hConsole, 6);break;
        case 7: SetConsoleTextAttribute(hConsole, 7);break;
        case 8: SetConsoleTextAttribute(hConsole, 8);break;
        case 9: SetConsoleTextAttribute(hConsole, 9);break;
        default: SetConsoleTextAttribute(hConsole, 7);break;
    }


}

char simbolo(int x){
    char caracter;
    switch (x){

    case 1: caracter='.';
    break;
    case 2: caracter='*';
    break;
    case 3: caracter='-';
    break;
    case 4: caracter='@';
    break;
    default: caracter='.';break;
    }

    return caracter;
}

void exportar(){

    string nombre;

    cout<<"Digite el nombre del archivo ";
    cin>> nombre;
    nombre += ".txt";
    ofstream outFile(nombre);

    for (int l = 0; l <= 100; l++) {
        for(int m=1; m<=6;m++){
        outFile << pantalla[l][m] << " ";
        }
        outFile<<endl;
    }

    // Cerrar el archivo
    outFile.close();


}

void importar(){

    string nombre;

    cout<<"Digite el nombre del archivo ";
    cin>> nombre;
    nombre += ".txt";

    ifstream inFile(nombre);

    if (!inFile) {
        cerr << "Error al abrir el archivo para lectura." << endl;
        return ;
    }

    // Leer los elementos del archivo y almacenarlos en el array
    for (int l = 0; l <= 100 ; l++) {
        for (int m = 1; m<= 6; m++) {
            inFile >> pantalla[l][m];
            if (inFile.fail()) {
                cerr << "Error al leer el archivo." << std::endl;
                return ;
            }
        }
    }

    // Cerrar el archivo
    inFile.close();
    imprimirPantalla();



}












