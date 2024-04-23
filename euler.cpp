// Find an Euler trail in a graph
#include "graph.h"
#include <iostream>
#include <list>
using namespace std;

void extend_path (Graph<int>& g, list<int>& p);
list<int> find_path (const Graph<int>& g);
void print_path (const list<int>& p);

int main () {
	Graph<int> g1;
	list<int> path;

	// Sample graph #1, has an Euler circuit
	g1.add_edge(1, 2);
	g1.add_edge(1, 3);
	g1.add_edge(1, 4);
	g1.add_edge(1, 5);
	g1.add_edge(2, 3);
	g1.add_edge(2, 5);
	g1.add_edge(2, 6);
	g1.add_edge(3, 6);
	g1.add_edge(3, 7);
	g1.add_edge(4, 5);
	g1.add_edge(5, 6);
	g1.add_edge(6, 7);

	path = find_path(g1);

	cout << g1;
	print_path(path);

	// Sample graph #2, has an Euler path
	Graph<int> g2;
	g2.add_edge(1, 2);
	g2.add_edge(1, 4);
	g2.add_edge(2, 3);
	g2.add_edge(2, 4);
	g2.add_edge(3, 5);
	g2.add_edge(4, 5);

	path = find_path(g2);
	cout << g2;
	print_path(path);

	// Sample graph #3, non-Eulerian
	Graph<int> g3;
	g3.add_edge(1, 2);
	g3.add_edge(1, 3);
	g3.add_edge(1, 4);
	g3.add_edge(1, 5);
	g3.add_edge(2, 3);
	g3.add_edge(2, 5);
	g3.add_edge(3, 6);
	g3.add_edge(4, 5);
	g3.add_edge(4, 6);
	g3.add_edge(5, 6);

	path = find_path(g3);
	cout << g3;
	print_path(path);
}

void extend_path (Graph<int>& g, list<int>& p) {
	// If end of path has no neighbors, we're done
	if (!g.degree(p.back()))
		return;

	// Find a neighbor of last vertex on path, but not starting vertex
	int v_next = 0; // Next vertex on path, assumes no vertex 0
	for (int v : g.neighbors(p.back()))
		if (!v_next && v != p.front())
			v_next = v;

	// If no vertex found, starting vertex is the only neighbor
	if (!v_next)
		v_next = p.front();

	// Remove from g the edge from end of the path to next vertex
	g.remove_edge(p.back(), v_next);

	// Add next vertex to end of path
	p.push_back(v_next);

	// Find next edge along the path
	extend_path(g, p);
}

list<int> find_path (const Graph<int>& g) {
	// Find first odd vertex, if any, and count odd vertices along the way
	int count_odd = 0; // Count of vertices with odd degree
	int first_odd = 0; // First vertex of odd degree, assumes no vertex #0
	for (int v : g.vertices()) {
		if (g.degree(v) % 2) { // If vertex with odd degree
			count_odd++; // Count v as among vertices with odd degree
			if (!first_odd) // If first such vertex found
				first_odd = v; // Will be start path, if one exists
		}
	}

	// For building a list of vertices to describe the path
	list<int> p;

	// If a path exists, find one
	if (!count_odd || count_odd == 2) { // Must have 0 or 2 odd-degree vertices
		// Add start vertex to the current path; the first odd-degree vertex
		// encountered if one exists, else first vertex in the list of vertices
		p.push_back(first_odd ? first_odd : g.vertices().front());
		// Extend the path to form a path, passing a copy of the graph (which
		// will be modified)
		Graph<int> g_copy(g);
		extend_path(g_copy, p);
	}

	// Return the path
	return p;
}

void print_path (const list<int>& p) {
	cout << "Euler Path: ";
	if (p.size())
		for (int v : p)
			cout << " " << v;
	else
		cout << "none.";
	cout << "\n\n";
}
