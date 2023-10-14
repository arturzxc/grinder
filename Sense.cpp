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
        //item highlights
        for (int highlightId = 31; highlightId < 35; highlightId++) {
            const GlowMode newGlowMode = { 137,138,35,127 };
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
            if (!p->enemy) continue;
            p->glow();
        }
    }

};
