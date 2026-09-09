#include <stdio.h>
#include <graphics.h>
#include <math.h>

#define MAX_POINTS 4500

//Int coordinates for initial points
typedef struct {
    int x;
    int y;
} Point;

//Create float point for more precise calculation on Chaikin cuts
typedef struct {
    float x;
    float y;
} FPoint;

//Make a function that draws a polygon, convert the points to integers for smooth drawing
void drawPolygon(FPoint points[], int n) {
    for (int i = 0; i < n; i++) {
        int next = (i + 1) % n; //Make sure that the last vertex of polygon is attached to first one, closing the polygon
        line((int)round(points[i].x), (int)round(points[i].y),
             (int)round(points[next].x), (int)round(points[next].y));
    }
}

void Chaikin(Point input[], int n, int iterations, float higher_ratio, float lower_ratio) {
    FPoint original[MAX_POINTS];
    FPoint next[MAX_POINTS * 2];
    int original_size = n;

    //Convert input to floating-point
    for (int i = 0; i < n; i++) {
        original[i].x = (float)input[i].x;
        original[i].y = (float)input[i].y;
    }

    //Draw original polygon in white
    setcolor(COLOR(255, 255, 255));
    drawPolygon(original, original_size);
    delay(500);

    for (int iter = 0; iter < iterations; iter++) {
        int next_index = 0;
        setcolor(COLOR(150, 0, 0));
        
        for (int i = 0; i < original_size; i++) {
            int next_i = (i + 1) % original_size;
            
            //Convert original int point to float and apply Chaikin proportions
            FPoint p1 = {
                .x = higher_ratio * original[i].x + lower_ratio * original[next_i].x,
                .y = higher_ratio * original[i].y + lower_ratio * original[next_i].y
            };
            FPoint p2 = {
                .x = lower_ratio * original[i].x + higher_ratio * original[next_i].x,
                .y = lower_ratio * original[i].y + higher_ratio * original[next_i].y
            };
            
            //Save new points
            next[next_index++] = p1;
            next[next_index++] = p2;
        }

        original_size = next_index;
        for (int i = 0; i < original_size; i++) {
            original[i] = next[i];
        }
        
        //Draw each iteration for visualization in darker red
        drawPolygon(original, original_size);
        delay(500);
    }

    //Draw final smoothed polygon in yellow
    setcolor(COLOR(255, 255, 0));
    drawPolygon(original, original_size);
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    //Define the shape to apply Chaikin to
    
	//Square
	Point poly[] = {
        {100, 100}, {400, 100},
        {400, 400}, {100, 400}
        
    };
    
    //Triangle
//    Point poly[] = {
//    {250, 200},
//    {250 - 100, 350},
//    {250 + 100, 350}
//    };
    
    //Pentagon
//    Point poly[] = {
//    {250, 125},
//    {358, 200},
//    {325, 325},
//    {175, 325},
//    {142, 200}
//    };
    
    
	int n = sizeof(poly)/sizeof(poly[0]); //Calculate number of vertices in the polygon

    Chaikin(poly, n, 5, 0.8, 0.2); //Number of iterations(MAX 10 with starting amount of MAX_POINTS) and ratios

    getch();
    closegraph();
    return 0;
}
