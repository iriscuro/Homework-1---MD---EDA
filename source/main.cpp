/*
Autor: Iris Rocio Curo Quispe
EDA - La maldición de la dimensionalidad
Homework N° 1
2.0
*/
#include <iostream>
#include <cmath>
#include <random>
#include <iomanip>
#include <chrono>
#include <vector>
#include <algorithm>
#include <functional>
#include <iterator>
#include <cstdlib>
#include <string>
#include <fstream>
#include <sstream>
#include <time.h>
#include <map>



using namespace std;

///DATOS
/*dim[] almacena la cantidad de dimensiones que tendran los puntos*/
int cant_p = 100;//Cantidad de puntos para hacer las pruebas
int dim[] = {2,5,10,50,100,500, 1000};

///RANDOM NUMBERS
/* function generator: [0-1]*/
float RandomNumber () {
    return 0 + static_cast<float>(rand()) * static_cast<float>(1 - 0) / RAND_MAX;
}

///FLOAT, DOUBLE TO STRING
/*Función para convertir a string el numero*/
template < typename Type > std::string to_str (const Type & t)
{
  std::ostringstream os;
  os << t;
  return os.str ();
}

///TRUNCAR
/*Función para redondear los flotantes*/
float roundoff(float value, unsigned char prec)
{
  float pow_10 = pow(10.0f, (float)prec);
  return round(value * pow_10) / pow_10;
}


///IMPRIMIR 1XN
/*
Funcion que imprime en consola el vector o
 punto n-dimensional
*/
template <class T>
void Print_1N(vector<T> v,int size){
  for (int i = 0; i < size; i++){
      cout<<v[i]<< "   ";

  }
  cout<< endl;
  return;
}

///IMPRIMIR NXM
/*Función para imprimir los N puntos de D dimensiones */
template <class T>
void Print_NN(vector< vector<T> > v,int size1, int size2){
  for(int y=0; y<size1 ; y++){
        for(int x=0; x<size2 ; x++){
            cout << v[y][x]<<" ";
        }
        cout<<endl;
    }
  cout<<endl;
}


///IMPRIMIR TABLA MAP
/*Función para imprimir en consola los datos del mapa Tabla*/
template <class T, class N>
void Print_Tabla( map<T, N>& t,int d, ofstream& file ){
  cout<<"--------------------------------------"<<endl;
  cout<<"/              "<<d<<"D                   /"<<endl;
  cout<<"--------------------------------------"<<endl;
  cout<<"/      Euc. D     /       number     /"<<endl;
  cout<<"--------------------------------------"<<endl;


//  file <<"--------------------------------------"<<endl;
//  file <<"/              "<< d <<"D                   /"<<endl;
//  file <<"--------------------------------------"<<endl;
  //auto iter = t.begin();
  for (auto i : t){
    string ss1 = to_str(i.first);
    string ss2 = to_str(i.second);
    int tam_f1 = ss1.size(); int tam_f2 = ss2.size();
    cout<<" ";
    for(int i=0; i<(19-tam_f1)/2 ; i++) cout<<" ";
    //file << i.first;
    cout << i.first;
    for(int i=0; i<(19-tam_f1)/2 ; i++){ //file << " ";
        cout<<" "; }
    cout<<" ";

    for(int i=0; i<(19-tam_f2)/2 ; i++) cout<<" ";
   // file << i.second<<endl;
    cout << i.second<<endl;
    //cout << i.first << " : " << i.second << "\n";
  }
//  file<<"--------------------------------------"<<endl;
//  file<<endl;
    cout<<"--------------------------------------"<<endl;
    cout<<endl;
  return ;
}

///IMPRIMIR TABLA MAP y ESCRIBIR EN TABLA.TXT
/* Con esta función se guarda los datos obtenidos en la tabla, es decir,
la cantidad de veces que una distancia calculada aparece se almacenan en
 un mapa cuyos datos se guardan en un archivo .txt*/
