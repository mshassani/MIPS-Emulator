#include "cpu/cpu.hpp"
#include "loader/loader.hpp"
#include "fstream"
#include <string>
#include <iostream>
#include <iomanip>

int main(int argc, char* argv[]) {
	CPU cpu;
	Loader loader(cpu.memoryInstance());

	cpu.reset();

	loader.load(argv[1], 0);

	std::string command;

    std::cout << "\n============================================================\n";
    std::cout << "                 MIPS32 Emulator\n";
    std::cout << "============================================================\n";


    while (true) {
        std::cout << "------------------------------------------------------------\n";
        std::cout << "PC          : 0x" << std::setw(8) << std::setfill('0') << std::hex << cpu.getPc() << '\n';

        std::cout << "Instruction : 0x" << std::setw(8) << cpu.getMemory(cpu.getPc()) << '\n';

        std::cout << "------------------------------------------------------------\n";
        std::cout << "\nRegisters\n";
        std::cout << "------------------------------------------------------------\n";

        for (int i = 0; i < 32; i++) {
            std::cout << std::dec << "R" << std::setw(2) << std::setfill('0') << i << " : 0x" << std::setw(8) << std::setfill('0') << std::hex << cpu.getRegister(i);

            if ((i + 1) % 4 == 0) {
                std::cout << '\n';
            }

            else {
                std::cout << "    ";
            }
        }

        std::cout << std::dec << '\n';

        std::cout << std::dec;

        std::cout << "\nCommands\n";
        std::cout << "  1 - Step\n";
        std::cout << "  2 - Exit\n";

        std::cout << "\n> ";

        std::cin >> command;

        if (command == "1") {
            cpu.step();
        }

        else if (command == "2") {
            break;
        }
    }
}