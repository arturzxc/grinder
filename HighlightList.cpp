#pragma once
struct HighlightList {
    long highlightMemorySize = 0x34;
    long highlighListBase;
    const int invisiblePlayerHighlightId = 8;
    Highlight invisiblePlayersHighlight;
    const int visiblePlayerHighlightId = 9;
    Highlight visiblePlayersHighlight;

    void readFromMemory() {
        highlighListBase = mem::Read<long>(OFF_REGION + OFF_GLOW_HIGHLIGHTS, "HighlightList Base");
        // printf("HighlightList base: %s\n", mem::convertPointerToHexString(highlighListBase).c_str());

        //modify the highlight for the invisible players
        invisiblePlayersHighlight = mem::Read<Highlight>(highlightBase(invisiblePlayerHighlightId), "HighlightElement functionBits - invisible players");
        // printf("HIGHLIGHT[ininvisiblePlayersHighlightvisible] %s \n", highlight.toString().c_str());

        //modify highlight for visible players
        visiblePlayersHighlight = mem::Read<Highlight>(highlightBase(visiblePlayerHighlightId), "HighlightElement functionBits - visible players");
        // printf("HIGHLIGHT[visiblePlayersHighlight] %s \n", highlight.toString().c_str());
    }

    void updateHighlights() {
        invisiblePlayersHighlight.bodyStyle = static_cast<std::byte>(118);
        invisiblePlayersHighlight.borderWidth = static_cast<std::byte>(45);
        invisiblePlayersHighlight.borderStyle = static_cast<std::byte>(6);
        invisiblePlayersHighlight.transparency = static_cast<std::byte>(64);
        invisiblePlayersHighlight.blue = 0;
        invisiblePlayersHighlight.red = 1;
        invisiblePlayersHighlight.green = 0;
        mem::Write<Highlight>(highlightBase(invisiblePlayerHighlightId), invisiblePlayersHighlight);

        visiblePlayersHighlight.blue = 0;
        visiblePlayersHighlight.red = 0;
        visiblePlayersHighlight.green = 1;
        mem::Write<Highlight>(highlightBase(visiblePlayerHighlightId), visiblePlayersHighlight);
    }

    bool isValid() {
        return mem::Valid(highlighListBase);
    }

    long highlightBase(int highlightIndex) {
        return highlighListBase + (highlightIndex * highlightMemorySize);
    }


};

