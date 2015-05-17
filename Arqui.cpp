#include <iostream>
#include <vector>
#include <fstream>

using namespace std;
//#####################-----Leer_Archivo-----###################
vector<string> Leer_Archivo(){
	string temp;
	vector<string> final;

	ifstream archivo;
	archivo.open ("memoria.txt");
	if(!archivo){
		cout << "No se encontro el archivo solicitado" << endl;
		exit(0);
	}
	while (!archivo.eof()){
		getline(archivo,temp);
		final.push_back(temp);
	}

	return final;
}
//####################-----Imprimir_Memoria-----###################
void Imprimir_Memoria (vector<string> memoria){
	cout << "-----------------------------------" << endl;
	cout << "##########---MEMORIA PRINCIPAL---##########" << endl;
	for (unsigned i=0;i<memoria.size();i++){
		cout << "pos[" << i << "]: " << memoria[i] << ", --> T[" << memoria[i].size() << "]" << endl;
	}
	cout << "-------------------------------------------" << endl;
}

//#####################-----DecimalaBinario-----###################
string DecimalaBinario (int entrada){
	int dividir = entrada;
	int residuo;
	string cambio, temp, binario, ceros, total;

	if (entrada != 0){
		while (dividir!=0){
			residuo = dividir % 2;
			cambio = to_string(residuo);
			temp.append(cambio);
			dividir = dividir / 2;
		}
		for (unsigned i=temp.size();i>0;i--){
			cambio = temp[i-1];
			binario.append(cambio);
		}
	}
	else {
		binario = "000000000000";
	}
	for (unsigned i= binario.size();i<12;i++){
		ceros.append("0");
	}
	total.append(ceros);
	total.append(binario);
	//cout << "Ceros: " << ceros << endl;

	return total;
}
//###############-----Tag de una Posicion-----#################
string Tag_Posicion_Dato(int posicion){
	string bin = DecimalaBinario(posicion);
	string final, temp;

	for (unsigned i=0;i<9;i++){
		temp = bin[i];
		final.append(temp);
	}
	return final;
}

//###############-----Index de una Posicion-----#################
string Index_Posicion_Dato(int posicion){
	string bin = DecimalaBinario(posicion);
	string final, temp;

	temp = bin[9];
	final.append(temp);
	return final;
}

//###############-----Agregar Dato a Cache-----#################
vector<int> Cuatro_Datos_a_Cache(vector<string> memoria, int posicion){
	vector<int> final;
	string tag = Tag_Posicion_Dato(posicion);
	string index = Index_Posicion_Dato(posicion);

	for (unsigned i=0;i< memoria.size();i++){
		if((tag == Tag_Posicion_Dato(i)) && (index == Index_Posicion_Dato(i))){
			final.push_back(i);
		}
	}
	return final;
}

//Es como la funcion anterior solo que esta si saca los datos la otra solo las posiciones de los datos
vector<string> Datos_Cache(vector<string> memoria, vector<int> datos){
	vector<string> final;
	int est;
	string result;

	for (unsigned i=0;i< datos.size();i++){
		est = datos[i];
		result = memoria[est];
		final.push_back(result);
	}
	return final;
}


//#####################-----Clase Cache-----###################
class Estructura_Memoria {
public:
	int miss;
	int hit;
	vector<int> D0; //Este es D[0]
	vector<int> V0; //Valid[0]
	vector<string> Tag0;
	vector<int> FIFO0;
	vector<vector<string> > Dato0; //son los datos que hay guardados en las posiciones Pos_Dato0
	vector<vector<int> > Pos_Dato0; //Son las posiciones de los datos(en numero)
	vector<int> D1; //Este es D[1]
	vector<int> V1; //Valid[1]
	vector<string> Tag1;
	vector<int> FIFO1;
	vector<vector<string> > Dato1;
	vector<vector<int> > Pos_Dato1;
};

