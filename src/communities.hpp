#include "header.hpp"

class Communities {
    vector<vector<int>> communities;

public:
    void read_community(string path)
    {
        ifstream file(path);

        if (!file.good()) {
            cout << "community file not found" << endl;
            exit(-1);
        }

        string line;

        while (getline(file, line)) {
            vector<int> community;

            int pos = 0;
            std::string delimiter = " ";
            while ((pos = line.find(delimiter)) != std::string::npos) {
                int nd = stoi(line.substr(0, pos));
                line.erase(0, pos + delimiter.length());
                community.push_back(nd);
            }
            if (!line.empty()) {
                int nd = stoi(line);
                community.push_back(nd);
            }
            communities.push_back(community);
        }
    }
    vector<vector<int>> get_communities()
    {
        return communities;
    }

    void print_communities()
    {
        for (auto community : communities) {
            for (auto nd : community)
                cout << nd << " ";
            cout << endl;
        }
    }
};