#include<bits/stdc++.h>
using namespace std;

struct Matricula{
    string codigo;
    string observaciones;
    int ciclo;
    float mensualidad;
    Matricula(string a,string b,int c,float d){
        codigo=a,observaciones=b;ciclo=c;mensualidad=d;
    }
    
    int tam(){
        return (codigo.size()+observaciones.size())*sizeof(char)+sizeof(ciclo)+sizeof(mensualidad)+12;
    }

    
};

void escribir(Matricula record,string nombre){
    ofstream file(nombre,ios::app|ios::binary);
    
    int j=record.tam();
    file.write((char*)&j,4);

    int j1=record.codigo.size();
    file.write((char*)&j1,4);

    file.write((char*)&record.codigo[0],record.codigo.size());
    
    int j2=record.observaciones.size();
    file.write((char*)&j2,4);

    file.write((char*)&record.observaciones[0],record.observaciones.size());
    file.write((char*)&record.ciclo,4);
    file.write((char*)&record.mensualidad,sizeof(record.mensualidad));

    file.close();
}

ostream& operator<<(ostream &os,vector<Matricula> &temp){
    for(auto &x:temp){
        cout<<x.codigo<<' '<<x.observaciones<<'\n';
    }
    cout<<"--------------------------------------"<<'\n';
    return os;
}


struct entryMeta{
    int pos,sz;
    entryMeta(int a,int b){
        pos=a;sz=b;
    }
    entryMeta(){};
};

class FixedRecord{
    private:
        string nombre;
        int n;
    public:
        FixedRecord(string a){ 
            nombre=a;
            ifstream temp(nombre, ios::in|ios::out|ios::binary);
            ofstream meta("metadata.dat",ios::out|ios::binary);

            temp.seekg(0, ios::end);
            n=temp.tellg();
            temp.seekg(0,ios::beg);

            int indice=0,ind=0;

            while(indice<n){
                int j;
                temp.seekg(0+indice,ios::beg);
                temp.read((char*)&j,4);

                entryMeta record(indice,j);
                meta.write((char*)&record,sizeof(record));
                indice=indice+j;
                ind++;
            }
            n=ind;
            temp.close();
            meta.close();
        }
        
        void add(Matricula record){
            auto x=get_info(n-1);
            int sz=record.tam();

            ofstream meta("metadata.dat",ios::app|ios::binary);
            meta.seekp(n,ios::beg);
            
            entryMeta temp_entry(x.first+sz,sz);
            meta.write((char*)&temp_entry,sizeof(temp_entry));
            meta.close();
            
            n++;            
            escribir(record,nombre);
        }

        vector<Matricula> load(){
            
            vector<Matricula> vec;
            for(int i=0;i<n;i++){
                vec.push_back(get_record(i));
            }
            return vec;
        }

        Matricula get_record(int pos){
            ifstream temp(nombre, ios::in|ios::out|ios::binary);
            auto pareja=get_info(pos);
            //cout<<"POS "<<pareja.first<<'\n';
            temp.seekg(pareja.first,ios::beg);
            
            int a,b,d,f;string c,e;float g;
                
            temp.read((char*)&a,4);
            temp.read((char*)&b,4);
            c.resize(b);                
            temp.read((char*)&c[0],b);
            temp.read((char*)&d,4);
            e.resize(d);
            temp.read((char*)&e[0],d);
            temp.read((char*)&f,4);
            temp.read((char*)&g,sizeof(g));
            Matricula record(c,e,f,g);
            temp.close();
            return record;
        }

        pair<int,int> get_info(int pos){
            entryMeta record;
            ifstream meta("metadata.dat",ios::out|ios::binary);
            meta.seekg(pos*sizeof(record),ios::beg);
            meta.read((char*)&record,sizeof(record));
            meta.close();
            return {record.pos,record.sz};
        }

        void lectura(){
            ifstream temp("metadata.dat",ios::binary|ios::in|ios::out);
            for(int i=0;i<n;i++){
                entryMeta j;
                temp.seekg(i*sizeof(j),ios::beg);
                temp.read((char*)&j,sizeof(j));
                cout<<j.pos<<' '<<j.sz<<'\n';
            }
            temp.close();
        }
        
};



void escribir_archivo(string nombre){
    Matricula a("1234567","------",123,12.2);
    Matricula b("4321","*****",222,24.2);
    Matricula c("77","$$$$$$",111,22.1);
    
    ofstream file(nombre,ios::out|ios::binary);
    file.close();

    escribir(a,nombre);
    escribir(b,nombre);
    escribir(c,nombre);
}

int main(){
    Matricula d("11","$#$$#$",458,22.1);
    string nombre="file.dat";
    escribir_archivo(nombre);
    FixedRecord a(nombre);
    a.lectura();
    auto x=a.load();
    cout<<x;
    a.add(d);
    a.lectura();
    x=a.load();
    cout<<x;
}
