#ifndef DATA_PATH_H
#define DATA_PATH_H

#include <vector>

class DataPath {
public:
    DataPath(int bitSize);
    void update(int ALU_op, bool ldA, bool shiftA, bool clrA, bool ldQ, bool shiftQ, bool clrQ, bool ldM, bool clrM);
    void setInput(int Q_in, int M_in);
    bool checkZero();
    int getResult() const;

    std::vector<int> A;
    std::vector<int> Q;
    std::vector<int> M;
    std::vector<int> ALU_OUT;
    int Q_1, Q_0, Qm_1;

private:
    int bitSize;
};

#endif // DATA_PATH_H
