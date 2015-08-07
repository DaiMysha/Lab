#include <iostream>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <GL/gl.h>

#define WIDTH   1000
#define HEIGHT  830

//font taken from http://www.fontspace.com/melifonts/sweet-cheeks
int main(int argc, char** argv) {

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML testy");
    sf::Texture tex_mask;
    tex_mask.loadFromFile("data/mask2.png");
    //sf::Sprite spr_mask(tex_mask);

    sf::Texture tex_map;
    tex_map.loadFromFile("data/map.jpg");
    sf::Sprite spr_map(tex_map);

    sf::Color mask_color = sf::Color::Cyan;

    sf::Shader shader;
    shader.loadFromFile("data/mask.frag", sf::Shader::Fragment);
    shader.setParameter("mask", tex_mask);
    shader.setParameter("texture", sf::Shader::CurrentTexture);
    shader.setParameter("mask_color", mask_color);

    sf::View view(sf::FloatRect(0,0,WIDTH,HEIGHT));
    view.setViewport(sf::FloatRect(0.75f, 0, 0.25f, 0.25f));

    sf::View player_view(sf::FloatRect(0,0,WIDTH,HEIGHT));

    sf::RenderTexture render;
    render.create(WIDTH,HEIGHT);
    sf::Sprite spr_render(render.getTexture());

    sf::RenderTexture render2;
    render2.create(WIDTH,HEIGHT);
    sf::Sprite spr_render2(render2.getTexture());


    int speed = 5;
    while (window.isOpen()) {
        sf::Event event;        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else if(event.type == sf::Event::KeyPressed) {
                switch(event.key.code) {
                    case sf::Keyboard::Escape:
                    {
                        window.close();
                    } break;
                    case sf::Keyboard::Up :
                    {
                        spr_map.move(0,-speed);
                    } break;
                    case sf::Keyboard::Down :
                    {
                        spr_map.move(0,speed);
                    } break;
                    case sf::Keyboard::Left :
                    {
                        spr_map.move(-speed,0);
                    } break;
                    case sf::Keyboard::Right :
                    {
                        spr_map.move(speed,0);
                    } break;

                    case sf::Keyboard::V :
                    {
                        player_view.rotate(10);
                    } break;
                    case sf::Keyboard::B :
                    {
                        player_view.rotate(-10);
                    } break;
                    default: break;
                }
            }
        }

        {
            render.clear(sf::Color::Red);
            sf::View old_view = window.getView();
            render.setView(player_view);
            render.draw(spr_map);
            render.setView(old_view);
            render.display();
        }
        {
            render2.clear(sf::Color(0,0,0,0));
            sf::View old_view = window.getView();
            view.setCenter(player_view.getCenter());
            render2.setView(view);
            render2.draw(spr_render,&shader);
            render2.setView(old_view);
            render2.display();
        }


        window.clear();
        window.draw(spr_render);
        window.draw(spr_render2);
        window.display();
    }
    return 0;
}
