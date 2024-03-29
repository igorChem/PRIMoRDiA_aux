//global.h
//Declarations for functions and source file with constant values. 

/*********************************************************************/
/* This source code file is part of LQQCMMtools software project created 
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

#ifndef GLOBAL_H
#define GLOBAL_H

#include <string>
#include <vector> 
#include <fstream>

#include <experimental/filesystem>
extern unsigned int m_NumOfProcess;
//========================================================
// FILE OPERATIONS
bool IF_file(const char* name); 
bool IF_file(std::experimental::filesystem::path& name); 
bool check_file_ext(std::string ext,const char* file_name);
std::string remove_extension(const char* file_name);
std::string change_extension(const char* file_name,std::string new_ext);
void rename_file(const char* file_name,std::string new_file_name);
std::string get_file_name(const char* path_name);
// VECTOR MATH/STAT OPERATIONS
double mean_dvec(std::vector<double>& vec);
double max_dvec(std::vector<double>& vec);
double min_dvec(std::vector<double>& vec);
double sum_dvec(std::vector<double>& vec);
double sd_dvec(std::vector<double>& vec);
std::vector<double> scale_dvec(std::vector<double>& vec);
//ATOMIC PROPERTIES GETTERS 
float get_atom_mass(std::string sym);
int get_atomic_number(std::string sym);
//OTHER HELPER FUNCTIONS 
void clean_dir();

/****************************************************************/
class logFile{
	public:
		std::ofstream data;
		std::string file_name;
		logFile();
		logFile(const char* fn);
		logFile(const logFile& rhs) = delete;
		logFile& operator=(const logFile& rhs ) = delete;
		void open();
		void input_line( std::string line);
		~logFile();
};
/****************************************************************/
extern logFile ut_log;
extern logFile test_log;
/////////////////////////////////////////////////////////////////
#endif
