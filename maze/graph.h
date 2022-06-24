#include <unordered_map>
#include "fssimplewindow.h"
#include <stdlib.h>
#include <ysglfontdata.h>

class Node{

    public:
    Node* left = nullptr;           // directional nodes
    Node* right = nullptr;
    Node* up = nullptr;
    Node* down = nullptr;

    Node* parent = nullptr;         // parent used to backtrack bfs

    int locx, locy, index;                  // used to draw cells
    int cellSize;

    bool visited, treasure, start;          // flags to color and mark cells
    bool dfsVisited, bfsVisited, path;      

    Node(float x, float y, float size, int idx)
    {
        locx = x;                       // position
        locy = y;

        index = idx;                    // index

        cellSize = size;                // pixel cell size

        visited = false;                // set all flags to false
        treasure = false;
        start = false;
        dfsVisited  = false;
        bfsVisited = false;
        path = false;
    }

    void draw()
    {
        if(visited)
            glColor3ub(20,108,164);         // Dark blue
        else
            glColor3ub(0,0,0);              // Black

        if(dfsVisited||bfsVisited)          
            glColor3ub(82,183,233);         // Light blue
        if(path)
            glColor3ub(251,228,126);        // Yellow
        if(start)
            glColor3ub(99,250,187);         // Green
        if(treasure)
            glColor3ub(235,76,60);          // Red

        
        glBegin(GL_TRIANGLES);              // fill cell
        
        glVertex3f(locx,locy,0);
        glVertex3f(locx+cellSize,locy+cellSize,0.0);
        glVertex3f(locx,locy+cellSize,0.0);

        glVertex3f(locx,locy,0);
        glVertex3f(locx+cellSize,locy+cellSize,0.0);
        glVertex3f(locx+cellSize,locy,0.0);

        glEnd();

        glColor3ub(0,0,0);
        glLineWidth(2);

        glBegin(GL_LINES);                  // draw walls
        if (left == nullptr){
            glVertex3f(locx,locy,0.0);
            glVertex3f(locx,locy+cellSize,0.0);
        }
        if (down == nullptr){
            glVertex3f(locx,locy+cellSize,0.0);
            glVertex3f(locx+cellSize,locy+cellSize,0.0);
        }
        if (right == nullptr){
            glVertex3f(locx+cellSize,locy+cellSize,0.0);
            glVertex3f(locx+cellSize,locy,0.0);
        }

        if (up == nullptr){
            glVertex3f(locx+cellSize,locy,0.0);
            glVertex3f(locx,locy,0.0);
        }

        glEnd();

        //drawIdx();                    // Draw index if needed
        //drawWallCount();              // Draw wall count if needed
        
    }

    void drawIdx()
    {
        glColor3ub(50,50,50);                   
        glRasterPos2i(locx,locy+cellSize-1);
		char str[256];
		sprintf(str,"%d", index);
		YsGlDrawFontBitmap12x16(str);
    }

    void drawWallCount(){
        glColor3ub(50,50,50);
        glRasterPos2i(locx,locy+cellSize-1);
		char str[256];
		sprintf(str,"%d", numWalls());
		YsGlDrawFontBitmap12x16(str);
    }

    int numWalls(){
        int count = 0;
        if (right == nullptr)
            count++;
        if (down == nullptr)
            count++;
        if (left == nullptr)
            count++;
        if (up == nullptr)
            count++;
        return count;
    }

};
