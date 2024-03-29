//gamessInput.h

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

#ifndef GAMESS_INPUT_H
#define GAMESS_INPUT_H

#include <vector>
#include <string>
#include <fstream>

class molecule;

/*********************************************************************/
enum GMS_Group{	
	OTHER=0, CTRL, SYS, SCF, BASIS,	DFTB, OPT, PCM,
	GUESS,	DATA, VEC, ELSDEN, GRID, ELSPOT, 	
	NumOfGMSgroups
};
//----------------------------
enum GMS_TheoryLevel { 	
	HF, DFT, DFTB2, DFTB3,
	FMO , P_HF, Semi,MP2,
	NumOfTheory
};
//----------------------------
enum SCF_TYPE { 
	RHF, UHF, ROHF,
	NumOfSCFoptions
};
//----------------------------
enum GMS_Run_Type { 
	InvalidRunType	,
	Energy			,
	GradientRun		,
	HessianRun		,
	OptimizeRun		,
	SadPointRun		,
	IRCRun			,
	SurfaceRun		,
	FMOEnergy		,
	FMOoptimize		,
	FMOdynamics		,
	NumOfRunTypeOptions
};
//----------------------------
enum GMS_Conv_OPT { 
	DIIS  , SOSCF, MIXED ,	
 	NumOfConvOpt
};
//----------------------------		
enum GMS_Conv_OPT2{ 
	None, SHIFT, DAMP, RSTRCT,	
	NumOfConvOpt2
};
//----------------------------
enum GMS_BasisSet {
	smDFTB, smAM1, 
	MINI, STO3G, x321G,
	x631G, x631Gd, x6311Gd,
	x6311Gdp, x6311GdpD,x6311Gdp2D,
	TZV
};
/*********************************************************************/
class GMS_basis{
	public:
		GMS_BasisSet type;
		std::string name;
		unsigned int ngauss;
		unsigned int npfunc;
		unsigned int ndfunc;
		bool ndiffuseS;
		bool ndiffuseP;
		std::string gaussBasis;
		std::string path_to_dftb;
		GMS_basis();
		GMS_basis(GMS_BasisSet bs);
		~GMS_basis();
		GMS_basis(const GMS_basis& rhs);
		GMS_basis& operator=(const GMS_basis& rhs);
		friend std::ostream& operator<<(std::ostream& out, const GMS_basis& obj);
		void print();
};

/*********************************************************************/
class gms_group{
	public:
		GMS_Group group;
		std::vector<std::string> inp_text;
		std::string grpName;
		gms_group();
		gms_group( GMS_Group grp_type );
		~gms_group();
		gms_group(const gms_group& rhs);
		gms_group& operator=(const gms_group& rhs);
		gms_group(gms_group&& rhs) noexcept;
		gms_group& operator=(gms_group&& rhs) noexcept;
		void print();
};
std::ostream& operator<<(std::ostream& out, gms_group& grp);
/*********************************************************************/
class gms_input{
	public:
		//basic data
		unsigned short multi;
		short charge;
		GMS_basis gbasis;
		GMS_Run_Type RunType;
		std::string QM_method;
		std::string dfttyp;
		//control data
		unsigned short nprint;
		unsigned int maxit;
		unsigned int mwords;
		unsigned short npunch;
		unsigned int nsteps;
		GMS_Conv_OPT copt;
		GMS_Conv_OPT2 copt2;
		GMS_TheoryLevel QMlevel;
		SCF_TYPE scftyp;
		std::string solvent;
		std::string guess;
		double opttol;
		double swoff;
		double swdiis;
		double ethrsh;
		double damph;
		std::string alg;
		std::string disp;
		//data to write
		std::vector<gms_group> groups;
		std::ofstream fl_data;		
		
		//constructors and methods
		gms_input();
		~gms_input();
		gms_input(const gms_input& rhs) = delete;
		gms_input& operator=(gms_input& rhs) = delete;
		void init(int chg, unsigned int mpcty, std::string rtype, std::string method, std::string basis);
		bool load_default_options(std::string path_dir);
		void load_molecule_info( molecule& mol );
		GMS_basis init_basis(std::string& bsis_nm);
		void read_input(const char* file_name);
		void restart_input(const char* inp_name, const char* vec_data);
		void write_input(std::string out_name);
		void clear_directory();
		friend std::ostream& operator<<(std::ostream& out, const gms_input& obj);
		void print();
};
/*********************************************************************
class FMO_fragment{
	
};
/*********************************************************************
class FMO_options{
	
};
*/
void UnitTest_gms_basis();
void UnitTest_gms_group();
void UnitTest_gms_input();




#endif