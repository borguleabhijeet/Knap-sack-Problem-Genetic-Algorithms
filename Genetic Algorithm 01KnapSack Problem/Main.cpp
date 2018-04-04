#include<iostream>
#include<vector>
#include<fstream>
#include <string>
#include "KnapsackData1.h"
#include <math.h>
#include<time.h>

using namespace std;



//
int main()
{
	
	Knapsackdata * obj;// Create constructor of the class knapscak 
	Initialize init;
	
	obj=new Knapsackdata("TestData(0-1Knapsack).txt");// Read the data from file and split the data into vector 
	obj->TotalWeightCapacity=13743;// Assign the total weight capacity
	obj->populationsize=100;//Population Size
	obj->CrossoverProbablity=0.90;//Set up the cross over probability
	obj->MutationProbablity=0.01;
	int numberofpoint=3;
		cout<<"Reading is done.."<<endl;
	Chromostruct param;
	init.GenerateChromo(*obj,param);// Generate Initial Chromosomes
	init.PopulationSelection(*obj,param);// Select BestPopulation which does not exceed weight limit initiallly.
	int iteration=0;
	cout<<"Please see the output file at the base directory after iteration"<<endl;
	bool Type=0;//"Roulette=0 and Tournament=1;
	ofstream myfile("Output.txt");
//	  myfile << "Population Fitness Weight AVGFitness\n";
	while(iteration<100)
	{
	init.RouletteWheelSelection(*obj,param,Type);// RouletteWheelSelection executes selection procedure type "Roulette=0 and Tournament=1;
	init.CrossOver(*obj,param,numberofpoint);//Peform cross over of two parents and create two offespring it has 3 point cross over;
	init.CheckFitness(*obj,param);// computes the fitness after the crossover;
	init.SaveResults(*obj,param,iteration,myfile);// Stores the results and get the final solution;
	iteration++;
	//cout<<iteration<<endl;
	}
	myfile.close();
	

	return 0;
}
