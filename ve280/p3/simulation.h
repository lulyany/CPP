#ifndef SIMULATION_H
#define SIMULATION_H

 //include files
#include "world_type.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <string>
#include <iomanip>

using namespace std;

void check_valid_file(ifstream& file, string const& filename);
bool check_point_bool(point_t location, grid_t grids);
void check_point(point_t location, grid_t grids, const string& species_name, const direction_t& direction);
bool init_grid(world_t& world, ifstream& speciesfile,
    ifstream& worldfile, grid_t& grid);
creature_t* return_creature(const grid_t& grid, point_t location);
void print_creature(creature_t creature);
bool check_overlapped(grid_t grid, point_t location, creature_t* this_creature);
void get_location(string& temp, int& number, string& species_name, direction_t& direction, point_t& location);
bool check_valid_input(int argc, char* argv[]);
creature_t get_creature(species_t species[], int species_number, string const& filename, string const& name, point_t location, direction_t dir);
bool init_world(world_t& world, const string& species_input_file,
    const string& world_input_file);
instruction_t get_instruction(string const& instruction);
species_t get_species(string const& species_input_file_name,
    string const& target_name);
instruction_t return_instruction(const creature_t& creature);
void print_grid(const grid_t& grid);
point_t terminal(point_t pt, direction_t dir);
void Hop(creature_t& creature, grid_t& grid);
void Left(creature_t& creature, grid_t& grid);
void Right(creature_t& creature, grid_t& grid);
void Infect(creature_t& creature, grid_t& grid);
void Ifempty(creature_t& creature, grid_t& grid, instruction_t instruction);
void Ifwall(creature_t& creature, grid_t& grid, instruction_t instruction);
void Ifsame(creature_t& creature, grid_t& grid, instruction_t instruction);
void Ifenemy(creature_t& creature, grid_t& grid, instruction_t instruction);
void move_creature(creature_t& creature, grid_t& grid, bool verbose);
void print_instruction(creature_t creature, bool verbose);

#endif