#include <iostream>
#include <sstream>

using namespace std;

class Ellipse {
private:
    int x_c ;
    int y_c ;
    int a ;
    int b ;
public:
    Ellipse(int x_= 0, int y_= 0, int a_= 1, int b_=1){
        x_c = x_;
        y_c = y_;
        a = a_;
        b = b_;
    }
    
    void print_points(int x_, int y_){
        cout << x_ << "," << y_ << endl;
        //cout << y_ << "," << x_ << endl;
        cout << -x_ << "," << y_ << endl;
        //cout << -y_ << "," << x_ << endl;
        cout << -x_ << "," << -y_ << endl;
        //cout << -y_ << "," << -x_ << endl;
        cout << x_ << "," << -y_ << endl;
        //cout << y_ << "," << -x_ << endl;
    }

    std::ostringstream& print_for_py(std::ostringstream& py_str, int x_, int y_){
        //py_str << "(" << x_ << "," << y_ << "), (" << y_ << "," << x_ << "), (" << -x_ << "," << y_ << "), (" << -y_ << "," << x_ << "), (" << -x_ << "," << -y_ << "), (" << -y_ << "," << -x_ << "), (" << x_ << "," << -y_ << "), (" << y_ << "," << -x_ << "), ";
        py_str << "(" << x_ << "," << y_ << "), (" << -x_ << "," << y_ << "), (" << -x_ << "," << -y_ << "), (" << x_ << "," << -y_ << "), ";
        return py_str;
    }

    void draw(){
        int x = 0;
        int y = b;
        int P = b*b + a*a*(0.25-b);
        std::ostringstream py_str;
        print_points(x_c + x, y_c + y);
        print_for_py(py_str, x_c + x, y_c + y);
        while (b*b*x < y * a * a){
            x += 1;
            if (P < 0){
                P += b*b*(2 * x + 1);
            }
            else{
                y -= 1;
                P += b*b*(2 * x + 1) - 2 * a * a * y;
            }
            print_points(x_c + x, y_c + y);
            print_for_py(py_str, x_c + x, y_c + y);
        }

        P = b * b * (x + 0.5) * (x + 0.5) + a * a * (y - 1) * (y - 1) - a*a*b*b;

        while (y >= 0){
            print_points(x_c + x, y_c + y);
            print_for_py(py_str, x_c + x, y_c + y);
            y -= 1;
            if (P > 0){
                P += a*a*(1 - 2 * y);
            }
            else{
                x += 1;
                P += a*a*(1 - 2 * y) + 2 * b * b * x;
            }
        }

        cout << py_str.str();
    }
};  

int main() {
    Ellipse E(0,0,16,5); //Circle with center at 1,1 and of radius 5
    E.draw();
    return 0;
}