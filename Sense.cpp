#pragma once
struct Sense {
    XDisplay* display;
    Level* level;
    LocalPlayer* localPlayer;
    std::vector<Player*>* players;

    Sense(XDisplay* display, Level* level, LocalPlayer* localPlayer, std::vector<Player*>* players) {
        this->display = display;
        this->level = level;
        this->localPlayer = localPlayer;
        this->players = players;
    }

    void modifyHighlights() {
        const long highlightSettingsPtr = mem::Read<long>(OFF_REGION + OFF_GLOW_HIGHLIGHTS);
        const long highlightSize = 0x28;
        { //player highlight 
            int highlightId = 0;
            const GlowMode newGlowMode = { 112,108,40,127 };
            const GlowMode oldGlowMode = mem::Read<GlowMode>(highlightSettingsPtr + (highlightSize * highlightId) + 4);
            if (newGlowMode != oldGlowMode)
                mem::Write<GlowMode>(highlightSettingsPtr + (highlightSize * highlightId) + 4, newGlowMode);
            Color newColor = { 0,10,0 };
            const Color oldColor = mem::Read<Color>(highlightSettingsPtr + (highlightSize * highlightId) + 8);
            if (oldColor != newColor)
                mem::Write<Color>(highlightSettingsPtr + (highlightSize * highlightId) + 8, newColor);
        }
        { //player highlight hidden
            int highlightId = 1;
            const GlowMode newGlowMode = { 118,108,40,127 };
            const GlowMode oldGlowMode = mem::Read<GlowMode>(highlightSettingsPtr + (highlightSize * highlightId) + 4);
            if (newGlowMode != oldGlowMode)
                mem::Write<GlowMode>(highlightSettingsPtr + (highlightSize * highlightId) + 4, newGlowMode);
            Color newColor = { 10,0,0 };
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
        for (int i = 0; i < players->size(); i++) {
            Player* p = players->at(i);
            if (!p->isValid()) continue;
            if (!p->enemy) continue;
            p->glow();
        }
    }

};
