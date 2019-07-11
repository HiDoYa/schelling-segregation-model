#ifndef GLOBAL_SETTINGS
#define GLOBAL_SETTINGS

namespace GlobalSettings {
    const int NumRaces = 2;
    const int NumCellsPerRace = 10;
    const int NumNeighbors = 1;

    // How many foreign neighbors that cells are happy with
    // Between 0 and 1
    const float Tolerance = 0.5; 
}
#endif