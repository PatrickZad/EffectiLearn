#include"bayes/core/bayes.h"
#include<string>
#include<fstream>
#include<vector>
#include<sstream>
std::vector<std::string> split(std::string& str, char c);
double str2float(std::string& str);
int main(){
    using namespace std;
    //read data, only 2 type
    ifstream iris_istream;
    iris_istream.open("./dataset/iris.data");
    string line;
    getline(iris_istream,line);
    
}

std::vector<std::string> split(std::string& str, char c)
{
    using namespace std;
    ssitream str_is;
    
}
double str2float(std::string& str);
