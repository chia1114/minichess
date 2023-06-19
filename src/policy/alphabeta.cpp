#include <cstdlib>
#include <algorithm>
#include <vector>
#include <climits>

#include "../state/state.hpp"
#include "./alphabeta.hpp"

int getvalue(State* , int, int, int, int);

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
    return ret;
  }
  else {
    for(auto temp:actions) {
      x=getvalue(state->next_state(temp), depth-1, -INT_MAX, INT_MAX, 1);
      if(x>value) {
        value=x;
        ret=temp;
      }
    }
    return ret;
  }
}

int getvalue(State* state, int depth, int alpha, int beta, int minimax) {
  int x;
  int maxvalue=-INT_MAX;
  int minvalue=INT_MAX;

  if(!state->legal_actions.size())
    state->get_legal_actions();

  auto actions = state->legal_actions;

  if(depth==1) {
    if(minimax==1) {
      for(auto temp:actions) {
        x=(state->next_state(temp))->evaluate();
        if(x<minvalue) {
          minvalue=x;
          if(minvalue<alpha) {
            break;
          }
        }
      }
      return minvalue;
    }
    else {
      for(auto temp:actions) {
        x=(state->next_state(temp))->evaluate();
        if(x<minvalue) {
          minvalue=x;
          if(-minvalue>beta) {
            break;
          }
        }
      }
      return -minvalue;
    }
  }
  else {
    if(minimax==0) {
      for(auto temp:actions) {
        x=getvalue(state->next_state(temp), depth-1, alpha, beta, 1-minimax);
        maxvalue=std::max(x, maxvalue);
      }
      return maxvalue;
    }
    else {
      for(auto temp:actions) {
        x=getvalue(state->next_state(temp), depth-1, alpha, beta, 1-minimax);
        minvalue=std::min(x, minvalue);
      }
      return minvalue;
    }
  }
}