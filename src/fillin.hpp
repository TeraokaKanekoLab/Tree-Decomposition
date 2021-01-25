#include "header.hpp"

class Fillin {
    vector<pair<int, double>> fillins;
    unordered_map<int, double> fillin_map;

public:
    void read_fillin(string path)
    {
        ifstream file(path);

        if (!file.good()) {
            cout << path << ": fillin file not found" << endl;
            exit(-1);
        }

        string line;

        while (getline(file, line)) {

            int pos = 0;
            std::string delimiter = " ";
            pos = line.find(delimiter);
            int nd = stoi(line.substr(0, pos));
            line.erase(0, pos + delimiter.length());

            pos = line.find(delimiter);
            int hit = stoi(line.substr(0, pos));
            line.erase(0, pos + delimiter.length());

            int size = stoi(line);
            fillins.push_back(make_pair(nd, (double)2 * hit / (size * (size - 1))));
            fillin_map[nd] = (double)2 * hit / (size * (size - 1));
        }
    }

    vector<pair<int, double>> get_fillins()
    {
        return fillins;
    }

    double fillin_of(int nd)
    {
        if (fillin_map.find(nd) == fillin_map.end())
            return -1;
        return fillin_map[nd];
    }
};