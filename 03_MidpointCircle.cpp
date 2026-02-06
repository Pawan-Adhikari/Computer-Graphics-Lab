#include <iostream>
#include <sstream>

using namespace std;

class Circle {
private:
    int x_c ;
    int y_c ;
    int r ;
public:
    Circle(int x_= 0, int y_= 0, int r_= 2){
        x_c = x_;
        y_c = y_;
        r = r_;
    }
    
    void print_points(int x_, int y_){
        cout << x_ << "," << y_ << endl;
        cout << y_ << "," << x_ << endl;
        cout << -x_ << "," << y_ << endl;
        cout << -y_ << "," << x_ << endl;
        cout << -x_ << "," << -y_ << endl;
        cout << -y_ << "," << -x_ << endl;
        cout << x_ << "," << -y_ << endl;
        cout << y_ << "," << -x_ << endl;
    }

    std::ostringstream& print_for_py(std::ostringstream& py_str, int x_, int y_){
        py_str << "(" << x_ << "," << y_ << "), (" << y_ << "," << x_ << "), (" << -x_ << "," << y_ << "), (" << -y_ << "," << x_ << "), (" << -x_ << "," << -y_ << "), (" << -y_ << "," << -x_ << "), (" << x_ << "," << -y_ << "), (" << y_ << "," << -x_ << "), ";
        return py_str;
    }

    void draw(){
        int x = 0;
        int y = r;
        int P = 1 - r;
        std::ostringstream py_str;
        while (x <= y){
            print_points(x_c + x, y_c + y);
            print_for_py(py_str, x_c + x, y_c + y);
            x += 1;
            if (P < 0){
                P += 2 * x + 1;
            }
            else{
                y -= 1;
                P += 2 * (x - y) + 1;
            }

        }
        cout << py_str.str();
    }
};  

int main() {
    Circle C(200, 200, 80);
    C.draw();

    return 0;
}