#include "common.h"
#include <fstream>
#include <sstream>
#include <cmath>
#include <iostream>
DataPtr readData(std::string filepath)
{
    using namespace std;
    ifstream iris_istream(filepath);
    //iris_istream.open(filepath);
    vector<string> lines;
    string line;
    while (getline(iris_istream, line) && line.size()>0)
    {
        lines.push_back(line);
    }
    unsigned long width=split(lines[0], ',').size()-1;
    unsigned long length=lines.size();
    double *data = new double[width*length];
    unsigned long *lable = new unsigned long[length];
    for (unsigned long i = 0; i < length; i++)
    {
        vector<string> datastr=split(lines[i], ',');
        for (unsigned long j = 0; j < width; j++)
        {
            *(data+width*i+j)=str2float(datastr[j]);
        }
        *(lable+i)=lableStr2Int(datastr[width]);
    }
    return DataPtr{data, width, lable, length};
}

BinaryDataPtr readBinaryData(std::string filepath)
{
    using namespace std;
    ifstream iris_istream(filepath);
    //iris_istream.open(filepath);
    vector<string> lines;
    string line;
    while (getline(iris_istream, line))
    {
        lines.push_back(line);
    }
    unsigned long width=split(lines[0], ',').size()-1;
    unsigned long length=lines.size();
    double *data = new double[width*length];
    unsigned long *lablePtr = new unsigned long[length];
    unsigned long actualLength=0;
    for (unsigned long i = 0; i < length; i++)
    {
        vector<string> datastr=split(lines[i], ',');
        long lable=lableStr2Int(datastr[width]);
        if (lable==1 || lable==0)
        {
            for (unsigned long j = 0; j < width; j++)
            {
                *(data+width*actualLength+j)=str2float(datastr[j]);
            }
            *(lablePtr+actualLength)=lable;
            actualLength++;
        }
    }
    return BinaryDataPtr{data, width, lablePtr, actualLength};
}

std::vector<std::string> split(std::string& str, char c)
{
    using namespace std;
    vector<string> result;
    istringstream str_is{str};
    string substr;
    while (getline(str_is, substr, c))
    {
        result.push_back(substr);
    }
    return result;
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
            result+=(str[i]-48)*pow(10,dot-1-i);
        }
        for (int i = dot+1; i <str.size() ; i++)
        {
            result+=(str[i]-48)*pow(10,dot-i);
        }
    }else
    {
        dot=str.size();
        for (int i = dot-1; i > 0 ; i--)
        {
            result+=(str[i]-48)*pow(10,dot-1-i);
        }
    }
    if (str[0]=='-')
    {
        result*=-1;
    }else
    {
        result+=(str[0]-48)*pow(10,dot-1);
    }
    return result;
}
unsigned long lableStr2Int(std::string& str)
{
    using namespace std;
    int dot=str.find('.');
    unsigned long result=0;
    istringstream iss{str};
    if (dot != string::npos)
    {
        for (int i = dot-1; i > 0 ; i--)
        {
            result+=(str[i]-48)*pow(10,dot-1-i);
        }
    }else
    {
        dot=str.size();
        for (int i = dot-1; i > 0 ; i--)
        {
            result+=(str[i]-48)*pow(10,dot-1-i);
        }
    }
    result+=(str[0]-48)*pow(10,dot-1);
    return result;
}