#include "simulation.h"

using namespace std;

// error case 3
void check_valid_file(ifstream &file, string const &filename)
{
    if (!file)
    {
        cout << "Error: Cannot open file " << filename << "!" << endl;
        exit(0);
    }
}

bool check_point_bool(point_t location, grid_t grids)
{
    return (location.c < 0 || location.c >= (int)grids.width || location.r < 0 || location.r >= (int)grids.height)
               ? false
               : true;
}

void check_point(point_t location, grid_t grids, const string &species_name, const direction_t &direction)
{

    //error case 10
    if (location.c < 0 || location.r < 0 || location.c >= (int)grids.width || location.r >= (int)grids.height)
    {
        cout << "Error: Creature (" << species_name << " " << directName[direction] << " " << location.r << " " << location.c << ") is out of bound!" << endl;
        cout << "The grid size is " << grids.height << "-by-" << grids.width << "." << endl;
        exit(0);
    }
}

bool init_grid(world_t &world, ifstream &speciesfile,
               ifstream &worldfile, grid_t &grid)
{
    int species_number = 0;
    string species_dir, temp;

    getline(speciesfile, species_dir);
    while (getline(speciesfile, temp))
    {
        // error case 2
        if (species_number == MAXSPECIES)
        {
            cout << "Error: Too many species!" << endl;
            cout << "Maximal number of species is " << MAXSPECIES << '.' << endl;
            exit(0);
        }
        world.species[species_number] = get_species((species_dir + '/' + temp), temp);
        species_number++;
    }
    speciesfile.close();
    world.numSpecies = species_number;
    getline(worldfile, temp);
    grid.height = stoi(temp);
    getline(worldfile, temp);
    grid.width = stoi(temp);

    if (grid.width < 1 || grid.width > MAXWIDTH)
    {
        cout << "Error: The grid width is illegal!" << endl;
        return false;
    }

    if (grid.height < 1 || grid.height > MAXHEIGHT)
    {
        cout << "Error: The grid height is illegal!" << endl;
        return false;
    }

    for (int i = 0; i < (int)grid.height; i++)
        for (int j = 0; j < (int)grid.width; j++)
            grid.squares[i][j] = nullptr;
    return true;
}

creature_t *return_creature(const grid_t &grid, point_t location) { return grid.squares[location.r][location.c]; }

void print_creature(creature_t creature)
{
    cout << "(" << creature.species->name << ' ' << directName[creature.direction] << ' ' << creature.location.r << ' ' << creature.location.c << ")";
}

bool check_overlapped(grid_t grid, point_t location, creature_t *this_creature)
{
    if (return_creature(grid, location) != nullptr)
    {
        cout << "Error: Creature ";
        print_creature(*this_creature);

        cout << " overlaps with creature ";
        print_creature(*return_creature(grid, location));

        cout << "!" << endl;
        return true;
    }
    else
        return false;
}

void get_location(string &temp, int &number, string &species_name, direction_t &direction, point_t &location)
{
    stringstream ss;
    string to_direction, r, c;
    bool flag = false;

    ss << temp;
    ss >> species_name >> to_direction >> r >> c;
    location.r = stoi(r);
    location.c = stoi(c);

    //check location
    for (int j = 0; j < 4; j++)
    {
        if (directName[j] == to_direction)
        {
            direction = static_cast<direction_t>(j);
            break;
        }

        if (j == 3)
            flag = true;

        //error case 9
        if (flag)
        {
            cout << "Error: Direction " << to_direction << " is not recognized!" << endl;
            exit(0);
        }
    }
}

bool check_valid_input(int argc, char *argv[])
{
    // error case 1
    if (argc < 4)
    {
        cout << "Error: Missing arguments!" << endl;
        cout << "Usage: ./p3 <species-summary> <world-file> <rounds> [v|verbose]"
             << endl;
        return false;
    }

    // error case 2
    if (atoi(argv[3]) < 0)
    {
        cout << "Error: Number of simulation rounds is negative!" << endl;
        return false;
    }
    else
        return true;
}

