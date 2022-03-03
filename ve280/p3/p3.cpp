#include "simulation.h"

using namespace std;

int main(int argc, char* argv[]) {

    //initialization
    bool verbose = false;
    world_t world; // world is the most important
    
    //check input
    if (!check_valid_input(argc, argv))
        return 0;

    //switch verbose
    if ((argc == 5) && ((string)argv[4] == "v" || (string)argv[4] == "verbose"))
        verbose = true;

    //init the world & check & will also init a world
    //argv[1] & argv[2] are names of species files and creature files
    if (!init_world(world, argv[1], argv[2]))
        return 0;


    cout << "Initial state" << endl;

    //print the grid
    print_grid(world.grid);

    //run the simulation round by round
    for (int i = 0; i < atoi(argv[3]); i++) {
        //print the number of current round
        cout << "Round " << i + 1 << endl;
        
        //move the creatures one by one
        for (int j = 0; j < (int)world.numCreatures; j++) {
            move_creature(world.creatures[j], world.grid, verbose);
            
            //if verbose, print the grid at the end of each action of each round
            if (verbose) print_grid(world.grid);
        }
        //ifn verbose only print at the end of each round
        if (!verbose) print_grid(world.grid);
    }
    return 0;
}
