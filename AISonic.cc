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

  

  
  map<int, City> pos_cities;    //id_city -> vector<Pos> of the City
  map<int, Path> pos_paths;     //id path -> pair<pair<int,int>, vector<Pos>> where: <<id of org city, id of dest city>, vector<Pos> of the Path> 
  set<Pos> pos_walls; 
  map<int, Pos> pos_units;      //id_unit -> pos of the unit    

  vector<int> units; 



  /**
   * Methods.
   */ 

  //Do if round() == 0:
  //Initialize pos_units, pos_cities, pos_paths
  void initialize_all() {
    units = my_units(me());
    int n_units = units.size();
    for (int i = 0; i < n_units; ++i) {
      int id = units[i];
      Unit u = unit(id);
      Pos aux = u.pos;
      pos_units.insert(make_pair(id,aux));
    }

    for (int i = 0; i < rows(); ++i) {
      for (int j = 0; j < cols(); ++j) {
        Cell aux = cell(i,j);
        if (aux.city_id != -1) {
          City c = city(aux.city_id);
          pos_cities.insert(make_pair(aux.city_id,c));
        }
        else if (aux.path_id != -1) {
          Path p = path(aux.path_id);
          pos_paths.insert(make_pair(aux.path_id,p));
        }
        else if (aux.type == WALL) {
          Pos paux; paux.i = i; paux.j = j;
          pos_walls.insert(paux);
        }
      }
    }
  }




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
