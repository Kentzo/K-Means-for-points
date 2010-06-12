// line.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "line.h"
#include "time.h"
//#include "stdio.h"
//#include "conio.h"
#include "math.h"
#include "stdlib.h"
#include <algorithm>

class random{
private:
	unsigned long a,b,c,x,m;
public:
	unsigned long get();
	random(void);
	~random(void);
}rnd;
random::random(void){
	a = 14642; //11^4+1
	b = 16807; //7^5
	c = 15625; //5^6
	x = time(0); //any
	m = 32768; //2^15
}
unsigned long random::get(){
	/*__asm{
		mov eax,a
		mov ebx,b
		mul ebx
		mul ebx
		mov edx,eax
		mov eax,b
		mul ebx
		add edx,eax
		add edx,c
		mov eax,edx
		mod m
		mov x,eax
	}*/
	x = (a*x*x + b*x + c)%m;
	return x;
}
random::~random(void){
}
unsigned long geo(double b){
	b -= floor(b);
	double p = 1-b,
		s = b,
		u = (double)rnd.get()/32768;
	unsigned long x = 0;
	while(u>s){
		x++;
		b *= p;
		s += b;
	};
	return x;
}
double x2geo(unsigned long *x, int n, double b){
	b -= floor(b);
	double s = 0;
	std::sort(x,x+n);
	unsigned long f=x[0],
		t=0;
	for(int i=0;i<n;i++)
		if(f==x[i])t++;
		else{
			s += t*t/(b*pow(1-b,(double)f));
			t = 1;
			f = x[i];
		}
	s += t*t/(b*pow(1-b,(double)f));
	s = s/n - n;
	return s;
}
unsigned long discrete(){
	/*
		|  0  |  1  |  5  |  7  |  9  |
		| 0.1 | 0.2 | 0.5 | 0.1 | 0.1 |
	*/
	unsigned long x[] = {0,1,5,7,9};
	double p[] = {0.1,0.2,0.5,0.1,0.1};
	double s = p[0],
		u = (double)rnd.get()/32768;
	unsigned long i = 0;
	while(u>s){
		s += p[++i];
	};
	return x[i];
}
double x2discrete(unsigned long *x, int n){
	unsigned long x0[] = {0,1,5,7,9};
	double p[] = {0.1,0.2,0.5,0.1,0.1};
	double s = 0;
	std::sort(x,x+n);
	unsigned long f=x[0],
		t=0;
	for(int i=0;i<n;i++)
		if(f==x[i])t++;
		else{
			int k=0;
			for(;k<5;k++)if(f==x0[k])break;
			s += t*t/p[k];
			t = 1;
			f = x[i];
		}
		int k=0;
		for(;k<5;k++)if(f==x0[k])break;
		s += t*t/p[k];
	s = s/n - n;
	return s;
}
double normal(){
	double x=0,n=5;
	for(int i=0;i<n;i++)x+=(double)rnd.get()/32768;
	x = sqrt(12.0/n)*(x-(double)n/2);
	return x-(3*x-pow(x,3.0)/100);
}
double gamma(double l,double a){
	if(a<0 || a>1)return 0;
	double S1,S2;
	do{
		S1 = pow((double)rnd.get()/32768,1.0/a);
		S2 = pow((double)rnd.get()/32768,1.0/(1-a));
	}while(S1+S2>1);
	return -(double)(S1*log((double)rnd.get()/32768))/(l*(S1+S2));
}