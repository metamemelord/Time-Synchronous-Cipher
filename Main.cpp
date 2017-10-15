/*
# -*- coding: utf-8 -*-
"""
@author: MetaMemeLord-
"""
*/

#include<iostream>
#include<string>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<vector>

using namespace std;

int* binaryConv(int num)
{
	int binNum[8] = {0};
	int counter = 8;
	while(counter>0)
	{
		counter--;
		binNum[counter] = num%2;
		num= num/2;
	}
	return binNum;
}

int* XORonArray(int *a,int *b)
{
	int result[8];
	for(int i=0;i<8;i++)
		result[i] = (*(a+i))^(*(b+i));
	return result;
}

int intConv(int *a)
{
	int counter=7;
	int val=0;
	for(int i=7;i>=0;i--)
		val += *(a+i) * pow(2,7-i);
	return val;
}

int main()
{
	cout<<endl<<"Enter string to encrypt: ";
	char password[32];
	gets(password);
#ifdef __TIME__
	string time;
	time = (string)__TIME__;
	cout<<endl<<"String encrypted at "<<time<<"  : ";
	char hh[]="00",mm[]="00",ss[]="00";
	hh[0]= time[0];
	hh[1]= time[1];
	mm[0]= time[3];
	mm[1]= time[4];
	ss[0]= time[6];
	ss[1]= time[7];
	int hours,minutes,seconds,determinant;
	hours = atoi(hh);
	minutes = atoi(mm);
	seconds = atoi(ss);
	determinant = hours+seconds;
	vector< vector<int> > cipherMatrix(3, vector<int> (3,0));
	hours=24-hours;
	seconds=60-seconds;
	cipherMatrix[0][0]=(-1)*hours/10;
	cipherMatrix[0][1]=(-1)*hours%10;
	cipherMatrix[0][2]= (-1)*(cipherMatrix[0][0] + cipherMatrix[0][1]);
	cipherMatrix[1][0]=minutes/10;
	cipherMatrix[1][1]=minutes%10;
	cipherMatrix[1][2]= cipherMatrix[0][2] - 1;
	cipherMatrix[2][0]=seconds/10;
	cipherMatrix[2][1]=seconds%10;
	cipherMatrix[2][2]= cipherMatrix[0][2] - 2;

#endif
//	cout<<endl<<"Matrix based on ASCII thus formed: "<<endl<<endl;
	int o=0,cols,length = strlen(password),appLength;
	switch(length%4){
		case 0: appLength=length;
		break;
		case 1: appLength=length+3;
		break;
		case 2: appLength=length+2;
		break;
		case 3: appLength=length+1;
		break;
	}
	#ifndef appPass
	#define LENGTH appLength
	#endif
	char appPass[LENGTH], cipherPass[LENGTH];
	strcpy(appPass,password);
	for(int o=length;o<appLength;o++)
		appPass[o] = '\n';
	vector< vector<int*> > matrixVar(4, vector<int*> (LENGTH/5));
	vector< vector<int*> > cipheredVar(4, vector<int*> (LENGTH/5));
	int *DETERMINANT = binaryConv(determinant);
	int *HOURS = binaryConv(hours);
	int *MINUTES = binaryConv(minutes);
	int *SECONDS = binaryConv(seconds);
	for(int p=0,t_val;p<LENGTH;p++)
	{	t_val = p%4;
		switch(t_val){
			case 0: matrixVar[0][p/4] = binaryConv(int(appPass[p]));
					break;
			case 1: matrixVar[1][p/4] = binaryConv(int(appPass[p]));
					break;
			case 2: matrixVar[2][p/4] = binaryConv(int(appPass[p]));
					break;
			case 3: matrixVar[3][p/4] = binaryConv(int(appPass[p]));
					break;
		}
	}
		for(int p=0,t_val;p<LENGTH;p++)
	{	t_val = p%4;
		switch(t_val){
			case 0: cipheredVar[0][p/4] = XORonArray(matrixVar[0][p/4],DETERMINANT);
					break;
			case 1: cipheredVar[1][p/4] = XORonArray(matrixVar[1][p/4],DETERMINANT);
					break;
			case 2: cipheredVar[2][p/4] = XORonArray(matrixVar[2][p/4],DETERMINANT);
					break;
			case 3: cipheredVar[3][p/4] = XORonArray(matrixVar[3][p/4],DETERMINANT);
					break;
		}
	}
	if(length%3==0)
		cols=length/3;
	else
		cols=(length/3)+1;
	vector< vector<int> > passwordMatrix(3, vector<int> (cols,0));
	for(int n=0;n<3;n++)
		for(int m=0;m<cols;m++)
		{
			if(o<length)
			{
				passwordMatrix[n][m]=(int)password[o];
				o++;
			}
			else
				passwordMatrix[n][m]=0;
		}
/*
		for(int i=0;i<3;i++)
		{
			for(int j=0;j<cols;j++)
				cout<<passwordMatrix[i][j]<<"\t";
			cout<<endl;
		}
cout<<endl;
*/
/*
	cout<<"Based on the time, i.e "<<time<<" the cipher matrix formed is :"<<endl<<endl;
	for(int i=0;i<3;i++)
		{
			for(int j=0;j<3;j++)
				cout<<cipherMatrix[i][j]<<"\t";
			cout<<endl;
		}
*/
//Matrix multiplication
		vector< vector<int> > cipheredMatrix(3, vector<int> (cols,0));
		int q=0,p=0;
		for(p=0;p<3;p++)
				for(q=0;q<cols;q++)
					cipheredMatrix[p][q] = 0;
		for(p=0;p<3;p++)
			for(q=0;q<cols;q++)
				for(int r=0;r<3;r++)
					cipheredMatrix[p][q] = cipheredMatrix[p][q] + cipherMatrix[p][r] * passwordMatrix[r][q];



			for(int i=0;i<3;i++)
		{
			for(int j=0;j<cols;j++)
				cout<<(char)cipheredMatrix[i][j];
		}

return 0;
}

