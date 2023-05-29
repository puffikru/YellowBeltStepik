#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>

using namespace std;

class Matrix
{
public:
    Matrix()
    {
        data.clear();
    }

    Matrix(int num_rows, int num_cols)
    {
        if (num_rows < 0 || num_cols < 0)
        {
            throw out_of_range("rows and cols can't be negative");
        }
        else if (num_rows == 0 || num_cols == 0)
        {
            data.clear();
        }
        else
        {
            data.resize(num_rows);
            for (vector<int>& d : data)
            {
                d.resize(num_cols, 0);
            }
        }
    }

    void Reset(int num_rows, int num_cols)
    {
        if (num_rows < 0 || num_cols < 0)
        {
            throw out_of_range("rows and cols can't be negative");
        }
        else if (num_rows == 0 || num_cols == 0)
        {
            data.clear();
        }
        else
        {
            data.clear();
            data.resize(num_rows);
            for (vector<int>& d : data)
            {
                d.resize(num_cols, 0);
            }
        }

    }

    int At(int num_row, int num_col) const
    {
        if (data.size() == 0 || num_row < 0 || num_row > data.size() - 1 || num_col < 0 || num_col > data[0].size() - 1)
        {
            throw out_of_range("row or col out of range");
        }
        return data[num_row][num_col];
    }

    int& At(int num_row, int num_col)
    {
        if (data.size() == 0 || num_row < 0 || num_row > data.size() - 1 || num_col < 0 || num_col > data[0].size() - 1)
        {
            throw out_of_range("row or col out of range");
        }
        return data[num_row][num_col];
    }

    int GetNumRows() const
    {
        return data.size();
    }

    int GetNumColumns() const
    {
        if (data.size() > 0)
        {
            return data[0].size();
        }
        return 0;
    }


private:
    vector<vector<int>> data;
};

istream& operator>>(istream& is, Matrix& matrix)
{
    int num_rows, num_cols;
    is >> num_rows >> num_cols;
    matrix.Reset(num_rows, num_cols);
    for (int i = 0; i < num_rows; ++i)
    {
        for (int j = 0; j < num_cols; ++j)
        {
            int q;
            is >> q;
            matrix.At(i, j) = q;
        }
    }
    return is;
}

ostream& operator<<(ostream& os, const Matrix& matrix)
{
    int rows = matrix.GetNumRows();
    int cols = matrix.GetNumColumns();
    os << rows << " " << cols << endl;
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            os << matrix.At(i, j) << " ";
        }
        os << endl;
    }
    return os;
}

bool operator==(const Matrix& lhs, const Matrix& rhs)
{
    bool result = false;
    if (lhs.GetNumRows() == rhs.GetNumRows() && lhs.GetNumColumns() == rhs.GetNumColumns())
    {
        if (lhs.GetNumRows() == 0 && lhs.GetNumColumns() == 0)
        {
            result = true;
        }
        else
        {
            for (int i = 0; i < lhs.GetNumRows(); ++i)
            {
                for (int j = 0; j < lhs.GetNumColumns(); ++j)
                {
                    result = lhs.At(i, j) == rhs.At(i, j);
                    if (!result)
                    {
                        return false;
                    }
                }
            }
        }
    }

    return result;
}

Matrix operator+(const Matrix& lhs, const Matrix& rhs)
{
    Matrix matrix;
    if (lhs.GetNumRows() == rhs.GetNumRows() && lhs.GetNumColumns() == rhs.GetNumColumns())
    {
        matrix.Reset(lhs.GetNumRows(), lhs.GetNumColumns());
        for (int i = 0; i < lhs.GetNumRows(); ++i)
        {
            for (int j = 0; j < lhs.GetNumColumns(); ++j)
            {
                matrix.At(i, j) = lhs.At(i, j) + rhs.At(i, j);
            }
        }
    }
    else
    {
        throw invalid_argument("Invalid argument matrix size should be equal");
    }
    return matrix;
}

int main() {
    try
    {
        Matrix one;
        Matrix two;

        cin >> one >> two;
        cout << one + two << endl;
    }
    catch(const out_of_range& e)
    {
        cout << e.what() << '\n';
    }
    
  return 0;
}
