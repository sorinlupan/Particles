#include "Matrices.h"


namespace Matrices
{ 
    Matrix::Matrix(int _rows, int _cols) {
        rows = _rows;
        cols = _cols;
        a.resize(rows, vector<double>(cols, 0.0));
    }
    ///************************************
    ///inline accessors / mutators, these are done:

    ///Read element at row i, column j
    ///usage:  double x = a(i,j);
    const double& Matrix::operator()(int i, int j) const
    {
        return a.at(i).at(j);
    }
    ///Assign element at row i, column j
    ///usage:  a(i,j) = x;
    double& Matrix::operator()(int i, int j)
    {
        return a.at(i).at(j);
    }
    int Matrix::getRows() const { return rows; }
    int Matrix::getCols() const { return cols; }

    Matrix operator+(const Matrix& a, const Matrix& b) {
        if (a.getRows() != b.getRows() && a.getCols() != b.getCols()) {
            throw runtime_error("Error: dimensions must agree");
        }
        else {
            Matrix c(a.getRows(), a.getCols());
            for (int i = 0; i < a.getRows(); ++i) {
                for (int j = 0; j < a.getCols(); ++j) {
                    c(i, j) = a(i, j) + b(i, j);
                }
            }
            return c;
        }
    }

    ///Matrix multiply.  See description.
   ///usage:  c = a * b;
    Matrix operator*(const Matrix& a, const Matrix& b) {
        if (a.getCols() != b.getRows()) {
            throw runtime_error("Error: dimensions must agree");
        }
        else {
            Matrix c(a.getRows(), b.getCols());
            for (int i = 0; i < a.getRows(); i++) {
                for (int j = 0; j < b.getCols(); j++) {
                    for (int k = 0; k < a.getCols(); k++) {
                        c(i, j) += a(i, k) * b(k, j);
                    }
                }
            }
            return c;
        }
    }

    ///Matrix comparison.  See description.
   ///usage:  a == b
    bool operator==(const Matrix& a, const Matrix& b) {
        if (a.getRows() != b.getRows() || a.getCols() != b.getCols()) {
            return false;
        }
        for (int i = 0; i < a.getRows(); i++) {
            for (int j = 0; j < a.getCols(); j++) {
                if (abs(a(i, j) - b(i, j)) >= 0.001)
                {
                    return false;
                }
            }
        }
        return true;
    }

    ///Matrix comparison.  See description.
   ///usage:  a != b
    bool operator!=(const Matrix& a, const Matrix& b)
    {
        return !(a == b);
    }

    //Output matrix.
    ///Separate columns by ' ' and rows by '\n'
    ostream& operator<<(ostream& os, const Matrix& a) {
        for (int i = 0; i < a.getRows(); ++i) {
            for (int j = 0; j < a.getCols(); ++j) {
                os << setw(10) << a(i, j) << " ";
            }
            os << '\n';
        }
        return os;
    }

    RotationMatrix::RotationMatrix(double theta) : Matrix(2, 2) {
        (*this)(0, 0) = cos(theta);
        (*this)(0, 1) = -sin(theta);
        (*this)(1, 0) = sin(theta);
        (*this)(1, 1) = cos(theta);
    }
    ScalingMatrix::ScalingMatrix(double scale) : Matrix(2, 2) {
        (*this)(0, 0) = scale;
        (*this)(0, 1) = 0;
        (*this)(1, 0) = 0;
        (*this)(1, 1) = scale;
    }
    TranslationMatrix::TranslationMatrix(double xShift, double yShift, int nCols) : Matrix(2, nCols)
    {
        for (int i = 0; i < nCols; ++i)
        {
            (*this)(0, i) = xShift;
            (*this)(1, i) = yShift;
        }
    }
}