#include "iostream"
#include "string"
#include <fstream>
#include <format>

using namespace std;

int main(void){

    string type1, type2, operation;
    string value1, value2;

	cin >> type1 >> value1;
	cin >> type2 >> value2;
	cin >> operation;
    
	cout << "Operation in process: " << type1 << ' ' << operation << ' ' << type2  << endl;

	ofstream fout("function.cpp");
	fout << "#include <iostream>" << endl;
    fout << "using namespace std;" << endl;
	fout << "int f(void) {" << endl;
	fout << format("\t{} var1 = {};", type1, value1) << endl;
	fout << format("\t{} var2 = {};", type2, value2) << endl;
	fout << format("\tcout << var1 {} var2 << endl;", operation) << endl;
	fout << "\treturn 0;" << endl;
	fout << "}" << endl;
	fout.close();
	
	return 0;
}
