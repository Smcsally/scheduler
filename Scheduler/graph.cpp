// complete.cpp

#include <cstring>
#include <iostream>
#include <fstream>
using namespace std;

template <int N>
class Graph {
public:
	// start with no edges at all
	Graph() {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				matrix[i][j] = 0;
			}
		}

		count = 0;
	}

	// insert an edge
	void insertEdge(const char fromcity[], const char tocity[], int cost) {
		int from = lookup(fromcity);
		int to = lookup(tocity);
		matrix[from][to] = cost;
		matrix[to][from] = cost;
	}

	// lookup the index of a name
	int lookup(const char name[]) const {
		for (int i = 0; i < count; i++) {
			if (strcmp(names[i], name) == 0) {
				return i;
			}
		}

		return -1;
	}

	// return name of an index
	const char* name(int index) const {
		return names[index];
	}

	// insert a node
	void insertNode(const char* name) {
		strcpy(names[count], name);
		count++;
	}

	// return the cost of an edge or 0 for none
	int getCost(int from, int to) const {
		return matrix[from][to];
	}

	// remove an edge
	void removeEdge(const char fromcity[], const char tocity[]) {
		int from = lookup(fromcity);
		int to = lookup(tocity);
		matrix[from][to] = 0;
		matrix[to][from] = 0;
	}

	// return the number of nodes
	int size() const {
		return count;
	}

	// return whether the graph is complete
	bool complete() const {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (i == j) {
					if (matrix[i][j] != 0) {
						return false;
					}
				}
				else {
					if (matrix[i][j] == 0) {
						return false;
					}
				}
			}
		}
		return true;
	}



private:
	int matrix[N][N];
	char names[N][25];
	int count;
};

int main(int argc, char* argv[]) {
	char temp[5];
	char filename[50];

	if (argc < 1) {
		cout << "Error, no parameter.  1 parameter must be supplied with the name of the input file." << endl;
	}
	else if (argc > 2) {
		cout << "Error, too many parameters.  1 parameter must be supplied with the name of the input file." << endl;
	}
	else {
		strcpy(filename, argv[1]);
		Graph<11> graph;
	
		//open the input stream
		ifstream fin(filename);
		if (fin.is_open()) {
			char temp[100];
			char course_name[15];

			// the file opened fine!
			fin >> temp;
			int count;

			//insert all nodes into the matrix
			while (!fin.eof()) {
				cout << "Inserted " << temp << " into the matrix" << endl;
				graph.insertNode(temp);
				fin >> count;
				for (int i = 1; i <= count; i++) {
					fin >> temp;
				}
				fin >> temp;
			}

			// reset end of file to false
			fin.clear();
			// move the input back to the start
			fin.seekg(0, ios::beg);

			//insert all edges into the matrix
			while (!fin.eof()) {
				//keep the course name for inserting edges
				fin >> course_name;
				//get the number of pre-requisites
				fin >> count;
				for (int i = 1; i <= count; i++) {
					fin >> temp;
					graph.insertEdge(temp, course_name, 1);
					cout << temp << " is a pre-req for " << course_name << endl;
				}
			}
		}
		else {
			cout << "Failed opening the file for input." << endl;
		}
		
		/*graph.insertNode("A");
		graph.insertNode("B");
		graph.insertNode("C");
		graph.insertNode("D");
		graph.insertNode("E");

		graph.insertEdge("A", "B", 13);
		graph.insertEdge("A", "C", 29);
		graph.insertEdge("A", "D", 31);
		graph.insertEdge("A", "E", 48);

		graph.insertEdge("B", "C", 13);
		graph.insertEdge("B", "D", 23);
		graph.insertEdge("B", "E", 26);

		graph.insertEdge("C", "D", 24);
		graph.insertEdge("C", "E", 18);

		graph.insertEdge("D", "E", 14);

		// should print "Complete!"
		if (graph.complete()) {
			cout << "Complete!" << endl;
		}
		else {
			cout << "Not complete!" << endl;
		}

		// remove an edge and try it again
		graph.removeEdge("B", "C");

		// should print "Not complete!"
		if (graph.complete()) {
			cout << "Complete!" << endl;
		}
		else {
			cout << "Not complete!" << endl;
		}*/

		cin >> temp;
		
	}
	return 0;
}

