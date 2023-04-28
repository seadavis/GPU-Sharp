#include "Matrix.h"
#include <string>

Matrix::Matrix(long numberOfRows, long numberOfColumns)
{
    this->numberOfColumns = numberOfColumns;
    this->numberOfRows = numberOfRows;
    data = vector<double>(numberOfColumns * numberOfRows);
}

Matrix::Matrix(vector<double> m, long columns, long rows)
{
    this->data = m;
    this->numberOfColumns = columns;
    this->numberOfRows = rows;
}

void Matrix::Set(long i, long j, double d)
{
    data[Index(i, j)] = d;
}

double Matrix::Get(long i, long j)
{
    return data[Index(i, j)];
}

vector<double> Matrix::data()
{
    return data;
}

string Matrix::print()
{
    string total;
    for (int i = 0; i < numberOfRows; i++)
    {
        string column = "";
        for (int j = 0; j < numberOfColumns - 1; j++)
        {
            column = column + to_string(Get(i, j)) + ", ";
        }
        column = column + "\n";

        total = total + column;
    }
    return total;
}

long Matrix::Index(long i, long j)
{
    return j * numberOfRows + i;
}