#include<bits/stdc++.h>
using namespace std;

struct Alumno{
    string Nombre;
    string Apellidos;
    string Carrera;
    float mensualidad;
    Alumno(string a,string b,string c,float d){
        Nombre=a,Apellidos=b,Carrera=c,mensualidad=d;
    }
    Alumno(){};
};


ostream& operator<<(ostream &os,vector<Alumno> &temp){
    for(auto &x:temp){
        cout<<x.Nombre<<' '<<x.Apellidos<<' '<<x.Carrera<<'\n';
    }
    cout<<"--------------------------------------"<<'\n';
    return os;
}

class variableRecord{   
    private:
        string nombre;
    public:
        variableRecord(string a){
            nombre=a;
        }
        vector<Alumno> load(){
            vector<Alumno> vec;
            ifstream file(nombre);
            string temp;
            while(getline(file,temp)) vec.push_back(desempaquetar(temp));
            file.close();
            return vec;
        }
        void add(Alumno record){
            ofstream file(nombre,ios::app);
            file<<record.Nombre<<'|'<<record.Apellidos<<'|'<<record.Carrera<<'|'<<record.mensualidad<<'\n';
            file.close();
        }
        Alumno readRecord(int pos){
            ifstream file(nombre);
            string temp;
            int i=0;
            while(getline(file,temp)){
                if(i==pos) return desempaquetar(temp);
                i++;           
            }
            file.close();
            cout<<"No existe el registro"<<'\n';
            Alumno a;
            return a;
        }
        Alumno desempaquetar(string temp){
            Alumno a;
            string aux="";
            int times=0;
            for(int i=0;i<temp.size();i++){
                if(temp[i]=='|'){
                    if(times==0) a.Nombre=aux;
                    else if(times==1) a.Apellidos=aux;
                    else a.Carrera=aux;
                    times++;
                    aux="";
                }else aux=aux+temp[i];
            }
            a.mensualidad=stof(aux);
            return a;
        }
};

void escribir(string nombre){
    Alumno a("Howard","Paredes Zegarra","Computacion",1500.00);
    Alumno b("Penny","Vargas Cordero","Industrial",2550.50);
    Alumno c("Sheldon","Cooper Quizpe","Mecatronica",1850.00);
    ofstream file(nombre,ios::out);
    file<<a.Nombre<<'|'<<a.Apellidos<<'|'<<a.Carrera<<'|'<<a.mensualidad<<'\n';
    file<<b.Nombre<<'|'<<b.Apellidos<<'|'<<b.Carrera<<'|'<<b.mensualidad<<'\n';
    file<<c.Nombre<<'|'<<c.Apellidos<<'|'<<c.Carrera<<'|'<<c.mensualidad<<'\n';
    file.close();
}
int main(){
    Alumno d("Paolo","armas vega","software",1500.00);
    string nombre="file.txt";
    escribir(nombre);
    variableRecord a(nombre);
    auto x=a.load();
    cout<<x;
    a.add(d);
    x=a.load();
    cout<<x;
    auto y=a.readRecord(2);
    cout<<y.Nombre<<'\n';
}