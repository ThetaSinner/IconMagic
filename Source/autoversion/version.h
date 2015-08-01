#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "01";
	static const char MONTH[] = "08";
	static const char YEAR[] = "2015";
	static const char UBUNTU_VERSION_STYLE[] =  "15.08";
	
	//Software Status
	static const char STATUS[] =  "Alpha";
	static const char STATUS_SHORT[] =  "a";
	
	//Standard Version Type
	static const long MAJOR  = 0;
	static const long MINOR  = 0;
	static const long BUILD  = 1;
	static const long REVISION  = 9;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT  = 11;
	#define RC_FILEVERSION 0,0,1,9
	#define RC_FILEVERSION_STRING "0, 0, 1, 9\0"
	static const char FULLVERSION_STRING [] = "0.0.1.9";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY  = 1;
	

}
#endif //VERSION_H