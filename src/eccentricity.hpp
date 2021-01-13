#include "header.hpp"

class Eccentricity {
    vector<pair<int, int>> ecs;

public:
    void read_eccentricity(string path)
    {
        ifstream file(path);

        if (!file.good()) {
            cout << path << ": eccentricity file not found" << endl;
            exit(-1);
        }

        string line;

        while (getline(file, line)) {

            int pos = 0;
            std::string delimiter = " ";
            pos = line.find(delimiter);
            int nd = stoi(line.substr(0, pos));
            line.erase(0, pos + delimiter.length());

            double bc = stoi(line);
            ecs.push_back(make_pair(nd, bc));
        }
    }

    vector<pair<int, int>> get_eccentricity()
    {
        return ecs;
    }
};