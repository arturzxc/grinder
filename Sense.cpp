#pragma once
struct Sense {
    ConfigLoader* cl;
    XDisplay* display;
    Level* level;
    LocalPlayer* localPlayer;
    std::vector<Player*>* players;

    Sense(ConfigLoader* cl, XDisplay* display, Level* level, LocalPlayer* localPlayer, std::vector<Player*>* players) {
        this->cl = cl;
        this->display = display;
        this->level = level;
        this->localPlayer = localPlayer;
        this->players = players;
    }

    void modifyHighlights() {
        if (!this->cl->FEATURE_SENSE_ON)return;
        const long highlightSettingsPtr = mem::Read<long>(OFF_REGION + OFF_GLOW_HIGHLIGHTS);
        const long highlightSize = 0x28;
        { //player highlight - visible 
            int highlightId = 0;
            const GlowMode newGlowMode = {
                cl->SENSE_ENEMY_VISIBLE_BODY_STYLE,
                cl->SENSE_ENEMY_VISIBLE_BORDER_STYLE,
                cl->SENSE_ENEMY_VISIBLE_BORDER_WIDTH,
                127
            };
            const GlowMode oldGlowMode = mem::Read<GlowMode>(highlightSettingsPtr + (highlightSize * highlightId) + 4);
            if (newGlowMode != oldGlowMode)
                mem::Write<GlowMode>(highlightSettingsPtr + (highlightSize * highlightId) + 4, newGlowMode);
            Color newColor = {
                cl->SENSE_ENEMY_VISIBLE_COLOR_RED,
                cl->SENSE_ENEMY_VISIBLE_COLOR_GREEN,
                cl->SENSE_ENEMY_VISIBLE_COLOR_BLUE
            };
            const Color oldColor = mem::Read<Color>(highlightSettingsPtr + (highlightSize * highlightId) + 8);
            if (oldColor != newColor)
                mem::Write<Color>(highlightSettingsPtr + (highlightSize * highlightId) + 8, newColor);
        }
        { //player highlight - invisible
            int highlightId = 1;
            const GlowMode newGlowMode = {
                cl->SENSE_ENEMY_INVISIBLE_BODY_STYLE,
                cl->SENSE_ENEMY_INVISIBLE_BORDER_STYLE,
                cl->SENSE_ENEMY_INVISIBLE_BORDER_WIDTH,
                100
            };
            const GlowMode oldGlowMode = mem::Read<GlowMode>(highlightSettingsPtr + (highlightSize * highlightId) + 4);
            if (newGlowMode != oldGlowMode)
                mem::Write<GlowMode>(highlightSettingsPtr + (highlightSize * highlightId) + 4, newGlowMode);
            Color newColor = {
                cl->SENSE_ENEMY_INVISIBLE_COLOR_RED,
                cl->SENSE_ENEMY_INVISIBLE_COLOR_GREEN,
                cl->SENSE_ENEMY_INVISIBLE_COLOR_BLUE
            };
            const Color oldColor = mem::Read<Color>(highlightSettingsPtr + (highlightSize * highlightId) + 8);
            if (oldColor != newColor)
                mem::Write<Color>(highlightSettingsPtr + (highlightSize * highlightId) + 8, newColor);
        }
        { //player highlight - aimbot locked
            int highlightId = 2;
            const GlowMode newGlowMode = {
                cl->SENSE_ENEMY_LOCKEDON_BODY_STYLE,
                cl->SENSE_ENEMY_LOCKEDON_BORDER_STYLE,
                cl->SENSE_ENEMY_LOCKEDON_BORDER_WIDTH,
                127
            };
            const GlowMode oldGlowMode = mem::Read<GlowMode>(highlightSettingsPtr + (highlightSize * highlightId) + 4);
            if (newGlowMode != oldGlowMode)
                mem::Write<GlowMode>(highlightSettingsPtr + (highlightSize * highlightId) + 4, newGlowMode);
            Color newColor = { cl->SENSE_ENEMY_LOCKEDON_COLOR_RED,cl->SENSE_ENEMY_LOCKEDON_COLOR_GREEN,cl->SENSE_ENEMY_LOCKEDON_COLOR_BLUE };
            const Color oldColor = mem::Read<Color>(highlightSettingsPtr + (highlightSize * highlightId) + 8);
            if (oldColor != newColor)
                mem::Write<Color>(highlightSettingsPtr + (highlightSize * highlightId) + 8, newColor);
        }

        const GlowMode newGlowModeShieldBased = { 2,113,80,127 };
        { //player highlight | shields = 0 
            int highlightId = 90;
            const GlowMode oldGlowMode = mem::Read<GlowMode>(highlightSettingsPtr + (highlightSize * highlightId) + 4);
            if (newGlowModeShieldBased != oldGlowMode)
                mem::Write<GlowMode>(highlightSettingsPtr + (highlightSize * highlightId) + 4, newGlowModeShieldBased);
            Color newColor = { 0,10,0 };
            const Color oldColor = mem::Read<Color>(highlightSettingsPtr + (highlightSize * highlightId) + 8);
            if (oldColor != newColor)
                mem::Write<Color>(highlightSettingsPtr + (highlightSize * highlightId) + 8, newColor);
        }
        { //player highlight | shields <= 50  
            int highlightId = 91;
            const GlowMode oldGlowMode = mem::Read<GlowMode>(highlightSettingsPtr + (highlightSize * highlightId) + 4);
            if (newGlowModeShieldBased != oldGlowMode)
                mem::Write<GlowMode>(highlightSettingsPtr + (highlightSize * highlightId) + 4, newGlowModeShieldBased);
            Color newColor = { 10,10,10 };
            const Color oldColor = mem::Read<Color>(highlightSettingsPtr + (highlightSize * highlightId) + 8);
            if (oldColor != newColor)
                mem::Write<Color>(highlightSettingsPtr + (highlightSize * highlightId) + 8, newColor);
        }
        { //player highlight | shields <= 75  
            int highlightId = 92;
            const GlowMode oldGlowMode = mem::Read<GlowMode>(highlightSettingsPtr + (highlightSize * highlightId) + 4);
            if (newGlowModeShieldBased != oldGlowMode)
                mem::Write<GlowMode>(highlightSettingsPtr + (highlightSize * highlightId) + 4, newGlowModeShieldBased);
            Color newColor = { 0,5,10 };
            const Color oldColor = mem::Read<Color>(highlightSettingsPtr + (highlightSize * highlightId) + 8);
            if (oldColor != newColor)
                mem::Write<Color>(highlightSettingsPtr + (highlightSize * highlightId) + 8, newColor);
        }
        { //player highlight | shields <= 100  
            int highlightId = 93;
            const GlowMode oldGlowMode = mem::Read<GlowMode>(highlightSettingsPtr + (highlightSize * highlightId) + 4);
            if (newGlowModeShieldBased != oldGlowMode)
                mem::Write<GlowMode>(highlightSettingsPtr + (highlightSize * highlightId) + 4, newGlowModeShieldBased);
            Color newColor = { 5,0,10 };
            const Color oldColor = mem::Read<Color>(highlightSettingsPtr + (highlightSize * highlightId) + 8);
            if (oldColor != newColor)
                mem::Write<Color>(highlightSettingsPtr + (highlightSize * highlightId) + 8, newColor);
        }
        { //player highlight | shields <= 125 
            int highlightId = 94;
            const GlowMode oldGlowMode = mem::Read<GlowMode>(highlightSettingsPtr + (highlightSize * highlightId) + 4);
            if (newGlowModeShieldBased != oldGlowMode)
                mem::Write<GlowMode>(highlightSettingsPtr + (highlightSize * highlightId) + 4, newGlowModeShieldBased);
            Color newColor = { 10,1,0 };
            const Color oldColor = mem::Read<Color>(highlightSettingsPtr + (highlightSize * highlightId) + 8);
            if (oldColor != newColor)
                mem::Write<Color>(highlightSettingsPtr + (highlightSize * highlightId) + 8, newColor);
        }
        { //player highlight - friendlies
            int highlightId = 95;
            const GlowMode oldGlowMode = mem::Read<GlowMode>(highlightSettingsPtr + (highlightSize * highlightId) + 4);
            GlowMode myGm = { 118,0,0,127 };
            if (myGm != oldGlowMode)
                mem::Write<GlowMode>(highlightSettingsPtr + (highlightSize * highlightId) + 4, myGm);
            Color newColor = { 0,0,0 };
            const Color oldColor = mem::Read<Color>(highlightSettingsPtr + (highlightSize * highlightId) + 8);
            if (oldColor != newColor)
                mem::Write<Color>(highlightSettingsPtr + (highlightSize * highlightId) + 8, newColor);
        }

        //item highlights
        for (int highlightId = 30; highlightId < 40; highlightId++) {
            const GlowMode newGlowMode = { 137,0,0,127 };
            const GlowMode oldGlowMode = mem::Read<GlowMode>(highlightSettingsPtr + (highlightSize * highlightId) + 4);
            if (newGlowMode != oldGlowMode)
                mem::Write<GlowMode>(highlightSettingsPtr + (highlightSize * highlightId) + 4, newGlowMode);
        }
    }

    void glowPlayers() {
        if (!this->cl->FEATURE_SENSE_ON)return;
        for (int i = 0; i < players->size(); i++) {
            Player* p = players->at(i);
            if (!p->isValid()) continue;
            if (p->enemy) {
                if (cl->SENSE_ENEMY_COLOR_SHIELD_BASED) p->glowShieldBased();
                else p->glow();
            }
            else
                p->glowFriendly();
        }
    }

};
