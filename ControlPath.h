#ifndef CONTROL_PATH_H
#define CONTROL_PATH_H

class ControlPath {
public:
    ControlPath();
    void updateState(bool start, bool eqz, int Q1, int Q0, int Qm1);

    bool ldA, shiftA, clrA, ldQ, shiftQ, clrQ, decr, ld_count, clrff, ldM, clrM, done;
    int ALU_op;

private:
    enum State { IDLE, LOAD, COMP, A1, A2, A3, A4, SHIFT, DONE };
    State PS, NS;

    void nextState();
};

#endif // CONTROL_PATH_H
