#pragma once
constexpr int WEAPON_HANDS = 113;
//Sniper ammo weapons
constexpr int WEAPON_SENTINEL = 1;
constexpr int WEAPON_CHARGE_RIFLE = 82;
constexpr int WEAPON_LONGBOW = 84;
//Shotgun ammo weapons
constexpr int WEAPON_MOZAMBIQUE = 95;
constexpr int WEAPON_EVA8 = 86;
constexpr int WEAPON_PEACEKEEPER = 102;
constexpr int WEAPON_MASTIFF = 94;
//Light ammo weapons
constexpr int WEAPON_P2020 = 104;
constexpr int WEAPON_RE45 = 80;
constexpr int WEAPON_ALTERNATOR = 79;
constexpr int WEAPON_R99 = 103;
constexpr int WEAPON_R301 = 0;
constexpr int WEAPON_SPITFIRE = 105;
constexpr int WEAPON_G7 = 88;
//Heavy ammo weapons
constexpr int WEAPON_CAR = 111;
constexpr int WEAPON_RAMPAGE = 20;
constexpr int WEAPON_3030 = 110;
constexpr int WEAPON_HEMLOCK = 89;
constexpr int WEAPON_FLATLINE = 87;
//Energy ammo weapons
constexpr int WEAPON_NEMESIS = 112;
constexpr int WEAPON_VOLT = 109;
constexpr int WEAPON_TRIPLE_TAKE = 106;
constexpr int WEAPON_LSTAR = 92;
constexpr int WEAPON_DEVOTION = 83;
constexpr int WEAPON_HAVOC = 85;
//Legendary ammo weapons
constexpr int WEAPON_WINGMAN = 108; //Emotional damage! :)
constexpr int WEAPON_PROWLER = 101;
constexpr int WEAPON_BOCEK = 2;
constexpr int WEAPON_KRABER = 91;
constexpr int WEAPON_THROWING_KNIFE = 158;


// Define a reverse mapping from integer values to string names
std::unordered_map<int, std::string> intToStringMap = {
    {WEAPON_HANDS,"WEAPON_HANDS"},
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
    {WEAPON_KRABER ,"WEAPON_KRABER"} ,
    {WEAPON_THROWING_KNIFE,"WEAPON_THROWING_KNIFE"} };

std::string WeaponName(int weaponId) {
    auto it = intToStringMap.find(weaponId);
    if (it != intToStringMap.end())
        return it->second;
    return "UNKNOWN! NEED WEAPONID UPDATE!?";
}


