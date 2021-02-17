//traj.h

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

#ifndef TRAJ_S
#define TRAJ_S

#include <iostream>
#include <vector>
#include <string>
#include <fstream>


class traj_script{
	public:
		std::vector<int> atoms_pairs;
		std::string traj_file;
		std::string py_name;
		std::string R_name;
		std::ofstream python_script;
		std::ofstream R_script;
		traj_script();
		traj_script(std::string file_name);
		traj_script(std::string file_name, std::vector<int> atoms);
		traj_script( const traj_script& rhs ) =  delete;
		traj_script& operator=( const traj_script& rhs ) =  delete;
		~traj_script();
		void mdtraj_geo();
		void calc_distances(const char* pdb_file);
		void extract_frame(const char* pdb_file, int frames);
		void extract_frames(const char* pdb_file, int interval,int fr_sz);
		int bi_most_probable_point( std::vector<double> v1, std::vector<double> v2 );
		void prune_waters(int radius);
	
};

#endif