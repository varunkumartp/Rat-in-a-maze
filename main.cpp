#include <iostream>
#include <cstring>
#include <stack>

using namespace std;

#define N 10            // Column size of maze
#define M 10            // Row size of maze

int n = N , m = M;       // maze of n*m matrix
int ix=0,iy=0;          // initial position of rat
int fx=9,fy=0;          // coordinates of food
bool visited[N][M];     // Matrix to represent visited coordinates

class node              // Node class to represent coordinates
{
public:
    int x, y;

    node(int i=0, int j=0)  //Constructor
    {
        x = i;
        y = j;
    }
};

void printstack(stack<node> s) // Function to print contents of stack
{
    if (s.empty())             // If stack is empty then return
        return;
    node c = s.top();
    s.pop();                   // Pop the top element of the stack
    printstack(s);             // Recursively call the function PrintStack
    cout<<"("<<c.x<<","<<c.y<<")"<<endl;
    s.push(c);                 // Push the same element onto the stack to preserve the order
}

bool isReachable(int maze[N][M])  // Function to find path in maze
{
    int i = ix, j = iy;           // Initial position of rat in maze
    node temp(i, j);              // Create an object temp
    stack<node> s;                // Create stack s of type node
    s.push(temp);                 // Push node temp to stack

    while (!s.empty())
    {
        temp=s.top();
        i=temp.x,j=temp.y;        // Stores current position of rat
        if(i==fx && j==fy)       // Checks if current position is equal to food coordinates
        {
            printstack(s);        // Prints the contents of stack
            return true;
        }
        if(j+1<m && visited[i][j+1] && maze[i][j+1])       //RIGHT
        {
            node temp1(i,j+1);      // creates an object with coordinates of node in the right
            s.push(temp1);          // Stores the coordinates in stack
            visited[i][j+1]=false;  // Stores false to indicate coordinates is visited
        }
        else if(i+1<n && visited[i+1][j] && maze[i+1][j])  //DOWN
        {
            node temp1(i+1,j);      // creates an object with coordinates of node below
            s.push(temp1);          // Stores the coordinates in stack
            visited[i+1][j]=false;  // Stores false to indicate coordinates is visited
        }
        else if(i-1>=0 && visited[i-1][j] && maze[i-1][j]) //UP
        {
            node temp1(i-1,j);      // creates an object with coordinates of node above
            s.push(temp1);          // Stores the coordinates in stack
            visited[i-1][j]=false;  // Stores false to indicate coordinates is visited
        }
        else if(j-1>=0 && visited[i][j-1] && maze[i][j-1]) //LEFT
        {
            node temp1(i,j-1);      // creates an object with coordinates of node in the left
            s.push(temp1);          // Stores the coordinates in stack
            visited[i][j-1]=false;  // Stores false to indicate coordinates is visited
        }
        else    // If there is no path, rat goes to previous coordinates
        {
            visited[temp.x][temp.y]=false;
            s.pop();
        }       
    }
    return false;   // If the stack is empty and no path is found return false.
}

int main()  //Main function
{
    // Initially setting the visited array to true (unvisited)
    memset(visited, true, sizeof(visited));

    // Maze matrix
    int maze[N][M] = {
        {1, 1, 0, 0, 1, 0, 0, 1, 0, 1},
        {0, 1, 0, 1, 1, 1, 1, 0, 1, 0},
        {1, 1, 0, 1, 1, 0, 1, 1, 1, 1},
        {0, 1, 0, 0, 1, 0, 1, 0, 1, 0},
        {1, 1, 1, 1, 1, 0, 0, 0, 1, 1},
        {1, 0, 0, 0, 1, 1, 1, 0, 0, 1},
        {0, 0, 1, 1, 0, 0, 0, 0, 1, 1},
        {1, 1, 1, 0, 1, 1, 1, 0, 1, 0},
        {1, 0, 1, 0, 1, 0, 1, 1, 1, 1},
        {1, 0, 1, 1, 1, 0, 0, 0, 1, 1},
        };

    if (isReachable(maze))              // Checks if path is available
        cout << "Path Found!" << '\n';
    else                                // If path is not available
        cout << "No Path Found!" << '\n';

    return 0;
}