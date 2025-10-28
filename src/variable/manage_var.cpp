#include "variable.h"


class ManageVariables {
public:
    bool add_variable_data(VariableNode *variable_data) {
        this->variable_datas[this->variable_data_memorys - 1] = *variable_data;
    }

    ManageVariables() {
        this->variable_datas = (VariableNode *)malloc(sizeof(VariableNode));
        this->variable_data_memorys = 1;
    }

    ~ManageVariables() {
        free(variable_datas);
    }
private:
    VariableNode *variable_datas;
    int variable_data_memorys;
};