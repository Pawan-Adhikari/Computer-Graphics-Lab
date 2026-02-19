#include <iostream>

using namespace std;


int abs(int n){
    if (n < 0){
        return -n;
    }
    else
        return n;
}

class Line {
private:
    int x1;
    int x2;
    int y1;
    int y2;
    int dx;
    int dy;
public:
    Line(int _x1, int _y1, int _x2, int _y2){
        x1 = _x1;
        y1 = _y1;
        x2 = _x2;
        y2 = _y2;
        dx = x2-x1;
        dy = y2-y1;
    }

    void BresenhamLine(){
        int Ix, Iy;
        Ix = (dx < 0) ? -1 : 1; //right->left or left->right
        Iy = (dy < 0) ? -1 : 1; //up->down or down->up

        dx = abs(dx);
        dy = abs(dy);

        if (dx>dy){ //m < 1

            int P = 2 * dy - dx;
            int Pnext;
            
            //cout << "I entered if block" << endl;

            do{
                //cout << "I entered loop" << endl;
                cout << x1 << " " << y1 << "\n";
                x1 += Ix;
                if (P<0){
                    Pnext = P + 2 * dy;
                }
                else{
                    Pnext = P + 2 * dy - 2 * dx;
                    y1 += Iy;
                }
                P = Pnext;
            }while (x1!=x2);
        }
        else //m>1
        {
            int P = 2 * dx - dy;
            int Pnext;
            
            //cout << "I entered if block" << endl;

            do{
                //cout << "I entered loop" << endl;
                cout << x1 << " " << y1 << "\n";
                y1 += Iy;
                if (P<0){
                    Pnext = P + 2 * dx;
                }
                else{
                    Pnext = P + 2 * dx - 2 * dy;
                    x1 += Ix;
                }
                P = Pnext;
            }while (y1!=y2);
        }
        cout << x1 << " " << y1 << "\n";
    }

};
    


int main() {
    
    Line l1(1,2,11,7); //Line from (1,2) to (11,7)
    Line l2(11,7,1,2); //Line from (11,7) to (1,2)
    Line l3(1,2,5,9); //Line from (1,2) to (5,9)
    Line l4(1,9,5,2); //Line from (11,7) to (1,2)

    l1.BresenhamLine();
    cout << "-----------------" << endl;
    l2.BresenhamLine();
    cout << "-----------------" << endl;
    l3.BresenhamLine();
    cout << "-----------------" << endl;
    l4.BresenhamLine();

    return 0;
}