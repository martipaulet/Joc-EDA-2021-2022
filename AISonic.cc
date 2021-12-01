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
  typedef vector<VB> VVB;     //matriz booleanos


  

  /**
   * Methods.
   */ 

  //returns an integer matrix of the board with -1 on the walss position
  VVI create_table() {
    VVI v(rows(),VI(cols(),-2));
    for(int i = 0; i < rows(); ++i) {
      for(int j = 0; j < cols(); ++j){
          Cell c = cell(i,j);
          if (c.type == WALL) v[i][j] = -1;
      }
    }
    return v;
  }


  Dir find_next_move(Pos &a, int d, VVI &VP) {
    /*
    cerr << "actual: " << VP[a.i][a.j] << endl; 
    cerr << "arriba: " << VP[(a.i)-1][a.j]<< endl;
    cerr << "abajo: " << VP[(a.i)+1][a.j]<< endl;
    cerr << "izquierda: " << VP[(a.i)][(a.j)-1]<< endl;
    cerr << "derecha: " << VP[(a.i)][(a.j)+1]<< endl;
  */
    if (pos_ok((a.i)-1,a.j) and VP[(a.i)-1][a.j] == d) {        //adalt
      a += TOP;
      return BOTTOM;
    }
    else if (pos_ok((a.i)+1,a.j) and VP[(a.i)+1][a.j] == d) {   //abaix
      a += BOTTOM;
      return TOP;
    }
    else if (pos_ok(a.i,(a.j)+1) and VP[a.i][(a.j)+1] == d) { //dreta
      a += RIGHT;
      return LEFT; 
    }
    else if (pos_ok(a.i,(a.j)-1) and VP[a.i][(a.j)-1] == d) {   //esq
      a += LEFT;
      return RIGHT;
    }
    return NONE;
  }

  //bfs to a city: (APPROVED)
  //returns the distance to the closest city (not conquered) or -1 otherwise
  void bfs_units(int id) {                               
    VVI VP = create_table();                                                    //board
    queue <pair<pair<int, int>, int> > q;                                       //queue with pos(i,j) and distance d 
    int movx[4] = {-1,1,0,0};                                                   //aux vectors
    int movy[4] = {0,0,-1,1};
    Unit u = unit(id);
    //cerr << "(" << u.pos.i <<","<< u.pos.j<< ") "; 
    //VP[u.pos.i][u.pos.j] = 0;                                                 
    q.push(make_pair(make_pair(u.pos.i,u.pos.j),0)); 
    int x,y,d;
    bool f = true;

    while(not q.empty()) {                         
      x = q.front().first.first;                                                  //pos
      y = q.front().first.second;     
      d = q.front().second;                                                       //distance
      q.pop();

      if (VP[x][y] == -2) {
        VP[x][y] = d;

        for (int i = 0; i < 4; ++i) {
          Cell c = cell(x+movx[i],y+movy[i]);

          if (c.type != WALL) {
            if (c.type == CITY or c.type == PATH) {
              int aux = c.city_id;
              int aux2 = c.path_id;

              if ((aux != -1 and city_owner(aux)!= me()) or (aux2 != -1 and path_owner(aux2) != me())) {
                Pos dest; dest.i = x+movx[i]; dest.j = y+movy[i];                        //posicio final
                Dir next_move = NONE;
                //IMPRIMIR MATRIU
                /*if (f) {
                  for (int i = 0; i < rows(); ++i) {
                    cerr << endl;
                    for (int j = 0; j < cols(); ++j) {
                      cerr << VP[i][j] << " ";
                    }
                  }
                  f = false;
                }*/
                
                int aux = d;
                //cerr << "(" << dest.i <<"," << dest.j << ") a distancia " << d <<  endl;

                for (int i = 0; i <= d; ++i) {
                  //cerr << "steps remaining " << aux << endl;
                  next_move = find_next_move(dest,aux,VP);
                  //cerr << dest.i << " " << dest.j << endl;
                  --aux;
                }     

                move(id,next_move);                                                             
                return;

              }

            }

          q.push(make_pair(make_pair(x+movx[i],y+movy[i]),d+1));
          }

        }

      }

    }

    return;   //error return

  }


  /**
   * Play method, invoked once per each round.
   */
  virtual void play () {
    //if (round() == 199) {
      vector<int> units_id = my_units(me());
      int n_units = units_id.size();
      for (int i = 0; i < n_units; ++i) {
        /*if (i == 0)*/ bfs_units(units_id[i]);
      }
   // }
  }
};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
