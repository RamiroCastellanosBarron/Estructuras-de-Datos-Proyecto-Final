#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
using namespace std;
#include "Edge.h"

template <class T>
class Graph
{
private:
	vector<T> vertices;
	vector<vector<Edge<T>>> adjacencyList;
	int size;
	int findVertex(T vertex);
	void dfsR(int index, vector<bool>& status);
	vector< stack<int> > pathList;
	int minVertex(vector<bool> status, vector<int> cost);
public:
	Graph();
	void loadVertices(vector<T> vertices);
	void loadGraph(vector<vector<T> > edges);
	void bfs(T vertex);
	void dfs(T vertex);
	void print();
	void shortestPath(T vertex);
	void shortestPathBetweenVertices(T source, T target);
};

template <class T>
Graph<T>::Graph()
{
	size = 0;
}

template <class T>
void Graph<T>::loadVertices(vector<T> vertices)
{
	// Asignamos el valor del parametro v�rtices a mi lista de v�rtices
	this->vertices = vertices;
	// Asignamos el tama�o del vector de vertices al atributo size
	size = vertices.size();
	// Inicializamos la lista de adyacencias en el tama�o de v�rtices que recibimos de parametro
	// Hacemos un vector vacio de tipo Edge de tipo T
	vector<Edge<T> > aux;
	// Hacemos un stack vacio de tipo entero
	stack<int> pathStack;
	// recorremos cada uno de los elementos de mi lista de v�rtices
	for (auto vertex : vertices)
	{
		adjacencyList.push_back(aux);
		pathList.push_back(pathStack);
	}

}

template <class T>
int Graph<T>::findVertex(T vertex)
{
	// Creamos una variable de tipo "iterator" para almacenar la posici�n encontrada
	typename vector<T>::iterator it;
	// buscamos el v�rtice en la lista de v�rtices
	it = find(vertices.begin(), vertices.end(), vertex);
	// Validamos i encontramos el v�rtice
	if (it != vertices.end())
	{
		// regresamos la posici�n donde se encuentra el v�rtice
		return it - vertices.begin();
	}
	else
	{
		// no encotramos el v�rtice
		return -1;
	}
}

template <class T>
void Graph<T>::loadGraph(vector<vector <T>> edges)
{
	// recorremos todos pares de elementos de mi vector edges
	for (auto edge : edges)
	{
		Edge<T> newEdge(edge[0], edge[1], stoi(edge[2]));
		// Buscar la pocisic�n del source en mi lista de vertices y asignarla a sourceIndex
		int sourceIndex = findVertex(newEdge.source);
		// Buscar la pocisic�n del target en mi lista de vertices y asignarla a targetIndex
		int targetIndex = findVertex(newEdge.target);
		// validamos que hayamos encontrado los vertices
		if (sourceIndex >= 0 && targetIndex >= 0)
		{
			// Agrema el valor de newEdge a la lista de que se encunetra en la posici�n de sourceIndex en mi lista de adyacencias
			adjacencyList[sourceIndex].push_back(newEdge);
		}
	}
}

template <class T>
void Graph<T>::bfs(T vertex) {
	// Validar que si existe el v�rtice que recibimos de par�metro
	int index = findVertex(vertex);
	if (index >= 0) {
		//Inicializar un vector de bool con falso en todos sus elementos con tama�o igual a size
		vector<bool> status(size, false);
		// Creamos una fila para almacenar la posici�n de los v�rtices
		queue<int> q;
		// Insertamos en la fila el v�rtice de inicio;
		q.push(index);
		// Recorremos los elementos de la fila hasta que ya no tenga elemento
		while (!q.empty()) {
			// Obtenemos el primer elemento de la fila (Esto es por que el pop no me regresa el valor de la fila)
			T indexVertex = q.front();
			// Imprimos el v�rtice procesado
			cout << vertices[indexVertex] << " ";
			// Sacamos de la fila el v�rtice procesado
			q.pop();
			// Cambiamos su estado a verdadero
			status[indexVertex] = true;
			// Recorrer todos los v�rtices adyacentes para agregarlos a la fila si es necesario
			for (auto edge : adjacencyList[indexVertex]) {
				// obtenemos el �ndice del v�rtice adyacente (es seguro que existe)
				int index = findVertex(edge.target);
				// Validamos si el estado del v�rtice adyacente es falso
				if (!status[index]) {
					// agregamos el �ndice del v�rtice adyacente a la fila
					q.push(index);
					// le cambiamos el esado a verdadero al v�rtice adyacente
					status[index] = true;
				}
			}
		}
		cout << endl;
	}
}

