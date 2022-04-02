#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct Alumno
{
    char codigo [5];
    char nombre [11];
    char apellidos [20];
    char carrera [15];
};

class FixedRecord{
    
    string nombre_archivo;

    public:

    FixedRecord(string Nombre_archivo){
        nombre_archivo=Nombre_archivo;
    }

    void load(){
        string linea;
        ifstream archivo;
        archivo.open(nombre_archivo);

        string s;
        int lines=0;
        
        if(archivo.is_open() && archivo.tellg() != 0 && archivo.tellg() != -1){
            while(!archivo.eof()) {
                getline(archivo, s);
                lines++;	
            }
            archivo.seekg(0);
            for(int i=0;i<lines;i++){
                Alumno temp;
                archivo.read((char*) &temp, sizeof(temp));
                archivo.get();

                temp.codigo[sizeof(temp.codigo)-1] = '\0';
                temp.nombre[sizeof(temp.nombre)-1] = '\0';
                temp.apellidos[sizeof(temp.apellidos)-1] = '\0';
                temp.carrera[sizeof(temp.carrera)-1] = '\0';

            }

            archivo.close();

        }
        else{
            //throw invalid_argument("Archivo para escritura no abierto");
        }
    }

    void add(Alumno record){
        string linea;
        int length;

        ofstream outfile;
        outfile.open(nombre_archivo,ios::app);
        if(outfile.is_open()){

            outfile.seekp(0,ios::end);
            length = outfile.tellp();

            if(length != 0){
                outfile << "\n";
            }
            
            outfile.write(record.codigo,sizeof(record.codigo));
            outfile.write(record.nombre,sizeof(record.nombre));
            outfile.write(record.apellidos,sizeof(record.apellidos));
            outfile.write(record.carrera,sizeof(record.carrera));
            

            outfile.close();
        }
        else{
            throw invalid_argument("Archivo para escritura no abierto");
        }
    }

    Alumno readRecord(int pos){
        Alumno temp;

        ifstream inFile(nombre_archivo);
        inFile.seekg((pos * sizeof(Alumno))+(2*pos));
        inFile.read((char*) &temp, sizeof(temp));
        inFile.close();

        temp.codigo[sizeof(temp.codigo)-1] = '\0';
        temp.nombre[sizeof(temp.nombre)-1] = '\0';
        temp.apellidos[sizeof(temp.apellidos)-1] = '\0';
        temp.carrera[sizeof(temp.carrera)-1] = '\0';

        return temp;
    }

    void display(){
        string linea;
        ifstream archivo;
        archivo.open(nombre_archivo,ios::app);

        string s;
        int lines=0;

        if(archivo.is_open() && (archivo.tellg() != 0 || archivo.tellg() != -1)){
            while(!archivo.eof()) {
                getline(archivo, s);
                lines++;	
            }
            archivo.seekg(0);
            for(int i=0;i<lines;i++){
                Alumno temp;
                archivo.read((char*) &temp, sizeof(temp));
                archivo.get();

                temp.codigo[sizeof(temp.codigo)-1] = '\0';
                temp.nombre[sizeof(temp.nombre)-1] = '\0';
                temp.apellidos[sizeof(temp.apellidos)-1] = '\0';
                temp.carrera[sizeof(temp.carrera)-1] = '\0';

                cout<<temp.codigo<<" "<<temp.nombre<<" "<<temp.apellidos<<" "<<temp.carrera<<endl;

            }

            archivo.close();
        }
        else{
            cout<<"No se entró al archivo";
            throw invalid_argument("Archivo para lectura no abierto");
        }
    }
};

void display(Alumno temp){
        cout<<temp.codigo<<" "<<temp.nombre<<" "<<temp.apellidos<<" "<<temp.carrera<<endl;
    }

Alumno initRecord(){
    string a,b,c="Computacion",d="0123";
    Alumno temp;
    cout<<"Nombre: ";
    cin>>a;
    cout<<"Apellidos: ";
    cin>>b;
    
    for(int i=0;i<a.size();i++){
        temp.nombre[i]=a[i];
    }
    for(int i=0;i<b.size();i++){
        temp.apellidos[i]=b[i];
    }
    for(int i=0;i<c.size();i++){
        temp.carrera[i]=c[i];
    }
    for(int i=0;i<d.size();i++){
        temp.codigo[i]=d[i];
    }
    
    temp.codigo[sizeof(temp.codigo)-1] = '\0';
    temp.nombre[sizeof(temp.nombre)-1] = '\0';
    temp.apellidos[sizeof(temp.apellidos)-1] = '\0';
    temp.carrera[sizeof(temp.carrera)-1] = '\0';

    for(int i=a.size();i<sizeof(temp.nombre);i++){
        temp.nombre[i]=' ';
    }
    for(int i=b.size();i<sizeof(temp.apellidos);i++){
        temp.apellidos[i]=' ';
    }
    for(int i=c.size();i<sizeof(temp.carrera);i++){
        temp.carrera[i]=' ';
    }
    for(int i=d.size();i<sizeof(temp.codigo);i++){
        temp.codigo[i]=' ';
    }

    return temp;
}

void anadir_elemento(FixedRecord &A){
    A.add(initRecord());
}

void leer(FixedRecord &A){
    A.load();
}

void registro(FixedRecord &A){
    int reg;
    cout<<"Numero de registro a leer: ";
    cin>>reg;
    display(A.readRecord(reg));
}

void display_total(FixedRecord &A){
    A.display();
}

void menu(FixedRecord &A){
    while (true){
        int opcion;
        cout<<"=================================="<<endl;
        cout<<"                P1:               "<<endl;
        cout<<"                                  "<<endl;
        cout<<"=================================="<<endl;
        cout<<"                                  "<<endl;
        cout<<"                                  "<<endl;
        cout<<"*   *   *   *   *   *   *   *   * "<<endl;
        cout<<"                                  "<<endl;
        cout<<"1.Añadir elementos al archivo     "<<endl;
        cout<<"2.Leer el archivo                 "<<endl;
        cout<<"3.Obtener registro                "<<endl;
        cout<<"4.Display de registros            "<<endl;
        cout<<"0.Salir                           "<<endl;
        cout<<"Opcion: ";
        cin>>opcion;
        if(opcion == 1){
            anadir_elemento(A);
        }
        else if(opcion == 2){
            leer(A);
        }
        else if(opcion == 3){
            registro(A);
        }
        else if(opcion == 4){
            display_total(A);
        }
        else if(opcion == 0){
            break;
        }
        else{
            cout<<"No te entendí"<<endl;
        }
    }
}

int main()
{
    FixedRecord A("datos1.txt");
    menu(A);
}