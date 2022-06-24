#include <iostream>
#include <vector>
#include <queue>
#include <string.h>
#include "graph.h"
#include <chrono>



class ApplicationMain
{
    public:

    bool term;                              // terminate application
    int rows, cols, total,WIDTH,HEIGHT;     // Drawing variables
    float size;

    int key;                                // User input
    int goal;                               // Destination index

    char* mode = "";                        // Side Menu Variables
    float searchTime;
    int searchCount;
    int visitCount;
    float completed;                        // % Completed

    std::unordered_map<int,Node*> graph;    // map of all nodes
    

    ApplicationMain(int r, int c, int width, int height){
        
        rows = r;               
        cols = c*2;             // For this application, 1x2 maze dimensions are predetermined
        total  = rows*cols;
        
        WIDTH = width;
        HEIGHT = height;

        term = false;

        if (cols>rows*width/height){            // sizing cells to window
            size = width/cols;
        }
        else{
            size = height/rows;
        }

        FsOpenWindow(50,500,WIDTH,HEIGHT,1);    // Open window

        populateMap();                          // Fill map with emptry nodes of correct index
        markTreasure();                         // Determine end point
        generateMaze(markStart(0));             // Generate maze based off of start point

    }

    bool terminate()                            // Terminate function
    {
        return term;
    }

    void clearGraph()                           // Set up map for new search without generating new maze
    {
        for (auto [idx, node] : graph){
            node->bfsVisited = false;
            node->dfsVisited = false;
            node->path = false;
            node->parent = nullptr;
        }
        draw();
    }

    void populateMap(){                         // Fill map with nodes of correct index
        graph.clear();
        for (int i = 0; i<rows; ++i){
            for(int j = 0; j<cols; ++j){
                Node* curr = new Node(j*size,i*size,size,(cols*i)+j);
                //std::cout<<j*size<<"    "<<i*size<<"    "<<(cols*i)+j<<std::endl;
                graph[(cols*i)+j] = curr;
            }
        }

    }

    void generateMaze(Node* root, bool animate = false)               // Generate maze by removing appropriate walls
    {
        std::vector<char> temp;
        int randPick;
        char chosen;
        
        root->visited = true;                                           // Mark node as visited
        if(animate)
            draw();                                                     // View maze generation
                                                                        // GENERATE A VECTOR OF POSSIBLE PATHS
        if((root->left==nullptr) && ((root->index)%cols != 0)){         // if left is available
            temp.push_back('l');
        }

        if((root->right==nullptr)&&((root->index)%cols != cols-1)){     // if right is available
            temp.push_back('r');
        }

        if((root->up==nullptr)&&(root->index>=cols)){                   // if up is available
            temp.push_back('u');
        }

        if((root->down==nullptr)&&(root->index<(total-cols))){          // if down is available
            temp.push_back('d');
        }

        while(temp.size()!=0){                                          // Unitl all possible paths are taken

            randPick = rand()%temp.size();                              // Pick random path

            chosen = temp[randPick];                                    // Select Node at given path

            if ((chosen == 'l'))                                        // If left is chosen
            {
                root->left = graph[(root->index)-1];                    // find left node from map
                if (root->left->visited)                                // CHeck if already visited
                {
                    root->left = nullptr;                               // if visited, revert
                }
                else
                {
                    root->left->right = root;                           // if not, create return path
                    generateMaze(root->left,animate);                           // RECURSIVELY START with left node
                }
            }

            else if ((chosen == 'r'))                                   // If right chosen
            {
                root->right = graph[(root->index)+1];
                if (root->right->visited)
                {
                    root->right = nullptr;
                }
                else
                {
                    root->right->left = root;
                    generateMaze(root->right,animate);
                }

            }

            else if ((chosen == 'u'))                                    // If up chosen
            {
                root->up = graph[(root->index)-cols];
                if (root->up->visited)
                {
                    root->up = nullptr;
                }
                else
                {
                    root->up->down = root;
                    generateMaze(root->up,animate);
                }
            }

            else if ((chosen == 'd'))                                   // if down chosen
            {
                root->down = graph[(root->index)+cols];
                if (root->down->visited)
                {
                    root->down = nullptr;
                }
                else
                {
                    root->down->up = root;
                    generateMaze(root->down,animate);    
                }

            }
            temp.erase(temp.begin()+randPick);                          // Delete current path from vector
        }
            
    }


