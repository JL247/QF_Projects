#ifndef __SIMPLE_MATRIX_H
#define __SIMPLE_MATRIX_H

#include <vector>

template <typename Type = double> class SimpleMatrix {
    private:
        //using a vector of vectors to store the values
        //here we setup a nested vector template to form our matrix "mat" object
        //it essentially creates a group of vectors of "Type" into one large vector to form the matrix
        std::vector<std::vector<Type> > mat;

    public:
        SimpleMatrix();     //Default constructor

        //Constructor we'll use to create the matrix
        SimpleMatrix(const int& rows, const int& cols, const Type& val);

        //Copy constructor
        SimpleMatrix(const SimpleMatrix<Type>& _rhs);

        //Assignment operator overloaded
        SimpleMatrix<Type>& operator= (const SimpleMatrix<Type>& _rhs);

        virtual ~SimpleMatrix();

        //we declare two functions to return the matrix and a specific value
        //The placement of std::vector<std::vector<Type> > and Type& describes the type of value the functions will return
        std::vector<std::vector<Type> > get_mat() const;    //placing std::vector<std::vector<Type> > at the start of the funciton signature
                                                            //means get_mat() returns a matrix of type "Type" when it's actually implemented in
                                                            //the .cpp file
        Type& value(const int& row, const int& col);
};

//#include "simple_matrix.cpp"

#endif