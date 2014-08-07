//
//  Constants.h
//  2048RPSPort
//
//  Created by Patrick Hoey on 8/2/14.
//
//

#ifndef _048RPSPort_Constants_h
#define _048RPSPort_Constants_h

namespace Constants {
    static const char* BACKGROUND_MUSIC = "Castle.mp3";
    static const char* BACKGROUND_MUSIC2 = "Castle2.mp3";
    static const char* LOSE_SOUND = "ME_defeat.mp3";
    static const char* WIN_SOUND = "ME_victory.mp3";
    static const char* MERGE_SOUND = "pop.mp3";
    
    
    static const char* UPDATE_SCORE = "Update_Score_Event";
    
    static const int GRID_SIZE = 4;
    static const int TOTAL_GRID_SIZE = 16;
    static const int START_TILES = 2;
    static const int WIN_TILE = 2048;
}


#endif
