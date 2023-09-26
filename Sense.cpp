#pragma once
struct Sense {
private:
    XDisplay* display;
    Level* level;
    LocalPlayer* localPlayer;
    std::vector<Item*>* items;
    std::vector<Player*>* players;

    const int HIGHLIGHT_ID_ENEMY = 0;
    const int HIGHLIGHT_ID_ENEMY_LOCKED = 1;

public:
    Sense(XDisplay* display, Level* level, LocalPlayer* localPlayer, std::vector<Item*>* items, std::vector<Player*>* players) {
        this->display = display;
        this->level = level;
        this->localPlayer = localPlayer;
        this->items = items;
        this->players = players;
    }

    void modifyHighlights() {
        //only modiy highlights on keypress. Basically hit the R button in the dropship and should be enough.
        if (display->keyDown(XK_R) && localPlayer->isCombatReady()) {

            //find pointer to all the highlights
            const long highlightSettingsPtr = mem::Read<long>(off::REGION + off::GLOW_HIGHLIGHTS);
            const long highlightSize = 0x28;

            {//highlight 0: highlight for enemies
                const int highlightId = HIGHLIGHT_ID_ENEMY;
                const GlowMode newGlowMode = { 112,108,35,127 };
                const GlowMode oldGlowMode = mem::Read<GlowMode>(highlightSettingsPtr + (highlightSize * highlightId) + 4);
                if (newGlowMode != oldGlowMode)
                    mem::Write<GlowMode>(highlightSettingsPtr + (highlightSize * highlightId) + 4, newGlowMode);
                Color newColor = { 0,10,0 };
                const Color oldColor = mem::Read<Color>(highlightSettingsPtr + (highlightSize * highlightId) + 8);
                if (oldColor != newColor)
                    mem::Write<Color>(highlightSettingsPtr + (highlightSize * highlightId) + 8, newColor);
            }

            {//highlight 1: highlight for enemies (locked)
                int highlightId = HIGHLIGHT_ID_ENEMY_LOCKED;
                const GlowMode newGlowMode = { 112,108,127,127 };
                const GlowMode oldGlowMode = mem::Read<GlowMode>(highlightSettingsPtr + (highlightSize * highlightId) + 4);
                if (newGlowMode != oldGlowMode)
                    mem::Write<GlowMode>(highlightSettingsPtr + (highlightSize * highlightId) + 4, newGlowMode);
                const Color newColor = { 100,100,100 };
                const Color oldColor = mem::Read<Color>(highlightSettingsPtr + (highlightSize * highlightId) + 8);
                if (oldColor != newColor)
                    mem::Write<Color>(highlightSettingsPtr + (highlightSize * highlightId) + 8, newColor);
            }

            //highlight for items
            for (int i = 31;i < 35;i++) {
                const int highlightId = i;
                const GlowMode newGlowMode = { 137,138,35,127 };
                const GlowMode oldGlowMode = mem::Read<GlowMode>(highlightSettingsPtr + (highlightSize * highlightId) + 4);
                if (newGlowMode != oldGlowMode)
                    mem::Write<GlowMode>(highlightSettingsPtr + (highlightSize * highlightId) + 4, newGlowMode);
            }
        }
    }

    void glowPlayers() {
        for (int i = 0; i < players->size(); i++)
            players->at(i)->glow();
    }

};
