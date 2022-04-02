#include <bits/stdc++.h>

using namespace std;

struct Alumno{
    char nombre[11]; 
    char apellidos[20];    
    char carrera[15];
    char codigo[5];
    int ciclo;
    float mensualidad;
    Alumno(){};
};

ostream& operator<<(ostream &os,vector<Alumno> &temp){
    for(auto &x:temp){
        for(int i=0;i<11;i++) cout<<x.nombre[i];
        cout<<' ';
        for(int i=0;i<20;i++) cout<<x.apellidos[i];
        cout<<'\n';
    }
    cout<<"--------------------------------------"<<'\n';
    return os;
}

class FixedRecord{
    private:
        string nombre;
        int n=0,centinela=-1;
    public:
        FixedRecord(string a){ 
            nombre=a;
            ifstream outfile(nombre, ios::in|ios::out|ios::binary);
            outfile.seekg(0, ios::end);
            n=outfile.tellg()/sizeof(Alumno);
            outfile.close();            

            ofstream meta("metadata.dat",ios::out|ios::binary);
            for(int i=0;i<n;i++){
                int j=0;
                meta.write((char*)&j,4);
            }
            meta.close();
        }        
        vector<Alumno> load(){
            ifstream temp(nombre,ios::binary|ios::in|ios::out);
            vector<Alumno> vec;
            for(int i=0;i<n;i++){
                if(esta_borrado(i+1)==0){
                    Alumno record;
                    //temp.seekg(i*sizeof(record),ios::beg);
                    temp.read((char *) &record,sizeof(record));
                    vec.push_back(record);
                }
            }
            temp.close();
            
            return vec;
        }
        
        void add(Alumno record){
            if(centinela==-1){
                ofstream temp(nombre,ios::app|ios::binary);
                temp.seekp(n*sizeof(record),ios::beg);
                temp.write(reinterpret_cast<char*>(&record),sizeof(record));
                temp.close();
                ofstream temp1("metadata.dat",ios::app|ios::binary);
                int j=0;
                temp1.seekp(n*4,ios::beg);
                temp1.write(reinterpret_cast<char*>(&j),4);
                temp1.close();
                n++;
            }else{
                ofstream temp(nombre,ios::binary|ios::in|ios::out);
                temp.seekp((centinela-1)*sizeof(record),ios::beg);
                temp.write(reinterpret_cast<char*>(&record),sizeof(record));
                temp.close();

                ifstream temp_meta("metadata.dat", ios::in|ios::out|ios::binary);
                int j;
                temp_meta.seekg((centinela-1)*4,ios::beg);
                temp_meta.read((char *) &j,4);
                temp_meta.close();
                ofstream temp_meta_1("metadata.dat",ios::binary|ios::in|ios::out);
                int j1=0;            
                temp_meta_1.seekp((centinela-1)*4,ios::beg);
                temp_meta_1.write((char*)&j1,4);
                temp_meta_1.close();
                centinela=j;

            }
        }
        Alumno readRecord(int pos){  
            Alumno record;
            if(esta_borrado(pos+1)==1) cout<<"El registro fue eliminado"<<'\n';
            else{
                ifstream temp(nombre, ios::in|ios::out|ios::binary);
                temp.seekg(pos*sizeof(record),ios::beg);
                temp.read((char *) &record,sizeof(record));
                temp.close();
            }
            return record;
        }

        void deletee(int pos){
            if(esta_borrado(pos+1)==1){
                cout<<"El registro fue eliminado"<<'\n';
                return;
            }
            ofstream temp("metadata.dat",ios::binary|ios::in|ios::out);
            int j=centinela;
            temp.seekp(pos*4,ios::beg);
            temp.write((char*)&j,sizeof(j));
            temp.close();
            centinela=pos+1;
        }

        void lectura(){
            cout<<"Centinela "<<centinela<<'\n';
            ifstream temp("metadata.dat",ios::binary|ios::in|ios::out);
            for(int i=0;i<n;i++){
                int j;
                temp.read((char*)&j,sizeof(j));
                cout<<j<<' ';
            }
            cout<<'\n';
            temp.close();
        }
        bool esta_borrado(int pos){
            int j;
            ifstream temp("metadata.dat",ios::binary|ios::in|ios::out);
            temp.seekg((pos-1)*4,ios::beg);
            temp.read((char*)&j,sizeof(j));
            temp.close();
            if(j==0) return 0;
            else return 1;
        }
};

Alumno initRecord(string a,string b,string c,string d,int ciclo,float mensualidad){
    Alumno temp;

    for(int i=0;i<min(11,int(a.size()));i++) temp.nombre[i]=a[i];
    for(int i=min(int(a.size()),11);i<11;i++) temp.nombre[i]=' ';

    for(int i=0;i<min(20,int(b.size()));i++) temp.apellidos[i]=b[i];
    for(int i=min(int(b.size()),20);i<20;i++) temp.apellidos[i]=' ';    
    
    for(int i=0;i<min(15,int(c.size()));i++) temp.carrera[i]=c[i];
    for(int i=min(int(c.size()),15);i<15;i++) temp.carrera[i]=' ';

    for(int i=0;i<min(5,int(d.size()));i++) temp.codigo[i]=d[i];
    for(int i=min(int(d.size()),5);i<5;i++) temp.codigo[i]=' '; 

    temp.mensualidad=mensualidad;
    temp.ciclo=ciclo;

    return temp;
}

void escribir_archivo(string nombre){
    Alumno a=initRecord("matias","avendano","cs","01234",2,12);
    Alumno b=initRecord("paolo","armas","meca","01235",3,12);
    Alumno c=initRecord("diego","guerra","meca","01236",3,12);
    ofstream file(nombre,ios::out|ios::binary);
    
    file.write((char*)&a,sizeof(a));
    file.write((char*)&b,sizeof(b));
    file.write((char*)&c,sizeof(c));

    file.close();
}

int main(){
    Alumno d=initRecord("marcos","ayala","meca","01236",3,12);
    Alumno e=initRecord("juan","sara","meca","01236",3,12);
    Alumno f=initRecord("jose","fiestas","meca12","01236",3,12);
    Alumno g=initRecord("heider","sanchez","meca12","01236",3,12);

    string nombre="tarea.dat";
    
    escribir_archivo(nombre); //crear .dat
    FixedRecord file(nombre);
    
    auto x=file.load();
    cout<<x;

    file.add(d);
    
    x=file.load();
    cout<<x;

    file.deletee(1);//indexado en 0  
    auto y=file.readRecord(1);
    x=file.load();
    cout<<x;
    
    file.deletee(3);
    file.add(e);
    file.lectura();

    x=file.load();
    cout<<x;

    file.add(f);
    
    x=file.load();
    cout<<x;

    file.add(g);
    
    x=file.load();
    cout<<x;

    file.deletee(1);
    file.deletee(4);
    x=file.load();
    cout<<x;
    file.lectura();
}