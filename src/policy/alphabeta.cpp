#include <cstdlib>
#include <algorithm>
#include <vector>
#include <climits>

#include "../state/state.hpp"
#include "./alphabeta.hpp"

int totaldepth;
Move ans;

int getvalue(State* , int, int, int, bool, bool);

/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
Move alphabeta::get_move(State *state, int depth){
  int x;
  int value=-INT_MAX;
  int depthvalue=INT_MAX;
  Move ret;

  if(!state->legal_actions.size())
    state->get_legal_actions();

  auto actions = state->legal_actions;

  if(depth==1) {
    for(auto temp:actions) {
      x=(state->next_state(temp))->evaluate();
      if(x<depthvalue) {
        depthvalue=x;
        ret=temp;
      }
    }
    if(depthvalue==INT_MAX) {
      return actions[(rand()+depth)%actions.size()];
    }
    return ret;
  }
  else {
    x=getvalue(state, depth, -INT_MAX, INT_MAX, false, true);
    if(x==-INT_MAX) {
      return actions[(rand()+depth)%actions.size()];
    }
    return ans;
  }
}

int getvalue(State* state, int depth, int alpha, int beta, bool minimax, bool first) {
  int x;

  if(!state->legal_actions.size())
    state->get_legal_actions();

  auto actions = state->legal_actions;

  if(depth==0) {
    if(minimax) {
      return -state->evaluate();
    }
    else {
      return state->evaluate();
    }
  }
  else {
    if(!minimax) {
      for(auto temp:actions) {
        x=getvalue(state->next_state(temp), depth-1, alpha, beta, !minimax, false);
        if(x>alpha) {
          alpha=x;
          if(first) {
            ans=temp;
          }
          if(alpha>=beta) {
            break;
          }
        }
      }
      return alpha;
    }
    else {
      for(auto temp:actions) {
        x=getvalue(state->next_state(temp), depth-1, alpha, beta, !minimax, false);
        if(x<beta) {
          beta=x;
          if(beta<=alpha) {
            break;
          }
        }
      }
      return beta;
    }
  }
}