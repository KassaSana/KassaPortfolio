#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <iomanip>
using namespace std;

// Adjacency List Graph
class AdjacencyList {
private:
    unordered_map<string, unsigned int> outgoingLinks;  // Store the outdegree connection
    unordered_map<string, vector<string> > incomingLinks;  // Store the idegree connection
    map<string, float> pageRank;
    int getTotalVertices() {
        return (int) incomingLinks.size();
    }
    void initializePageRank() {
        for (auto &vertex : incomingLinks) {
            pageRank[vertex.first] = 1.0f / (float) getTotalVertices();
        }
    }
    void printPageRanks() {
        // go through each vertex
        map<string, float>::iterator pageRankIt;
        for(pageRankIt = pageRank.begin(); pageRankIt != pageRank.end(); ++pageRankIt) {
            cout << std::setprecision(2) << std::fixed << pageRankIt->first << " " << pageRankIt->second;
            cout<<"\n";
        }
    }

public:
    AdjacencyList() = default; // const
    // Connect two vert
    void insertEdge(string &from, string &to) {
        outgoingLinks[from] += 1;
        incomingLinks[to].push_back(from);
        if (outgoingLinks.find(to) == outgoingLinks.end()) outgoingLinks[to] = 0;
        if (incomingLinks.find(from) == incomingLinks.end()) incomingLinks[from] = {};
    }
    void PageRank(int power_iterations) {
        initializePageRank();
        map<string, float> newPageRank;
        // looks for page rank
        for (int i = 1; i < power_iterations; i++) {
            newPageRank = pageRank; //temp rank to hold
            for (auto &webpage : incomingLinks) {
                float sum = 0.0f;
                for (auto &link : webpage.second) {
                    sum += (1.0f / (float) outgoingLinks.find(link)->second) * pageRank[link];
                }
                newPageRank[webpage.first] = sum; //update page rank
            }
            pageRank = newPageRank; // Update page rank
        }
        printPageRanks();
    }
};

int main() {
    AdjacencyList graph;
    int no_of_lines = 0, power_iterations = 0;
    string from, to;
//input
    cin >> no_of_lines;
    cin >> power_iterations;

    for (int i = 0; i < no_of_lines; i++) {
        cin >> from;
        cin >> to;

        graph.insertEdge(from, to);
    }
    graph.PageRank(power_iterations);

    return 0;
}