template <class T, class N>
void Show_Tabla( map<T, N>& t,int d, int cp, ofstream& file ){
  cout<<"--------------------------------------"<<endl;
  cout<<"/             "<<d<<" D                   /"<<endl;
  cout<<"--------------------------------------"<<endl;
  cout<<"/           "<<cp<<" Puntos             /"<<endl;
  cout<<"--------------------------------------"<<endl;
  cout<<"/      Euc. D     /       number     /"<<endl;
  cout<<"--------------------------------------"<<endl;


  file <<"--------------------------------------"<<endl;
  file <<"/              "<< d <<"D                   /"<<endl;
  file <<"--------------------------------------"<<endl;

  for (auto i : t){
    string ss1 = to_str(i.first);
    string ss2 = to_str(i.second);
    int tam_f1 = ss1.size(); int tam_f2 = ss2.size();
    cout<<" ";
    for(int i=0; i<(19-tam_f1)/2 ; i++) cout<<" ";
    file << i.first;
    cout << i.first;
    for(int i=0; i<(19-tam_f1)/2 ; i++){ file << " ";
        cout<<" "; }
    cout<<" ";

    for(int i=0; i<(19-tam_f2)/2 ; i++) cout<<" ";
    file << i.second<<endl;
    cout << i.second<<endl;
    //cout << i.first << " : " << i.second << "\n";
  }
  file<<"--------------------------------------"<<endl;
  file<<endl;
    cout<<"--------------------------------------"<<endl;
    cout<<endl;
  return ;
}

///EUCLIDEAN DISTANCE (ED)
/* Función que calcula la distancia euclidiana punto a punto
   Se saca la distancia euclidiana para tos los puntos respecto
   al primer punto creado
*/
template <class T, class N>
void ED(vector<T>& D,int canP, int d, vector< vector<N> > P ){
    float sum = 0;int n=0;
    for(int j=1; j<canP ; j++){//calcular las distancias para todos los puntos
        sum=0;
        //calculo de la D. E. de cada punto
        for(int ii=0; ii<d ; ii++){
            sum += pow(P[0][ii]- P[j][ii],2 );
        }
        D[n]= roundoff(sqrt(sum),1);
//        cout<<" D["<<n<<"] "<<D[n]<<endl;
        n++;
    }
//    cout<< "DISTANCIAS: "<<endl;
//    Print_1N<float>(D, canP-1) ;
    return ;
}

int main() {

    ///ARCHIVO txt
    //Aqui se guarda los resultados
    string nameA = "Tables.txt";
    ofstream Arch;

    ///RANDOM NUMBERS srand(time(0))
    srand((unsigned int)time(NULL));//semilla


    Arch.open(nameA.c_str(), fstream::out);

    //Para cada cantidad de dimensiones de los puntos
    for(int i=0; i<7; i++){
        vector< vector<float> > Points ( cant_p, vector<float> (dim[i]) );
        vector<float> Dist(cant_p-1);
        //cout<<"size.Dist: "<< Dist.size()<<endl;
        map<float, int> tabla;

        ///MATRIZ DE PUNTOS ALEATORIOS
        for(int y=0; y<cant_p ; y++){
            for(int x=0; x<dim[i] ; x++){
                Points[y][x] = RandomNumber() ;//bien

            }
        }

//        cout<<"PUNTOS: "<<endl;
//        Print_NN<float>(Points, cant_p, dim[i]);


        ///<<<<HALLANDO CANTIDAD POR CADA DISTANCIA>>>
        ///HALLANDO LA DISTANCIA EUCLIDIANA
        ED<float,float>(Dist,cant_p,dim[i],Points);//check

        //Print_1N<float>(Dist, cant_p[it]-1) ;


        ///CANTIDAD DE DISTANCIAS IGUALES
        //se llena la tabla con la cantidad de veces que se repite una distancia calculada
        //cout<<"size Dist: "<< Dist.size()<<endl;
        for(size_t i = 0; i < Dist.size(); i++){
            tabla[Dist[i]]++;
        }

        ///IMPRIMIR TABLA
        //Print_Tabla<float, int>(tabla, dim[i], Arch);
        Show_Tabla<float, int>(tabla, dim[i], cant_p, Arch);


        tabla.clear();
        Arch.close();
        cout<<endl;
    }


    cout<<"           ...   Fin     ..."<<endl;



	return 0;
}
