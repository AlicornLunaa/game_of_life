#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/PrimitiveType.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/VertexArray.hpp"
#include "SFML/Window/VideoMode.hpp"
#include "SFML/Window/Event.hpp"

#define WIDTH 640
#define HEIGHT 480
#define CELL_SIZE 10
#define VERTICIAL_VERTEX_COUNT 2*(WIDTH/(float)CELL_SIZE)
#define HORIZONTAL_VERTEX_COUNT 2*(HEIGHT/(float)CELL_SIZE)

const sf::Color gridColor = sf::Color(40, 40, 40, 200);

void generate_array(sf::VertexArray& va){
    // Generate grid
    int counter = 0;
    
    for(int x = 0; x < VERTICIAL_VERTEX_COUNT; x += 2){
        va[x].position.x = counter * CELL_SIZE;
        va[x].position.y = 0;
        va[x].color = gridColor;
        va[x + 1].position.x = counter * CELL_SIZE;
        va[x + 1].position.y = HEIGHT;
        va[x + 1].color = gridColor;
        counter++;
    }
    
    counter = 0;
    for(int y = VERTICIAL_VERTEX_COUNT; y < VERTICIAL_VERTEX_COUNT + HORIZONTAL_VERTEX_COUNT; y += 2){
        va[y].position.x = 0;
        va[y].position.y = counter * CELL_SIZE;
        va[y].color = gridColor;
        va[y + 1].position.x = WIDTH;
        va[y + 1].position.y = counter * CELL_SIZE;
        va[y + 1].color = gridColor;
        counter++;
    }
}

int main(){
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Game of Life", sf::Style::Default);
    sf::Event ev;

    sf::VertexArray gridArray(sf::PrimitiveType::Lines, VERTICIAL_VERTEX_COUNT + HORIZONTAL_VERTEX_COUNT);
    generate_array(gridArray);

    while(window.isOpen()){
        while(window.pollEvent(ev)){
            switch(ev.type){
                case sf::Event::Closed:
                    window.close();
                    break;

                default:
                    break;
            }
        }

        window.clear();
        window.draw(gridArray);
        window.display();
    }

    return 0;
}