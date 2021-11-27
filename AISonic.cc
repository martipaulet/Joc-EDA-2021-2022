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

  typedef vector<int> VI;
  typedef vector<VI>  VVI;

  typedef vector<bool> VB;
  typedef vector<VB> VVB; //matriz booleanos
  
  map<int, City> pos_cities;    //id_city -> vector<Pos> of the City
  map<int, Path> pos_paths;     //id path -> pair<pair<int,int>, vector<Pos>> where: <<id of org city, id of dest city>, vector<Pos> of the Path> 
  set<Pos> pos_walls;           //walls Pos
  map<int, Pos> pos_units;      //id_unit -> pos of the unit    
  vector<int> units;            //vector containing id of all my_units
  
  int movx[4] = {-1,1,0,0};
  int movy[4] = {0,0,-1,1};

  /**
   * Methods.
   */ 

  //(APPROVED) may not be necessary!!!
  //Do if round() == 0:
  //Initialize pos_units, pos_cities, pos_paths, pos_walls
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

  // (APPROVED)
  //a-b distance (ignoring obstacles(walls,players,virus))
  int dist(const Pos &a, const Pos &b) {  
    return abs(a.i-b.i) + abs(a.j-b.j);
  }

  //(APPROVED)
  //Move one step
  Dir step (Pos dest, Pos act) {
    if (act.j < dest.j) return RIGHT;
    else if (act.j > dest.j) return LEFT;
    else if (act.i < dest.i) return BOTTOM;
    else if (act.i > dest.i) return TOP;
    else return NONE;
  }

  //bfs to a city: (APPROVED)
  //returns the distance to the closest city (not conquered) or -1 otherwise
  pair<pair<int,int>,int> bfs_units(int id) {                               
    VVB vis(rows(), VB(cols(), false));   //visited_positions matrix
    Unit u = unit(id);
    queue <pair<pair<int, int>, int> > q; //pos(i,j) and distance d 
    q.push(make_pair(make_pair(u.pos.i,u.pos.j),0));
    int x,y,d;
    while(not q.empty()) {                         
      x = q.front().first.first;       
      y = q.front().first.second;     
      d = q.front().second;           //distance
      q.pop();
      if (not vis[x][y]) {
        vis[x][y] = true;
        Cell c = cell(x,y);
        if (c.type == CITY) {
          int aux = c.city_id;
          if (city_owner(aux) != me()) return make_pair(make_pair(x,y),d);
        }
        for (int i = 0; i < 4; ++i) {
          c = cell(x+movx[i],y+movy[i]);
          if (c.type != WALL) q.push(make_pair(make_pair(x+movx[i],y+movy[i]),d+1));
        }
      }
    }
    return make_pair(make_pair(u.pos.i,u.pos.j),-1);  //error return
  }

  //obtenerruta bfs: https://jariasf.wordpress.com/2012/02/27/algoritmo-de-busqueda-breadth-first-search/
  
  

  /**
   * Play method, invoked once per each round.
   */
  virtual void play () {
    if (round() == 0) initialize_all();
    int n_units = units.size();
    for (int i = 0; i < n_units; ++i) {}
      pair<pair<int,int>,int> p = bfs_units(units[i]);
  }
  }
};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
