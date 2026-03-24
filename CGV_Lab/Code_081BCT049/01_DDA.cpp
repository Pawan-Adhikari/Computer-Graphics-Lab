
#include <iostream>
using namespace std;

int abs(int n){
    if (n < 0){
        return -n;
    }
    else
        return n;
}

// function for rounding off the pixels
int roundValue(float n)
{
    if (n - (int)n < 0.5)
        return (int)n;
    return (int)(n + 1);
}

// Function for line generation
void DDALine(int x0, int y0, int x1, int y1)
{

    // Calculate dx and dy
    int dx = x1 - x0;
    int dy = y1 - y0;

    int step;


    // If dx > dy we will take step as dx
    // else we will take step as dy to draw the complete
    // line
    if (dx > dy){
        step = abs(dx);
        //cout << "dx > dy" << endl;
    }
    else{
        step = abs(dy);
        //cout << "dx < dy" << endl;
    }

   // cout << "Step = " << step << endl;

    // Calculate x-increment and y-increment for each step
    float x_incr = (float)dx / step;
    float y_incr = (float)dy / step;

    // cout << "x_incr = " << x_incr << endl;
    //cout << "y_incr = " << y_incr << endl;

    // Take the initial points as x and y
    float x = x0;
    float y = y0;

    for (int i = 0; i < step; i++) {
        //cout << x << " " << y << "\n";
        x += x_incr;
        y += y_incr;
        // delay(10);
    }
}

// Driver code
int main()
{

    int x0 = 200, y0 = 180, x1 = 180, y1 = 160;
    //cout << "Test" << endl;
    // Function call
    DDALine(x0, y0, x1, y1);

    return 0;
}
