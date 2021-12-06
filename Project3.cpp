
#include <iostream>
#include <map>
#include <iterator>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

class Graph
{
private:
    map<long, vector<pair<long, unsigned int>>> adjList;
    vector<pair<float, float>> locations;
public:
    Graph();
    void parseUsers();
    void parseLocations();
    void addEdge(map <long, vector<pair<long, unsigned int>>> &adjList, long u, long v);
};

Graph::Graph()
{
    parseLocations(); 
    parseUsers();
}
//Takes in the file of locations and places into a vector called locations
void Graph::parseLocations()
{
    string line;
    string x;
    float lat;
    float longitude;
    

    ifstream locFile("1_million_location.txt");
    if (locFile.is_open()) {
        while (getline(locFile, line))
        {
            vector<string> coordinates;
            stringstream input(line);
            //puts the two coordinates into a temporary vector
            while (getline(input, x, ','))
            {
                coordinates.push_back(x);
            }

            lat = stof(coordinates[0]);
            longitude = stof(coordinates[1]);

            this->locations.push_back(make_pair(lat, longitude));
        }
    }
}
//Takes in the file of users. Parses each line and connects the users in an adjacency list (which is a map of vectors)
void Graph::parseUsers()
{
    string user;
    long userNum;
    long firstUser;
    
    string line;
    ifstream userFile("1_million_user.txt");
    if (userFile.is_open())
    {
        while (getline(userFile, line))
        {
            long count = 0;
            bool moreVertices = true;
            while (moreVertices)
            {
                //To get the first user in the line that the rest connect to
                if (line.find(",") != std::string::npos && count == 0)
                {
                    int position = line.find(",");
                    user = line.substr(0, position);
                    line = line.substr(position + 2);
                    firstUser = stol(user);
                    count++;
                }
                //connects the rest of the users to the first user
                else if (line.find(",") != std::string::npos)
                {
                    int position = line.find(",");
                    user = line.substr(0, position);
                    line = line.substr(position + 2);
                    userNum = stol(user);
                    addEdge(this->adjList, firstUser, userNum);
                }
                //connects the last user of the line
                else
                {
                    userNum = stol(line);
                    addEdge(this->adjList, firstUser, userNum);
                    moreVertices = false;
                }
            }
        }
    }
}

//Connects two vertices and how far they are apart. Adds to adjacency list
void Graph::addEdge(map <long, vector<pair<long, unsigned int>>> &adjList, long from, long to)
{
    unsigned int distance = 0;//Change this to the distance function

    //Checks to see if the vertex(from) already exists. If it does, it adds the new connected vertex(to)
    if (adjList.find(from) != adjList.end())
        adjList.find(from)->second.push_back(make_pair(to, distance));

    //If the vertex(from) does not exist, it creates it and adds its connected vertex (to)
    else
    {
        vector <pair<long, unsigned int>> temp;
        temp.push_back(make_pair(to, distance));
        adjList.emplace(from, temp);
    }

    //If the connected vertex(to) does not exist, it is added
    if (adjList.find(to) == adjList.end())
    {
        vector <pair<long, unsigned int>> temp;
        temp.push_back(make_pair(-1, 0));
        adjList.emplace(to, temp);
    }
        
}
int main()
{
    Graph myGraph;
    
}