//###############-----Imprimir Cache-----#################
void Imprimir_Cache(Estructura_Memoria cache){
	cout << "---------------------------------------" << endl;
	cout << "####################------MEMORIA CACHE------####################" << endl;
	cout << "--> Cantidad Hits: " << cache.hit << endl;
	cout << "--> Cantidad Miss: " << cache.miss << endl;

	cout << "_________________1 Via Memoria Cache_________________" << endl;
	cout << "D[0,0]: " << cache.D0[0] << " | "; 
	cout << "V[0,0]: " << cache.V0[0] << " | "; 
	cout << "Tag[0,0]: " << cache.Tag0[0] << " | ";
	for (unsigned i=0;i<4;i++){
		cout << "M[" << cache.Pos_Dato0[0][i] << "] ";
	}
	cout << endl;
	cout << "-->Datos en 0: " << endl;
	for (unsigned i=0;i<4;i++){
		cout << "M[" << cache.Pos_Dato0[0][i] << "]: " << cache.Dato0[0][i] << "    ";
	}
	cout << endl;
	//------------
	cout << endl;
	cout << "D[0,1]: " << cache.D1[0] << " | "; 
	cout << "V[0,1]: " << cache.V1[0] << " | ";
	cout << "Tag[0,1]: " << cache.Tag1[0] << " | ";
	for (unsigned i=0;i<4;i++){
		cout << "M[" << cache.Pos_Dato1[0][i] << "] ";
	}
	cout << endl;
	cout << "-->Datos en 1: " << endl;
	for (unsigned i=0;i<4;i++){
		cout << "M[" << cache.Pos_Dato1[0][i] << "]: " << cache.Dato1[0][i] << "    ";
	}
	cout << endl;
	cout << "_______________________________________________________" << endl;
	//##########2 Via##############
	cout << "_________________2 Via Memoria Cache_________________" << endl;
	cout << "D[1,0]: " << cache.D0[1] << " | "; 
	cout << "V[1,0]: " << cache.V0[1] << " | "; 
	cout << "Tag[1,0]: " << cache.Tag0[1] << " | ";
	for (unsigned i=0;i<4;i++){
		cout << "M[" << cache.Pos_Dato0[1][i] << "] ";
	}
	cout << endl;
	cout << "-->Datos: " << endl;
	for (unsigned i=0;i<4;i++){
		cout << "M[" << cache.Pos_Dato0[1][i] << "]: " << cache.Dato0[1][i] << "    ";
	}
	cout << endl;
	//------------
	cout << endl;
	cout << "D[1,1]: " << cache.D1[1] << " | "; 
	cout << "V[1,1]: " << cache.V1[1] << " | ";
	cout << "Tag[1,1]: " << cache.Tag1[1] << " | ";
	for (unsigned i=0;i<4;i++){
		cout << "M[" << cache.Pos_Dato1[1][i] << "] ";
	}
	cout << endl;
	cout << "-->Datos: " << endl;
	for (unsigned i=0;i<4;i++){
		cout << "M[" << cache.Pos_Dato1[1][i] << "]: " << cache.Dato1[1][i] << "    ";
	}
	cout << endl;
	cout << "_______________________________________________________" << endl;

	//##########3 Via##############
	cout << "_________________3 Via Memoria Cache_________________" << endl;
	cout << "D[2,0]: " << cache.D0[2] << " | "; 
	cout << "V[2,0]: " << cache.V0[2] << " | "; 
	cout << "Tag[2,0]: " << cache.Tag0[2] << " | ";
	for (unsigned i=0;i<4;i++){
		cout << "M[" << cache.Pos_Dato0[2][i] << "] ";
	}
	cout << endl;
	cout << "-->Datos: " << endl;
	for (unsigned i=0;i<4;i++){
		cout << "M[" << cache.Pos_Dato0[2][i] << "]: " << cache.Dato0[2][i] << "    ";
	}
	cout << endl;
	//------------
	cout << endl;
	cout << "D[2,1]: " << cache.D1[2] << " | "; 
	cout << "V[2,1]: " << cache.V1[2] << " | ";
	cout << "Tag[2,1]: " << cache.Tag1[2] << " | ";
	for (unsigned i=0;i<4;i++){
		cout << "M[" << cache.Pos_Dato1[2][i] << "] ";
	}
	cout << endl;
	cout << "-->Datos: " << endl;
	for (unsigned i=0;i<4;i++){
		cout << "M[" << cache.Pos_Dato1[2][i] << "]: " << cache.Dato1[2][i] << "    ";
	}
	cout << endl;
	cout << "_______________________________________________________" << endl;

	//##########4 Via##############
	cout << "_________________4 Via Memoria Cache_________________" << endl;
	cout << "D[3,0]: " << cache.D0[3] << " | "; 
	cout << "V[3,0]: " << cache.V0[3] << " | "; 
	cout << "Tag[3,0]: " << cache.Tag0[3] << " | ";
	for (unsigned i=0;i<4;i++){
		cout << "M[" << cache.Pos_Dato0[3][i] << "] ";
	}
	cout << endl;
	cout << "-->Datos: " << endl;
	for (unsigned i=0;i<4;i++){
		cout << "M[" << cache.Pos_Dato0[3][i] << "]: " << cache.Dato0[3][i] << "    ";
	}
	cout << endl;
	//------------
	cout << endl;
	cout << "D[3,1]: " << cache.D1[3] << " | "; 
	cout << "V[3,1]: " << cache.V1[3] << " | ";
	cout << "Tag[3,1]: " << cache.Tag1[3] << " | ";
	for (unsigned i=0;i<4;i++){
		cout << "M[" << cache.Pos_Dato1[3][i] << "] ";
	}
	cout << endl;
	cout << "-->Datos: " << endl;
	for (unsigned i=0;i<4;i++){
		cout << "M[" << cache.Pos_Dato1[3][i] << "]: " << cache.Dato1[3][i] << "    ";
	}
	cout << endl;
	cout << "_______________________________________________________" << endl;
	cout << "FIFO0: ";
	for (unsigned i=0; i<cache.FIFO0.size();i++){
		cout << cache.FIFO0[i] << " " ;
	}
	cout << endl;
	cout << "FIFO1: ";
	for (unsigned i=0; i<cache.FIFO1.size();i++){
		cout << cache.FIFO1[i] << " " ;
	}
	cout << endl;
	cout << "#####################------FIN CACHE------#####################" << endl;
}
//###############-----Inicializar Cache-----#################
Estructura_Memoria Inicializar_Cache(Estructura_Memoria cache){
	cache.miss = 0;
	cache.hit = 0;
	vector<int> posiciones;
	posiciones.push_back(0);
	posiciones.push_back(0);
	posiciones.push_back(0);
	posiciones.push_back(0);
	vector<string> datos;
	datos.push_back("na");
	datos.push_back("na");
	datos.push_back("na");
	datos.push_back("na");

	for (unsigned i=0;i<4;i++){
		cache.Pos_Dato0.push_back(posiciones);
		cache.Pos_Dato1.push_back(posiciones);
	}
	for (unsigned i=0;i<4;i++){
		cache.Dato0.push_back(datos);
		cache.Dato1.push_back(datos);
	}

	for (unsigned i=0;i< 4;i++){
		cache.D0.push_back(0);
		cache.V0.push_back(0);
		cache.D1.push_back(0);
		cache.V1.push_back(0);
	}
	for (unsigned i=0;i< 4;i++){
		cache.Tag0.push_back("-");
		cache.Tag1.push_back("-");
	}	

	cache.FIFO0.push_back(10);
	cache.FIFO1.push_back(10);
	//Falta FIFO

	return cache;
}
//###############-----Quitar primer calor del FIFO-----#################
vector<int> Nuevo_FIFO(vector<int> fifo){
	vector<int> final;
	for (unsigned i=0;i<fifo.size();i++){
		if (i == 0){}
		else {
			final.push_back(fifo[i]);
		}
	}
	return final;
}

