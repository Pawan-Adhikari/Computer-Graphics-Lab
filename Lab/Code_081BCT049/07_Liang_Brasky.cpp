#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
using namespace std;
class Line{
    public:
        int x1, y1;
        int x2, y2;
        int dx, dy;
        double m;
    Line(int _x1=0, int _y1=0, int _x2=0, int _y2=0){
        x1 = _x1;
        y1 = _y1;
        x2 = _x2;
        y2 = _y2;
        dx = x2 - x1;
        dy = y2 - y1;
        if ((x2-x1) != 0) m = double(y2-y1)/double(x2-x1);
        else m = 0;
    }
    void display(){
        cout << x1 << "," << y1 << endl;
        cout << x2 << "," << y2 << endl;
    }
};
class LiangBTarget{
    public:
    int xmax;
    int xmin;
    int ymax;
    int ymin;
    int height;
    int width;
    LiangBTarget(int _xmin, int _ymin, int _xmax, int _ymax):
    xmin(_xmin), ymin(_ymin), xmax(_xmax), ymax(_ymax){
        height = ymax - ymin;
        width = xmax - xmin;
    }
    LiangBTarget(){}

    Line ClipLine(Line l){
        cout<< "Clipping to: \n" << xmin << ", " << ymin << endl << xmax << ", " << ymax << endl;

        float ustart = 0.0f; //ustart = u1
        float uend = 1.0f; //uend = u2

        int p1 = -l.dx;
        int q1 = l.x1-xmin;
        if ((p1 == 0) && (q1 < 0)) return Line();
        float r1 = float(q1)/p1;

        if ((p1 < 0) && (r1 > ustart)) ustart = r1;
        else if ((p1 > 0) && (r1 < uend)) uend = r1;

        int p2 = l.dx;
        int q2 = xmax - l.x1;
        if ((p2 == 0) && (q2 < 0)) return Line();
        float r2 = float(q2)/p2;

        if ((p2 < 0) && (r2 > ustart)) ustart = r2;
        else if ((p2 > 0) && (r2 < uend)) uend = r2;
        int p3 = -l.dy;
        int q3 = l.y1-ymin;
        if ((p3 == 0) && (q3 < 0)) return Line();
        float r3 = float(q3)/p3;

        if ((p3 < 0) && (r3 > ustart)) ustart = r3;
        else if ((p3 > 0) && (r3 < uend)) uend = r3;
        int p4 = l.dy;
        int q4 = ymax-l.y1;
        if ((p4 == 0) && (q4 < 0)) return Line();
        float r4 = float(q4)/p4;

        if ((p4 < 0) && (r4 > ustart)) ustart = r4;
        else if ((p4 > 0) && (r4 < uend)) uend = r4;

        if (ustart > uend) return Line();

        int x1 = static_cast<int>(lround(l.x1 + ustart * l.dx));
        int y1 = static_cast<int>(lround(l.y1 + ustart * l.dy));
        int x2 = static_cast<int>(lround(l.x1 + uend   * l.dx));
        int y2 = static_cast<int>(lround(l.y1 + uend   * l.dy)); 

        return Line(x1, y1, x2, y2);
    }
};

int main(){
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(400, 400)), "081BCT049");
    Line original(200, 200, 300, 250);
    cout << "Before: " << endl;
    original.display();
    LiangBTarget st(150, 150, 250, 250);
    Line clipped = st.ClipLine(original);
    cout << "After: " << endl;
    clipped.display();
    sf::RectangleShape boundary(sf::Vector2f(st.width, st.height));
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

//g++ -std=c++17 07_Liang_Brasky.cpp -o 07_Liang_Brasky -I/opt/homebrew/include -L/opt/homebrew/lib -lsfml-graphics -lsfml-window -lsfml-system && ./07_Liang_Brasky