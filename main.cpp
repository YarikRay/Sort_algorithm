
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <map>
#include <vector>
#include <algorithm>


using namespace std;
using namespace std::filesystem;

struct mystruct
{
    int deep;
    string name;
    string text;
};

int main()
{
    vector<pair<int, string>> new_v; // ����� ������ ��� ���������� ������������ ����� �������� � �������

    vector<pair<int, int>> depth_ind_vect; // ������ ��� ���������� ������ � �� ��������
    vector<pair<int, string>> text_ind_vect; // ������ ��� ���������� �������� � ������
    vector <mystruct> vect;

    for (const auto& entry : recursive_directory_iterator("mydirectory"))
    {
        if(entry.is_regular_file())
        {
            ifstream in(entry.path());
            if (in.is_open())
            {
                mystruct var;
                var.name = entry.path().filename().string();
                while(in >> var.deep >> var.text)
                {
                    vect.push_back(var);
                }
            }
        }
    }
    // ������������� ������ � ������
    for(int i = 0; i < vect.size(); i++)
    {
        depth_ind_vect.push_back(make_pair(vect[i].deep, i));
    }


    stable_sort(depth_ind_vect.begin(), depth_ind_vect.end());

    vector<pair<int,int>> index; // ������ ��� ���������� �������� �������
    for(auto i: depth_ind_vect)
    {
        index.push_back(make_pair(i.first,i.second));

    }

    for(int i = 0; i < vect.size(); i++)
    {
        text_ind_vect.push_back(make_pair(i, vect[i].name));
    }

    // ����� �� �����
    for (int i = 0; i < index.size(); i++)
	{
		cout << index[i].first << " " << text_ind_vect[index[i].second].second << endl;
	}

    return 0;
}
