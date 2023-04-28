#include <memory>
#include <vector>

using namespace std;

class Matrix
{

public:
    Matrix(long columns, long rows);

    Matrix(vector<double> m, long columns, long rows);

    void Set(long i, long j, double d);

    double Get(long i, long j);

    vector<double> data();

    string print();

private:
    long Index(long i, long j);
    vector<double> data;
    long numberOfColumns;
    long numberOfRows;

};