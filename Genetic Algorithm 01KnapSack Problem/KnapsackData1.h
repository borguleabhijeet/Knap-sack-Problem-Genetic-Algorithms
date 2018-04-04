#pragma once
#ifndef KNAPSACKDATA1_H
#define KNAPSACKDATA1_H
#include<string>
#include<time.h>

using namespace std;
 typedef struct 
 {
	vector<vector<bool>>Population;
	vector<vector<double>>FitnessValues;
	double totalprofit;
	double totalweight;
	vector<vector<double>>FitnessProbValues;
	vector<vector<bool>>Populationforcrossover;
		 vector<vector<bool>>CrossMutatePopulation;
vector<int>FinalSolution;

}Chromostruct;

 class Knapsackdata
{public:
	Knapsackdata(string fname);
		~Knapsackdata();
		vector<int>item;
		vector<int>weight;
		vector<int>profit;
	   int TotalWeightCapacity;
	   int populationsize;
	   double CrossoverProbablity;
	   double MutationProbablity;	
	
};
 class Initialize
{
	public:	
	vector<double>FitnessFunction(vector<int>Weight,vector<int>Profit,vector<bool>type);	
	void PopulationSelection(Knapsackdata & data, Chromostruct & val);
	void GenerateChromo(Knapsackdata & data, Chromostruct & val);
	void RouletteWheelSelection(Knapsackdata & data, Chromostruct & val,bool type);
	void CrossOver(Knapsackdata & data, Chromostruct & val,int NumofPoint);
	void CheckFitness(Knapsackdata & data, Chromostruct & val);
	void SaveResults(Knapsackdata & data, Chromostruct & val,int iter, ofstream & myfile);
};
void Initialize::SaveResults(Knapsackdata & data, Chromostruct & val,int iter, ofstream & myfile)
{
	int sum=0;
	 if (myfile.is_open())// open the text file and save the data
  {		double tmp;
		tmp=0;
		int indx;
	for(int w=0;w<val.FinalSolution.size();w++)
	{
		cout<<"Total Fitness:    "<<val.FitnessValues[val.FinalSolution[w]][0]<<"    Weight:    "<<val.FitnessValues[val.FinalSolution[w]][1]<<endl;
		sum=sum+val.FitnessValues[val.FinalSolution[w]][0];
		if(val.FitnessValues[val.FinalSolution[w]][0]>tmp)
		{
			tmp=val.FitnessValues[val.FinalSolution[w]][0];
			indx=w;
		}
	}

	if (val.FinalSolution.size()>1)
	{
		myfile<<iter<<" "<<val.FitnessValues[val.FinalSolution[indx]][0]<<" "<<val.FitnessValues[val.FinalSolution[indx]][1]<<" "<<sum/val.FinalSolution.size()<<"\n";
		cout<<iter<<"  Max Fitness:"<<val.FitnessValues[val.FinalSolution[indx]][0]<<endl;
	}
	val.FinalSolution.clear();
	}
}
void  Initialize::CheckFitness(Knapsackdata & data, Chromostruct & val)
{
	int cnt=0;
	vector<vector<double>>OLDFitnessValues=	val.FitnessValues;
		vector<vector<bool>>OLDPopulation=val.Population;
		val.FitnessValues.clear();
	for(int i=0;i<val.CrossMutatePopulation.size();i++)
	{
		vector<vector<double>>newfitenss;
		val.FitnessValues.push_back(FitnessFunction(data.weight,data.profit,val.CrossMutatePopulation[i]));		
	}
	
		for(int i=0;i<val.FitnessValues.size();i++)
		{
			if((int)val.FitnessValues[i][1]<=data.TotalWeightCapacity)// check weight capacity of the population
			{
				if(val.FitnessValues[i][0]>=OLDFitnessValues[i][0])
				{
					if((int)val.FitnessValues[i][1]>data.TotalWeightCapacity)
						continue;					
							val.Population[i]=val.CrossMutatePopulation[i];		// if fitness is greater than old one then add up to next generation
							val.FinalSolution.push_back(i);
				}
		}
			else if((int)val.FitnessValues[i][1]<=data.TotalWeightCapacity)
			{
			val.FitnessValues[i]=OLDFitnessValues[i];
				val.Population[i]=OLDPopulation[i];			
			}else if((int)val.FitnessValues[i][1]>data.TotalWeightCapacity)
			{
				val.FitnessValues[i][0]=0;//In addittion if Chromosomes exceeds weight limit capacity
			}
		}

	double profittotal=0,weighttotal=0;
	for(int i=0;i<val.FitnessValues.size();i++)
	{
		  profittotal+=val.FitnessValues[i][0];	// compute total fitness for the next iteration	
	}

		val.totalprofit=profittotal;
	



}
void Initialize::CrossOver(Knapsackdata & data, Chromostruct & val, int NumofPoint)
{
	 vector<vector<bool>>Crossed;
	
	
	val.CrossMutatePopulation.clear();
	for(int i=0;i<val.Populationforcrossover.size();i=i+2)
	{

		for(int j=i;j<i+2;j++)
					Crossed.push_back(val.Populationforcrossover[j]);

				 vector<bool>offspring1,offspring2;
		

				double x= (((double) rand() / (RAND_MAX)));// Random from 0-1 check with crossover probaliity

					if(x<=data.MutationProbablity)// do mutation if probability falls from 0.001
					{
									int pos=rand() % (Crossed[0].size());									
								 	Crossed[0][pos]=~Crossed[0][pos];
									Crossed[1][pos]=~Crossed[1][pos];		
					}
					else if (x<=data.CrossoverProbablity && x>=data.MutationProbablity)//Do. 3 point cross over if prob grateer than 0.90
					{
						int m=Crossed[0].size()/(NumofPoint+1);// divided the chromosomes
							double Pm= (((double) rand() / (RAND_MAX)));
							for(int p=0;p<Crossed[0].size();p++)
							{
								if (p<m)
								{
									offspring1.push_back(Crossed[0][p]);
									offspring2.push_back(Crossed[1][p]);
								}
								else if(p>=m && p<m*2)
								{
									offspring1.push_back(Crossed[1][p]);
									offspring2.push_back(Crossed[0][p]);
								}else if(p>=m*2 && p<m*3)
								{
										offspring1.push_back(Crossed[0][p]);
									offspring2.push_back(Crossed[1][p]);
								}else if(p>=m*3  && p<=Crossed[0].size())
								{
									offspring1.push_back(Crossed[1][p]);
									offspring2.push_back(Crossed[0][p]);
								}
							}
												
						Crossed[0]=offspring1;
						Crossed[1]=offspring2;
					}
					
				
					val.CrossMutatePopulation.push_back(Crossed[0]);
					val.CrossMutatePopulation.push_back(Crossed[1]);
	}
	

}
void Initialize::RouletteWheelSelection(Knapsackdata & data, Chromostruct & val,bool type)
{
	
	val.Populationforcrossover.clear();

	val.FitnessProbValues=val.FitnessValues;

	for(int i=0;i<val.FitnessValues.size();i++)
	{
		val.FitnessProbValues[i][0]=(val.FitnessValues[i][0]/(double)val.totalprofit);
	}

	vector<double>CumlativeValues;
	CumlativeValues.assign(val.FitnessProbValues.size(), 0);

	double check=0;
	CumlativeValues[0]=val.FitnessProbValues[0][0];

	for(int i=1;i<val.FitnessProbValues.size();i++)
	 	CumlativeValues[i]=CumlativeValues[i-1]	+(val.FitnessProbValues[i][0]);	// scale the probability in wheel

	if (type==0)
	{
		for(int N=0;N<val.FitnessProbValues.size();N++)
		{
	
			double x= (((double) rand() / (RAND_MAX)));
			int k=0;
			while(k<val.FitnessProbValues.size() && x>=CumlativeValues[k])// Roulette Wheel Selection 
			{
				k++;
			}
			
			val.Populationforcrossover.push_back(val.Population[k]);// get the population from the roulett wheel selection

		}
	}else// pair wise tournament selection
	{
		 int pos=0;
		for(int m=0;m<val.FitnessProbValues.size();m++)
		{
				  pos=rand() % (val.FitnessProbValues.size());			
				if (val.FitnessValues[m][0]>val.FitnessValues[pos][0])// Pair wise tournament check for the best
				{
					val.Populationforcrossover.push_back(val.Population[m]);
				}else
				{
					val.Populationforcrossover.push_back(val.Population[m]);
				}

		}
	
	}

}
void Initialize::PopulationSelection(Knapsackdata & data,Chromostruct & val)// Population fiteness computation
{
	val.FitnessValues.clear();

	for(int i=0;i<data.populationsize;i++)
	{
		val.FitnessValues.push_back(FitnessFunction(data.weight,data.profit,val.Population[i]));
	}
	
	long double profittotal=0,weighttotal=0;
	for(int i=0;i<val.FitnessValues.size();i++)
	{
		  profittotal+=val.FitnessValues[i][0];
		  	  weighttotal+=val.FitnessValues[i][1];
	}

	val.totalprofit=profittotal;// total sum of profit of only rendomly selected item
	val.totalweight=weighttotal;// total sum of weight ......"...........
}

