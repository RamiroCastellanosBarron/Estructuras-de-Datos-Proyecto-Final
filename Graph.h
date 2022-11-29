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
	// Asignamos el valor del parametro vértices a mi lista de vértices
	this->vertices = vertices;
	// Asignamos el tamaño del vector de vertices al atributo size
	size = vertices.size();
	// Inicializamos la lista de adyacencias en el tamaño de vértices que recibimos de parametro
	// Hacemos un vector vacio de tipo Edge de tipo T
	vector<Edge<T> > aux;
	// Hacemos un stack vacio de tipo entero
	stack<int> pathStack;
	// recorremos cada uno de los elementos de mi lista de vértices
	for (auto vertex : vertices)
	{
		adjacencyList.push_back(aux);
		pathList.push_back(pathStack);
	}

}

template <class T>
int Graph<T>::findVertex(T vertex)
{
	// Creamos una variable de tipo "iterator" para almacenar la posición encontrada
	typename vector<T>::iterator it;
	// buscamos el vértice en la lista de vértices
	it = find(vertices.begin(), vertices.end(), vertex);
	// Validamos i encontramos el vértice
	if (it != vertices.end())
	{
		// regresamos la posición donde se encuentra el vértice
		return it - vertices.begin();
	}
	else
	{
		// no encotramos el vértice
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
		// Buscar la pocisicón del source en mi lista de vertices y asignarla a sourceIndex
		int sourceIndex = findVertex(newEdge.source);
		// Buscar la pocisicón del target en mi lista de vertices y asignarla a targetIndex
		int targetIndex = findVertex(newEdge.target);
		// validamos que hayamos encontrado los vertices
		if (sourceIndex >= 0 && targetIndex >= 0)
		{
			// Agrema el valor de newEdge a la lista de que se encunetra en la posición de sourceIndex en mi lista de adyacencias
			adjacencyList[sourceIndex].push_back(newEdge);
		}
	}
}

template <class T>
void Graph<T>::bfs(T vertex) {
	// Validar que si existe el vértice que recibimos de parámetro
	int index = findVertex(vertex);
	if (index >= 0) {
		//Inicializar un vector de bool con falso en todos sus elementos con tamaño igual a size
		vector<bool> status(size, false);
		// Creamos una fila para almacenar la posición de los vértices
		queue<int> q;
		// Insertamos en la fila el vértice de inicio;
		q.push(index);
		// Recorremos los elementos de la fila hasta que ya no tenga elemento
		while (!q.empty()) {
			// Obtenemos el primer elemento de la fila (Esto es por que el pop no me regresa el valor de la fila)
			T indexVertex = q.front();
			// Imprimos el vértice procesado
			cout << vertices[indexVertex] << " ";
			// Sacamos de la fila el vértice procesado
			q.pop();
			// Cambiamos su estado a verdadero
			status[indexVertex] = true;
			// Recorrer todos los vértices adyacentes para agregarlos a la fila si es necesario
			for (auto edge : adjacencyList[indexVertex]) {
				// obtenemos el índice del vértice adyacente (es seguro que existe)
				int index = findVertex(edge.target);
				// Validamos si el estado del vértice adyacente es falso
				if (!status[index]) {
					// agregamos el índice del vértice adyacente a la fila
					q.push(index);
					// le cambiamos el esado a verdadero al vértice adyacente
					status[index] = true;
				}
			}
		}
		cout << endl;
	}
}

