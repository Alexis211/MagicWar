/*	MagicWar 0.1 alpha
 *	by Alexis211
 *  ----------------------------
 *  	functions.h
 *  	Header file for various functions
 *  	*/
#ifndef DEF_MW_FUNCTIONS
#define DEF_MW_FUNCTIONS

#include <sstream>
#include <string>
#include <vector>

std::string Int2Str(int i);
std::string Float2Str(float f);
float Str2Float(std::string s);
int Str2Int(std::string s);

float deg2rad(float angle);

std::vector<std::string> SplitStr(std::string s, char separator = ' ');

#endif
