#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <stdexcept>

 

#include "main.h"

using namespace std;

//NF_20221228_VER_CTRL

map<int,string> map_command_id_2_txt = {{100, "ALGC"}, {10, "DECM"},{20, "TEMP"},};


vector<string> err_codes_bin_to_txt = {
 "ERROR_CODE_WRONG_BYTE_SUM    ",
 "ERROR_CODE_CORRECT_BYTE_SUM  ",
 "ERROR_CODE_MISSED_CYCLES     ",
 "ERROR_CODE_INVALID_CYCLES    ",
 "ERROR_CODE_SUCCESS_CYCLES    ",
 "ERROR_CODE_INVALID_DPP_CMD   ",
 "ERROR_CODE_NA_BFFR           ",
 "ERROR_CODE_UNK_ALGO          ",
 "ERROR_CODE_INVALID_SZ        ",

};

vector<string> vrsn_id_bin_to_txt = {
	"MAJOR NUMBER                 ",
	"MINOR NUMBER                 ",
	"YEAR                         ",
	"MONTH                        ",
	"DAY                          ",
	"COMMAND ID                   ",
	"SPARE0                       ",
	"SPARE1                       ",

};

const int cmnd_id_ind = 5;
const int spare0_ind = 6;
const int non_relevant_strings_num = 20;
 
 
static uint32_t align_4_plus(uint32_t addr) {
	uint32_t tmp = addr + 4;
	return tmp - tmp % 4;
}

vector<uint8_t> readFile(const char* filename)
{
    ifstream file(filename, ios::binary);
    
    if(!file) {
      cout << "Cannot open file!" << endl;
      return vector<uint8_t> {0};
    }
    
    return vector<uint8_t>((istreambuf_iterator<char>(file)),
                              istreambuf_iterator<char>());
}


int main(int argc, char** argv) {
	
   if(2 > argc){
   		cout << "Enter file name and path" << endl;
	    return 0;
   }
   vector<uint8_t> v = readFile(argv[1]);	
   vector<string> vrsn_id_printout;
   int skip_bytes = align_4_plus(ALGO_CTRL_MAX_ERROR_CODE);
   
	int i = 0;
	int j = 0;
	
	for(auto it = v.begin(); it!= v.end();it++){
		if(ALGO_CTRL_MAX_ERROR_CODE > i){
			if( 0 == i){
				cout << "ERROR_CODES:" << endl;
			}
			cout << err_codes_bin_to_txt[i] << ": ";
			printf("%d \n",  *it);
			i++;
		}else if( skip_bytes > i) {
			i++;
		}else{
			if( 0 == j){
				vrsn_id_printout.push_back("\nVERSION ID: \n");
			}
			
			if(spare0_ind > j){ //don't print spares
						 
				vrsn_id_printout.push_back(vrsn_id_bin_to_txt[j]);
				vrsn_id_printout.push_back(": ");
				
				if(j == cmnd_id_ind ){
					if( 0 == *it){     //the rest are zeros so stop printing it, and clean the queueu.
						if(0 < vrsn_id_printout.size()-non_relevant_strings_num){
							vrsn_id_printout.resize(vrsn_id_printout.size()-non_relevant_strings_num);
						}
						vrsn_id_printout.resize(v.size()-non_relevant_strings_num);
						break;
					}else{
						vrsn_id_printout.push_back(map_command_id_2_txt[*it]);
					 	vrsn_id_printout.push_back("\n");
					}
				}else{
					char tmp[10];
					sprintf(tmp, "%d \n", *it);
					vrsn_id_printout.push_back(tmp);
				}
			}
					
			j++;
			if(sizeof(DPP_vrsn_id_t) <= j){
				j=0;
				vrsn_id_printout.push_back("\n");
			}
		}
		
	 
	}	
	
	for(auto it = vrsn_id_printout.begin(); it!= vrsn_id_printout.end(); it++){
		cout << *it;
	}	   
 	
	return 0;
}