    bool dfsRecursive(Node* root, Node* dest, bool found = false)       // Recursive depth first search
    {

        root->dfsVisited = true;                            // Mark current node as visited
        draw();
        visitCount++;

        if (root == dest)                                   // if destination node found
        {
            visitCount--;
            return true;                                    // return true for "found" boolean
        }
        else if (!found){

            if((root->right != nullptr) &&(!root->right->dfsVisited)&&(!found)){        // check if walled, visited, or still searching
                found = dfsRecursive(root->right, dest, found);                         // found will be true only if destination is found
            }
            if((root->down != nullptr) &&(!root->down->dfsVisited)&&(!found)){
                found = dfsRecursive(root->down, dest, found);
            }
            if((root->left != nullptr) &&(!root->left->dfsVisited)&&(!found)){
                found = dfsRecursive(root->left, dest, found);
            }
            if((root->up != nullptr) &&(!root->up->dfsVisited)&&(!found)){
                found = dfsRecursive(root->up, dest, found);
            }
            

        }
        if(found){                          // only if node is found
            root->path = true;              // back track and paint the path to destination
            draw();
            searchCount ++; 
        }

        
        return found;           // return found boolean
    }



    void bfsQueue(Node* root, Node* dest)           // Breadth First Search with queue
    {
        std::queue<Node*> q;                        // first in first out queue
        visitCount = 0;
        searchCount = 0;
        //root->bfsVisited = true;
        q.push(root);                               // Push root initially
        Node* curr;                                 

        while(!q.empty())
        {
            curr = q.front();                       // access next element

            if (curr == dest){                      // break loop if destination is found
                break;
            }
            curr->bfsVisited = true;                // mark first node as visited
            visitCount++;

            draw();
            
            if((curr->right != nullptr)&&(!curr->right->bfsVisited)){       // Check if nullpointer and if already visited
                q.push(curr->right);                                        // Enqueue 
                curr->right->parent = curr;                                 // Set parent node to facilitate backtrack
            }
            if((curr->down != nullptr)&&(!curr->down->bfsVisited)){
                q.push(curr->down);
                curr->down->parent = curr;
            }
            if((curr->left != nullptr)&&(!curr->left->bfsVisited)){
                q.push(curr->left);
                curr->left->parent = curr;
            }
            if((curr->up != nullptr)&&(!curr->up->bfsVisited)){
                q.push(curr->up);
                curr->up->parent = curr;
            }

            q.pop();              // pop first element of queue
        }

        while(dest->parent!=nullptr)        // Paint path back to start
        {
            dest->path = true;
            draw();
            dest = dest->parent;
            searchCount++;
        }

    }


    void markTreasure(){                                // Mark destination cell red
        goal = rand() % total;                          // randomly chosen
        graph[goal]->treasure = true;
    }

    Node* markStart(int idx){                           // Return start node
        graph[idx]->start = true;                       // flag to paint green
        return graph[idx];
    }

