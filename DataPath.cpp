#include "DataPath.h"
#include "ALU.h"
#include "BinaryUtils.h"

DataPath::DataPath(int bitSize) : bitSize(bitSize) {
    A.resize(bitSize, 0);
    Q.resize(bitSize, 0);
    M.resize(bitSize, 0);
    ALU_OUT.resize(bitSize, 0);
    Q_1 = Q_0 = Qm_1 = 0;
}

void DataPath::update(int ALU_op, bool ldA, bool shiftA, bool clrA, bool ldQ, bool shiftQ, bool clrQ, bool ldM, bool clrM) {
    if (ldA) {
        ALU_OUT = ALU::execute(A, M, ALU_op);
        A = std::vector<int>(ALU_OUT.begin(), ALU_OUT.begin() + bitSize);
    }
    if (shiftA) {
        Qm_1 = Q[0];
        Q_0 = Q[1];
        Q_1 = Q[2];
        A.pop_back();
        A.insert(A.begin(), A.front());
        Q.pop_back();
        Q.insert(Q.begin(), A.back());
    }
    if (clrA) {
        std::fill(A.begin(), A.end(), 0);
    }
    if (ldQ) {
        Q = BinaryUtils::toBinary(Q_1, bitSize);
    }
    if (shiftQ) {
        Q.pop_back();
        Q.insert(Q.begin(), A.back());
    }
    if (clrQ) {
        std::fill(Q.begin(), Q.end(), 0);
    }
    if (ldM) {
        M = BinaryUtils::toBinary(BinaryUtils::binaryToDecimal(M), bitSize);
    }
    if (clrM) {
        std::fill(M.begin(), M.end(), 0);
    }
}

void DataPath::setInput(int Q_in, int M_in) {
    Q = BinaryUtils::toBinary(Q_in, bitSize);
    M = BinaryUtils::toBinary(M_in, bitSize);
}

bool DataPath::checkZero() {
    for (int bit : Q) {
        if (bit != 0) return false;
    }
    return true;
}

int DataPath::getResult() const {
    return BinaryUtils::binaryToDecimal(A) + BinaryUtils::binaryToDecimal(Q);
}