template <class T>
void Graph<T>::dfsR(int index, vector<bool>& status) {
	// // Validamos si el vértice ya esta procesado
	// if (!status[index]) {
		// Cambiamos el estado del vértice a procesar a verdadero
	status[index] = true;
	// Imprimimos el vértice a procesar
	cout << vertices[index] << " ";
	// Recorremos todos sus vértices adyacentes y los procesamos si su estado es falso
	for (auto edge : adjacencyList[index]) {
		// buscamos el índice del vértice adyacente
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
	// Validar que si existe el vértice que recibimos de parámetro
	int index = findVertex(vertex);
	if (index >= 0) {
		//Inicializar un vector de bool con falso en todos sus elementos con tamaño igual a size
		vector<bool> status(size, false);
		// Llamamos a la función de recursividad
		dfsR(index, status);
		cout << endl;
	}
}

// método par encontrar el vértice con el menor costo
template <class T>
int Graph<T>::minVertex(vector<bool> status, vector<int> cost) {
	// incializamos en INT_MAX como costo mínimo
	int minCost = INT_MAX;
	// variable con el índice con menor costo
	int minIndex = -1;
	// creamos una variable aux para detectar que haya vértices con estado en falso
	bool auxFalse = false;
	// Recorremos todos los vértices en false hasta encontrar el mínimo
	for (int i = 0; i < size; i++) {
		if (!status[i]) {
			auxFalse = true;
			// Camparamos con el costo mínimo
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
	// Buscamos el índice del vértice de inicio
	int indexStart = findVertex(vertex);
	// Validamos que exista
	if (indexStart >= 0) {
		// Asignar un costo de 0 al vértice de inicio en la lista de costos
		cost[indexStart] = 0;
		// Llamamos a la función para encontrar el vértice más pequeño con estado de falso
		int sourceIndex = minVertex(status, cost);
		// Recorrecor los vértices mientras exista un vértice con estado en false
		while (sourceIndex != -1) {
			// Cambiamos el estado a verdadero del vértice con menor costo (fuente)
			status[sourceIndex] = true;
			// Recorremos todos los vecinos del vértice fuente
			for (auto edge : adjacencyList[sourceIndex]) {
				// Por cada vecino
				// Buscamos la posición del vecino
				int adjacencyIndex = findVertex(edge.target);
				// Validamos su estado
				if (!status[adjacencyIndex]) {
					// si es falso
					// Comparamos el costo del vecino con el costo del fuente más el peso entre fuente y el vecino dado (costo[vecino] > costo[fuente] + peso)
					if (cost[adjacencyIndex] > cost[sourceIndex] + edge.weight) {
						// si es mayor      
						// Cambiamos el costo el vecino por el costo del fuente más el peso (costo[vecino] = costo[fuente] + peso)                
						cost[adjacencyIndex] = cost[sourceIndex] + edge.weight;
						// Actualizamos el path del vecino (path[vecino] = fuente)
						path[adjacencyIndex] = sourceIndex;
					}
				}
			}
			// vuelvo a encontrar el menor de los índices
			sourceIndex = minVertex(status, cost);
		}

		// Creamos una lista de pilas del tamaño de la cantidad de vértices (ya la definimos)

		// Recorremos todos los vértices
		for (int vertexIndex = 0; vertexIndex < size; vertexIndex++) {
			// Validar si existe path
			if (path[vertexIndex] != -1 || vertexIndex == indexStart) {
				// Agregar el índice del vértice a la pila
				pathList[vertexIndex].push(vertexIndex);
			}
			// Inicializamos una variable auxPath con el valor del path del vértice (auxPath = path[index])
			int auxPath = path[vertexIndex];
			// Hacemos un ciclo mientras la variable auxPath sea diferente de -1
			while (auxPath != -1) {
				// Agregamos el auxPath a la pila
				pathList[vertexIndex].push(auxPath);
				// cambiamos el valor de auxPath por el path del vértice con índice auxPath (auxPath = path[auxPath])
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
	// Buscamos el índice del vértice de inicio
	int indexStart = findVertex(source);
	// Validamos que exista
	if (indexStart >= 0) {
		// Asignar un costo de 0 al vértice de inicio en la lista de costos
		cost[indexStart] = 0;
		// Llamamos a la función para encontrar el vértice más pequeño con estado de falso
		int sourceIndex = minVertex(status, cost);
		// Recorrecor los vértices mientras exista un vértice con estado en false
		while (sourceIndex != -1) {
			// Cambiamos el estado a verdadero del vértice con menor costo (fuente)
			status[sourceIndex] = true;
			// Recorremos todos los vecinos del vértice fuente
			for (auto edge : adjacencyList[sourceIndex]) {
				// Por cada vecino
				// Buscamos la posición del vecino
				int adjacencyIndex = findVertex(edge.target);
				// Validamos su estado
				if (!status[adjacencyIndex]) {
					// si es falso
					// Comparamos el costo del vecino con el costo del fuente más el peso entre fuente y el vecino dado (costo[vecino] > costo[fuente] + peso)
					if (cost[adjacencyIndex] > cost[sourceIndex] + edge.weight) {
						// si es mayor      
						// Cambiamos el costo el vecino por el costo del fuente más el peso (costo[vecino] = costo[fuente] + peso)                
						cost[adjacencyIndex] = cost[sourceIndex] + edge.weight;
						// Actualizamos el path del vecino (path[vecino] = fuente)
						path[adjacencyIndex] = sourceIndex;
					}
				}
			}
			// vuelvo a encontrar el menor de los índices
			sourceIndex = minVertex(status, cost);
		}

		// Creamos una lista de pilas del tamaño de la cantidad de vértices (ya la definimos)

		// Recorremos todos los vértices
		for (int vertexIndex = 0; vertexIndex < size; vertexIndex++) {
			// Validar si existe path
			if (path[vertexIndex] != -1 || vertexIndex == indexStart) {
				// Agregar el índice del vértice a la pila
				pathList[vertexIndex].push(vertexIndex);
			}
			// Inicializamos una variable auxPath con el valor del path del vértice (auxPath = path[index])
			int auxPath = path[vertexIndex];
			// Hacemos un ciclo mientras la variable auxPath sea diferente de -1
			while (auxPath != -1) {
				// Agregamos el auxPath a la pila
				pathList[vertexIndex].push(auxPath);
				// cambiamos el valor de auxPath por el path del vértice con índice auxPath (auxPath = path[auxPath])
				auxPath = path[auxPath];
			}
		}
		// imprimimos la ruta entre los vértices
		// Buscamos el índice del vértice destino (findVertex)

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