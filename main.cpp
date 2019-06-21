#include <iostream>
#include <fstream>
#include <string>
#include <ctype.h>
#include <stdio.h>
#include <cstddef>

void SplitFilename (const std::string& str)
{
    std::cout << "Splitting: " << str << '\n';
    std::size_t found = str.find_last_of("/\\");
    std::cout << " path: " << str.substr(0,found) << '\n';
    std::cout << " file: " << str.substr(found+1) << '\n';
}

using namespace std;

size_t UltimaposicionCaracter (const string& direccion)
    {
        int n;
        size_t found;
        found = direccion.find_last_of("/\\");
        return found;
    }
string nombreTabla (const string& direccion)
{
    string tabla;
    size_t found;
    found = UltimaposicionCaracter(direccion);
    tabla = direccion.substr(found+1);
    return tabla;
}
string nombrePATH (const string& direccion)
{
    string path;
    size_t found;
    found = UltimaposicionCaracter(direccion);
    path = direccion.substr(0,found+1);
    return path;
}
void mayus (string& file)
    {

    std::for_each(file.begin(), file.end(), [](char & c){
        c = ::toupper(c);
    });
    }
int deleteChar (string &file, int n = 4)
    {
        for (int i = 0; i<n;i++)
            {
                file.pop_back();
            }
    }

int main() {
    bool flag = true;
    bool firstOperation = true;
    char resp;
    string file,path,aux;
    string archivoTXT;
    string direccion;
    cout<<"Ingrese la direccion del archivo (en .txt) para cascade: "<<endl;
    getline(cin,direccion);
    path = nombrePATH(direccion);
    file = nombreTabla(direccion);
    mayus(file);
    deleteChar(file,4);
    cout<<file<<endl;
    path += "DROP_CASCADE.txt";
    archivoTXT = path;
    ofstream archivoGenerado (archivoTXT.c_str(),ios::out);
    while (flag)
    {
        if (!firstOperation) {
            direccion = "";
            cout<<"Ingrese la direccion del archivo (en .txt) para cascade: "<<endl;
            getline(cin,direccion);
            file = nombreTabla(direccion);
            mayus(file);
            deleteChar(file,4);

        }
        archivoGenerado<<"DROP TABLE "<<file<<" CASCADE CONSTRAINTS;"<<endl;
        cout<<"Continuar? [S/N]"<<endl;
        cin>>resp;
        cin.ignore();
        if (toupper(resp) == 'N') {flag = false;}
        firstOperation =false;
    }
    cout<<"Archivo generado en: "<<archivoTXT;
    archivoGenerado.close();
    return 0;
}