creature_t get_creature(species_t species[], int species_number, string const &filename, string const &name, point_t location, direction_t dir)
{
    //initialize
    string temp, target_files, next;
    ifstream species_file;

    species_file.open(filename);
    getline(species_file, target_files);

    while (getline(species_file, temp))
    {
        if (temp == name)
        {
            //the directory
            next = (target_files + "/" + name);
            break;
        }
    }

    // error case 8
    if (next.empty())
    {
        cout << "Error: Species " << name << " not found!" << endl;
        exit(0);
    }

    species_t onespecies = get_species(next, name);
    creature_t creature = {
        .location = location,
        .direction = dir,
        .species = &onespecies,
        .programID = 0};

    for (int i = 0; i < species_number; i++)
    {
        if (species[i].name == onespecies.name)
        {
            creature.species = &(species[i]);
            break;
        }
    }
    species_file.close();
    return creature;
}

bool init_world(world_t &world, const string &species_input_file,
                const string &world_input_file)
{
    // initialize
    int creature_number = 0;
    grid_t grid;
    string temp;
    
    // initialize file && open it 
    ifstream species_file(species_input_file), world_file(world_input_file);

    check_valid_file(species_file, species_input_file);
    check_valid_file(world_file, world_input_file);

    
    if (!init_grid(world, species_file, world_file, grid)) //pass fstream but not filename, so no need to open a file again
        return 0;

    while (getline(world_file, temp))
    {

        //error case 7
        if (creature_number == MAXCREATURES)
        {
            cout << "Error: Too many creatures!" << endl;
            cout << "Maximal number of creatures is " << MAXCREATURES << "." << endl;
            return 0;
        }

        int number = 0;
        string species_name;
        direction_t direction;
        point_t location;

        get_location(temp, number, species_name, direction, location);
        check_point(location, grid, species_name, direction);

        world.creatures[creature_number] = get_creature(world.species, (int)world.numSpecies, species_input_file, species_name, location, direction);
        
        if (check_overlapped(grid, location, &world.creatures[creature_number]))
            return false;
        grid.squares[location.r][location.c] = &world.creatures[creature_number];
        creature_number++;
    }
    world.numCreatures = creature_number;
    world.grid = grid;
    world_file.close();
    return true;
}

instruction_t get_instruction(string const &instruction)
{
    instruction_t target_instruction;
    target_instruction.address = 0;
    string op;
    stringstream ss;
    ss << instruction;
    ss >> op;
    bool flag = true;

    for (int i = 0; i < 9; i++)
    {
        if (op == opName[i])
        {
            target_instruction.op = static_cast<opcode_t>(i);
            flag = false;
            break;
        }
    }

    // error case 6
    if (flag)
    {
        cout << "Error: Instruction " << op << " is not recognized!" << endl;
        exit(0);
    }
    if ((int)target_instruction.op >= 4)
    {
        ss >> target_instruction.address;
    }
    return target_instruction;
}

species_t get_species(string const &species_input_file_name,
                      string const &target_name)
{
    species_t target_species;
    string temp;
    ifstream species_input;
    species_input.open(species_input_file_name);

    target_species.name = target_name;
    target_species.programSize = 0;

    // check file validation
    check_valid_file(species_input, species_input_file_name);

    while (getline(species_input, temp))
    {
        if (temp.empty())
            break;
        // error case 5
        if (target_species.programSize == MAXPROGRAM)
        {
            cout << "Error: Too many instructions for species "
                 << target_name << "!" << endl;
            cout << "Maximal number of instructions is " << MAXPROGRAM << "." << endl;
            exit(0);
        }
        target_species.program[target_species.programSize] = get_instruction(temp);
        target_species.programSize++;
    }
    species_input.close();
    return target_species;
}

instruction_t return_instruction(const creature_t &creature)
{
    return creature.species->program[creature.programID];
}

void print_grid(const grid_t &grid)
{
    for (unsigned int i = 0; i < grid.height; i++)
    {
        for (unsigned int j = 0; j < grid.width; j++)
        {
            if (grid.squares[i][j] != nullptr)
            {
                creature_t thisone = *grid.squares[i][j];
                string shortname = thisone.species->name.substr(0, 2);
                cout << shortname << "_";
                string dirshort = directShortName[static_cast<direction_t>(thisone.direction)];
                cout << dirshort << " ";
            }
            else
                cout << "____ ";
        }
        cout << endl;
    }
}

point_t terminal(point_t pt, direction_t dir)
{
    switch (dir)
    {
    case EAST:
        pt.c++;
        break;
    case SOUTH:
        pt.r++;
        break;
    case WEST:
        pt.c--;
        break;
    case NORTH:
        pt.r--;
        break;
    }
    return pt;
}

