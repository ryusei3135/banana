extern "C" {
    #include "variable.h"
}


class ManageVariables {
public:
    int add_variable_data(VariableNode *variable_data) {
        this->variable_datas[this->variable_data_memorys - 1] = *variable_data;
        this->variable_datas = (VariableNode *)realloc(
                this->variable_datas, 
                sizeof(VariableNode) * (this->variable_data_memorys + 1));
        this->variable_data_memorys++;
        return 1;
    }

    int update_variable_data(VariableNode *update_value) {
        int update_subject_pos = 0;

        if (update_subject_pos = this->search_variable(update_value->var_name) >= 0) {
            this->variable_datas[
                    update_subject_pos].value = update_value->value;
        } else {
            return 0;
        }
    }

    CalculNode* get_value(char *var_name) {
        int update_subject_pos = 0;

        if ((update_subject_pos = this->search_variable(var_name)) >= 0) {
            return this->variable_datas[update_subject_pos].value;
        }

        exit(1);
    }

    ManageVariables() {
        this->variable_datas = (VariableNode *)malloc(sizeof(VariableNode));
        this->variable_data_memorys = 1;
    }

    ~ManageVariables() {
        free(variable_datas);
    }
private:
    int search_variable(char *var_name) {
        for (int count = 0; this->variable_data_memorys - 2 >= count; count++) {
            if (!strcmp(this->variable_datas[count].var_name, var_name)) {
                return count;
            }
        }

        return -1;
    }

    VariableNode *variable_datas;
    int variable_data_memorys;
};


ManageVariables* access_variable_data() {
    static ManageVariables variable_data;
    return &variable_data;
}

int add_variable(VariableNode *var_data) {
    return access_variable_data()->add_variable_data(var_data);
}

CalculNode* get_var_value(char *var_name) {
    return access_variable_data()->get_value(var_name);
}