int Posicion_Fifo(vector<int> fifo){
	int cero=0, uno=0, dos=0, tres=0;
	for (unsigned i=0;i<fifo.size();i++){
		if (fifo[i] == 0){
			cero = 1;
		} else if (fifo[i] == 1){
			uno = 1;
		}else if (fifo[i] == 2){
			dos = 1;
		}else if (fifo[i] == 3){
			tres = 1;
		}else {}
	}
	if (cero == 0){
		return 0;
	} else if(uno == 0){
		return 1;
	}else if(dos == 0){
		return 2;
	}else if(tres == 0){
		return 3;
	}else {
		return 11;
	}

}
//###############-----Agregar Dato a Cache-----#################
Estructura_Memoria Agregar_Dato_MemCache(Estructura_Memoria cache, vector<string> memoria, int posicion){
	string index = Index_Posicion_Dato(posicion);
	string tag = Tag_Posicion_Dato(posicion);
	vector<int> pos = Cuatro_Datos_a_Cache(memoria, posicion);
	vector<string> dats = Datos_Cache(memoria, pos);
	int temptag, lugarfifo=0;

	//cout << "Index: " << index << endl;
	//cout << "Tag: " << tag << endl;

	if(index == "0"){
		for(unsigned i=0;i<4;i++){
			if(tag == cache.Tag0[i]){
				temptag = 1;
				i = 4;
				//cout << "Encontro que ya esta el tag0" << endl;
			} 
			else {
				temptag = 0;
				//cout << "No esta el tag0" << endl;
			}
		}
		
	}
	else if(index == "1"){
		for(unsigned i=0;i<4;i++){
			if(tag == cache.Tag1[i]){
				temptag = 1;
				i = 4;
				//cout << "Encontro que ya esta el tag1" << endl;
			} 
			else {
				temptag = 0;
				//cout << "No esta el tag1" << endl;
			}

		}
		
	}
	//cout << "Este es el temptag: " << temptag << endl;
	//Si temptag es 1 significa que el dato ya esta cargado entonces es un hit por lo que suma 1 a hit
	if(temptag == 1){
		cache.hit = cache.hit + 1;
	} 
	else if(temptag == 0){
		cache.miss = cache.miss + 1;
		//cout << "entro1" << endl;
		if (index == "0"){
			if (cache.FIFO0[0] == 10){
				lugarfifo = 0;
				cache.FIFO0.push_back(lugarfifo);
				cache.FIFO0 = Nuevo_FIFO(cache.FIFO0);
			}
			else {
				lugarfifo = Posicion_Fifo(cache.FIFO0);
				if (lugarfifo == 11){
					lugarfifo = cache.FIFO0[0];
					cache.FIFO0.push_back(lugarfifo);
					cache.FIFO0 = Nuevo_FIFO(cache.FIFO0);
				}
				else {
					cache.FIFO0.push_back(lugarfifo);
				}
			}

			cache.D0[lugarfifo] = 0;
			cache.V0[lugarfifo] = 1;
			cache.Tag0[lugarfifo] = tag;
			cache.Pos_Dato0[lugarfifo] = pos;
			cache.Dato0[lugarfifo] = dats;
			//cout << "entro2" << endl;
		}
		else {
			if (cache.FIFO1[0] == 10){
				lugarfifo = 0;
				cache.FIFO1.push_back(lugarfifo);
				cache.FIFO1 = Nuevo_FIFO(cache.FIFO1);
			}
			else {
				lugarfifo = Posicion_Fifo(cache.FIFO1);
				if (lugarfifo == 11){
					lugarfifo = cache.FIFO1[0];
					cache.FIFO1.push_back(lugarfifo);
					cache.FIFO1 = Nuevo_FIFO(cache.FIFO1);
				}
				else {
					cache.FIFO1.push_back(lugarfifo);
				}
			}

			cache.D1[lugarfifo] = 0;
			cache.V1[lugarfifo] = 1;
			cache.Tag1[lugarfifo] = tag;
			cache.Pos_Dato1[lugarfifo] = pos;
			cache.Dato1[lugarfifo] = dats;
			//cout << "entro2" << endl;
		
		}

	}

	return cache;
}

//######################------Main-----#########################

int main(){
	vector<string> memoria = Leer_Archivo(); //Esta es la memoria Principal
	//Imprimir_Memoria(memoria);
	//cout << "190: " << DecimalaBinario(190) << "--> T[" << DecimalaBinario(190).size() << "]" << endl;
	Estructura_Memoria cache;
	cache = Inicializar_Cache(cache);
	//Imprimir_Cache(cache);
	cache = Agregar_Dato_MemCache(cache, memoria, 0);
	cache = Agregar_Dato_MemCache(cache, memoria, 4);
	cache = Agregar_Dato_MemCache(cache, memoria, 8);
	cache = Agregar_Dato_MemCache(cache, memoria, 12);
	cache = Agregar_Dato_MemCache(cache, memoria, 17);
	cache = Agregar_Dato_MemCache(cache, memoria, 21);
	cache = Agregar_Dato_MemCache(cache, memoria, 24);
	cache = Agregar_Dato_MemCache(cache, memoria, 30);
	cache = Agregar_Dato_MemCache(cache, memoria, 32);
	cache = Agregar_Dato_MemCache(cache, memoria, 40);
	cache = Agregar_Dato_MemCache(cache, memoria, 41);

	
	Imprimir_Cache(cache);

	return 0;
}