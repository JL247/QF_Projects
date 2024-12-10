#ifndef __SIMPLE_MATRIX_CPP
#define __SIMPLE_MATRIX_CPP

#include "SimpleMatrix.h"

//default constructor
template <typename Type> SimpleMatrix<Type>::SimpleMatrix() {}

template <typename Type> SimpleMatrix<Type>::SimpleMatrix( const int& rows, 
                                                           const int& cols,
                                                           const Type& val){
    for (int i=0; i<rows; i++){
        std::vector<Type> col_vec (cols, val);
        mat.push_back(col_vec);
     }
}

//implement the copy method
template <typename Type> SimpleMatrix<Type>::SimpleMatrix(const SimpleMatrix<Type>& _rhs){
    mat = _rhs.get_mat();
}

//implement the overriden assignment operator
// - template <typename Type>, means the function is a template
// - SimpleMatrix<Type>&, describes the return type, in this
//   case it's a REFERENCE (hence &) to another SimpleMatrix object
// - SimpleMatrix<Type>::, this scopes to the operator function in the SimpleMatrix class so that we can implement it
// - operator = (const SimpleMatrix<Type>& _rhs), tells us the object's "=" operator accepts a const reference to another
//   SimpleMatrix object that we're gonna call "_rhs"
template <typename Type> SimpleMatrix<Type>& SimpleMatrix<Type>::operator= (const SimpleMatrix<Type>& _rhs){
    //when we try to assign one object to another, we check if the current obejct
    //"this" is the same as the other object "rhs" then just return the curretn
    //object because there's no point wasting resource on copying the same thing
    if(this == &_rhs){
        return *this;
    }

    //otherwise assign the matrix to the public member "mat"
    mat = _rhs.get_mat();
    return *this;
}

//Destructor
template <typename Type> SimpleMatrix<Type>::~SimpleMatrix(){}

//matrix access
// - template <typename Type>, declares this is a template function
// - std::vector<std::vector<Type> >, is a nested vector template, it describes a vector of vectors filled
//   with entries of type "Type"
template <typename Type> std::vector<std::vector<Type> > SimpleMatrix<Type>::get_mat() const{
    return mat;
}


//matrix elemtent access
template <typename Type> Type& SimpleMatrix<Type>::value(const int& row, const int& col){
    return mat[row][col];
}


#endif