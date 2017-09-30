// Program made by Juan Pablo Bernal.
// This program will model a series of posible termocuples designs ad find the radious where the time to get
//the real temperature is less than 5s.
#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
#define pi 3.141592
// function prototype 
double rate_of_change(double h,double a,double T1,double T2,double m,double c);

int main (void){
	double time_step, T3,T4,T1,T2,h,c,p,a,vol,m,r,change,time;
	ofstream outfile;
	outfile.open("result2.txt");
	 //get values from teh euser 
	cout<< "Enter the initial temperature of thermocouple junction (sphere)(C°)--->";
	cin >>T3;
    cout<< "\nEnter the Liquid temperature --->";
	cin >>T4;	
	cout<< "\nEnter heat transfer coeficient (W/m^2C)--->";
	cin >>h;
	cout<< "\nEnter sphere dencity (kg/m^3)--->";
	cin >>p;
	cout<< "\nEnter sphere specific heat (J/kgC) --->";
	cin >>c;
	cout<< "\nEnter sphere radious (m)--->";
	cin >>r;
	cout<< "\nEnter desired time step for temperature history (s)--->";
	cin >>time_step;		
	outfile<< "Enter the initial temperature of thermocouple junction (sphere)(C°)--->"<<T1;
	outfile<< "\nEnter the Liquid temperature --->"<< T2;
	outfile<< "\nEnter heat transfer coeficient (W/m^2C)--->"<<h;
	outfile<< "\nEnter sphere dencity (kg/m^3)--->"<<p;
	outfile<< "\nEnter sphere specific heat (J/kgC) --->"<<c;
	outfile<< "\nEnter sphere radious (m)--->"<<r;
    outfile<< "\nEnter desired time step for temperature history (s)--->"<<time_step;

	//compute volume sureface area and mass 
	vol = 4.0/3.0*pi*pow(r,3);
	m = vol *p;
	a = 4*pi*pow(r,2);
      outfile<< "\nTime (s)     Radius(m)"<<endl;
    time=0;
    //calculate the change in temperature and print radius and the time 
	while (time <= 5 ){
		time=0;
		T1=T3;
		T2=T4;	 

	do{
		change = rate_of_change( h, a, T1, T2, m, c)*time_step;
		T1 += change;
		time += time_step;
	}while (T1 > T2+0.1 || T1 < T2-0.1);	
	outfile<< time <<"         "<<r<<endl;
    r+=0.0001;
    vol = 4.0/3.0*pi*pow(r,3);
	m = vol *p;
	a = 4*pi*pow(r,2);
}
//give the final answer to the user 
if (time >5 ){
	r-=0.0001*2;
	outfile<< "the bigest radious with this material is "<<r<<" m "<<endl;
}else {
		r-=0.0001;
		outfile<< "the bigest radious with this material is "<<r<<" m "<<endl;
}

}
// function that calculates the rate of change in temperature 
double rate_of_change(double h,double a,double T1,double T2,double m,double c)
{
    return (h*a*(T2-T1))/(m*c);
}