template <class T>
void Graph<T>::dfsR(int index, vector<bool>& status) {
	// // Validamos si el v�rtice ya esta procesado
	// if (!status[index]) {
		// Cambiamos el estado del v�rtice a procesar a verdadero
	status[index] = true;
	// Imprimimos el v�rtice a procesar
	cout << vertices[index] << " ";
	// Recorremos todos sus v�rtices adyacentes y los procesamos si su estado es falso
	for (auto edge : adjacencyList[index]) {
		// buscamos el �ndice del v�rtice adyacente
		int indexAdj = findVertex(edge.target);
		// validamos si ya esta procesado
		if (!status[indexAdj]) {
			dfsR(indexAdj, status);
		}
		// }
	}
}

template <class T>
void Graph<T>::dfs(T vertex) {
	// Validar que si existe el v�rtice que recibimos de par�metro
	int index = findVertex(vertex);
	if (index >= 0) {
		//Inicializar un vector de bool con falso en todos sus elementos con tama�o igual a size
		vector<bool> status(size, false);
		// Llamamos a la funci�n de recursividad
		dfsR(index, status);
		cout << endl;
	}
}

// m�todo par encontrar el v�rtice con el menor costo
template <class T>
int Graph<T>::minVertex(vector<bool> status, vector<int> cost) {
	// incializamos en INT_MAX como costo m�nimo
	int minCost = INT_MAX;
	// variable con el �ndice con menor costo
	int minIndex = -1;
	// creamos una variable aux para detectar que haya v�rtices con estado en falso
	bool auxFalse = false;
	// Recorremos todos los v�rtices en false hasta encontrar el m�nimo
	for (int i = 0; i < size; i++) {
		if (!status[i]) {
			auxFalse = true;
			// Camparamos con el costo m�nimo
			if (cost[i] < minCost) {
				minCost = cost[i];
				minIndex = i;
			}
		}
	}
	if (!auxFalse) {
		return -1;
	}
	else {
		return minIndex;
	}
}

template <class T>
void Graph<T>::shortestPath(T vertex) {
	// Inicializar tablas
	// Lista de estados
	vector<bool> status(size, false);
	// Lista de pesos
	vector<int> cost(size, INT_MAX);
	// Lista de paths
	vector<int> path(size, -1);
	// Buscamos el �ndice del v�rtice de inicio
	int indexStart = findVertex(vertex);
	// Validamos que exista
	if (indexStart >= 0) {
		// Asignar un costo de 0 al v�rtice de inicio en la lista de costos
		cost[indexStart] = 0;
		// Llamamos a la funci�n para encontrar el v�rtice m�s peque�o con estado de falso
		int sourceIndex = minVertex(status, cost);
		// Recorrecor los v�rtices mientras exista un v�rtice con estado en false
		while (sourceIndex != -1) {
			// Cambiamos el estado a verdadero del v�rtice con menor costo (fuente)
			status[sourceIndex] = true;
			// Recorremos todos los vecinos del v�rtice fuente
			for (auto edge : adjacencyList[sourceIndex]) {
				// Por cada vecino
				// Buscamos la posici�n del vecino
				int adjacencyIndex = findVertex(edge.target);
				// Validamos su estado
				if (!status[adjacencyIndex]) {
					// si es falso
					// Comparamos el costo del vecino con el costo del fuente m�s el peso entre fuente y el vecino dado (costo[vecino] > costo[fuente] + peso)
					if (cost[adjacencyIndex] > cost[sourceIndex] + edge.weight) {
						// si es mayor      
						// Cambiamos el costo el vecino por el costo del fuente m�s el peso (costo[vecino] = costo[fuente] + peso)                
						cost[adjacencyIndex] = cost[sourceIndex] + edge.weight;
						// Actualizamos el path del vecino (path[vecino] = fuente)
						path[adjacencyIndex] = sourceIndex;
					}
				}
			}
			// vuelvo a encontrar el menor de los �ndices
			sourceIndex = minVertex(status, cost);
		}

		// Creamos una lista de pilas del tama�o de la cantidad de v�rtices (ya la definimos)

		// Recorremos todos los v�rtices
		for (int vertexIndex = 0; vertexIndex < size; vertexIndex++) {
			// Validar si existe path
			if (path[vertexIndex] != -1 || vertexIndex == indexStart) {
				// Agregar el �ndice del v�rtice a la pila
				pathList[vertexIndex].push(vertexIndex);
			}
			// Inicializamos una variable auxPath con el valor del path del v�rtice (auxPath = path[index])
			int auxPath = path[vertexIndex];
			// Hacemos un ciclo mientras la variable auxPath sea diferente de -1
			while (auxPath != -1) {
				// Agregamos el auxPath a la pila
				pathList[vertexIndex].push(auxPath);
				// cambiamos el valor de auxPath por el path del v�rtice con �ndice auxPath (auxPath = path[auxPath])
				auxPath = path[auxPath];
			}
		}
		// imprimimos las rutas con sus pesos
		for (int i = 0; i < size; i++) {
			cout << "Source: " << vertices[i] << " -> ";
			// Validamos si hay path
			if (pathList[i].empty()) {
				// No hay path
				cout << "No hay path" << endl;
			}
			else {
				while (!pathList[i].empty()) {
					cout << pathList[i].top() << " ";
					pathList[i].pop();
				}
				cout << " dist: " << cost[i] << endl;
			}
		}


	}
}

