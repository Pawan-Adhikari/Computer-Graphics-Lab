#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <utility>
using namespace std;
int abs(int n){
    if (n < 0){
        return -n;
    }
    else
        return n;
}
int roundValue(float n)
{
    if (n - (int)n < 0.5)
        return (int)n;
    return (int)(n + 1);
}
class Line {
private:
    int x0;
    int x1;
    int y0;
    int y1;
    int dx;
    int dy;
public:
    vector<pair<int, int>> points;
    Line(int _x0, int _y0, int _x1, int _y1){
        x0 = _x0;
        y0 = _y0;
        x1 = _x1;
        y1 = _y1;
        dx = x1-x0;
        dy = y1-y0;
    }
    void DDALine()
    {
        int step;
        if (dx > dy){
            step = abs(dx);
        }
        else step = abs(dy);
        float x_incr = (float)dx / step;
        float y_incr = (float)dy / step;
        float x = x0;
        float y = y0;

        for (int i = 0; i < step; i++) {
            points.push_back({x, y});
            x += x_incr;
            y += y_incr;
        }
    }
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(400, 400)), "DDA Line");
    Line l1(50, 50, 350, 200);
    Line l2(350, 200, 50, 50);
    Line l3(50, 50, 200, 350);
    Line l4(50, 350, 200, 50);
    l1.DDALine();
    l2.DDALine();
    l3.DDALine();
    l4.DDALine();
    while (window.isOpen()) {
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        window.clear(sf::Color::Black);
        auto drawPoints = [&](const vector<pair<int, int>>& pts, sf::Color color) {
            for (auto& p : pts) {
                sf::Vertex point{
                    sf::Vector2f(static_cast<float>(p.first), static_cast<float>(p.second)),
                    color
                };
                window.draw(&point, 1, sf::PrimitiveType::Points);
            }
        };
        drawPoints(l1.points, sf::Color::White);
        drawPoints(l2.points, sf::Color::Green);
        drawPoints(l3.points, sf::Color::Cyan);
        drawPoints(l4.points, sf::Color::Red);
        window.display();
    }
    return 0;
}

//g++ -std=c++17 01_DDA_SFML.cpp -o 01_DDA_SFML -I/opt/homebrew/include -L/opt/homebrew/lib -lsfml-graphics -lsfml-window -lsfml-system && ./01_DDA_SFML
