#ifndef CORE_PERCEPTION_H
#define CORE_PERCEPTION_H

namespace patrick{
    class Perception
    {
    private:
        
    public:
        Perception();
        ~Perception();

        void train(double dataRows[],unsigned int typeColumn[],unsigned int types);//nonnumeric lables should be transfered to int value
        unsigned int classify(double dataRow[]);//return index of type in typeColumn

    };

    class DescriminationFunc
    {
    public:

        DescriminationFunc();
        ~DescriminationFunc();
    };
    
}



#endif