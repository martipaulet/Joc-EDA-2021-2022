#include "Player.hh"


/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME Sonic_v1


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
  typedef vector<VB> VVB;     //matriz booleanos


  /**
   * Methods.
   */ 


  //moves the unit with identifier id to pos dest at distance d 
  void move_unit (int id, VVI &VP, int d, Pos &dest) {
    Dir next_move = NONE;
    int aux = d;
    for (int i = 0; i <= aux; ++i) {
      next_move = find_next_move(dest,d,VP);
      --d;
    }     
    move(id,next_move);                    
  }


  //Returns the move to do from the position a to the original pos (going backwards) to know the movement the unit has to do  
  Dir find_next_move(Pos &a, int d, VVI &VP) {
    //CHECK TOP
    if (pos_ok((a.i)-1,a.j) and VP[(a.i)-1][a.j] == d) {        
      a += TOP;
      return BOTTOM;
    }
    //CHECK BOTTOM
    else if (pos_ok((a.i)+1,a.j) and VP[(a.i)+1][a.j] == d) {   
      a += BOTTOM;
      return TOP;
    }
    //CHECK RIGHT
    else if (pos_ok(a.i,(a.j)+1) and VP[a.i][(a.j)+1] == d) {   
      a += RIGHT;
      return LEFT; 
    }
    //CHECK LEFT
    else if (pos_ok(a.i,(a.j)-1) and VP[a.i][(a.j)-1] == d) {  
      a += LEFT;
      return RIGHT;
    }
    return NONE;
  }


  //bfs  (APPROVED)
  void bfs_units(int id) {                               
    VVI VP(rows(),VI(cols(),-1));                                               //BOARD
    queue <pair<pair<int, int>, int> > q;                                       //QUEUE CONTAINING POSITIONS (i,j) AT DISTANCE D
    int movx[4] = {-1,1,0,0};                                                   //CHECK SURROUNDING VECTORS
    int movy[4] = {0,0,-1,1};
    Unit u = unit(id);                                                          //ORIGINAL POS AT DISTANCE 0
    q.push(make_pair(make_pair(u.pos.i,u.pos.j),0));                            
    int x,y,d;
  
    while(not q.empty()) {                         
      x = q.front().first.first;                                                //CURRENT POSITION (on the bfs search)
      y = q.front().first.second;     
      d = q.front().second;                                                     //DISTANCE TO THE UNIT POS
      q.pop();

      if (VP[x][y] == -1) {                                                     //IF NOT VISITED
        VP[x][y] = d;                                                           //MARK AS VISITED AT DISTANCE D OF THE UNIT POSITION

        for (int i = 0; i < 4; ++i) {                                           //CHECK_SURROUNDINGS (top,bottom,left,right) (fer funcio int distance_to_a_path_or_city)
          Cell c = cell(x+movx[i],y+movy[i]);
          if (c.type != WALL) {
            if (c.type == CITY or c.type == PATH) {                             //CITY OR PATH FOUND AT DISTANCE D+1
              int aux = c.city_id;
              int aux2 = c.path_id;
              if ((aux != -1 and city_owner(aux)!= me()) or (aux2 != -1 and path_owner(aux2) != me())) {
                Pos dest;   dest.i = x+movx[i];   dest.j = y+movy[i];                        
                move_unit (id, VP, d, dest);                                                           
                return;
              }
            }
          q.push(make_pair(make_pair(x+movx[i],y+movy[i]),d+1));
          }
        }
      }
    }
    return;                                                                      //error return
  }


  /**
   * Play method, invoked once per each round.
   */
  virtual void play () {
      vector<int> units_id = my_units(me());
      int n_units = units_id.size();
      for (int i = 0; i < n_units; ++i) {
        bfs_units(units_id[i]);
      }
  }
};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
