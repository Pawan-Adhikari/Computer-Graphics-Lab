#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <utility>
using namespace std;
class Ellipse {
private:
    int x_c ;
    int y_c ;
    int a ;
    int b ;
public:
    vector<pair<int, int>> points;
    Ellipse(int x_= 0, int y_= 0, int a_= 1, int b_=1){
        x_c = x_;
        y_c = y_;
        a = a_;
        b = b_;
    }
    void add_points(int x_, int y_) {
        points.push_back({x_c + x_, y_c + y_});
        points.push_back({x_c - x_, y_c + y_});
        points.push_back({x_c - x_, y_c - y_});
        points.push_back({x_c + x_, y_c - y_});
    }
    void draw(){
        int x = 0;
        int y = b;
        int P = b*b + a*a*(0.25-b);
        while (b*b*x < y * a * a){
            add_points(x, y);
            x += 1;
            if (P < 0){
                P += b*b*(2 * x + 1);
            }
            else{
                y -= 1;
                P += b*b*(2 * x + 1) - 2 * a * a * y;
            }
        }
        P = b * b * (x + 0.5) * (x + 0.5) + a * a * (y - 1) * (y - 1) - a*a*b*b;
        while (y >= 0){
            add_points(x, y);
            y -= 1;
            if (P > 0){
                P += a*a*(1 - 2 * y);
            }
            else{
                x += 1;
                P += a*a*(1 - 2 * y) + 2 * b * b * x;
            }
        }
    }
};  

int main() {
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(400, 400)), "Midpoint Ellipse");
    Ellipse E(200, 200, 160, 80);
    E.draw();
    while (window.isOpen()) {
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        window.clear(sf::Color::Black);
        for (auto& p : E.points) {
            sf::Vertex point{
                sf::Vector2f(static_cast<float>(p.first), static_cast<float>(p.second)),
                sf::Color::White
            };
            window.draw(&point, 1, sf::PrimitiveType::Points);
        }
        window.display();
    }
    return 0;
}

//g++ -std=c++17 04_MidpointEllipse_SFML.cpp -o 04_MidpointEllipse_SFML -I/opt/homebrew/include -L/opt/homebrew/lib -lsfml-graphics -lsfml-window -lsfml-system && ./04_MidpointEllipse_SFML