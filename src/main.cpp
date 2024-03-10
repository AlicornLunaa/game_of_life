#include <vector>

#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/PrimitiveType.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/VertexArray.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/VideoMode.hpp"
#include "SFML/Window/Event.hpp"

#define WIDTH 640
#define HEIGHT 480
#define CELL_SIZE 20
#define VERTICIAL_VERTEX_COUNT 2*(WIDTH/CELL_SIZE)
#define HORIZONTAL_VERTEX_COUNT 2*(HEIGHT/CELL_SIZE)

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

sf::Vector2i get_selected_cell(sf::RenderWindow& window){
    sf::Vector2f pos = (sf::Vector2f)sf::Mouse::getPosition(window);
    pos /= (float)CELL_SIZE;
    pos.x = (int)pos.x;
    pos.y = (int)pos.y;
    return (sf::Vector2i)pos;
}

void update_cursor(sf::RenderWindow& window, sf::RectangleShape& cursor){
    // Get current mouse position and round to grid
    sf::Vector2f pos = (sf::Vector2f)get_selected_cell(window);
    pos *= (float)CELL_SIZE;
    cursor.setPosition(pos);
}

void toggle_cell(bool cellGrid[WIDTH / CELL_SIZE][HEIGHT / CELL_SIZE], const sf::Vector2i& pos){
    cellGrid[pos.x][pos.y] = !cellGrid[pos.x][pos.y];
}

int main(){
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Game of Life", sf::Style::Default);
    sf::Event ev;

    sf::VertexArray gridArray(sf::PrimitiveType::Lines, VERTICIAL_VERTEX_COUNT + HORIZONTAL_VERTEX_COUNT);
    generate_array(gridArray);

    sf::RectangleShape gridCursor({ CELL_SIZE, CELL_SIZE });
    gridCursor.setFillColor(gridColor);
    gridCursor.setOutlineColor(sf::Color::Cyan);
    gridCursor.setOutlineThickness(2);

    sf::RectangleShape cellSprite({ CELL_SIZE, CELL_SIZE });
    cellSprite.setFillColor(sf::Color::White);

    bool cellGrid[WIDTH / CELL_SIZE][HEIGHT / CELL_SIZE];

    while(window.isOpen()){
        while(window.pollEvent(ev)){
            switch(ev.type){
                case sf::Event::Closed:
                    window.close();
                    break;

                case sf::Event::MouseButtonReleased:
                    toggle_cell(cellGrid, get_selected_cell(window));
                    break;

                default:
                    break;
            }
        }

        update_cursor(window, gridCursor);

        window.clear();
        window.draw(gridArray);
        window.draw(gridCursor);

        for(int x = 0; x < WIDTH / CELL_SIZE; x++){
            for(int y = 0; y < HEIGHT / CELL_SIZE; y++){
                if(!cellGrid[x][y]) continue;
                cellSprite.setPosition(x * CELL_SIZE, y * CELL_SIZE);
                window.draw(cellSprite);
            }
        }

        window.display();
    }

    return 0;
}