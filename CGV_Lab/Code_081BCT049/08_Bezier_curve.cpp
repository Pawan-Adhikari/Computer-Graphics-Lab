#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <vector>

double combinations_count(int n, int r) {
    if (r < 0 || r > n) return 0;
    if (r == 0 || r == n) return 1;
    if (r > n / 2) r = n - r; 

    double res = 1;
    for (int i = 1; i <= r; ++i) {
        res = res * (n - r + i) / i;
    }
    return res;
}

class BezierCurve {
private:
    int n; 
    int *controlX;
    int *controlY;
    sf::VertexArray curvePoints;

public:
    BezierCurve(int n_, int *x_, int *y_) 
        : n(n_), controlX(x_), controlY(y_), curvePoints(sf::PrimitiveType::LineStrip) {}

    void calculate(float screenHeight) {
        curvePoints.clear();
        int degree = n - 1;

        for (double u = 0.0; u <= 1.001; u += 0.01) {
            double x0 = 0.0, y0 = 0.0;

            for (int i = 0; i < n; i++) {
                double basis = combinations_count(degree, i) * std::pow(u, i) * std::pow(1.0 - u, degree - i);
                x0 += basis * controlX[i];
                y0 += basis * controlY[i];
            }

            sf::Vertex v;
            v.position = { (float)x0, screenHeight - (float)y0 };
            v.color = sf::Color::White;
            curvePoints.append(v);
        }
    }

    void draw(sf::RenderWindow& window) {
        window.draw(curvePoints);
    }
};

int main() {
    const float H = 400.0f;
    
    // Classroom Example: (40, 20), (80, 80), (160, 40)
    int x[] = {40, 80, 160}; 
    int y[] = {20, 80, 40};
    const int controlCount = sizeof(x) / sizeof(x[0]);

    BezierCurve b1(controlCount, x, y);
    b1.calculate(H);

    sf::RenderWindow window(sf::VideoMode({400, 400}), "081BCT049");

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear(sf::Color::Black);

        b1.draw(window);

        for (int i = 0; i < controlCount; i++) {
            sf::CircleShape cp(4.0f);
            cp.setFillColor(sf::Color::Red);
            cp.setOrigin({4.0f, 4.0f});
            cp.setPosition({(float)x[i], H - (float)y[i]});
            window.draw(cp);

            if (i < controlCount - 1) {
                sf::Vertex line[2];
                
                line[0].position = {(float)x[i], H - (float)y[i]};
                line[0].color = sf::Color(100, 100, 100);
                
                line[1].position = {(float)x[i+1], H - (float)y[i+1]};
                line[1].color = sf::Color(100, 100, 100);

                window.draw(line, 2, sf::PrimitiveType::Lines);
            }
        }

        window.display();
    }

    return 0;
}
//g++ -std=c++17 08_Bezier_curve.cpp -o 08_Bezier_curve -I/opt/homebrew/include -L/opt/homebrew/lib -lsfml-graphics -lsfml-window -lsfml-system && ./08_Bezier_curve
