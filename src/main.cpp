#include <iostream>
//#include <SFML/Graphics.hpp>
#include "../inc/nes.h"

//**(IMPLEMENT THREADING FOR THE NES TO RUN ON SEPARATE FROM THE SFML)
//^^ thread will execute the evalutate function to emulate the next instruction
//^^ this way the cpu will execute to the next state and the frame will be displayed then paused until the next state 
//-- ^^ >> auto 60 fps at right delay

using namespace std;

int main()
{
    //sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");

    nes system = nes();

    //Set If Debugging is Necessary
    system.set_debug(1);

    system.load("../test.nes");

    /*
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed){
                window.close();
            }
        }

        window.clear();
        window.display();
    }
    */

    return 0;
}