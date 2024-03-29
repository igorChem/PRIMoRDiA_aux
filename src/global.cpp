//global.h
//Declarations for functions and source file with constant values. 

/*********************************************************************/
/* This source code file is part of OOCCuPy++ software project created 
 * by Igor Barden Grillo at Federal University of Paraíba. 
 * barden.igor@gmail.com ( Personal e-mail ) 
 * igor.grillo@acad.pucrs.br ( Academic e-mail )
 * quantum-chem.pro.br ( group site )
 * IgorChem ( Git Hub account )
 */ 

/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */
 
/*********************************************************************/

//Including header from the c++
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include <experimental/filesystem>
#include <stdexcept>
#include <map>

#include "../include/global.h"
//=============================================================================
using std::string;
using std::vector;
using std::move;
using std::map;

using std::cout;
using std::endl;

namespace fs = std::experimental::filesystem;
unsigned int m_NumOfProcess = 1;
//============================================================================================
string atomType[] = {
					 "H",																			      "He",
					 "Li","Be",											  		 "B", "C", "N", "O", "F", "Ne",
					 "Na","Mg",										  			 "Al","Si","P", "S", "Cl","Ar",
					 "K","Ca", "Sc","Ti", "V","Cr","Mn","Fe","Co","Ni","Cu","Zn","Ga","Ge","As","Se","Br","Kr",
					 "Rb","Sr", "Y","Zr","Nb","Mo","Tc","Ru","Rh","Pd","Ag","Cd","In","Sn","Sb","Te", "I","Xe",
					 "Cs","Ba",
								"La","Ce","Pr","Nd","Pm","Sm","Eu","Gd","Tb","Dy","Ho","Er","Tm","Yb","Lu",
								"Hf","Ta","W","Re","Os","Ir","Pt","Au","Hg","Tl","Pb","Bi","Po","At","Rn",
					 "Fr","Ra",
							  "Ac","Th","Pa","U","Np","Pu","Am","Cm","Bh","Bk","Cf","Es","Fm","Md","No","Lr"
					 };
/************************************************************************************************************/
double atomMass[] = {
					1.00794,																				   		 				 			4.0026,
					6.941,9.012182,																	10.811,	12.0107,14.0067,15.9994,18.9984,	20.1797,
					22.9897,24.305,																	26.981,28.0855,30.973762,32.065,35.453,39.948,39.948,
					40.078,44.9559,47.867,50.9415,51.9961,54.938,55.845,58.6934,58.9332,58.693,63.546,65.39,69.723,72.64,74.9216,78.96,79.904,83.8,
					85.467,87.62l,88.9059,91.224,92.9064,95.94,98,101.07,102.9055,106.42,107.8682,112.411,114.818,118.71,121.76,126.9045,127.6,131.293,
					132.9055,137.327,
									138.9055,140.116,140.9077,144.24,145,150.36,151.964,157.25,158.9253,162.5,164.9303,167.259,168.9342,173.04,174.967,
									178.49,180.9479,183.84,186.207,190.23,192.217,195.078,196.9665,200.59,204.3833,207.2,208.9804,209,210,222,
					223,226,
							227,231.0359,232.0381,237,238.0289,243,244,247,247,251,252,257,258,259,261,262
					};	
/************************************************************************************************************/
///////////////////////////////////////////////
// FILE HANDLING UTILITIES :

bool IF_file(const char* name){
	fs::path file_name(name);
	return fs::exists(file_name);
}
/***************************************************************************/
bool IF_file(fs::path& name){
	return fs::exists(name);
}
/***************************************************************************/
bool check_file_ext(string ext				,
					const char* file_name){

	fs::path f_name(file_name);
	//string filename_ext = f_name.extension();
	if ( f_name.extension() == ext ){
		return true;
	}
	else return false;
}
/***************************************************************************/
string get_file_name(const char* path_name){
	fs::path f_name(path_name);
	string resultS( f_name.filename() );
	return resultS;
}
/**************************************************************************/
string remove_extension(const char* file_name){
	string file_name_string  = file_name;
	int point = 0;
	char dot = '.';
	for(unsigned int i = 0;i<file_name_string.size();i++){
		char character = file_name_string[i];
		if ( character == dot){	point = i; }
	}
	int pos = file_name_string.size()-point;
	return file_name_string.substr(0,file_name_string.size()-pos);
}
/***************************************************************************/
string change_extension(const char* file_name,
						string new_ext		){
							
	string name_wth_ext = remove_extension(file_name);
	name_wth_ext += new_ext;
	return name_wth_ext;
}
/***************************************************************************/
void rename_file(const char* file_name,
				string new_file_name){
					
	fs::path f_name(file_name);
	fs::path nf_name( fs::current_path() / new_file_name );
	fs::rename(f_name,nf_name);
}
////////////////////////////////////////////////////////
// VECTOR MATH/STAT MANIPULATION :

double mean_dvec(vector<double>& vec){
	double result = 0.0;
	for(unsigned int i=0;i<vec.size();i++){
		result += vec[i];
	}	
	return result/vec.size();
}
/********************************************************************************/
double max_dvec(vector<double>& vec){
	std::sort( vec.begin(), vec.end() );
	if ( vec.size() > 0) return vec[vec.size()-1];
	else return 0.0;
}
/********************************************************************************/
double min_dvec(vector<double>& vec){
	std::sort( vec.begin(), vec.end() );
	if ( vec.size() > 0) return vec[0];
	else return 0.0;
}
/********************************************************************************/
double sum_dvec(std::vector<double>& vec){
	double result = 0.0;
	for(unsigned int i=0;i<vec.size();i++){
		result += vec[i];
	}	
	return result;
}
/******************************************************************************/
double sd_dvec(vector<double>& vec){
	double mean = mean_dvec(vec);
	double sd = 0;
	for(unsigned int i=0;i<vec.size();i++){
		sd += (vec[i]-mean)*(vec[i]-mean);
	}
	sd/=vec.size();
	sd = sqrt(sd);
	return sd;
}
/******************************************************************************/
vector<double> scale_dvec(vector<double>& vec){
	vector<double> result( vec.size() );
	double mean = mean_dvec(vec);
	for(unsigned int i=0;i<vec.size();i++){
		result[i] = vec[i] - mean;
	}
	double sd = sd_dvec(result);
	for(unsigned int i=0;i<result.size();i++){
		result[i]/=sd;
	}
	return result;
}
/******************************************************************************/
//ATOMIC PROPERTIES GETTERS :
float get_atom_mass(std::string sym){
	int indx = 0;
	for (unsigned int i=0;i<103;i++) {
		if ( sym == atomType[i] ) {
			indx = i;
		}
	}
	return atomMass[indx];
}
/******************************************************************************/
int get_atomic_number(std::string sym){
	int atomic_num;
	for (unsigned int i=0;i<103;i++) if ( sym == atomType[i] ) {
		atomic_num = i+1;
	}
	return atomic_num;
}
/******************************************************************************/
//OTHER HELPER FUNCTIONS :
void clean_dir(){

}
/******************************************************************************/
logFile::logFile()			:
	file_name("no_init.log"){
	data.open( file_name.c_str() );
}
/******************************************************************************/
void logFile::input_line(std::string line){
	data << line << endl;
}
/******************************************************************************/
logFile::logFile(const char* fn):
	file_name(fn)				{
}
/******************************************************************************/
void logFile::open()	{
	data.open(file_name);
}
/******************************************************************************/
logFile::~logFile(){
	data.close();
}
/******************************************************************************/
logFile ut_log("unit_test.log");
logFile test_log("test.log");
////////////////////////////////////////////////////////////////////////////////