template <class T>
void Graph<T>::shortestPathBetweenVertices(T source, T target) {
	// Inicializar tablas
	// Lista de estados
	vector<bool> status(size, false);
	// Lista de pesos
	vector<int> cost(size, INT_MAX);
	// Lista de paths
	vector<int> path(size, -1);
	// Buscamos el �ndice del v�rtice de inicio
	int indexStart = findVertex(source);
	// Validamos que exista
	if (indexStart >= 0) {
		// Asignar un costo de 0 al v�rtice de inicio en la lista de costos
		cost[indexStart] = 0;
		// Llamamos a la funci�n para encontrar el v�rtice m�s peque�o con estado de falso
		int sourceIndex = minVertex(status, cost);
		// Recorrecor los v�rtices mientras exista un v�rtice con estado en false
		while (sourceIndex != -1) {
			// Cambiamos el estado a verdadero del v�rtice con menor costo (fuente)
			status[sourceIndex] = true;
			// Recorremos todos los vecinos del v�rtice fuente
			for (auto edge : adjacencyList[sourceIndex]) {
				// Por cada vecino
				// Buscamos la posici�n del vecino
				int adjacencyIndex = findVertex(edge.target);
				// Validamos su estado
				if (!status[adjacencyIndex]) {
					// si es falso
					// Comparamos el costo del vecino con el costo del fuente m�s el peso entre fuente y el vecino dado (costo[vecino] > costo[fuente] + peso)
					if (cost[adjacencyIndex] > cost[sourceIndex] + edge.weight) {
						// si es mayor      
						// Cambiamos el costo el vecino por el costo del fuente m�s el peso (costo[vecino] = costo[fuente] + peso)                
						cost[adjacencyIndex] = cost[sourceIndex] + edge.weight;
						// Actualizamos el path del vecino (path[vecino] = fuente)
						path[adjacencyIndex] = sourceIndex;
					}
				}
			}
			// vuelvo a encontrar el menor de los �ndices
			sourceIndex = minVertex(status, cost);
		}

		// Creamos una lista de pilas del tama�o de la cantidad de v�rtices (ya la definimos)

		// Recorremos todos los v�rtices
		for (int vertexIndex = 0; vertexIndex < size; vertexIndex++) {
			// Validar si existe path
			if (path[vertexIndex] != -1 || vertexIndex == indexStart) {
				// Agregar el �ndice del v�rtice a la pila
				pathList[vertexIndex].push(vertexIndex);
			}
			// Inicializamos una variable auxPath con el valor del path del v�rtice (auxPath = path[index])
			int auxPath = path[vertexIndex];
			// Hacemos un ciclo mientras la variable auxPath sea diferente de -1
			while (auxPath != -1) {
				// Agregamos el auxPath a la pila
				pathList[vertexIndex].push(auxPath);
				// cambiamos el valor de auxPath por el path del v�rtice con �ndice auxPath (auxPath = path[auxPath])
				auxPath = path[auxPath];
			}
		}
		// imprimimos la ruta entre los v�rtices
		// Buscamos el �ndice del v�rtice destino (findVertex)

		 for (int i=0; i<size; i++) {
		     cout << "Source: " << vertices[i] << " -> ";
		     // Validamos si hay path
		     if (pathList[i].empty()) {
		         // No hay path
		         cout << "No hay path" << endl;
		     } else {
		         while (!pathList[i].empty()) {
		             cout << pathList[i].top() << " ";
		             pathList[i].pop();
		         }
		         cout << " dist: " << cost[i] << endl;
		     }
		 }


	}
}

template <class T>
void Graph<T>::print()
{
	for (int i = 0; i < vertices.size(); i++)
	{
		cout << vertices[i] << " -> ";
		for (auto edge : adjacencyList[i])
		{
			cout << edge.target << "," << edge.weight << " ";
		}
		cout << endl;
	}
}