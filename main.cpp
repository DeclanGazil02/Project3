#include <time.h>  
#include <string>
#include<unordered_set>
#include <cmath>
//for graph
#include "Bridges.h"
#include "GraphAdjList.h"
//for data
#include "DataSource.h"
#include "data_src/Game.h"
//our created Datastrucutres
#include "HashTable.h"
#include "MaxHeap.h"

using namespace std;
using namespace bridges;

string tostring (float value) {
    int result = (value * 10);
    string ans = to_string(result);
    if (result == 100) {
        ans = "10.0";
    }
    else {
        ans.insert(1,".");
    }
    return ans;
} //to round to the first decimal place

void displayMenu(){
  std::cout << R"( 
 __________________________________________________________________________________
             _______             _ _ _              ______ _                       
     /\     |  ____|            (_) (_)            |  ____| |                      
    /  \    | |__ __ _ _ __ ___  _| |_  __ _ _ __  | |__  | | __ ___   _____  _ __ 
   / /\ \   |  __/ _` | '_ ` _ \| | | |/ _` | '__| |  __| | |/ _` \ \ / / _ \| '__|
  / ____ \  | | | (_| | | | | | | | | | (_| | |    | |    | | (_| |\ V / (_) | |   
 /_/    \_\ |_|  \__,_|_| |_| |_|_|_|_|\__,_|_|    |_|    |_|\__,_| \_/ \___/|_|  
 __________________________________________________________________________________
)" << '\n';
  cout << "Color Rating System"  << endl;
  cout << "purple:1 pink:2 limegreen:3 cyan:4 white:5 red:6 blue:7 green:8 yellow:9 orange:10" << endl << endl;
  cout << "0: Exit program." << endl;
  cout << "1: Load all games, coorelate between rating and genre." << endl;
  cout << "2: Load all games, coorelate between rating and platform." << endl;
  cout << "3: Load a specific genre." << endl;
  cout << "4: Load a specific platform." << endl;
  cout << "5: Load a specific game" << endl;
  cout << "6: Cluster by ratings." << endl;
  cout << "7: Load top N highest rated games" << endl;
}

int main(int argc, char **argv) {
  const double MAX_VERTEX_SIZE = 50.0;
  const double VERTEX_SIZE_CONST = 4.5;
  bool isPlaying = true;
  int userInput;
  int lowestRanking;
  unordered_set<string> titles;
  
  vector<string> platforms = {"Game.Com", "Lynx", "Nintendo 64", "DVD / HD Video Game", "WonderSwan", "Dreamcast", "Game Boy Advance", "GameCube", "Vectrex", "Game Boy", "NeoGeo Pocket Color", "Sega CD", "Atari 2600", "N-Gage", "NeoGeo", "Windows Phone", "Nintendo 3DS", "WonderSwan Color", "iPad", "iPod", "Xbox 360", "TurboGrafx-16", "Macintosh", "Wii U", "PlayStation 4", "TurboGrafx-CD", "PlayStation Vita", "Sega 32X", "PC", "iPhone", "Xbox One", "Wireless", "PlayStation", "Linux", "PlayStation Portable", "Android", "Commodore 64/128", "PlayStation 2", "Game Boy Color", "Super NES", "Wii", "Nintendo 64DD", "Pocket PC", "Windows Surface", "Nintendo DS", "PlayStation 3", "Nintendo DSi", "Dreamcast VMU", "Atari 5200", "Web Games", "Saturn", "Arcade", "NES", "Xbox", "Master System", "Genesis"};
  
  vector<string> genres = {"Compilation", "Action", "Board", "Sports", "Party", "Adventure", "Simulation", "Fighting", "Pinball", "Hunting", "RPG", "Racing", "Strategy", "Card", "Trivia", "Platformer", "Wrestling", "Virtual Pet", "Baseball", "None", "Battle", "Casino", "Flight", "Puzzle", "Educational", "Shooter", "Adult", "Music", "Productivity", "Other"};
  
  vector<string> ratings = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10"};
  vector<string> colors = {"purple", "pink", "limegreen", "cyan", "white", "red", "blue", "green", "yellow", "orange"};

  //introductory statement
  cout << "Welcome to A Familiar Flavor, where we aim to help you tackle the broad and confusing world of gaming." << endl << "Please insert the lowest ranking of game you would like to view:";
  cin >> lowestRanking;
  cout << endl;
  
  while(isPlaying){
    //load bridges graph and data source
    Bridges bridges (1, "DeclanGazil", "1387522173459");
    GraphAdjList<string> graph;
    bridges.setTitle("IGN Game Data");
	  DataSource ds (&bridges);
	  vector<Game> game_list = ds.getGameData();
    
    //create hashtable and time
    cout << "Time for Hash Table insertion of games: ";
    clock_t t;
    t = clock();
    HashTable hashList(game_list);
    t = clock() - t;
    cout << t << " ticks or " << float(t)/CLOCKS_PER_SEC << " seconds." << endl;
    //create max heap and time
    MaxHeap maxHeap;
    cout << "Time for Max Heap insertion of games: ";
    t = clock();
    for(int i = 0; i < game_list.size(); i++){
      maxHeap.insertGame(game_list[i]);
    }
    cout << t << " ticks or " << float(t)/CLOCKS_PER_SEC << " seconds." << endl;

    
    //for switch statement
    string tempGenre;
    string displayInfo;
    string userGenre;
    string userPlatform;
    string userTitle;
    string ratingValue;
    string vertex;
    string colorTemp;
    int userNum;
    int colorValue;
    
    bool genreFound;
    bool platformFound;
    Game userGame;
    Game tempGame;

    displayMenu();
    cin >> userInput;
    
      switch(userInput){
      case 0:
        cout << "Exit program." << endl;
        isPlaying = !isPlaying;
      break;
      case 1://generate different colors and spread out
        bridges.setDescription("Load all games, coorelate between rating and genre.");
        //add all genres as base vertices
        for(int i = 0; i < genres.size(); i++){
          graph.addVertex(genres[i]);
          graph.getVertex(genres[i])->setSize(MAX_VERTEX_SIZE);
          graph.getVertex(genres[i])->setColor("black");
        }
        
        //add all games to respective genre, size changing based off rating
        for(int i = 0; i < game_list.size(); i++){
            if(game_list[i].getRating() >= lowestRanking){
              tempGenre = game_list[i].getGameGenre()[0];
              displayInfo = game_list[i].getTitle() + ": " + tostring(game_list[i].getRating()) + " " + game_list[i].getPlatformType() + 
" " + tempGenre;
          
              graph.addVertex(displayInfo);
              graph.addEdge(displayInfo,tempGenre);
              graph.getVertex(displayInfo)->setSize(game_list[i].getRating() * VERTEX_SIZE_CONST);
            //set color based on rating
            colorValue = int(ceil(game_list[i].getRating())) - 1;
            graph.getVertex(displayInfo)->setColor(colors[colorValue]);
            }
        }
        bridges.setDataStructure(&graph);
        bridges.visualize();
      break;

        case 2:
        bridges.setDescription("Load all games, coorelate between rating and platform.");
        //add all platforms as base vertices
        for(int i = 0; i < platforms.size(); i++){
          graph.addVertex(platforms[i]);
          graph.getVertex(platforms[i])->setSize(MAX_VERTEX_SIZE);
          graph.getVertex(platforms[i])->setColor("black");
        }
          
        //add all games to respective platform, size changing based off rating
        for(int i = 0; i < game_list.size(); i++){
          if(game_list[i].getRating() >= lowestRanking){
            tempGenre = game_list[i].getGameGenre()[0];
            displayInfo = game_list[i].getTitle() + ": " + tostring(game_list[i].getRating()) + " " + game_list[i].getPlatformType() + 
" " + tempGenre;
          
            graph.addVertex(displayInfo);
            graph.addEdge(displayInfo,game_list[i].getPlatformType());
            graph.getVertex(displayInfo)->setSize(game_list[i].getRating() * VERTEX_SIZE_CONST);
            //set color based on rating
            colorValue = int(ceil(game_list[i].getRating())) - 1;
            graph.getVertex(displayInfo)->setColor(colors[colorValue]);
        }
          }
        bridges.setDataStructure(&graph);
        bridges.visualize();
      break;
         
      case 3:
        cout << "Please input a genre." << endl;
        bridges.setDescription("Load a specific genre.");
        cin.get();
        getline(cin, userGenre);
        
        genreFound = false;
        //search to see if that genre exists
        for(int i = 0; i < genres.size(); i++){
          if(genres[i] == userGenre)
              genreFound = true;
        }
        if(!genreFound){ 
          cout << "Genre not found." << endl;
        }
        else{
          //add that genre as a base vertex
          graph.addVertex(userGenre);
          graph.getVertex(userGenre)->setSize(MAX_VERTEX_SIZE);
          graph.getVertex(userGenre)->setColor("black");

          //go through the list of games and all games with user genre
          for(int i = 0; i < game_list.size(); i++){
            if(game_list[i].getGameGenre()[0] == userGenre && game_list[i].getRating() >= lowestRanking){
              tempGenre = game_list[i].getGameGenre()[0];
              displayInfo = game_list[i].getTitle() + ": " + tostring(game_list[i].getRating()) + " " + game_list[i].getPlatformType() + 
" " + tempGenre;
              
              graph.addVertex(displayInfo);
              graph.getVertex(displayInfo)->setSize(game_list[i].getRating() * VERTEX_SIZE_CONST);
              
              //set color based on rating
              colorValue = int(ceil(game_list[i].getRating())) - 1;
              graph.getVertex(displayInfo)->setColor(colors[colorValue]);
              graph.addEdge(displayInfo,userGenre);
            }
          }
          bridges.setDataStructure(&graph);
          bridges.visualize();
        }
      break;
      case 4:
        bridges.setDescription("Load a specific platform.");
        cout << "Please input a platform." << endl;
        //get userInput
        cin.get();
        getline(cin, userPlatform);
        platformFound = false;
        //search to see if input platform is valid
        for(int i = 0; i < platforms.size(); i++){
          if(platforms[i] == userPlatform)
            platformFound = true;
        }
        if(!platformFound){
            cout << "Platform not found." << endl;
        }

        else{
        //add base vertex
          graph.addVertex(userPlatform);
          graph.getVertex(userPlatform)->setSize(MAX_VERTEX_SIZE);
          graph.getVertex(userPlatform)->setColor("black");

          //add all games with that platform
          for(int i = 0; i < game_list.size(); i++){
            if(game_list[i].getPlatformType() == userPlatform && game_list[i].getRating() >= lowestRanking){
              tempGenre = game_list[i].getGameGenre()[0];
              displayInfo = game_list[i].getTitle() + ": " + tostring(game_list[i].getRating()) + " " + game_list[i].getPlatformType() + 
" " + tempGenre;
              
              graph.addVertex(displayInfo);
              graph.getVertex(displayInfo)->setSize(game_list[i].getRating() * VERTEX_SIZE_CONST);
              
              //set color based on rating
              colorValue = int(ceil(game_list[i].getRating())) - 1;
              graph.getVertex(displayInfo)->setColor(colors[colorValue]);
              graph.addEdge(displayInfo,userPlatform);
            }
          }
          bridges.setDataStructure(&graph);
          bridges.visualize();
        }
      break;
        
      case 5:
        bridges.setDescription("Load a specific game.");
        cout << "Please input a title." << endl;
        cin.get();
        getline(cin, userTitle);

        //hashList search
        cout << "Time for Hash Table search of specific title: ";
        t = clock();
        userGame = hashList.Find(userTitle);
        t = clock() - t;
        cout << t << " ticks or " << float(t)/CLOCKS_PER_SEC << " seconds." << endl;

        //goes through max heap till found
        cout << "Time for Max Heap search of specific title: ";
        t = clock();
        while (true) {
          if (maxHeap.getSize() == 0) {
            break;
          }
          if (maxHeap.removeTop().getTitle() == userTitle) {
            break;
          }
        }
        cout << t << " ticks or " << float(t)/CLOCKS_PER_SEC << " seconds." << endl;

          if(userGame.getTitle() == userTitle){ //see if title exists
            tempGenre = userGame.getGameGenre()[0];
            displayInfo = userGame.getTitle() + ": "  + tostring(userGame.getRating()) + " " + userGame.getPlatformType() + " " + tempGenre;
            
            graph.addVertex(displayInfo);
            graph.getVertex(displayInfo)->setSize(MAX_VERTEX_SIZE);
            colorValue = int(ceil(userGame.getRating())) - 1;
            graph.getVertex(displayInfo)->setColor(colors[colorValue]);
            bridges.setDataStructure(&graph);
            bridges.visualize();
          }
          else //if the title does not exist in the data set
            cout << "Game not found." << endl;
      break;
      case 6:
        bridges.setDescription("Cluster by ratings.");
        //make vertices for all game ratings 
          for(int i = 0; i < ratings.size(); i++){
            ratingValue = ratings[i];
            ratingValue.append(" and below");
            graph.addVertex(ratingValue);
            colorTemp = colors[i];
            graph.getVertex(ratingValue)->setSize(MAX_VERTEX_SIZE);
            graph.getVertex(ratingValue)->setColor("black");
          }
        //add all games to the respective ratings 
          for(int i = 0; i < game_list.size(); i++){
            if(game_list[i].getRating() >= lowestRanking){
              tempGenre = game_list[i].getGameGenre()[0];
              displayInfo = game_list[i].getTitle() + ": " + tostring(game_list[i].getRating()) + " " + game_list[i].getPlatformType() + 
" " + tempGenre;
              graph.addVertex(displayInfo);
              graph.getVertex(displayInfo)->setSize(game_list[i].getRating() * VERTEX_SIZE_CONST);
              //set color based on rating
              vertex = ratings[ceil(game_list[i].getRating()) - 1] + " and below";
              colorValue = int(ceil(game_list[i].getRating())) - 1;
              graph.getVertex(displayInfo)->setColor(colors[colorValue]);
              graph.addEdge(displayInfo, vertex);
              }
            }
        bridges.setDataStructure(&graph);
        bridges.visualize();
      break;
      case 7:
        cout << "Insert number of games to retrieve up to 17,534" << endl;
        cin >> userNum;
        bridges.setDescription("Load top " + to_string(userNum) + " games.");
        vertex = "Top " + to_string(userNum) + " games";
        graph.addVertex(vertex);
        graph.getVertex(vertex)->setSize(MAX_VERTEX_SIZE);
        graph.getVertex(vertex)->setColor("black");
        for(int i = 0; i < userNum; i++){ //need to change on whether we are retirieving game object or title
          tempGame = maxHeap.removeTop();
          tempGenre = tempGame.getGameGenre()[0];
          displayInfo = tempGame.getTitle() + ": " + tostring(tempGame.getRating()) + " " + tempGame.getPlatformType() + " " + tempGenre;
          graph.addVertex(displayInfo);
          graph.getVertex(displayInfo)->setSize(tempGame.getRating() * VERTEX_SIZE_CONST);
          colorValue = int(ceil(tempGame.getRating())) - 1;
          graph.getVertex(displayInfo)->setColor(colors[colorValue]);
          graph.addEdge(displayInfo,vertex);
        }
        bridges.setDataStructure(&graph);
        bridges.visualize();
        break;
      default:
      cout << "Unrecognized input." << endl;
      break;
    }//end of switch
  }//end of while

  
  cout << "Thank you for participating!" << endl;
	return 0;
}//end of main




