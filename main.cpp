#include <iostream>
#include <string>

class DiskExplorer {
private:
    int user_input;

public:
    DiskExplorer() : user_input(0) {};

    int menu() {
        const std::string logo = R"(
    ____  _      __   ______           __                    
   / __ \(_)____/ /__/ ____/  ______  / /___  ________  _____
  / / / / / ___/ //_/ __/ | |/_/ __ \/ / __ \/ ___/ _ \/ ___/
 / /_/ / (__  ) ,< / /____>  </ /_/ / / /_/ / /  /  __/ /    
/_____/_/____/_/|_/_____/_/|_/ .___/_/\____/_/   \___/_/     
                            /_/                              
    )";

        std::cout << logo << "\n";
    }
};

DiskExplorer t;

int main(void) {
    int y = t.menu();
    
    return 0;
}