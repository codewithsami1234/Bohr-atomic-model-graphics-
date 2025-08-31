#include <graphics.h>
#include <cmath>
#include <iostream>
#include <thread>
#include <chrono> 
using namespace std;
class Orbit {
protected:
    int centerX, centerY, radius;
public:
    Orbit(int x, int y, int r) : centerX(x), centerY(y), radius(r) {}
    virtual void draw() = 0; 
    virtual void animate(float angleOffset) = 0;
    virtual ~Orbit() {}
};
class ElectronOrbit : public Orbit {
    int electronCount;
public:
    ElectronOrbit(int x, int y, int r, int eCount)
        : Orbit(x, y, r), electronCount(eCount) {}
    void draw() override {
        setcolor(BLACK);
        circle(centerX, centerY, radius);
    }
    void animate(float angleOffset) override {
        for (int i = 0; i < electronCount; i++) {
            float angle = i * (2 * M_PI / electronCount) + angleOffset;
            int electronX = centerX + radius * cos(angle);
            int electronY = centerY + radius * sin(angle);
            setcolor(BLUE);                          // Electron border color
            setfillstyle(SOLID_FILL, BLUE);                // Electron fill color
            fillellipse(electronX, electronY, 5, 5);           // Electron size
        }
    }
};
int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");
    setbkcolor(WHITE);
    cleardevice(); 
    int centerX = getmaxx() / 2;
    int centerY = getmaxy() / 2;
    Orbit* orbits[] = {
        new ElectronOrbit(centerX, centerY, 50, 2),               // First orbit with 2 electrons
        new ElectronOrbit(centerX, centerY, 100, 8),            // Second orbit with 8 electrons
        new ElectronOrbit(centerX, centerY, 150, 18)           // Third orbit with 18 electrons
    };
    float angle = 0.0;
    while (true) {
        cleardevice(); 
        //  nucleus
        setcolor(RED);
        setfillstyle(SOLID_FILL, RED);
        fillellipse(centerX, centerY, 20, 20);               // Nucleus size
        //  static orbits
        for (int i = 0; i < 3; i++) {
            orbits[i]->draw();
        }
        // Animate electrons
        for (int i = 0; i < 3; i++) {
            orbits[i]->animate(angle);
        }
        // Update the angle
        angle += 0.05;                         // Speed of revolution
        if (angle > 2 * M_PI) {
            angle -= 2 * M_PI;                 // Reset angle after a full revolution
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
    for (int i = 0; i < 3; i++) {
        delete orbits[i];
    }
    closegraph();
    return 0;
}
