#include <stdio.h>
#include <ctime>
#include <cilk/cilk.h>
#include <cilk/cilk_api.h>
#include <cilk/reducer_opadd.h>
#include <chrono>
#include <iostream>

using namespace std::chrono;
using namespace std;

//#define NUMPOINT 70000000 // количество точек
//#define NUMPOINT 70
//#define PI 3.1415926536
#define PI 2.0
#define A 2.0
double integral(int NUMPOINT)
{
	double step, t, x;
	double* f = new double[NUMPOINT];
	printf("Количество точек = %d\n", NUMPOINT);
	step =A/NUMPOINT; 
	printf("Величина шага = %lf\n", step);
	cilk::reducer_opadd<double> value(0);
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	cilk_for (int i = 0; i<NUMPOINT; i++) 
	{
		f[i] =4/(1+(-1+i*step)*(-1+i*step));
	}
	
	cilk_for(int i = 0; i < NUMPOINT; i++)
	{
		*value += f[i];
	} 
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	//high_resolution_clock::time_point t3 = high_resolution_clock::now();

	duration<double> duration = (t2 - t1);

	
	cout <<"Значение интеграла : "<< value.get_value()*step<<endl;
	cout << "Время выполнения : " << duration.count() << " сек" << endl;
	cout<<endl;
	delete []f;
	return duration.count();
}
void main() {
	__cilkrts_set_param("nworkers", "8");
	
	setlocale(LC_ALL, "Russian");
	cout<< " Число процессов равно 8 "<<endl;
	double time81 = integral(10000000);
	double time82 = integral(80000000);
		
	cout<<endl;
	cout<<"Насколько увеличилось время выполнения программы с увеличением разбиения : "<<time82/time81 << endl;
	cout<<endl;
	double time83 = integral(130000000);
	cout<<"Насколько увеличилось время выполнения программы с увеличением разбиения : "<<time83/time82 << endl;
	
}