    void drawMenu(){                                    // Draw Menu
        glColor3ub(82,183,223);

        glRasterPos2i(cols*size+5,20);                  // Mode
		char str[256];
		//sprintf(str,"%s", numWalls());
        sprintf(str,"Mode: %s", mode);
		YsGlDrawFontBitmap12x16(str);

        glRasterPos2i(cols*size+5,50);                  // Time
		sprintf(str,"Time: %f s", searchTime);
		YsGlDrawFontBitmap12x16(str);

        glRasterPos2i(cols*size+5,80);                  // How many cells visited?
        sprintf(str,"Visited: %d", visitCount);
		YsGlDrawFontBitmap12x16(str);

        glRasterPos2i(cols*size+5,110);                 // How many cells in return path
        sprintf(str,"Distance: %d", searchCount);
		YsGlDrawFontBitmap12x16(str);
        
        completed = 100 * (float)visitCount/(float)total;             // Percentage of total cells visited
        glRasterPos2i(cols*size+5,140);
        sprintf(str,"Percent: %.2f %%", completed);
		YsGlDrawFontBitmap12x16(str);

        completed = 100 * (float)searchCount/(float)visitCount;             // Percentage of total cells visited
        glRasterPos2i(cols*size+5,170);
        sprintf(str,"Efficiency: %.2f %%", completed);
		YsGlDrawFontBitmap12x16(str);

        glColor3ub(251,228,126);

        glRasterPos2i(cols*size+5,230);
        sprintf(str,"R       = Reset");
		YsGlDrawFontBitmap12x16(str);

        glRasterPos2i(cols*size+5,260);
        sprintf(str,"SHIFT+R = Draw Reset");
		YsGlDrawFontBitmap12x16(str);

        glRasterPos2i(cols*size+5,290);
        sprintf(str,"D       = DFS");
		YsGlDrawFontBitmap12x16(str);

        glRasterPos2i(cols*size+5,320);
        sprintf(str,"B       = BFS");
		YsGlDrawFontBitmap12x16(str);

        glRasterPos2i(cols*size+5,350);
        sprintf(str,"ESC     = Exit");
		YsGlDrawFontBitmap12x16(str);

        glRasterPos2i(cols*size+5,410);
        sprintf(str,"Rows     = %d",rows);
		YsGlDrawFontBitmap12x16(str);

        glRasterPos2i(cols*size+5,440);
        sprintf(str,"Cols     = %d",cols);
		YsGlDrawFontBitmap12x16(str);


    }

    void draw(){
        glClearColor(0.0,0.0,0.0,0.0);                          // Set background as black
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

        for (auto [ loc, node ] : graph) {                      // Draw every cell
            node->draw();
            }

        drawMenu();                                             // Draw menu

        FsSwapBuffers();
        FsSleep(10);
    }

    void run(){                                         // User input
        FsPollDevice();
        key = FsInkey();

        if (key == FSKEY_ESC){                          // Exit
            term = true;
            std::cout<<term<<std::endl;
        }   
        
        else if ((FsCheckKeyHeldDown()==FSKEY_SHIFT)){//&&(key == FSKEY_R)){
            clearGraph();
            populateMap();
            markTreasure();
            generateMaze(markStart(0),true);
        }
        
        
        else if (key == FSKEY_R){                       // Regenerate maze and destination cell
            clearGraph();
            populateMap();
            markTreasure();
            if(FsGetKeyState(FSKEY_SHIFT)==1)
                generateMaze(markStart(0),true);
            else
                generateMaze(markStart(0));
        }
        

        else if (key == FSKEY_D){                       // depth first search
            mode = "DFS";
            clearGraph();
            visitCount = 0;
            searchCount = 0;

            auto timeStart = std::chrono::high_resolution_clock::now();
            dfsRecursive(graph[0], graph[goal]);
            auto timeEnd = std::chrono::high_resolution_clock::now();
            std::chrono::duration<float> dur = timeEnd-timeStart;
            searchTime = dur.count();

        }

        else if (key == FSKEY_B){                                               // Breadth first search
            mode = "BFS";
            clearGraph();

            auto timeStart = std::chrono::high_resolution_clock::now();
            bfsQueue(graph[0], graph[goal]);
            auto timeEnd = std::chrono::high_resolution_clock::now();
            std::chrono::duration<float> dur = timeEnd-timeStart;
            searchTime = dur.count();
        }

        }

};
    