#ifndef TARGET_HPP
#define TARGET_HPP 

struct Target{
public:
    inline Target() {}
    inline Target(int p, int c) : playerId(p), cardId(c) {}
    int playerId;//player id or -1 for global cards
    int cardId;//card id of equipped cards or -1 for player themselves
};

#endif /* TARGET_HPP */
