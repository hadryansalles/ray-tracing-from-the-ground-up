#pragma once

// Matrix is a 4 x 4 square matrix that is used to represent affine transformations
//----------------------------------------- class Matrix
class Matrix {	
public:
	double m[4][4];								// elements

	Matrix();									// default constructor
	Matrix(const Matrix& mat);					// copy constructor
	~Matrix ();									// destructor
	
	Matrix& operator= (const Matrix& rhs); 		// assignment operator
	Matrix operator* (const Matrix& mat) const;	// multiplication of two matrices
	Matrix operator/ (const double d);			// divsion by a double
	void set_identity(void);					// set to the identity matrix
};