#include "header.hpp"

class Betweenness_centrality {
    vector<pair<int, double>> bcs;

public:
    void read_betweenness_centrality(string path)
    {
        ifstream file(path);

        if (!file.good()) {
            cout << path << ": betweenness_centrality file not found" << endl;
            exit(-1);
        }

        string line;

        while (getline(file, line)) {

            int pos = 0;
            std::string delimiter = " ";
            pos = line.find(delimiter);
            int nd = stoi(line.substr(0, pos));
            line.erase(0, pos + delimiter.length());

            double bc = stod(line);
            bcs.push_back(make_pair(nd, bc));
        }
    }

    vector<pair<int, double>> get_betweenness_centrality()
    {
        return bcs;
    }
};