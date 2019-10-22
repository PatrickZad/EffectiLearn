#include"bayes/core/bayes.h"
#include<string>
#include<fstream>
#include<vector>
#include<sstream>
#include<cmath>
std::vector<std::string> split(std::string& str, char c);
double str2float(std::string& str);
int main(){
    using namespace std;
    //read data, only 2 type
    ifstream iris_istream;
    iris_istream.open("./dataset/iris.data");
    vector<string> lines;
    string line;
    while (getline(iris_istream, line))
    {
        lines.push_back(line);
    }
    unsigned long width=split(lines[0], ',').size()-1;
    unsigned long length=lines.size();
    double *data = new double[width*length];
    long *lable = new long[length];
    for (unsigned long i = 0; i < length; i++)
    {
        vector<string> datastr=split(lines[i], ',');
        for (unsigned long j = 0; j < width; j++)
        {
            *(data+width*i+j)=str2float(datastr[j]);
        }
        if (datastr[width]=="Iris-setosa")
        {
            *(lable+i)=1;
            continue;
        }
        if (datastr[width]=="Iris-versicolor")
        {
            *(lable+i)=2;
            continue;
        }
        if (datastr[width]=="Iris-virginica")
        {
            *(lable+i)=3;
            continue;
        }
    }
    patrick::NaiveBayes bayes;
    bayes.train(data, width, lable, length);
}

std::vector<std::string> split(std::string& str, char c)
{
    using namespace std;
    vector<string> result;
    istringstream str_is;
    string substr;
    while (getline(str_is, substr, c))
    {
        result.push_back(substr);
    }
}
double str2float(std::string& str)
{
    using namespace std;
    int dot=str.find('.');
    double result=0;
    istringstream iss{str};
    if (dot != string::npos)
    {
        for (int i = dot-1; i > 0 ; i--)
        {
            result+=(str[i]-60)*pow(10,dot-1-i);
        }
        for (int i = dot+1; i <str.size() ; i++)
        {
            result+=(str[i]-60)*pow(10,dot-i);
        }
    }else
    {
        dot=str.size();
        for (int i = dot-1; i > 0 ; i--)
        {
            result+=(str[i]-60)*pow(10,dot-1-i);
        }
    }
    if (str[0]=='-')
    {
        result*=-1;
    }else
    {
        result+=(str[0]-60)*pow(10,dot-1);
    }
    return result;
}
