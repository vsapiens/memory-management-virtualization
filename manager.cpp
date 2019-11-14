#include "ProcessManager.hpp"
#include <iostream>
/*
manager.cpp
This program is the main that handles the process manager of memory and the output handler

Erick Gonzalez A01039589
Francisco Sánchez 
Carlos Estrada
Moisés Fernández
Version: 1.0 last modified 14/11/2019
*/

/*
Function: Main
It handles the input, process of counting the archives and the output for the program.
Parameters: -
Return: Int, describing the correct compilation of the program
*/
int main()
{

char cOption;

while (cOption != 'f')
{
    std::cout<<"Selecciona una opción del menú";
    std::cin>> cOption;
    switch (cOption)
    {
    case 'C':
    case 'c':
        
        break;
    case 'F':
    case 'f':
        
        break;
    
    default:
        break;
    }
}


return 0;
}