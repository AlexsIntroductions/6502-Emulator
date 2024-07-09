#include "../inc/nes.h"

/**
 * SELF NOTE SCHEME:
 * !!() - Indicates something important
 * ??() - Indicates something that should be replaces/confirmed to be correct
 * **() - Sudden Idea -> Something to Look into
 * ()   - Defines a statement/something you have to say. The opening one is the
 *        starting point of the statement and the closing one is the end of the
 *        statment. Can be omitted if the statement is one line or added if a
 *        statement needs to be multline.
 * vv   - Referring to Below
 * ^^   - Referring to Above
 * >>   - Extrapolates to
 * --   - Nests the statement that follows to the line above and is used
 *        to multiline statement/concept
 * ->   - next step:
 * :    - What follows after is a comma separated list pertaining to what comes
 *        before the colon
 * //   - Just a regular comment, no special system needed to be applied and if you
 *        cant figure it out from context clues ask someone online.
 *
 *
 * Essentially the scheme promotes the idea that each line is one concept/starting point
 * and works down to create the whole idea and process to do it. Highlighting things that
 * the person writing should already know and then apply vs things that need to be looked
 * into vs things that need to be learned and expanded on.
 */

/**
 * NOTES FOR STRUCTURE?
 *  -Memory Loading is done by creating the passing the file location of the rom into the
 *   nes, a new nes_mem is created and stored as a pointer in the nes. Then a pointer to the nes_mem
 *   is given to the nes_cpu to read and write to.
 *
 */

/**
 * TODO:
 *  -CPU START STATE
 *  -PPU START STATE
 */

using namespace std;

nes::nes()
{
    cout << "In NES" << endl;
    cpu = new nes_cpu();
    ppu = new nes_ppu();
    apu = new nes_apu();
    mem = new nes_mem();

    // window = nullptr;
}

// nes::nes(sf::RenderWindow* _window){
//     cout << "In NES" << endl;
//     cpu = new nes_cpu();
//     ppu = new nes_ppu();
//     apu = new nes_apu();
//     mem = new nes_mem();

//     window = _window;
// }

nes::~nes()
{
}

void nes::load(string filename)
{
    mem->load(filename);
    cpu->set_mem(mem);
    ppu->set_mem(mem);
    /**
     * WILL NEED TO RESET THE CPU AND PPU TO INITIAL STATES HERE vv
     */
}

void nes::loadNesTest()
{
    mem->loadNesTest();
    cpu->set_mem(mem);
    /**
     * WILL NEED TO RESET THE CPU AND PPU TO INITIAL STATES HERE vv
     */
}

void nes::eject()
{
}

void nes::start()
{
    // If there isnt a memory loaded
    if (mem == nullptr)
    {
        cout << "Not Started" << endl;
        return;
    }
    cout << "Started" << endl;

    if (debug == 1)
    {
        mem->print_mem();
    }
}

void nes::reset()
{
}

void nes::set_debug(int val)
{
    debug = val;
    cpu->set_debug(val);
    mem->set_debug(val);
    ppu->set_debug(val);
}