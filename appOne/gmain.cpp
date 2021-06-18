#include"libOne.h"
struct POS {
    float x, y, z;
};
void gmain() {
    window(1000, 1000, 1);

    int stopFlag = 1;
    int numCorners = 36;
    int numRings = numCorners / 2 + 1;
    int numVertices = numCorners * numRings;
    float deg = 360.0f / numCorners;
    angleMode(DEGREES);
    struct POS* op = new POS[numVertices];
    for (int j = 0; j < numRings; j++) {
        float r = sin(deg * j);
        float z = cos(deg * j);
        for (int i = 0; i < numCorners; i++) {
            int k = j * numCorners + i;
            op[k].x = sin(deg * i) * r;
            op[k].y = cos(deg * i) * r;
            op[k].z = z;
        }
    }
    

    struct POS* p = new POS[numVertices];

    deg = 0;
    int state = 0;
    while (notQuit) {
        float s = sin(deg);
        float c = cos(deg);
        if (isTrigger(KEY_SPACE))stopFlag = -stopFlag;
        if (stopFlag == 1) {
            deg += 1;
        }
        if (deg > 360) {
            deg = 0;
            ++state %= 2;
        }
        for (int i = 0; i < numVertices; i++) {
            if (state == 0) {
                p[i].x = op[i].x * c + op[i].z * -s;
                p[i].y = op[i].y;
                p[i].z = op[i].x * s + op[i].z * c;
            }
            else {
                p[i].x = op[i].x;
                p[i].y = op[i].y * c + op[i].z * -s;
                p[i].z = op[i].y * s + op[i].z * c;
            }


            p[i].z += 5;

            p[i].x /= p[i].z;
            p[i].y /= p[i].z;
        }
        
        clear(31, 30, 51);
        mathAxis(0.5);
        stroke(97, 250, 138, 127);
        for (int i = 0; i < numVertices; i++) {
            strokeWeight(5);
            //mathPoint(p[i].x, p[i].y);
            int j = i + 1;
            if (j % numCorners == 0)j -= numCorners;
            strokeWeight(1);
            mathLine(p[i].x, p[i].y, p[j].x, p[j].y);
            if (i < numVertices - numCorners) {
                j = i + numCorners;
                mathLine(p[i].x, p[i].y, p[j].x, p[j].y);
            }
        }


    }
    delete[]op;
    delete[]p;
}