void Hop(creature_t &creature, grid_t &grid)
{
    point_t oldlocation = creature.location;
    if ((check_point_bool(terminal(creature.location, creature.direction), grid) && return_creature(grid, terminal(creature.location, creature.direction)) == nullptr))
        creature.location = terminal(creature.location, creature.direction);
    creature.programID++;

    if (creature.location.c != oldlocation.c || creature.location.r != oldlocation.r)
    {
        grid.squares[creature.location.r][creature.location.c] = grid.squares[oldlocation.r][oldlocation.c];
        grid.squares[oldlocation.r][oldlocation.c] = nullptr;
    }
}

void Left(creature_t &creature, grid_t &grid)
{
    if (static_cast<int>(creature.direction) == 0)
        creature.direction = NORTH;
    else
        creature.direction = static_cast<direction_t>(static_cast<int>(creature.direction) - 1);
    creature.programID++;
}

void Right(creature_t &creature, grid_t &grid)
{
    if (static_cast<int>(creature.direction) == 3)
        creature.direction = EAST;
    else
        creature.direction = static_cast<direction_t>(static_cast<int>(creature.direction) + 1);
    creature.programID++;
}

void Infect(creature_t &creature, grid_t &grid)
{
    if (check_point_bool(terminal(creature.location, creature.direction), grid))
    {
        creature_t *nextpt = return_creature(grid, terminal(creature.location, creature.direction));
        if (nextpt != nullptr)
        {
            nextpt->species = creature.species;
            nextpt->programID = 0;
        }
    }
    creature.programID++;
}

void Ifempty(creature_t &creature, grid_t &grid, instruction_t instruction)
{
    if (check_point_bool(terminal(creature.location, creature.direction), grid))
        if (return_creature(grid, terminal(creature.location, creature.direction)) == nullptr)
        {
            creature.programID = instruction.address - 1;
            return;
        }
    creature.programID++;
    return;
}

void Ifwall(creature_t &creature, grid_t &grid, instruction_t instruction)
{
    if (!check_point_bool(terminal(creature.location, creature.direction), grid))
    {
        creature.programID = instruction.address - 1;
        return;
    }
    creature.programID++;
    return;
}

void Ifsame(creature_t &creature, grid_t &grid, instruction_t instruction)
{
    if (check_point_bool(terminal(creature.location, creature.direction), grid))
        if ((return_creature(grid, terminal(creature.location, creature.direction)) != nullptr) && return_creature(grid, terminal(creature.location, creature.direction))->species->name == creature.species->name)
        {
            creature.programID = instruction.address - 1;
            return;
        }
    creature.programID++;
    return;
}

void Ifenemy(creature_t &creature, grid_t &grid, instruction_t instruction)
{
    if (check_point_bool(terminal(creature.location, creature.direction), grid))
        if ((return_creature(grid, terminal(creature.location, creature.direction)) != nullptr) && (return_creature(grid, terminal(creature.location, creature.direction))->species->name != creature.species->name))
        {
            creature.programID = instruction.address - 1;
            return;
        }
    creature.programID++;
    return;
}

void move_creature(creature_t &creature, grid_t &grid, bool verbose)
{
    cout << "Creature ";
    print_creature(creature);
    cout << " takes action:";
    if (verbose)
        cout << endl;

    void (*direction_fp[])(creature_t &, grid_t &) = {Hop, Left, Right, Infect};

    void (*if_fp[])(creature_t &, grid_t &, instruction_t) = {Ifempty, Ifenemy, Ifsame, Ifwall};

    while (true)
    {
        print_instruction(creature, verbose);
        int return_op = (int)return_instruction(creature).op;
        if (return_op <= 3)
        {
            direction_fp[return_op](creature, grid);
            break;
        }
        else if (return_op == 8)
            creature.programID = return_instruction(creature).address - 1;
        else
            if_fp[return_op - 4](creature, grid, return_instruction(creature));
    }
}

void print_instruction(creature_t creature, bool verbose)
{
    instruction_t instruct = return_instruction(creature);
    if (verbose)
    {
        cout << "Instruction " << creature.programID + 1 << ": " << opName[instruct.op];
        if (instruct.address != 0)
            cout << " " << instruct.address << endl;
        else
            cout << endl;
    }
    else
    {
        if (instruct.address == 0)
            cout << " " << opName[instruct.op] << endl;
    }
}