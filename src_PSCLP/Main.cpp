/*
 *		Main.cpp
 *		Created on: 01/12/2017
 *		Author: Fabio Furini
 */




#include "global_functions.h"
#include "global_variables.h"
#include "PSCLP.h"
#include "PSCLP_BEN.h"


int main() {
	char* argv[6];

	//the instance name
	string arg_1 = "..\\PCSLP_INSTANCES\\GRID_PSCLP_n100_m100000_d1_100_f10_100_s5.dat";
	argv[1] = const_cast<char*>(arg_1.data());

	//1 for the compact model 2 for the Branch-and-Benders-cut
	string arg_2 = "2";
	argv[2] = const_cast<char*>(arg_2.data());

	//time limits
	string arg_3 = "600";
	argv[3] = const_cast<char*>(arg_3.data());

	//the radius of coverage
	string arg_4 = "6.25";
	argv[4] = const_cast<char*>(arg_4.data());

	//for the MCLP the Covering Demand and for the PSCLP the Budget
	string arg_5 = "100";
	argv[5] = const_cast<char*>(arg_5.data());

	instance inst;

	inst.input_file = (char*)calloc(1000, sizeof(char));

	////////////////////////////////////////////////////////////////////////////////////////
	/*Param1*/strcpy(inst.input_file, argv[1]);
	/*Param2*/inst.algorithm = atoi(argv[2]);
	/*Param3*/inst.timelimit = atof(argv[3]);
	/*Param4*/inst.RADIUS = atof(argv[4]);
	/*Param5*/inst.COVERING_DEMAND = atof(argv[5]);
	////////////////////////////////////////////////////////////////////////////////////////


	inst.cohordinates_loaded = false;

	cout << "***RADIUS\t" << inst.RADIUS << endl;
	cout << "***BUDGET\t" << inst.COVERING_DEMAND << endl;


	/////////////////////////////////////////////////////////////////////////////////////////
	clock_t time_start = clock();

	READ_NEW_FILE(&inst);

	clock_t time_end = clock();
	double inst_generation_time = (double)(time_end - time_start) / (double)CLOCKS_PER_SEC;

	cout << "\n\nREADING TIME:\t" << inst_generation_time << endl;
	/////////////////////////////////////////////////////////////////////////////////////////


	inst.number_of_CPU = 16;
	cout << "\n***NUMBER OF CPUs\t" << inst.number_of_CPU << endl;


	if (inst.algorithm == 1)
	{
		cout << "\n\n----------->>>>>>COMPACT MODEL\n";

		///////////////////////////
		build_model_CFL(&inst);
		solve_model_CFL(&inst);
		clean_model_CFL(&inst);
		///////////////////////////

	}



	if (inst.algorithm == 2)
	{
		cout << "\n\n----------->>>>>>BRANCH-AND-BENDERS-CUT\n";

		//this bender an advanced  implementation of the bender (it generates cuts using combinatorial algorithms) *** in addition there is the possibility of activating an  initial cut loop

		///////////////////////////
		build_model_CFL_BEN_2(&inst);
		solve_model_CFL_BEN_2(&inst);
		clean_model_CFL_BEN_2(&inst);
		///////////////////////////

	}


	free(inst.input_file);

	free_data(&inst);

	printf("\nDONE!");

	getchar();
	return 1;
}

