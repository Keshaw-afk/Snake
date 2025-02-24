#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>

const int width = 800;
const int height = 800;
const sf::Color screen_color_red = sf::Color::Red;
const int initial_snake_length = 5;
const sf::Color snake_outline_black = sf::Color::Black;
const sf::Color snake_body_color_white = sf::Color::White;
const sf::Color snake_head_color_green = sf::Color::Green;
const float snake_unit_side = 30;

void move(sf::Event, sf::RenderWindow&, std::vector<sf::RectangleShape>&);
void handle_event(sf::Event, sf::RenderWindow&, std::vector<sf::RectangleShape>&);
void draw(std::vector<sf::RectangleShape>&, sf::RenderWindow&);

void move(sf::Event event, sf::RenderWindow& window, std::vector<sf::RectangleShape>& snake)
{
    sf::Keyboard::Key key = event.key.code;
    sf::Vector2f movement = {0.0f, 0.0f};
    if (key == sf::Keyboard::W)
    {
        movement = {0.0f, -30.0f};
    }
    else if (key == sf::Keyboard::A)
    {
        movement = {-30.0f, 0.0f};
    }
    else if (key == sf::Keyboard::S)
    {
        movement = {0.0f, 30.0f};
    }
    else if (key == sf::Keyboard::D)
    {
        movement = {30.0f, 0.0f};
    }
    int length = snake.size();
    for (int i = length-1; i > 0; i--)
    {
        snake[i].setPosition(snake[i-1].getPosition());
    }
    snake[0].move(movement);
}

void handle_event(sf::Event event, sf::RenderWindow& window, std::vector<sf::RectangleShape>& snake)
{
    switch(event.type)
    {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::KeyPressed:
            move(event, window, snake);
            break;
            
    }
}

void draw(std::vector<sf::RectangleShape>& snake, sf::RenderWindow& window)
{
    for (auto& square : snake)
    {
        window.draw(square);
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode({width, height}), "Snake Game");
    std::vector<sf::RectangleShape> snake_body;
    int snake_length = initial_snake_length;
    for (int i = 0; i<snake_length; i++)
    {
        sf::RectangleShape square;
        if (i == 0)
        {
            square.setFillColor(snake_head_color_green);
        }
        else
        {
            square.setFillColor(snake_body_color_white);
        }
        square.setOutlineColor(snake_outline_black);
        square.setOutlineThickness(4.0);
        square.setPosition({(float)(width/2.0 + snake_unit_side*i), height/2.0});
        square.setSize({snake_unit_side, snake_unit_side});
        snake_body.push_back(square);

    }
    snake_body[0].setFillColor(sf::Color::Green); //head
    
    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            handle_event(event, window, snake_body);
        }

        window.clear(screen_color_red);
        draw(snake_body, window);
        window.display();

    }
}