void Initialize::GenerateChromo(Knapsackdata & data, Chromostruct & val)// generate the chromosomes 
{
	val.Population.clear();
	val.Population.reserve(data.populationsize);
	 srand ( time(NULL) );

	for(int i=0;i<data.populationsize;i++)
	{
		vector<bool>rnd;
		for (int j=0;j<(data.item.size());j++)
			rnd.push_back(rand()%2);// Generate random bianary values 0 or 1
			
		val.Population.push_back(rnd);// stores the chromosomes 
		
	}

}

vector<double> Initialize::FitnessFunction(vector<int>Weight,vector<int>Profit,vector<bool>type)// Fitness calculations
{
vector<double>values(2);
	for(int i=0;i<Profit.size();i++)
	{
		values[0]=values[0]+Profit[i]*type[i];   
		values[1]=values[1]+Weight[i]*type[i];//summation of selected weight and profit
	}


	return values;
}


Knapsackdata::Knapsackdata(string fname)// read file data ans stores into vector. Data contains profit and weight
{

	cout<<"Reading Data..."<<endl;
	
		string buf;//
	ifstream fp( fname,std::ios_base::in );// read the data from txt file
	 string val; 
	 int cnt=0;
		  while(!fp.eof())	
	  {
		  
		     getline(fp,val);// read each string in txt file checking CR+LF
			 // cout<<val<<endl;
		
			   cnt++;
			  if (cnt<6)// Ignore some beginning text from file 
			  continue;
			  	
			  std::string delimiter = "	";
			size_t pos =0;
			double token;
			  	vector<double>element;		

			while ((pos = val.find(delimiter)) != std::string::npos) // split the string values into 3 vector item/profit/weight
			{				
				element.push_back(atof( val.substr(0, pos).c_str()));
			
				val.erase(0, pos + delimiter.length());
			}	
				element.push_back(atof( val.c_str()));

				item.push_back(element[0]);
				weight.push_back(element[1]);
				profit.push_back(element[2]);
		
				element.clear();
		  }
		
}


#endif KNAPSACKDATA1_H





