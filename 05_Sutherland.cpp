#include <vector>
#include <iostream>

using namespace std;

class Line{
    public:
        int x1, y1;
        int x2, y2;
        int m;
    Line(int _x1=0, int _y1=0, int _x2=0, int _y2=0){
        x1 = _x1;
        y1 = _y1;
        x2 = _x2;
        y2 = _y2;

        if ((x2-x1) != 0) m = (y2-y1)/(x2-x1);
        else m = 0;
    }

    void display(){
        cout << x1 << "," << y1 << endl;
        cout << x2 << "," << y2 << endl;
    }
};

class SutherlandTarget{
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

    public:
    SutherlandTarget(int _xmin, int _ymin, int _xmax, int _ymax):
    xmin(_xmin), ymin(_ymin), xmax(_xmax), ymax(_ymax){
        
    }
    SutherlandTarget(){}

    int assign_region(int x1, int y1){
        int END = 0;
        if (x1<xmin) END |= LEFT;
        else if (x1>xmax) END |= RIGHT;
        else END |= TARGET
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

        int xi1 = 0;
        int xi2 = 0;
        int yi1 = 0;
        int yi2 = 0;
        int x,y;

        while (true){

            if ((END1 | END2) == 0) break;           
            if ((END1 & END2) != 0) break;  

            int out = END1 ? END1 : END2;

            if (out & UP){ y = ymax; x = l.x1 + (l.x2 - l.x1) * (ymax - l.y1) / (l.y2 - l.y1); }
            else if (out & DOWN)  { y = ymin; x = l.x1 + (l.x2 - l.x1) * (ymin - l.y1) / (l.y2 - l.y1); }
            else if (out & RIGHT) { x = xmax; y = l.y1 + (l.y2 - l.y1) * (xmax - l.x1) / (l.x2 - l.x1); }
            else if (out & LEFT)  { x = xmin; y = l.y1 + (l.y2 - l.y1) * (xmin - l.x1) / (l.x2 - l.x1); }

            if (out == END1) { xi1 = x; yi1 = y; END1 = assign_region(xi1, yi1); }
            else { xi2 = x; yi2 = y; END2 = assign_region(xi2, yi2); }
        }
        
        /*
        if (END1 == 0) {
            if ((END2 & UP) != 0) {
                yi2 = ymax;
                xi2 = line.x1 + (1.0/line.m)*(yi2 - line.y1);
            }
            else if ((END2 & DOWN) != 0) {
                yi2 = ymin;
                xi2 = line.x1 + (1.0/line.m)*(yi2 - line.y1);
            }
            if ((END2 & RIGHT) != 0) {
                xi2 = xmax;
                yi2 = line.y1 + (line.m)*(xi2 - line.x1);
            }
            else if ((END2 & LEFT) != 0) {
                xi2 = xmin;
                yi2 = line.y1 + (line.m)*(xi2 - line.x1);
            }
            xi1 = line.x1;
            yi1 = line.y1;
            
        }
        else if (END2 == 0) {
            if ((END1 & UP) != 0) {
                yi1 = ymax;
                xi1 = line.x1 + (1.0/line.m)*(yi1 - line.y1);
            }
            else if ((END1 & DOWN) != 0) {
                yi1 = ymin;
                xi1 = line.x1 + (1.0/line.m)*(yi1 - line.y1);
            }
            if ((END1 & RIGHT) != 0) {
                xi1 = xmax;
                yi1 = line.y1 + (line.m)*(xi1 - line.x1);
            }
            else if ((END1 & LEFT) != 0) {
                xi1 = xmin;
                yi1 = line.y1 + (line.m)*(xi1 - line.x1);
            }
            xi2 = line.x2;
            yi2 = line.y2;
        }
        */

        return Line(xi1, yi1, xi2, yi2);
    }
};

int main(){
    Line l(10,10,60,60);
    cout << "Before: " << endl;
    l.display();

    SutherlandTarget st(15,15,25,25);
    l = st.ClipLine(l);

    cout << "After: " << endl;
    l.display();
}
