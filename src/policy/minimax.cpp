#include <cstdlib>
#include <algorithm>
#include <vector>

#include "../state/state.hpp"
#include "./minimax.hpp"


/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
Move minimax::get_move(State *state, int depth){
    int maxvalue=0;
    Move ret;

  if(!state->legal_actions.size())
    state->get_legal_actions();
  
  auto actions = state->legal_actions;
  std::vector<Move>::iterator temp;
  for(temp=actions.begin(); temp!=actions.end(); temp++) {
    if((state->next_state(*temp))->evaluate()>maxvalue) {
        maxvalue=(state->next_state(*temp))->evaluate();
        ret=*temp;
    }
  }
  if(temp==actions.end()) {
    return actions[(rand()+depth)%actions.size()];
  }

  return ret;

}