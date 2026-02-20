#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
using namespace std;
class Line{
    public:
        int x1, y1;
        int x2, y2;
        double m;
    Line(int _x1=0, int _y1=0, int _x2=0, int _y2=0){
        x1 = _x1;
        y1 = _y1;
        x2 = _x2;
        y2 = _y2;

        if ((x2-x1) != 0) m = double(y2-y1)/double(x2-x1);
        else m = 0;
    }
    void display(){
        cout << x1 << "," << y1 << endl;
        cout << x2 << "," << y2 << endl;
    }
};
class SutherlandTarget{
    public:
    int UP = 8;
    int RIGHT = 4;
    int LEFT = 1;
    int DOWN = 2;
    int U_RIGHT = 12;
    int U_LEFT = 9;
    int D_RIGHT = 6;
    int D_LEFT = 3;
    int TARGET = 0;
    int xmax;
    int xmin;
    int ymax;
    int ymin;
    int height;
    int width;
    SutherlandTarget(int _xmin, int _ymin, int _xmax, int _ymax):
    xmin(_xmin), ymin(_ymin), xmax(_xmax), ymax(_ymax){
        height = ymax - ymin;
        width = xmax - xmin;
    }
    SutherlandTarget(){}
    int assign_region(double x1, double y1){
        int END = 0;
        if (x1<xmin) END |= LEFT;
        else if (x1>xmax) END |= RIGHT;
        else END |= TARGET;
        if (y1<ymin) END |= DOWN;
        else if (y1>ymax) END |= UP;
        else END |= TARGET;
        return END;
    }
    Line ClipLine(Line l){
        cout<< "Clipping to: \n" << xmin << ", " << ymin << endl << xmax << ", " << ymax << endl;
        int END1 = assign_region(l.x1, l.y1);
        int END2 = assign_region(l.x2,l.y2);
        cout << "END1 assigned region code: " << END1 << endl;
        cout << "END2 assigned region code: " << END2 << endl;
        int intersection = END1 & END2;
        cout << "Intersection: " << intersection << endl;
        if ((END1 == 0) && (END2 == 0)) return l;
        if (intersection != 0) return Line();
        double x1 = l.x1;
        double y1 = l.y1;
        double x2 = l.x2;
        double y2 = l.y2;
        bool accept = false;
        while (true){
            if ((END1 | END2) == 0) { accept = true; break; }
            if ((END1 & END2) != 0) { break; }
            int out = END1 ? END1 : END2;
            double x = 0.0;
            double y = 0.0;
            if (out & UP){ y = ymax; x = x1 + (x2 - x1) * (ymax - y1) / (y2 - y1); }
            else if (out & DOWN)  { y = ymin; x = x1 + (x2 - x1) * (ymin - y1) / (y2 - y1); }
            else if (out & RIGHT) { x = xmax; y = y1 + (y2 - y1) * (xmax - x1) / (x2 - x1); }
            else if (out & LEFT)  { x = xmin; y = y1 + (y2 - y1) * (xmin - x1) / (x2 - x1); }
            if (out == END1) { x1 = x; y1 = y; END1 = assign_region(x1, y1); }
            else { x2 = x; y2 = y; END2 = assign_region(x2, y2); }
        }
        if (!accept) return Line();
        return Line(
            static_cast<int>(lround(x1)),
            static_cast<int>(lround(y1)),
            static_cast<int>(lround(x2)),
            static_cast<int>(lround(y2))
        );
    }
};

int main(){
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(400, 400)), "081BCT049");
    Line original(200, 200, 250, 300);
    cout << "Before: " << endl;
    original.display();
    SutherlandTarget st(150, 150, 250, 250);
    Line clipped = st.ClipLine(original);
    cout << "After: " << endl;
    clipped.display();
    sf::RectangleShape boundary(sf::Vector2f(st.height, st.width));
    boundary.setPosition(sf::Vector2f(st.xmin, st.ymin));
    boundary.setFillColor(sf::Color::Transparent);
    boundary.setOutlineThickness(1.0f);
    boundary.setOutlineColor(sf::Color::Black);
    sf::Vertex originalLine[] = {
        { sf::Vector2f(static_cast<float>(original.x1), static_cast<float>(original.y1)), sf::Color::Blue },
        { sf::Vector2f(static_cast<float>(original.x2), static_cast<float>(original.y2)), sf::Color::Blue }
    };
    sf::Vertex clippedLine[] = {
        { sf::Vector2f(static_cast<float>(clipped.x1), static_cast<float>(clipped.y1)), sf::Color::Red },
        { sf::Vector2f(static_cast<float>(clipped.x2), static_cast<float>(clipped.y2)), sf::Color::Red }
    };
    while (window.isOpen()) {
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }
        window.clear(sf::Color::White);
        window.draw(boundary);
        window.draw(originalLine, 2, sf::PrimitiveType::Lines);
        window.draw(clippedLine, 2, sf::PrimitiveType::Lines);
        window.display();
    }
}

//g++ -std=c++17 05_Sutherland.cpp -o 05_Sutherland -I/opt/homebrew/include -L/opt/homebrew/lib -lsfml-graphics -lsfml-window -lsfml-system && ./05_Sutherland