#include <iostream>
#include <string>
#include <vector>
#include <map>

int regCnt = 0;

int labelCnt = 1;

std::string generateLabel() {
    std::string res = "label";
    res += std::to_string(labelCnt);
    labelCnt++;
    return res;
}

std::string generateRegister() {
    std::string res = "r";
    res += std::to_string(regCnt);
    regCnt++;
    return res;
}

bool checkRegister(std::string s) {
    
    if (s.length() == 1) return false;

    if (s[0] == 'r') {
        bool check = true;
        for (int i = 1; i < s.length(); i++) {
            if (s[i] < '0' || s[i] > '9') {
                check = false;
                break;
            }
        }
        return check;
    }
    
    return false;

}

// INT, FLOAT etc..
class VARIABLE_DECLARATION
{
    public:
        std::string type;
        std::string id;
        int line;
};

// STRING (derived from VARIABLE_DECLARATION)
class STRING_VARIABLE_DECLARATION: public VARIABLE_DECLARATION
{
    public:
        std::string value;
};

// SYBMOL TABLE class
class SYMBOL_TABLE {
    public:

        int linkCounter = 1;
        int argCounter = 2;

        std::map<std::string,std::string> varMap;
        
        std::string whoseFirst = ""; // VAR or STR
        std::string st_name; // symbol table name
        std::vector<VARIABLE_DECLARATION*> VARS; // INT, FLOAT etc..
        std::vector<STRING_VARIABLE_DECLARATION*> STRING_VARS; // STRING    

};

// AST node class
class ASTnode {
    
    public:

        std::string factor_1;
        std::string factor_2;
        std::string result;
        std::string opType;

        std::vector<std::string> codeGenList;

        std::string curInstruction;
        std::string type;

        ASTnode* left;
        ASTnode* right;
        ASTnode* parent;
        
        ASTnode() {
            this->left = NULL;
            this->right = NULL;
            this->parent = NULL;
        }

};

ASTnode* globalNode = NULL;

// symbol tables
std::vector<SYMBOL_TABLE*> symbol_tables;

 // current symbol table
SYMBOL_TABLE* curST = NULL;

// current variable type (INT, FLOAT etc..)
std::string curVarType = "";    

// whether the func local variable is not mapped to a argument
bool isLink = false;

// whether the func local variable is mapped to a argument
bool isArg = false;

 // block counter
int blockCounter = 1;          

std::vector<int> adder;

std::vector<int> multiplier;
    
int temporary = 0;

void printSymbolTable() {

    for (int i = 0; i < symbol_tables.size(); i++) {
            
        if (symbol_tables[i]->st_name == "BLOCK") {
            std::cout << "Symbol table " << symbol_tables[i]->st_name << " " << blockCounter << std::endl;
            blockCounter++;
        } else {
            std::cout << "Symbol table " << symbol_tables[i]->st_name << std::endl;
        }

        if (symbol_tables[i]->whoseFirst == "VAR") {

            for (auto& var: symbol_tables[i]->VARS) {
                std::cout << "name " << var->id << " type " << var->type << std::endl;
            }
            for (auto& strvar: symbol_tables[i]->STRING_VARS) {
                std::cout << "name " << strvar->id << " type " << strvar->type << " value " << strvar->value << std::endl;
            }

        } else {

            for (auto& strvar: symbol_tables[i]->STRING_VARS) {
                std::cout << "name " << strvar->id << " type " << strvar->type << " value " << strvar->value << std::endl;
            }
            for (auto& var: symbol_tables[i]->VARS) {
                std::cout << "name " << var->id << " type " << var->type << std::endl;
            }
            
        }
        
        if (i != symbol_tables.size() - 1) std::cout << std::endl;
        
    }
}

// parent symbol tables stack
std::vector<SYMBOL_TABLE*> PST; 

// Function return type map
std::map<std::string,std::string> FRM;

// FST function symbol tables stack
std::vector<SYMBOL_TABLE*> FST;