#pragma once
//Sniper ammo weapons
constexpr int WEAPON_SENTINEL = 106;
constexpr int WEAPON_CHARGE_RIFLE = 284;
constexpr int WEAPON_LONGBOW = 2827;
//Shotgun ammo weapons
constexpr int WEAPON_MOZAMBIQUE = 3045;
constexpr int WEAPON_EVA8 = 760;
constexpr int WEAPON_PEACEKEEPER = 266;
constexpr int WEAPON_MASTIFF = 1050;
//Light ammo weapons
constexpr int WEAPON_P2020 = 226;
constexpr int WEAPON_RE45 = 2754;
constexpr int WEAPON_ALTERNATOR = 823;
constexpr int WEAPON_R99 = 225;
constexpr int WEAPON_R301 = 103;
constexpr int WEAPON_SPITFIRE = 3222;
constexpr int WEAPON_G7 = 325;
//Heavy ammo weapons
constexpr int WEAPON_CAR = 3411;
constexpr int WEAPON_RAMPAGE = 205;
constexpr int WEAPON_3030 = 1573;
constexpr int WEAPON_HEMLOCK = 228;
constexpr int WEAPON_FLATLINE = 1449;
//Energy ammo weapons
constexpr int WEAPON_NEMESIS = 3439;
constexpr int WEAPON_VOLT = 3326;
constexpr int WEAPON_TRIPLE_TAKE = 3258;
constexpr int WEAPON_LSTAR = 231;
constexpr int WEAPON_DEVOTION = 2801;
constexpr int WEAPON_HAVOC = 1508;
//Legendary ammo weapons
constexpr int WEAPON_WINGMAN = 894; //Emotional damage! :)
constexpr int WEAPON_PROWLER = 3055;
constexpr int WEAPON_BOCEK = 109;
constexpr int WEAPON_KRABER = 2997;


// Define a reverse mapping from integer values to string names
std::unordered_map<int, std::string> intToStringMap = {    
    {WEAPON_SENTINEL,"WEAPON_SENTINEL"},
    {WEAPON_CHARGE_RIFLE,"WEAPON_CHARGE_RIFLE"},
    {WEAPON_LONGBOW ,"WEAPON_LONGBOW"},
    {WEAPON_MOZAMBIQUE,"WEAPON_MOZAMBIQUE"},
    {WEAPON_EVA8,"WEAPON_EVA8"},
    {WEAPON_PEACEKEEPER,"WEAPON_PEACEKEEPER"},
    {WEAPON_MASTIFF,"WEAPON_MASTIFF"},
    {WEAPON_P2020,"WEAPON_P2020"},
    {WEAPON_RE45,"WEAPON_RE45"},
    {WEAPON_ALTERNATOR,"WEAPON_ALTERNATOR"},
    {WEAPON_R99 ,"WEAPON_R99"},
    {WEAPON_R301,"WEAPON_R301"},
    {WEAPON_SPITFIRE,"WEAPON_SPITFIRE"},
    {WEAPON_G7,"WEAPON_G7"},
    {WEAPON_CAR,"WEAPON_CAR"},
    {WEAPON_RAMPAGE,"WEAPON_RAMPAGE"},
    {WEAPON_3030,"WEAPON_3030"},
    {WEAPON_HEMLOCK,"WEAPON_HEMLOCK"},
    {WEAPON_FLATLINE,"WEAPON_FLATLINE"},
    {WEAPON_NEMESIS,"WEAPON_NEMESIS"},
    {WEAPON_VOLT,"WEAPON_VOLT"},
    {WEAPON_TRIPLE_TAKE,"WEAPON_TRIPLE_TAKE"},
    {WEAPON_LSTAR,"WEAPON_LSTAR"},
    {WEAPON_DEVOTION ,"WEAPON_DEVOTION"},
    {WEAPON_HAVOC ,"WEAPON_HAVOC"},
    {WEAPON_WINGMAN ,"WEAPON_WINGMAN"},
    {WEAPON_PROWLER ,"WEAPON_PROWLER"},
    {WEAPON_BOCEK ,"WEAPON_BOCEK"},
    {WEAPON_KRABER ,"WEAPON_KRABER"} };

std::string WeaponName(int weaponId) {
    auto it = intToStringMap.find(weaponId);
    if (it != intToStringMap.end())
        return it->second;
    return "UNKNOWN! NEED WEAPONID UPDATE!?";
}


