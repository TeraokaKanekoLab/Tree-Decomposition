#include "header.hpp"

void print_vector(vector<int> v)
{
    if (v.size() == 0) {
        cout << "[]" << endl;
        return;
    }
    cout << "[" << v[0];
    for (int i = 1; i < v.size(); ++i) {
        cout << ", " << v[i];
    }
    cout << "]" << endl;
}

void print_vector_with_index(vector<int> v)
{
    if (v.size() == 0) {
        cout << "[]" << endl;
        return;
    }
    for (int i = 0; i < v.size(); i++) {
        cout << i << ": " << v[i] << endl;
    }
}