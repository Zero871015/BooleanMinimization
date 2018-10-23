// Name: zero871015(B10615032)
// Date: 2018/10/21
// Last Update: 2018/10/23
// Problem statement: Exact Boolean Minimization

#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

//Data structure of SOP.
struct sop
{
	set<int> num;
	string bits;
	bool isused;
	bool operator==(sop s) { if (s.bits == this->bits)return true; else return false; }
};

void Quine_McCluskey(ifstream&,ofstream&);
void Simplification(vector<sop>*,int,vector<sop>*);
int diffStr(string s1, string s2);
sop Merge(sop& s1, sop& s2);

int main(int argc, char *argv[])
{
	//Need input and output files.
	if (argc != 3)
	{
		cout << "parameter error!" << endl;
		return -1;
	}
	else
	{
		ifstream fin(argv[1]);
		//Can not open.
		if (!fin)
		{
			cout << "file error!" << endl;
			return -1;
		}
		else
		{
			ofstream fout(argv[2], ofstream::out);
			Quine_McCluskey(fin,fout);
		}
	}
	return 0;
}

void Quine_McCluskey(ifstream &fin, ofstream &fout)
{
	string str;
	int num_in,num_sop;
	string ilbs;
	string ob;
	char *table = NULL;
	while (!fin.eof())
	{
		fin >> str;
		//How many input.
		if (str == ".i")
		{
			fin >> num_in;
			//Initialize the truth table.
			table = new char[(int)pow(2, num_in)];
			for (int i = 0; i < (int)pow(2,num_in); i++)
			{
				table[i] = '0';
			}
		}
		//How many output.
		else if (str == ".o")
		{
			//In this case, output always only one.
			getline(fin, str);
		}
		//Name of input.
		else if (str == ".ilb")
		{
			getline(fin, ilbs);
		}
		//Name of output.
		else if (str == ".ob")
		{
			fin >> ob;
		}
		//Input SOP.
		else if (str == ".p")
		{
			//Get the karnaugh map.
			fin >> num_sop;
			string in, out;
			for (int i = 0; i < num_sop; i++)
			{
				fin >> in >> out;
				reverse(in.begin(), in.end());
				//Fill in truth table.
				for (int j = 0; j < (int)pow(2, num_in); j++)
				{
					int temp = j;
					bool f = true;
					for (int k = 0; k < num_in; k++)
					{
						if (temp % 2 == 1)
						{
							if (in[k] == '0')
							{
								f = false;
								break;
							}
						}
						else
						{
							if (in[k] == '1')
							{
								f = false;
								break;
							}
						}
						temp /= 2;
					}
					if (table[j] == '0'&&f)
					{
						table[j] = out[0];
					}
				}
			}
			//Record the target cells.
			map<int,bool> targets;
			//For sop of only one 1, two 1, three 1....
			vector<sop>* S = new vector<sop>[num_in + 1];

			for (int i = 0; i < (int)pow(2,num_in); i++)
			{
				if (table[i] != '0')
				{
					string str;
					int temp = i;
					int count = 0;
					for (int j = 0; j < num_in; j++)
					{
						if (temp % 2 == 1)
						{
							count++;
							str += "1";
						}
						else
							str += "0";
						temp /= 2;
					}
					sop Stemp;
					Stemp.num.insert(i);
					Stemp.bits = str;
					Stemp.isused = false;
					S[count].push_back(Stemp);
				}

				if (table[i] == '1')
					targets[i] = false;
			}
			vector<sop> Result;
			//Recursion to find prime implicants.
			Simplification(S, num_in + 1, &Result);

			bool *pick = new bool[Result.size() + 1];
			for (int i = 0; i < (int)Result.size()+1; i++)
			{
				pick[i] = false;
			}

			int Maxterm = 99999;
			string pickwho;
			//Find the term or terms composed of the minimum total number of literals.
			while (!pick[Result.size()])
			{
				for (auto i = targets.begin(); i != targets.end(); i++)
				{
					i->second = false;
				}
				int term = 0;
				for (int i = 0; i < (int)Result.size(); i++)
				{
					if (pick[i])
					{
						for (auto j = Result[i].num.begin(); j != Result[i].num.end(); j++)
						{
							targets[*j] = true;
						}
						term++;
					}
				}
				bool isok = true;
				for (auto i = targets.begin(); i != targets.end(); i++)
				{
					if (i->second == false)
					{
						isok = false;
						break;
					}
				}

				if(isok)
					if (term < Maxterm)
					{
						pickwho.clear();
						Maxterm = term;
						for (int i = 0; i < (int)Result.size(); i++)
						{
							if (pick[i])
								pickwho += "1";
							else
								pickwho += "0";
						}
					}
				pick[0] = !pick[0];
				for (int i = 0; i < (int)Result.size(); i++)
				{
					if (!pick[i])
						pick[i + 1] = !pick[i + 1];
					else
						break;
				}
			}
			//Save file.
			int literals = 0;
			fout << ".i " << num_in << endl;
			fout << ".o 1" << endl;
			fout << ".ilb" << ilbs << endl;
			fout << ".ob " << ob << endl;
			fout << ".p " << Maxterm << endl;
			for (int i = 0; i < (int)pickwho.length(); i++)
			{
				if (pickwho[i] == '1')
				{
					reverse(Result[i].bits.begin(), Result[i].bits.end());
					for (int j = 0; j < (int)Result[i].bits.length(); j++)
					{
						if (Result[i].bits[j] != '-')
							literals++;
					}
					fout << Result[i].bits << " 1" << endl;
				}
			}
			fout << ".e";
			cout << "Total number of terms: " << Maxterm << endl;
			cout << "Total number of literals: " << literals << endl;
			fout.close();
		}
		else if(str==".e")
		{
			break;
		}
	}
}

//Return how many different of two string.
int diffStr(string s1, string s2)
{
	int count = 0;
	for (int i = 0; i < (int)s1.length(); i++)
	{
		if (s1[i] != s2[i])
			count++;
	}
	return count;
}

//Merge two sop, and return sop which contain '-'.
sop Merge(sop& s1, sop& s2)
{
	sop temp;
	string str;
	for (int i = 0; i < (int)s1.bits.length(); i++)
	{
		if (s1.bits[i] != s2.bits[i])
		{
			str += '-';
		}
		else
			str += s1.bits[i];
	}
	for (auto i = s1.num.begin(); i != s1.num.end(); i++)
	{
		temp.num.insert(*i);
	}
	for (auto i = s2.num.begin(); i != s2.num.end(); i++)
	{
		temp.num.insert(*i);
	}
	s1.isused = true;
	s2.isused = true;
	temp.bits = str;
	temp.isused = false;
	return temp;
}

void Simplification(vector<sop>* S, int size, vector<sop>* R)
{
	bool F = false;
	vector<sop>* next = new vector<sop>[size];
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = i + 1; j < size; j++)
		{

			for (int k = 0; k < (int)S[i].size(); k++)
			{
				for (int l = 0; l < (int)S[j].size(); l++)
				{
					if (diffStr(S[i][k].bits, S[j][l].bits) == 1)
					{
						sop temp = Merge(S[i][k], S[j][l]);
						if (find(next[i].begin(), next[i].end(), temp) == next[i].end())
						{
							next[i].push_back(temp);
							F = true;
						}
					}
				}
			}
			
		}
	}
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < (int)S[i].size(); j++)
		{
			if (S[i][j].isused == false)
				R->push_back(S[i][j]);
		}
	}
	if(F)
		Simplification(next, size, R);
}