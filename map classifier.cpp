// map classifier.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#define e   2.71
#define pi  3.14

using namespace std;
//---------------sakhtan parametr Nk------------------------------
int NK(string rade,string rade_mesal [],int m)
{
	int count = 0;
	for (int i = 0; i < m; i++)
	{
		if (rade_mesal[i] == rade) count++;
	}
	return count;
}
//-------------miangin----------------------------------------------
float miangin(vector <float> gp) 
{
	float sum = 0;
	for (int i = 0; i < gp.size(); i++)
		sum += gp[i];
	return sum / gp.size();
}
//--------------------------varians------------------------------------------------
float varians(vector <float> gp)
{
	float s = 0;
	float m = miangin(gp);
	for (int i = 0; i < gp.size(); i++)
		s += (gp[i] - m)*(gp[i] - m);
	return s/ gp.size();
}
//-----------sakhtan qsmt avval formool sevvom--------------------------------
float zarib(float vari)
{
	float a= 2 * pi*vari;
	return 1 / (sqrt(a));
}
//--------------------sakhtan tavan e------------------------------------------
float tavan(float xi, float midd,float vari)
{	
	float a = xi - midd;
	return -1 * (pow (a,2) / (2 * vari));
}
//--------------------------main-----------------------------------------------------
int main()
{
	int n = 0;//tedad vizhegi
	int k = 0; //tedad rade ha
	vector <float> pck;//zakhire pck har rade
	cout << "tedad vizhegi = ";
	cin >> n;
	cout << "tedad rade = ";
	cin >> k;
	string a;//komaki 
	vector <string> radeha;//esm radeha
	for (int i = 0; i < k; ++i)//grftn esm rade ha
	{
		cout << "rade " << i + 1 << " om = ";
		cin >> a;
		radeha.push_back(a);
	}
	cout << endl << "esm file ra vared konid = ";
	string esmfile;
	cin >> esmfile;
	ifstream ifs;
	ifs.open(esmfile);
	int m;//tedad nmoone haye mojood dar file(tedad khat)
	ifs >> m;
	//---------------dadehaye nmoone ha------------allocation----------------------------------
	float **ex = new float *[m];
	for (int i = 0; i < m; i++)
		ex[i] = new float[n];
	//----------------------------grftn rade nmoone ha-----------------------------------------
	string *rade_mesal = new string[m];
	//-----------------------------grftn nmoone ha az file---------------------------------------------
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n+1; j++)
		{
			if (j == n) ifs >> rade_mesal[i];//zakhire rade nmoone 
			else ifs >> ex[i][j];//zakhire adad nmoone
		}
	}
	
	for (int i = 0; i < k; i++)
		pck.push_back(NK(radeha[i], rade_mesal, m) / (static_cast <float> (m))); //por krdn vector pck ba estefade az formool (nk/m)
	//sakhtan yek vector braye zakhire dade haii k bayad miangin shan ba ham grfte shvd
	vector <float> gp;
	//-------sakhtan matris miangin-------------------
	float **mid = new float *[k];
	for (int i = 0; i < k; i++)
		mid[i] = new float[n];
	//------sakhtan matris varians---------------------
	float **var = new float *[k];
	for (int i = 0; i < k; i++)
		var[i] = new float[n];
	//goroh bandi krdn aadad va por krdn matris haye mid , var
	for (int l=0;l<n;l++)//vizhegi b vizhegi jlo mire
	{ 
		for (int i = 0; i < k; i++)//rade asli b rade asli jlo mire
		{	
			gp.clear();
			for (int j = 0; j < m; j++)//rade mesal b rade mesal jlo mire
			{	
				if (radeha[i] == rade_mesal[j])
				{
					gp.push_back(ex[j][l]);
				}
			}
			mid[i][l] = miangin(gp);
			var[i][l] = varians(gp);
		}
	}//---------grftn dade haye test va zakhire anha--------------------
	cout << "tedad dade haye test ra vared konid "<<endl;
	int r = 0;
	cin >> r;
	float **test = new float *[r];
	for (int i = 0; i < r; i++)
		test[i] = new float[n];
	cout << "dade haye test ra vared konid " << endl;
	for (int i = 0; i < r; i++)
		for (int j = 0; j < n; j++)
			cin >> test[i][j];
	//---------------sakhtan mitris formol sevvom-----------------------
	float **f3 = new float *[k];
	for (int i = 0; i < k; i++)
		f3[i] = new float[n];
	//--------------------por krdn matris f3 va anjam formool avval va etmam kar ------------------------------
	float * ehtemal = new float[k];
	for (int v = 0; v < r; v++)//baraye har test hesab mishe
	{
		for (int i = 0; i < k; i++)//por krdn f3
		{
			for (int j = 0; j < n; j++)
			{
				float power = tavan(test[v][j], mid[i][j], var[i][j]);
				f3[i][j] = zarib(var[i][j]) * pow(e, power);
			}
		}
		for (int i = 0; i < k; i++)//ehtemal har rade bdst miad
		{
			for (int j = 0; j < n; j++)//pi zarb
				f3[i][0] *= f3[i][j + 1];

			ehtemal[i] = pck[i] * f3[i][0];
		}
		cout << "ehtemal dade test " << r << "om :"<<endl;
		for (int i = 0; i < k; i++)
			cout << "ehtemal " << radeha[i] << " = " << ehtemal[i]<<endl;
	}
	

 return 0;
}

