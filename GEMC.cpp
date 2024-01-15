// 01/09/2024 Cheng-Hao-Lu
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <map>
#include <fstream>

using namespace std;
double b = 1;
double els = 1;
double sig = 1;
vector<int> atomnu = {10, 10};
vector<double> lengbox = {10.0, 10.0};

double ljenergy(vector<double> atom1, vector<double> atom2)
{
    if (atom1.size() != atom2.size())
    {
        throw invalid_argument("vectors have different size.");
    }
    double sum = 0;
    for (int i = 0; i < atom1.size(); i++)
    {
        sum += pow(atom1[i] - atom2[i], 2);
    };
    double dis = sqrt(sum);
    double energy = 4 * els * (pow((sig / dis), 12) - pow((sig / dis), 6));
    return energy;
};

vector<vector<double>> ranmove(vector<vector<double>> ranmovecon, int step){
    return {{0.0}};
};


class state
{
public:
    double energy(int index)
    {
        double tote = 0;
        vector<vector<double>> con;
        switch (index)
        {
        case 1:
            con = config1;
        case 2:
            con = config2;
        };
        int i, j;
        for (i = 0; i < con.size(); i++)
        {
            for (j = i + 1; j < con.size(); j++)
            {
                vector<double> dis = {con[i][0] - con[j][0], con[i][1] - con[j][1], con[i][2] - con[j][2]};
                for (double &coor : dis)
                {
                    if (coor > 0.5 * lengbox[index])
                    {
                        coor = coor - lengbox[index];
                    }
                    else if (i < -0.5 * lengbox[index])
                    {
                        coor = coor + lengbox[index];
                    }
                }
                tote = tote + ljenergy(con[i], dis);
            };
        };
        return tote;
    };

private:
    vector<vector<double>> config1 = {};
    vector<vector<double>> config2 = {};
};
int main()
{
    char ch;
    ifstream initfile("initfile.txt");
    if (initfile.is_open())
    {
        while (!initfile.eof())
        {
            initfile.get(ch);
            cout << ch << endl;
        };
    }
    else
    {
        cerr << "test" << endl;
    }
    return 0;
};