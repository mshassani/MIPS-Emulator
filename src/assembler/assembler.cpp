#include <cstdint>
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <string>
#include <algorithm>
using namespace std;

uint8_t regNum(string r) {
    unordered_map<string, uint8_t> reg = {
        {"$zero",0},{"$at",1},{"$v0",2},{"$v1",3},{"$a0",4},{"$a1",5},
        {"$a2",6},{"$a3",7},{"$t0",8},{"$t1",9},{"$t2",10},{"$t3",11},
        {"$t4",12},{"$t5",13},{"$t6",14},{"$t7",15},{"$s0",16},{"$s1",17},
        {"$s2",18},{"$s3",19},{"$s4",20},{"$s5",21},{"$s6",22},{"$s7",23},
        {"$t8",24},{"$t9",25},{"$k0",26},{"$k1",27},{"$gp",28},{"$sp",29},
        {"$fp",30},{"$ra",31}
    };

    auto it = reg.find(r);

    if (it == reg.end())
        throw runtime_error("Unknown register: " + r);

    return it->second;
}

string cleanLine(string line) {
    replace(line.begin(), line.end(), ',', ' ');
    replace(line.begin(), line.end(), '\t', ' ');

    size_t start = line.find_first_not_of(' ');
    size_t end = line.find_last_not_of(' ');
    if (start == string::npos) return ""; 

    return line.substr(start, end - start + 1);
}

vector<string> split(string cline) {
    vector<string> tokens;
    stringstream ss(cline);
    string token;

    while (getline(ss, token, ' ')) {
        if (!token.empty()) { tokens.push_back(token); };
    }
    return tokens;
}

void assemble(string filename) {
    ifstream file(filename);

    if (!file.is_open()) {
        throw runtime_error("Cannot open file: " + filename);
    }

    string line;
    vector<string> lines;
    vector<uint32_t> code;

    uint32_t address = 0;
    unordered_map<string, uint32_t> labels;

    while (getline(file, line)) {
        string s = cleanLine(line);

        if (s.empty()) {
            continue;
        }

        if (s.find(':') != string::npos) {
            string label = s.substr(0, s.find(':'));
            labels[label] = address;
        }

        else {
            lines.push_back(s);
            address += 4;
        }
    }

    address = 0;
    file.clear();
    file.seekg(0);

    for (const string& line : lines) {
        vector<string> parts = split(line);

        if (parts.empty()) {
            continue;
        }

        string op = parts[0];
        uint32_t instr = 0;

        if (op == "add" || op == "sub" || op == "and" || op == "or" || op == "slt") {
            uint8_t rd = regNum(parts[1]);
            uint8_t rs = regNum(parts[2]);
            uint8_t rt = regNum(parts[3]);
            uint8_t funct = (op == "add") ? 32 : (op == "sub") ? 34 : (op == "and") ? 36 : (op == "or") ? 37 : 42;

            instr = (0 << 26) | (rs << 21) | (rt << 16) | (rd << 11) | (0 << 6) | funct;
        }

        else if (op == "lw" || op == "sw") {
            uint8_t rt = regNum(parts[1]);
            string offset_reg = parts[2];
            size_t paren = offset_reg.find('(');
            int16_t offset = stoi(offset_reg.substr(0, paren));
            string reg = offset_reg.substr(paren + 1);

            reg.pop_back();

            uint8_t rs = regNum(reg);
            uint8_t opcode = (op == "lw") ? 35 : 43;

            instr = (opcode << 26) | (rs << 21) | (rt << 16) | (offset & 0xFFFF);
        }

        else if (op == "addi") {
            uint8_t rt = regNum(parts[1]);
            uint8_t rs = regNum(parts[2]);
            int16_t imm = stoi(parts[3]);

            instr = (0x08 << 26) | (rs << 21) | (rt << 16) | (static_cast<uint16_t>(imm));
        }

        else if (op == "beq" || op == "bne") {
            uint8_t rs = regNum(parts[1]);
            uint8_t rt = regNum(parts[2]);
            int16_t offset = labels[parts[3]] - (address + 4);
            offset >>= 2; 
            uint8_t opcode = (op == "beq") ? 4 : 5;

            instr = (opcode << 26) | (rs << 21) | (rt << 16) | (offset & 0xFFFF);
        }

        else if (op == "j") {
            uint32_t target = labels[parts[1]] >> 2;

            instr = (2 << 26) | (target & 0x3FFFFFF);
        }

        code.push_back(instr);
        address += 4;
    }

    ofstream out("output.bin", ios::binary);
    for (uint32_t instr : code) {
        out.write(reinterpret_cast<const char*>(&instr), sizeof(instr));
    }
     
    out.close();

    cout << "Assembled " << code.size() << " instructions" << endl;
}


int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: assembler <program.asm>\n";
        return 1;
    }

    try {
        assemble(argv[1]);
    }
    catch (const exception& e) {
        cerr << "Assembler Error: " << e.what() << '\n';
        return 1;
    }
}