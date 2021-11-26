#include "Player.hh"


/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME Sonic


struct PLAYER_NAME : public Player {

  /**
   * Factory: returns a new instance of this class.
   * Do not modify this function.
   */
  static Player* factory () {
    return new PLAYER_NAME;
  }

  /**
   * Types and attributes for your player can be defined here.
   */ 

  typedef vector<Cell> VC;
  typedef vector<VC> Grid;

  
  map<int, City> pos_cities;    //id_city -> vector<Pos> of the City
  map<int, Path> pos_paths;     //id path -> pair<pair<int,int>, vector<Pos>> where: <<id of org city, id of dest city>, vector<Pos> of the Path> 
  map<int, Pos> pos_units;      //id_unit -> pos of the unit     

  vector<int> units; 


  Grid table(const int rows(), VC(cols()));  //Matrix of the game_map
  /**
   * Methods.
   */ 

  //a-b distance (ignoring obstacles(walls,players,virus))
  int dist(const Pos &a, const Pos &b) {  
    return abs(a.i-b.i) + abs(a.j-b.j);
  }

  //Move one step
  Dir step (Pos dest, Pos act) {
    if (act.j < dest.j) return RIGHT;
    else if (act.j > dest.j) return LEFT;
    else if (act.i < dest.i) return BOTTOM;
    else if (act.i > dest.i) return TOP;
    else return NONE;
  }

  //bfs to a city
  void bfs_units(int id) {
  }
  

  /**
   * Play method, invoked once per each round.
   */
  virtual void play () {
  }

};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
