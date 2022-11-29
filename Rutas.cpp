#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <vector>
#include <sstream>
using namespace std;
#include "Graph.h"

void menu(string ciudadOrigen, string ciudadDestino) {
	cout << "\n\nM E N U\n\n"
		<<"_________________________\n\n"
		<<"Ciudad de origen: "<<ciudadOrigen<<"\n"
		<<"Ciudad de destino: "<<ciudadDestino<<"\n\n"
		<< "\t1. Ingresar origen y destino\n"
		<< "\t2. Desplegar ruta optima\n"
		<< "\t3. Salir\n\n"
		<< "\t>> Ingrese una opcion: ";
}

int main()
{
	bool llave = true;
	int opcion = 0;
	bool archivoValido = true;
	string nombreArchivo = "";

	do {
		cout << "\n\n\t>> Ingrese el nombre del archivo: ";
		cin >> nombreArchivo;
		if (nombreArchivo == "archivo") {
			archivoValido = false;
			nombreArchivo += ".txt";
		}
		else {
			cout << "\n\n\t>> Ingrese una opcion valida.";
		}
	} while (archivoValido);

	Graph<string> graph;
	string Text;
	vector<string> cities;
	ifstream File(nombreArchivo);
	vector<string> origen, destino, weight;
	string ciudadOrigen, ciudadDestino, destinoPeso, peso;
	int posEspacioOrigen, posEspacioDestino;
	vector<string>archivo;
	while (getline(File, Text)) {
		archivo.push_back(Text);
	}

	int numero = stoi(archivo.at(0));

	for (int i = 1; i < numero + 1; i++) {
		posEspacioOrigen = archivo.at(i).find(" ");
		ciudadOrigen = archivo.at(i).substr(0, posEspacioOrigen);
		origen.push_back(ciudadOrigen);

		destinoPeso = archivo.at(i).substr(posEspacioOrigen + 1);
		posEspacioOrigen = destinoPeso.find(" ");
		ciudadDestino = destinoPeso.substr(0, posEspacioOrigen);
		destino.push_back(ciudadDestino);

		peso = destinoPeso.substr(posEspacioOrigen + 1);
		weight.push_back(peso);
	}

	vector<vector<string>> edges;
	for (int i = 0; i < numero; i++) {
		edges.push_back({ origen.at(i), destino.at(i), weight.at(i) });
	}

	/*for (vector<string> atributos : edges) {
		for (string atributo : atributos) {
			cout << atributo << "\t\t";
		}
		cout << endl;
	}*/

	int sizeVertices = stoi(archivo.at(31));
	for (int i = 32; i < (32 + sizeVertices); i++) {
		cities.push_back(archivo.at(i));
	}

	graph.loadVertices(cities);

	graph.loadGraph(edges);

	string CiudadOrigen = "Por definir", CiudadDestino = "Por definir";

	do {
		menu(CiudadOrigen, CiudadDestino);
		cin >> opcion;
		system("cls");
		switch (opcion) {
		case 1:
			cout << "\n\n\t>> Ingrese la ciudad de origen: ";
			cin >> CiudadOrigen;
			cout << "\n\n\t>> Ingrese la ciudad de destino: ";
			cin >> CiudadDestino;
			graph.shortestPathBetweenVertices(CiudadOrigen, CiudadDestino);
			system("cls");
			break;
		case 2:
			graph.print();
			break;
		case 3:
			cout << "\n\nSalir\n\n";
			llave = false;
			system("cls");
			break;
		default:
			cout << "\n\n\t>> Ingrese una opcion valida.\n\n";
			break;
		}

	} while (llave);

	return 0;
}
