#ifndef DATA_H
#define DATA_H

/**
 * @brief The available game play modes
 */
enum class PlayMode {Idle = -1, Man_AI, Man_Man, AI_AI};
/**
 * @brief The types of JSON messages exchanged between the game server and the client
 */
enum class JsonType {Test = -1, New_Game, Player_Choice, Game_Over, Load_Game, Save_Game};

#endif //DATA_H