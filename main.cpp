#include "main.h"

int main(int argc, char* argv[]){
	HSQUIRRELVM vm;

	vm = sq_open(1024);
	sqstd_seterrorhandlers(vm);
	registerGlobalFunc(vm, getInput, "getInput");
	registerGlobalFunc(vm, pausefunc, "pause");
	registerGlobalFunc(vm, clear, "clear");
	registerGlobalFunc(vm, randInt, "randInt");
	registerGlobalFunc(vm, randFloat, "randFloat");

	sq_setprintfunc(vm, printfunc, printfunc);
	sq_pushroottable(vm);
	bool quit = 0;
	string valid = "";
	string input = "";

	//Get argument
	if(argc >= 2) input = argv[1];

	while(!quit){
		if(input == "quit" || input == "exit") quit = 1;
		else {
			//If the string is not blank
			if(input != ""){
				//Check that the file exists
				if(fileExists(input.c_str())) valid = input;
				else {
					printf("\"%s\" does not exist! Checking for \"%s.nut\"...\n", input.c_str(), input.c_str());
					string inputnut = input;
					inputnut += ".nut";

					if(fileExists(inputnut.c_str())) valid = inputnut;
					else {
						printf("\"%s.nut\" does not exist! Checking for \"%s.sq\"...\n", input.c_str(), input.c_str());
						string inputsq = input;
						inputsq += ".nut";

						if(fileExists(inputsq.c_str())) valid = inputsq;
						else valid = "";
					};
				};

				//If the file is valid, run it
				if(valid.length()){
					clear(0);
					sqstd_dofile(vm, valid.c_str(), 0, 1);
				} else printf("File not found! %s", input.c_str());

				printf("\n\n");
			};

			//Get the next input
			printf("SQ>:");
			getline(cin, input, '\n');
			printf("\n");

			//Reset valid for next check
			valid = "";
		};
	};

	return 0;
};

bool getYN(){
	string input;
	while(true){
		getline(cin, input, '\n');
		//transform(input.begin(), input.end(), input.begin(), tolower);

		if(input == "y" || input == "yes"){
			return true;
		} else if(input == "n" || input == "no"){
			return false;
		} else {
			printf("\nCome again? (Y/N) ");
		};
	};
};

SQInteger pausefunc(HSQUIRRELVM v){
	std::cout << "\n\nPress ENTER to continue...";
	std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );

	return 0;
};

void printfunc(HSQUIRRELVM v, const SQChar *s, ...){
	va_list arglist;
	va_start(arglist, s);
	scvprintf(s, arglist);
	va_end(arglist);
};

void callfunc(HSQUIRRELVM v, int n, float f, const SQChar *s){
	int top = sq_gettop(v); //saves the stack size before the call
	sq_pushroottable(v); //pushes the global table
	sq_pushstring(v,_SC("main"),-1);
	if(SQ_SUCCEEDED(sq_get(v,-2))) { //gets the field 'foo' from the global table
		sq_pushroottable(v); //push the 'this' (in this case is the global table)
		sq_pushinteger(v,n);
		sq_pushfloat(v,f);
		sq_pushstring(v,s,-1);
		sq_call(v,4,0,0); //calls the function
	};
	sq_settop(v,top); //restores the original stack size
};

SQInteger getInput(HSQUIRRELVM v){
	string input;
	getline(cin, input, '\n');
	sq_pushstring(v, input.c_str(), input.length());
	return 1;
};

SQInteger registerGlobalFunc(HSQUIRRELVM v, SQFUNCTION f, const char *fname)
{
	sq_pushroottable(v);
	sq_pushstring(v,fname,-1);
	sq_newclosure(v, f, 0); //create a new function
	sq_newslot(v,-3,SQFalse);
	sq_pop(v,1); //pops the root table

	return 0;
};

SQInteger clear(HSQUIRRELVM v) {
#ifdef ON_WIN
	system("CLS");
#else
	std::cout << "\x1B[2J\x1B[H";
#endif

	return 0;
};

/*void runfile(HSQUIRRELVM v, string* str){
	ofstream file(str->c_str());
	string longname = *str + ".nut";
	ofstream longfile(longname.c_str());
	if(ifstream(file) sqstd_dofile(v, str->c_str(), 0, 1);
	else if(ifstream(longfile)) sqstd_dofile(v, str->c_str(), 0, 1);
	else printf("Unable to find file!");
};*/

bool fileExists(const char* file){
	//Checks if a file exists
	struct stat buff;
	if (stat(file, &buff) != -1) return true;

	return false;
};

//Squirrel bindings
SQInteger randInt(HSQUIRRELVM v){
	SQInteger i;
	sq_getinteger(v, 2, &i);

	SQInteger n = rand();
	n %= i;

	sq_pushinteger(v, n);

	return 1;
};

SQInteger randFloat(HSQUIRRELVM v){
	float f;
	sq_getfloat(v, 2, &f);

	float n = rand();
	while(n > f) n -= f;

	sq_pushinteger(v, n);

	return 1;
};