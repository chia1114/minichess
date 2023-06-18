#include <cstdlib>
#include <algorithm>
#include <vector>
#include <climits>

#include "../state/state.hpp"
#include "./minimax.hpp"

int getvalue(State* , int, int);

/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
Move minimax::get_move(State *state, int depth){
  int x;
  int value=-INT_MAX;
  Move ret;

  if(!state->legal_actions.size())
    state->get_legal_actions();

  auto actions = state->legal_actions;

  for(auto temp:actions) {
    x=getvalue(state->next_state(temp), depth-1, 1);
    if(x>value) {
      value=x;
      ret=temp;
    }
  }
  return ret;
}

int getvalue(State* state, int depth, int minimax) { //0:max 1:mini
  int x;
  int myvalue=-INT_MAX;
  int oppnvalue=INT_MAX;

  if(!state->legal_actions.size())
    state->get_legal_actions();

  auto actions = state->legal_actions;

  if(depth==1) {
    if(minimax==1) {
      for(auto temp:actions) {
        x=(state->next_state(temp))->evaluate();
        if(x<myvalue) {
          myvalue=x;
        }
      }
      return myvalue;
    }
    else {
      for(auto temp:actions) {
        x=(state->next_state(temp))->evaluate();
        if(x<oppnvalue) {
          oppnvalue=x;
        }
      }
      return -oppnvalue;
    }
  }
  else {
    if(minimax==0) {
      for(auto temp:actions) {
        myvalue=std::max(getvalue(state->next_state(temp), depth-1, 1-minimax), myvalue);
      }
      return myvalue;
    }
    else {
      for(auto temp:actions) {
        oppnvalue=std::min(getvalue(state->next_state(temp), depth-1, 1-minimax), oppnvalue);
      }
      return oppnvalue;
    }
  }
}