#include "ControlPath.h"

ControlPath::ControlPath() : PS(IDLE), NS(IDLE) {
    ldA = shiftA = clrA = ldQ = shiftQ = clrQ = decr = ld_count = clrff = ldM = clrM = done = false;
    ALU_op = 0;
}

void ControlPath::updateState(bool start, bool eqz, int Q2_1, int Q2, int Q2_0) {
    switch (PS) {
        case IDLE:
            if (start) NS = LOAD;
            break;
        case LOAD:
            NS = COMP;
            break;
        case COMP:
            if (eqz) NS = DONE;
            else if ((Q2_1 == 0 && Q2 == 0 && Q2_0 == 0) || (Q2_1 == 1 && Q2 == 1 && Q2_0 == 1)) NS = SHIFT;
            else if ((Q2_1 == 0 && Q2 == 0 && Q2_0 == 1) || (Q2_1 == 0 && Q2 == 1 && Q2_0 == 0)) NS = A1;
            else if ((Q2_1 == 1 && Q2 == 0 && Q2_0 == 1) || (Q2_1 == 1 && Q2 == 1 && Q2_0 == 0)) NS = A2;
            else if (Q2_1 == 0 && Q2 == 1 && Q2_0 == 1) NS = A3;
            else if (Q2_1 == 1 && Q2 == 0 && Q2_0 == 0) NS = A4;
            break;
        case A1:
            NS = SHIFT;
            break;
        case A2:
            NS = SHIFT;
            break;
        case A3:
            NS = SHIFT;
            break;
        case A4:
            NS = SHIFT;
            break;
        case SHIFT:
            if (eqz) NS = DONE;
            else NS = COMP;
            break;
        case DONE:
            NS = DONE;
            break;
        default:
            NS = IDLE;
            break;
    }

    PS = NS;
    nextState();
}

void ControlPath::nextState() {
    switch (PS) {
        case IDLE:
            ldA = shiftA = clrA = ldQ = shiftQ = clrQ = decr = ld_count = clrff = ldM = clrM = done = false;
            break;
        case LOAD:
            ldA = ldQ = ldM = ld_count = true;
            clrA = clrQ = clrff = clrM = false;
            break;
        case COMP:
            ldA = ldQ = ldM = ld_count = false;
            break;
        case A1:
            ALU_op = 0;
            ldA = true;
            break;
        case A2:
            ALU_op = 1;
            ldA = true;
            break;
        case A3:
            ALU_op = 2;
            ldA = true;
            break;
        case A4:
            ALU_op = 3;
            ldA = true;
            break;
        case SHIFT:
            shiftA = shiftQ = true;
            ldA = decr = false;
            break;
        case DONE:
            done = true;
            break;
    }
}
