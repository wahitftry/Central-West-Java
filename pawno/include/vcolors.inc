
#include <MerRandom>
#include <vehicletypes>

#define DEFAULT_VEHICLE_HEALTH 999.0
#define INVALID_VEHICLE_HEALTH (DEFAULT_VEHICLE_HEALTH + 1.0)

//new vmodelused[212] = {0, ...};

//new vehiclemodels = 0;

new colorused[212] = {0, ...};

new vehcol[VEHICLES + 1][2];

new bool:dvucc[MAX_VEHICLES + 1] = {false, ...};

new bool:carwindows[MAX_VEHICLES + 1];

new cargobobobleft[MAX_VEHICLES + 1] = {0, ...};
new cargobobobright[MAX_VEHICLES + 1] = {0, ...};

#define CARGOBOB_OB_X_OFFSET 1.7702
#define CARGOBOB_OB_Y_OFFSET 1.2804
#define CARGOBOB_OB_Z_OFFSET 1.7401

new varray[][][] =
{
	{{400, 8}, {4,1}, {123,1}, {113,1}, {101,1}, {75,1}, {62,1}, {40,1}, {36,1}, {0,0}},
	{{401, 8}, {41,41}, {47,47}, {52,52}, {66,66}, {74,74}, {87,87}, {91,91}, {113,113}, {0,0}},
	{{402, 8}, {10,10}, {13,13}, {22,22}, {30,30}, {39,39}, {90,90}, {98,98}, {110,110}, {0,0}},
	{{403, 8}, {36,1}, {37,1}, {30,1}, {28,1}, {25,1}, {40,1}, {101,1}, {113,1}, {0,0}},
	{{404, 8}, {113,39}, {119,50}, {123,92}, {109,100}, {101,101}, {95,105}, {83,110}, {66,25}, {0,0}},
	{{405, 8}, {11,1}, {24,1}, {36,1}, {40,1}, {75,1}, {91,1}, {123,1}, {4,1}, {0,0}},
	{{406, 1}, {1,1}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}},
	{{407, 1}, {3,1}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}},
	{{408, 1}, {26,26}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}},
	{{409, 1}, {1,1}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}},
	{{410, 8}, {4,1}, {9,1}, {10,1}, {25,1}, {36,1}, {40,1}, {45,1}, {84,1}, {0,0}},
	{{411, 8}, {12,1}, {64,1}, {123,1}, {116,1}, {112,1}, {106,1}, {80,1}, {75,1}, {0,0}},
	{{412, 8}, {9,1}, {10,8}, {11,1}, {25,8}, {27,1}, {29,8}, {30,1}, {37,8}, {0,0}},
	{{413, 8}, {87,1}, {88,1}, {91,1}, {105,1}, {109,1}, {119,1}, {4,1}, {25,1}, {0,0}},
	{{414, 8}, {25,1}, {28,1}, {43,1}, {67,1}, {72,1}, {9,1}, {95,1}, {24,1}, {0,0}},
	{{415, 8}, {20,1}, {25,1}, {36,1}, {40,1}, {62,1}, {75,1}, {92,1}, {0,1}, {0,0}},
	{{416, 1}, {1,3}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}},
	{{417, 1}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}}, //
	{{418, 8}, {119,119}, {117,227}, {114,114}, {108,108}, {95,95}, {81,81}, {61,61}, {41,41}, {0,0}},
	{{419, 8}, {45,75}, {47,76}, {33,75}, {13,76}, {54,75}, {69,76}, {59,75}, {87,76}, {0,0}},
	{{420, 1}, {6,1}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}},
	{{421, 8}, {4,1}, {13,1}, {25,1}, {30,1}, {36,1}, {40,1}, {75,1}, {95,1}, {0,0}},
	{{422, 7}, {96,25}, {97,25}, {101,25}, {111,31}, {113,36}, {83,57}, {67,59}, {0,0}, {0,0}},
	{{423, 6}, {1,16}, {1,56}, {1,17}, {1,53}, {1,5}, {1,35}, {0,0}, {0,0}, {0,0}},
	{{424, 8}, {1,0}, {2,2}, {3,2}, {3,6}, {6,16}, {15,30}, {24,53}, {35,61}, {0,0}},
	{{425, 1}, {43,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}},
	{{426, 8}, {37,37}, {42,42}, {53,53}, {62,62}, {7,7}, {10,10}, {11,11}, {15,15}, {0,0}},
	{{427, 1}, {0,1}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}},
	{{428, 1}, {4,75}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}},
	{{429, 8}, {12,12}, {13,13}, {14,14}, {1,2}, {2,1}, {1,3}, {3,1}, {10,10}, {0,0}},
	{{430, 1}, {46,26}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}},
	{{431, 8}, {71,59}, {75,59}, {92,72}, {47,74}, {55,83}, {59,83}, {71,87}, {82,87}, {0,0}},
	{{432, 1}, {43,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}},
	{{433, 1}, {43,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}},
	{{434, 7}, {1,1}, {12,12}, {2,2}, {6,6}, {4,4}, {46,46}, {53,53}, {0,0}, {0,0}},
	{{435, 1}, {1,1}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}},
	{{436, 7}, {83,1}, {87,1}, {92,1}, {95,1}, {109,1}, {119,45}, {11,1}, {0,0}, {0,0}},
	{{437, 8}, {54,7}, {79,7}, {87,7}, {95,16}, {98,20}, {105,20}, {123,20}, {125,21}, {0,0}},
	{{438, 1}, {6,76}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}},
	{{439, 8}, {57,8}, {8,17}, {43,21}, {54,38}, {67,8}, {37,78}, {65,79}, {25,78}, {0,0}},
	{{440, 8}, {34,34}, {32,32}, {20,20}, {110,110}, {66,66}, {84,84}, {118,118}, {121,121}, {0,0}},
	{{441, 8}, {2,96}, {79,42}, {82,54}, {67,86}, {126,96}, {70,96}, {110,54}, {67,98}, {0,0}},
	{{442, 8}, {0,0}, {11,105}, {25,109}, {36,0}, {40,36}, {75,36}, {0,36}, {0,109}, {0,0}},
	{{443, 8}, {4,1}, {20,1}, {24,1}, {25,1}, {36,1}, {40,1}, {54,1}, {84,1}, {0,0}},
	{{444, 6}, {32,36}, {32,42}, {32,53}, {32,66}, {32,14}, {32,32}, {0,0}, {0,0}, {0,0}},
	{{445, 8}, {34,34}, {35,35}, {37,37}, {39,39}, {41,41}, {43,43}, {45,45}, {47,47}, {0,0}},
	{{446, 8}, {0,0}, {1,5}, {3,3}, {1,22}, {1,35}, {1,44}, {1,53}, {1,57}, {0,0}},
	{{447, 1}, {75,2}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}},
	{{448, 1}, {3,6}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}},
	{{449, 1}, {1,74}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}},
	{{450, 1}, {1,1}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}},
	{{451, 8}, {123,123}, {125,125}, {36,36}, {16,16}, {18,18}, {46,46}, {61,61}, {75,75}, {0,0}},
	{{452, 8}, {1,3}, {1,5}, {1,16}, {1,22}, {1,35}, {1,44}, {1,53}, {1,57}, {0,0}},
	{{453, 1}, {56,56}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}},
	{{454, 1}, {26,26}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}},
	{{455, 8}, {84,15}, {84,58}, {84,31}, {32,74}, {43,31}, {1,31}, {77,31}, {32,74}, {0,0}},
	{{456, 8}, {84,63}, {91,63}, {102,65}, {105,72}, {110,93}, {121,93}, {12,95}, {23,1}, {0,0}},
	{{457, 8}, {58,1}, {2,1}, {63,1}, {18,1}, {32,1}, {45,1}, {13,1}, {34,1}, {0,0}},
	{{458, 8}, {91,1}, {101,1}, {109,1}, {113,1}, {4,1}, {25,1}, {30,1}, {36,1}, {0,0}},
	{{459, 8}, {26,26}, {28,28}, {44,44}, {51,51}, {57,57}, {72,72}, {106,106}, {112,112}, {0,0}},
	{{460, 8}, {1,3}, {1,9}, {1,18}, {1,30}, {17,23}, {46,23}, {46,32}, {57,34}, {0,0}},
	{{461, 8}, {36,1}, {37,1}, {43,1}, {53,1}, {61,1}, {75,1}, {79,1}, {88,1}, {0,0}},
	{{462, 8}, {12,12}, {13,13}, {14,14}, {1,2}, {2,1}, {1,3}, {3,1}, {10,10}, {0,0}},
	{{463, 8}, {79,79}, {84,84}, {7,7}, {11,11}, {19,19}, {22,22}, {36,36}, {53,53}, {0,0}},
	{{464, 1}, {14,75}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}},
	{{465, 1}, {14,75}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}},
	{{466, 8}, {67,76}, {68,76}, {78,76}, {2,76}, {16,76}, {18,76}, {25,76}, {45,88}, {0,0}},
	{{467, 8}, {51,1}, {58,8}, {60,1}, {68,8}, {2,1}, {13,8}, {22,1}, {36,8}, {0,0}},
	{{468, 4}, {6,6}, {46,46}, {53,53}, {3,3}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}},
	{{469, 1}, {1,3}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}},
	{{470, 1}, {43,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}},
	{{471, 8}, {120,117}, {103,111}, {120,114}, {74,91}, {120,112}, {74,83}, {120,113}, {66,71}, {0,0}},
	{{472, 2}, {56,15}, {56,53}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}},
	{{473, 2}, {56,15}, {56,53}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}},
	{{474, 8}, {97,1}, {81,1}, {105,1}, {110,1}, {91,1}, {74,1}, {84,1}, {83,1}, {0,0}},
	{{475, 8}, {2,39}, {9,39}, {17,1}, {21,1}, {33,0}, {37,0}, {41,29}, {56,29}, {0,0}},
	{{476, 8}, {6,7}, {7,6}, {1,6}, {89,91}, {119,117}, {103,102}, {77,87}, {71,77}, {0,0}},
	{{477, 8}, {92,1}, {94,1}, {101,1}, {121,1}, {0,1}, {22,1}, {36,1}, {75,1}, {0,0}},
	{{478, 8}, {72,1}, {66,1}, {59,1}, {45,1}, {40,1}, {39,1}, {35,1}, {20,1}, {0,0}},
	{{479, 8}, {27,36}, {59,36}, {60,35}, {55,41}, {54,31}, {49,23}, {45,32}, {40,29}, {0,0}},
	{{480, 7}, {73,45}, {12,12}, {2,2}, {6,6}, {4,4}, {46,46}, {53,53}, {0,0}, {0,0}},
	{{481, 8}, {1,1}, {3,3}, {6,6}, {46,46}, {65,9}, {14,1}, {12,9}, {26,1}, {0,0}},
	{{482, 8}, {41,41}, {48,48}, {52,52}, {64,64}, {71,71}, {85,85}, {10,10}, {62,62}, {0,0}},
	{{483, 8}, {1,31}, {1,31}, {1,20}, {1,5}, {0,6}, {3,6}, {16,0}, {17,0}, {0,0}},
	{{484, 4}, {12,35}, {50,32}, {40,26}, {66,36}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}},
	{{485, 7}, {1,73}, {1,74}, {1,75}, {1,76}, {1,77}, {1,78}, {1,79}, {0,0}, {0,0}},
	{{486, 1}, {1,1}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}},
	{{487, 8}, {26,14}, {29,42}, {26,57}, {54,29}, {26,3}, {3,29}, {12,39}, {74,35}, {0,0}},
	{{488, 2}, {2,26}, {2,29}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}},
	{{489, 6}, {13,118}, {14,123}, {120,123}, {112,120}, {84,110}, {76,102}, {0,0}, {0,0}, {0,0}},
	{{490, 1}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}},
	{{491, 6}, {40,65}, {71,72}, {52,66}, {64,72}, {30,72}, {60,72}, {0,0}, {0,0}, {0,0}},
	{{492, 8}, {30,26}, {77,26}, {81,27}, {24,55}, {28,56}, {49,59}, {52,69}, {71,107}, {0,0}},
	{{493, 1}, {36,13}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}},
	{{494, 8}, {36,117}, {36,13}, {42,30}, {42,33}, {54,36}, {75,79}, {92,101}, {98,109}, {0,0}},
	{{495, 8}, {123,124}, {119,122}, {118,117}, {116,115}, {114,108}, {101,106}, {88,99}, {5,6}, {0,0}},
	{{496, 8}, {74,72}, {66,72}, {53,56}, {37,19}, {22,22}, {20,20}, {9,14}, {0,0}, {0,0}},
	{{497, 1}, {0,1}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}},
	{{498, 8}, {11,123}, {13,120}, {20,117}, {24,112}, {27,107}, {36,105}, {37,107}, {43,93}, {0,0}},
	{{499, 8}, {109,25}, {109,32}, {112,32}, {10,32}, {30,44}, {32,52}, {84,66}, {84,69}, {0,0}},
	{{500, 8}, {75,84}, {40,84}, {40,110}, {28,119}, {25,119}, {21,119}, {13,119}, {4,119}, {0,0}},
	{{501, 1}, {14,75}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}},
	{{502, 8}, {7,94}, {36,88}, {51,75}, {53,75}, {58,67}, {75,67}, {75,61}, {79,62}, {0,0}},
	{{503, 8}, {83,66}, {87,74}, {87,75}, {98,83}, {101,100}, {103,101}, {117,116}, {123,36}, {0,0}},
	{{504, 8}, {51,39}, {57,38}, {45,29}, {34,9}, {65,9}, {14,1}, {12,9}, {26,1}, {0,0}},
	{{505, 6}, {13,118}, {14,123}, {120,123}, {112,120}, {84,110}, {76,102}, {0,0}, {0,0}, {0,0}},
	{{506, 5}, {3,3}, {6,6}, {7,7}, {52,52}, {76,76}, {0,0}, {0,0}, {0,0}, {0,0}},
	{{507, 8}, {37,37}, {42,42}, {53,53}, {62,62}, {7,7}, {10,10}, {11,11}, {15,15}, {0,0}},
	{{508, 1}, {1,1}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}},
	{{509, 8}, {7,1}, {74,1}, {61,1}, {16,1}, {25,1}, {30,1}, {36,1}, {53,1}, {0,0}},
	{{510, 8}, {43,43}, {46,46}, {39,39}, {28,28}, {16,16}, {6,6}, {5,5}, {2,2}, {0,0}},
	{{511, 8}, {3,90}, {4,90}, {7,68}, {8,66}, {12,60}, {27,97}, {34,51}, {37,51}, {0,0}},
	{{512, 8}, {17,39}, {15,123}, {32,112}, {45,88}, {52,71}, {57,67}, {61,96}, {96,96}, {0,0}},
	{{513, 8}, {38,51}, {21,36}, {21,34}, {30,34}, {54,34}, {55,20}, {48,18}, {51,6}, {0,0}},
	{{514, 8}, {10,1}, {25,1}, {28,1}, {36,1}, {40,1}, {54,1}, {75,1}, {113,1}, {0,0}},
	{{515, 8}, {13,76}, {24,77}, {63,78}, {42,76}, {54,77}, {39,78}, {11,76}, {62,77}, {0,0}},
	{{516, 8}, {116,1}, {119,1}, {122,1}, {4,1}, {9,1}, {24,1}, {27,1}, {36,1}, {0,0}},
	{{517, 8}, {37,36}, {36,36}, {40,36}, {43,41}, {47,41}, {51,72}, {54,75}, {55,84}, {0,0}},
	{{518, 8}, {2,39}, {9,39}, {17,1}, {21,1}, {33,0}, {37,0}, {41,29}, {56,29}, {0,0}},
	{{519, 1}, {1,1}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}},
	{{520, 1}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}}, //
	{{521, 8}, {74,74}, {75,13}, {87,118}, {92,3}, {115,118}, {25,118}, {36,0}, {118,118}, {0,0}},
	{{522, 8}, {3,3}, {3,8}, {6,25}, {7,79}, {8,82}, {36,105}, {39,106}, {51,118}, {0,0}},
	{{523, 1}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}}, //
	{{524, 8}, {60,24}, {61,27}, {65,31}, {61,61}, {81,35}, {62,61}, {83,66}, {83,64}, {0,0}},
	{{525, 7}, {1,1}, {17,20}, {18,20}, {22,30}, {36,43}, {44,51}, {52,54}, {0,0}, {0,0}},
	{{526, 8}, {2,39}, {9,39}, {17,1}, {21,1}, {33,0}, {37,0}, {41,29}, {56,29}, {0,0}},
	{{527, 8}, {52,1}, {53,1}, {66,1}, {75,1}, {76,1}, {81,1}, {95,1}, {109,1}, {0,0}},
	{{528, 1}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}}, //
	{{529, 8}, {37,37}, {42,42}, {53,53}, {62,62}, {7,7}, {10,10}, {11,11}, {15,15}, {0,0}},
	{{530, 8}, {110,1}, {111,1}, {112,1}, {114,1}, {119,1}, {122,1}, {4,1}, {13,1}, {0,0}},
	{{531, 6}, {2,35}, {36,2}, {51,53}, {91,2}, {11,22}, {40,35}, {0,0}, {0,0}, {0,0}},
	{{532, 1}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}}, //
	{{533, 8}, {73,1}, {74,1}, {75,1}, {77,1}, {79,1}, {83,1}, {84,1}, {91,1}, {0,0}},
	{{534, 8}, {37,37}, {42,42}, {53,53}, {62,62}, {7,7}, {10,10}, {11,11}, {15,15}, {0,0}},
	{{535, 8}, {3,1}, {28,1}, {31,1}, {55,1}, {66,1}, {97,1}, {123,1}, {118,1}, {0,0}},
	{{536, 8}, {9,1}, {12,1}, {26,96}, {30,96}, {32,1}, {37,1}, {57,96}, {71,96}, {0,0}},
	{{537, 1}, {1,1}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}},
	{{538, 1}, {1,1}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}},
	{{539, 7}, {96,67}, {86,70}, {79,74}, {70,86}, {61,98}, {75,75}, {75,91}, {0,0}, {0,0}},
	{{540, 8}, {37,37}, {42,42}, {53,53}, {62,62}, {7,7}, {10,10}, {11,11}, {15,15}, {0,0}},
	{{541, 8}, {51,1}, {58,8}, {60,1}, {68,8}, {2,1}, {13,8}, {22,1}, {36,8}, {0,0}},
	{{542, 8}, {13,118}, {24,118}, {31,93}, {32,92}, {45,92}, {113,92}, {119,113}, {122,113}, {0,0}},
	{{543, 8}, {76,8}, {32,8}, {43,8}, {67,8}, {11,11}, {8,90}, {2,2}, {83,13}, {0,0}},
	{{544, 1}, {3,1}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}},
	{{545, 8}, {50,1}, {47,1}, {44,96}, {40,96}, {39,1}, {30,1}, {28,96}, {9,96}, {0,0}},
	{{546, 8}, {62,37}, {78,38}, {2,62}, {3,87}, {2,78}, {113,78}, {119,62}, {7,78}, {0,0}},
	{{547, 8}, {122,1}, {123,1}, {125,1}, {10,1}, {24,1}, {37,1}, {55,1}, {66,1}, {0,0}},
	{{548, 1}, {1,1}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}},
	{{549, 8}, {74,39}, {72,39}, {75,39}, {79,39}, {83,36}, {84,36}, {89,35}, {91,35}, {0,0}},
	{{550, 8}, {37,37}, {42,42}, {53,53}, {62,62}, {7,7}, {10,10}, {11,11}, {15,15}, {0,0}},
	{{551, 8}, {67,1}, {72,1}, {75,1}, {83,1}, {91,1}, {101,1}, {109,1}, {20,1}, {0,0}},
	{{552, 3}, {56,56}, {49,49}, {26,124}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}},
	{{553, 8}, {38,9}, {55,23}, {61,74}, {71,87}, {91,87}, {98,114}, {102,119}, {111,3}, {0,0}},
	{{554, 8}, {53,32}, {15,32}, {45,32}, {34,30}, {65,32}, {14,32}, {12,32}, {43,32}, {0,0}},
	{{555, 8}, {51,1}, {58,1}, {60,1}, {68,1}, {2,1}, {13,1}, {22,1}, {36,1}, {0,0}},
	{{556, 1}, {1,1}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}},
	{{557, 1}, {1,1}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}},
	{{558, 8}, {112,1}, {116,1}, {117,1}, {24,1}, {30,1}, {35,1}, {36,1}, {40,1}, {0,0}},
	{{559, 8}, {51,1}, {58,8}, {60,1}, {68,8}, {2,1}, {13,8}, {22,1}, {36,8}, {0,0}},
	{{560, 8}, {52,39}, {9,39}, {17,1}, {21,1}, {33,0}, {37,0}, {41,29}, {56,29}, {0,0}},
	{{561, 8}, {57,8}, {8,17}, {43,21}, {54,38}, {67,8}, {37,78}, {65,79}, {25,78}, {0,0}},
	{{562, 8}, {36,1}, {35,1}, {17,1}, {11,1}, {116,1}, {113,1}, {101,1}, {92,1}, {0,0}},
	{{563, 1}, {1,6}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}},
	{{564, 1}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}}, //
	{{565, 8}, {37,37}, {42,42}, {53,53}, {62,62}, {7,7}, {10,10}, {11,11}, {15,15}, {0,0}},
	{{566, 8}, {109,1}, {30,8}, {95,1}, {84,8}, {83,1}, {72,8}, {71,1}, {52,8}, {0,0}},
	{{567, 8}, {97,96}, {88,64}, {90,96}, {93,64}, {97,96}, {99,81}, {102,114}, {114,1}, {0,0}},
	{{568, 8}, {2,39}, {9,39}, {17,1}, {21,1}, {33,0}, {37,0}, {41,29}, {56,29}, {0,0}},
	{{569, 1}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}}, //
	{{570, 1}, {1,1}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}},
	{{571, 6}, {2,35}, {36,2}, {51,53}, {91,2}, {11,22}, {40,35}, {0,0}, {0,0}, {0,0}},
	{{572, 8}, {94,1}, {101,1}, {116,1}, {117,1}, {4,1}, {25,1}, {30,1}, {37,1}, {0,0}},
	{{573, 8}, {91,38}, {115,43}, {85,6}, {79,7}, {78,8}, {77,18}, {79,18}, {86,24}, {0,0}},
	{{574, 1}, {26,26}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}},
	{{575, 8}, {12,1}, {19,96}, {31,64}, {25,96}, {38,1}, {51,96}, {57,1}, {66,96}, {0,0}},
	{{576, 8}, {67,1}, {68,96}, {72,1}, {74,8}, {75,96}, {76,8}, {79,1}, {84,96}, {0,0}},
	{{577, 6}, {1,3}, {8,7}, {8,10}, {8,16}, {23,31}, {40,44}, {0,0}, {0,0}, {0,0}},
	{{578, 1}, {1,1}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}},
	{{579, 8}, {37,37}, {42,42}, {53,53}, {62,62}, {7,7}, {10,10}, {11,11}, {15,15}, {0,0}},
	{{580, 9}, {92,92}, {81,81}, {67,67}, {66,66}, {61,61}, {53,53}, {51,51}, {47,47}, {43,43}},
	{{581, 8}, {54,1}, {58,1}, {66,1}, {72,1}, {75,1}, {87,1}, {101,1}, {36,1}, {0,0}},
	{{582, 8}, {41,10}, {41,20}, {49,11}, {56,123}, {110,113}, {112,116}, {114,118}, {119,101}, {0,0}},
	{{583, 1}, {1,1}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}},
	{{584, 1}, {1,1}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}},
	{{585, 8}, {37,37}, {42,42}, {53,53}, {62,62}, {7,7}, {10,10}, {11,11}, {15,15}, {0,0}},
	{{586, 8}, {119,1}, {122,1}, {8,1}, {10,1}, {13,1}, {25,1}, {27,1}, {32,1}, {0,0}},
	{{587, 8}, {36,1}, {40,1}, {43,1}, {53,1}, {72,1}, {75,1}, {95,1}, {101,1}, {0,0}},
	{{588, 1}, {1,1}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}},
	{{589, 8}, {37,37}, {31,31}, {23,23}, {22,22}, {7,7}, {124,124}, {114,114}, {112,112}, {0,0}},
	{{590, 1}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}}, //
	{{591, 1}, {1,1}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}},
	{{592, 1}, {1,1}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}},
	{{593, 8}, {51,1}, {58,8}, {60,1}, {68,8}, {2,1}, {13,8}, {22,1}, {36,8}, {0,0}},
	{{594, 1}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}}, //
	{{595, 1}, {112,20}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}},
	{{596, 1}, {0,1}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}},
	{{597, 1}, {0,1}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}},
	{{598, 1}, {0,1}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}},
	{{599, 1}, {0,1}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}},
	{{600, 8}, {81,8}, {32,8}, {43,8}, {67,8}, {11,11}, {8,90}, {2,2}, {83,13}, {0,0}},
	{{601, 1}, {1,1}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}},
	{{602, 8}, {58,1}, {69,1}, {75,77}, {18,1}, {32,1}, {45,45}, {13,1}, {34,1}, {0,0}},
	{{603, 8}, {58,1}, {69,1}, {75,77}, {18,1}, {32,1}, {45,45}, {13,1}, {34,1}, {0,0}},
	{{604, 8}, {67,76}, {68,76}, {78,76}, {2,76}, {16,76}, {18,76}, {25,76}, {45,88}, {0,0}},
	{{605, 8}, {61,8}, {32,8}, {43,8}, {67,8}, {11,11}, {8,90}, {2,2}, {83,13}, {0,0}},
	{{606, 1}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}}, //
	{{607, 1}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}}, //
	{{608, 1}, {1,1}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}},
	{{609, 1}, {36,36}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}},
	{{610, 1}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}}, //
	{{611, 1}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}} //
};

stock AddStaticVehicle2(modelid, Float:spawn_x, Float:spawn_y, Float:spawn_z, Float:z_angle)
{
	if (colorused[modelid-400] < varray[modelid-400][0][1]) colorused[modelid-400] ++;
	else colorused[modelid-400] = 1;

//	vmodelused[modelid-400] ++;
//	if (vmodelused[modelid-400] == 1) vehiclemodels ++;

	new vehicleid = AddStaticVehicle(modelid, spawn_x, spawn_y, spawn_z, z_angle, varray[modelid-400][colorused[modelid-400]][0], varray[modelid-400][colorused[modelid-400]][1]);

	vehcol[vehicleid][0] = varray[modelid-400][colorused[modelid-400]][0];
	vehcol[vehicleid][1] = varray[modelid-400][colorused[modelid-400]][1];

	SetVehicleHealth(vehicleid, DEFAULT_VEHICLE_HEALTH);

	if (modelid == 548) {
		cargobobobleft[vehicleid] = CreateObject(19848, spawn_x + (floatsin(-(z_angle - 90.0), degrees) * CARGOBOB_OB_X_OFFSET), spawn_y + (floatcos(-(z_angle - 90.0), degrees) * CARGOBOB_OB_Y_OFFSET), spawn_z + CARGOBOB_OB_Z_OFFSET, 0.0, 0.0, z_angle);
		AttachObjectToVehicle(cargobobobleft[vehicleid], vehicleid, -CARGOBOB_OB_X_OFFSET, CARGOBOB_OB_Y_OFFSET, -CARGOBOB_OB_Z_OFFSET, 0.0, 0.0, 0.0);
		cargobobobright[vehicleid] = CreateObject(19848, spawn_x + (floatsin(-(z_angle + 90.0), degrees) * CARGOBOB_OB_X_OFFSET), spawn_y + (floatcos(-(z_angle + 90.0), degrees) * CARGOBOB_OB_Y_OFFSET), spawn_z + CARGOBOB_OB_Z_OFFSET, 0.0, 0.0, z_angle < 180.0 ? z_angle + 180.0 : z_angle - 180.0);
		AttachObjectToVehicle(cargobobobright[vehicleid], vehicleid, CARGOBOB_OB_X_OFFSET, CARGOBOB_OB_Y_OFFSET, -CARGOBOB_OB_Z_OFFSET, 0.0, 0.0, 180.0);
	}

//	SetVehicleBeenOccupied(vehicleid, true);
	return vehicleid;
}

stock AddStaticVehicleEx2(modelid, Float:spawn_x, Float:spawn_y, Float:spawn_z, Float:z_angle, respawn_delay)
{
	modelid = GetVehicleRandomModel(modelid);

	if (colorused[modelid-400] < varray[modelid-400][0][1]) colorused[modelid-400] ++;
	else colorused[modelid-400] = 1;

//	vmodelused[modelid-400] ++;
//	if (vmodelused[modelid-400] == 1) vehiclemodels ++;

	new vehicleid = AddStaticVehicleEx(modelid, spawn_x, spawn_y, spawn_z, z_angle, varray[modelid-400][colorused[modelid-400]][0], varray[modelid-400][colorused[modelid-400]][1], respawn_delay);

	vehcol[vehicleid][0] = varray[modelid-400][colorused[modelid-400]][0];
	vehcol[vehicleid][1] = varray[modelid-400][colorused[modelid-400]][1];

	SetVehicleHealth(vehicleid, DEFAULT_VEHICLE_HEALTH);

	if (modelid == 548) {
		cargobobobleft[vehicleid] = CreateObject(19848, spawn_x + (floatsin(-(z_angle - 90.0), degrees) * CARGOBOB_OB_X_OFFSET), spawn_y + (floatcos(-(z_angle - 90.0), degrees) * CARGOBOB_OB_Y_OFFSET), spawn_z + CARGOBOB_OB_Z_OFFSET, 0.0, 0.0, z_angle);
		AttachObjectToVehicle(cargobobobleft[vehicleid], vehicleid, -CARGOBOB_OB_X_OFFSET, CARGOBOB_OB_Y_OFFSET, -CARGOBOB_OB_Z_OFFSET, 0.0, 0.0, 0.0);
		cargobobobright[vehicleid] = CreateObject(19848, spawn_x + (floatsin(-(z_angle + 90.0), degrees) * CARGOBOB_OB_X_OFFSET), spawn_y + (floatcos(-(z_angle + 90.0), degrees) * CARGOBOB_OB_Y_OFFSET), spawn_z + CARGOBOB_OB_Z_OFFSET, 0.0, 0.0, z_angle < 180.0 ? z_angle + 180.0 : z_angle - 180.0);
		AttachObjectToVehicle(cargobobobright[vehicleid], vehicleid, CARGOBOB_OB_X_OFFSET, CARGOBOB_OB_Y_OFFSET, -CARGOBOB_OB_Z_OFFSET, 0.0, 0.0, 180.0);
	}

//	SetVehicleBeenOccupied(vehicleid, true);
	return vehicleid;
}

stock AddStaticVehicleEx3(modelid, Float:spawn_x, Float:spawn_y, Float:spawn_z, Float:z_angle, respawn_delay)
{
	if (colorused[modelid-400] < varray[modelid-400][0][1]) colorused[modelid-400] ++;
	else colorused[modelid-400] = 1;

//	vmodelused[modelid-400] ++;
//	if (vmodelused[modelid-400] == 1) vehiclemodels ++;

	new vehicleid = AddStaticVehicleEx(modelid, spawn_x, spawn_y, spawn_z, z_angle, varray[modelid-400][colorused[modelid-400]][0], varray[modelid-400][colorused[modelid-400]][1], respawn_delay);

	vehcol[vehicleid][0] = varray[modelid-400][colorused[modelid-400]][0];
	vehcol[vehicleid][1] = varray[modelid-400][colorused[modelid-400]][1];

	SetVehicleHealth(vehicleid, DEFAULT_VEHICLE_HEALTH);

	if (modelid == 548) {
		cargobobobleft[vehicleid] = CreateObject(19848, spawn_x + (floatsin(-(z_angle - 90.0), degrees) * CARGOBOB_OB_X_OFFSET), spawn_y + (floatcos(-(z_angle - 90.0), degrees) * CARGOBOB_OB_Y_OFFSET), spawn_z + CARGOBOB_OB_Z_OFFSET, 0.0, 0.0, z_angle);
		AttachObjectToVehicle(cargobobobleft[vehicleid], vehicleid, -CARGOBOB_OB_X_OFFSET, CARGOBOB_OB_Y_OFFSET, -CARGOBOB_OB_Z_OFFSET, 0.0, 0.0, 0.0);
		cargobobobright[vehicleid] = CreateObject(19848, spawn_x + (floatsin(-(z_angle + 90.0), degrees) * CARGOBOB_OB_X_OFFSET), spawn_y + (floatcos(-(z_angle + 90.0), degrees) * CARGOBOB_OB_Y_OFFSET), spawn_z + CARGOBOB_OB_Z_OFFSET, 0.0, 0.0, z_angle < 180.0 ? z_angle + 180.0 : z_angle - 180.0);
		AttachObjectToVehicle(cargobobobright[vehicleid], vehicleid, CARGOBOB_OB_X_OFFSET, CARGOBOB_OB_Y_OFFSET, -CARGOBOB_OB_Z_OFFSET, 0.0, 0.0, 180.0);
	}

//	SetVehicleBeenOccupied(vehicleid, true);
	return vehicleid;
}

stock AddStaticVehicleEx4(modelid, Float:spawn_x, Float:spawn_y, Float:spawn_z, Float:z_angle, color1, color2, respawn_delay)
{
//	vmodelused[modelid-400] ++;
//	if (vmodelused[modelid-400] == 1) vehiclemodels ++;

	new vehicleid = AddStaticVehicleEx(modelid, spawn_x, spawn_y, spawn_z, z_angle, color1, color2, respawn_delay);

	vehcol[vehicleid][0] = color1;
	vehcol[vehicleid][1] = color2;

	SetVehicleHealth(vehicleid, DEFAULT_VEHICLE_HEALTH);

	if (modelid == 548) {
		cargobobobleft[vehicleid] = CreateObject(19848, spawn_x + (floatsin(-(z_angle - 90.0), degrees) * CARGOBOB_OB_X_OFFSET), spawn_y + (floatcos(-(z_angle - 90.0), degrees) * CARGOBOB_OB_Y_OFFSET), spawn_z + CARGOBOB_OB_Z_OFFSET, 0.0, 0.0, z_angle);
		AttachObjectToVehicle(cargobobobleft[vehicleid], vehicleid, -CARGOBOB_OB_X_OFFSET, CARGOBOB_OB_Y_OFFSET, -CARGOBOB_OB_Z_OFFSET, 0.0, 0.0, 0.0);
		cargobobobright[vehicleid] = CreateObject(19848, spawn_x + (floatsin(-(z_angle + 90.0), degrees) * CARGOBOB_OB_X_OFFSET), spawn_y + (floatcos(-(z_angle + 90.0), degrees) * CARGOBOB_OB_Y_OFFSET), spawn_z + CARGOBOB_OB_Z_OFFSET, 0.0, 0.0, z_angle < 180.0 ? z_angle + 180.0 : z_angle - 180.0);
		AttachObjectToVehicle(cargobobobright[vehicleid], vehicleid, CARGOBOB_OB_X_OFFSET, CARGOBOB_OB_Y_OFFSET, -CARGOBOB_OB_Z_OFFSET, 0.0, 0.0, 180.0);
	}

//	SetVehicleBeenOccupied(vehicleid, true);
	return vehicleid;
}

stock CreateVehicle2(modelid, Float:x, Float:y, Float:z, Float:rotation, respawn_delay, addsiren = 0)
{
	if (colorused[modelid-400] < varray[modelid-400][0][1]) colorused[modelid-400] ++;
	else colorused[modelid-400] = 1;

//	vmodelused[modelid-400] ++;
//	if (vmodelused[modelid-400] == 1) vehiclemodels ++;

	new vehicleid = CreateVehicle(modelid, x, y, z, rotation, varray[modelid-400][colorused[modelid-400]][0], varray[modelid-400][colorused[modelid-400]][1], respawn_delay, addsiren);

	vehcol[vehicleid][0] = varray[modelid-400][colorused[modelid-400]][0];
	vehcol[vehicleid][1] = varray[modelid-400][colorused[modelid-400]][1];

	SetVehicleHealth(vehicleid, DEFAULT_VEHICLE_HEALTH);

	if (modelid == 548) {
		cargobobobleft[vehicleid] = CreateObject(19848, x + (floatsin(-(rotation - 90.0), degrees) * CARGOBOB_OB_X_OFFSET), y + (floatcos(-(rotation - 90.0), degrees) * CARGOBOB_OB_Y_OFFSET), z + CARGOBOB_OB_Z_OFFSET, 0.0, 0.0, rotation);
		AttachObjectToVehicle(cargobobobleft[vehicleid], vehicleid, -CARGOBOB_OB_X_OFFSET, CARGOBOB_OB_Y_OFFSET, -CARGOBOB_OB_Z_OFFSET, 0.0, 0.0, 0.0);
		cargobobobright[vehicleid] = CreateObject(19848, x + (floatsin(-(rotation + 90.0), degrees) * CARGOBOB_OB_X_OFFSET), y + (floatcos(-(rotation + 90.0), degrees) * CARGOBOB_OB_Y_OFFSET), z + CARGOBOB_OB_Z_OFFSET, 0.0, 0.0, rotation < 180.0 ? rotation + 180.0 : rotation - 180.0);
		AttachObjectToVehicle(cargobobobright[vehicleid], vehicleid, CARGOBOB_OB_X_OFFSET, CARGOBOB_OB_Y_OFFSET, -CARGOBOB_OB_Z_OFFSET, 0.0, 0.0, 180.0);
	}

//	SetVehicleBeenOccupied(vehicleid, true);

	dvucc[vehicleid] = true;

	return vehicleid;
}

stock DestroyVehicle2(vehicleid)
{
	new modelid = GetVehicleModel(vehicleid);

	if (colorused[modelid-400] > 0) colorused[modelid-400] --;
	else colorused[modelid-400] = varray[modelid-400][0][1];

	dvucc[vehicleid] = false;

	if (cargobobobleft[vehicleid] != 0) {
		DestroyObject(cargobobobleft[vehicleid]);
		cargobobobleft[vehicleid] = 0;
	}
	if (cargobobobright[vehicleid] != 0) {
		DestroyObject(cargobobobright[vehicleid]);
		cargobobobright[vehicleid] = 0;
	}

//	vmodelused[modelid-400] --;
//	if (vmodelused[modelid-400] == 0) vehiclemodels --;

	DestroyVehicle(vehicleid);
}

stock CreateVehicle3(modelid, Float:x, Float:y, Float:z, Float:rotation, color1, color2, respawn_delay, addsiren = 0)
{
//	vmodelused[modelid-400] ++;
//	if (vmodelused[modelid-400] == 1) vehiclemodels ++;

	new vehicleid = CreateVehicle(modelid, x, y, z, rotation, color1, color2, respawn_delay, addsiren);

	vehcol[vehicleid][0] = color1;
	vehcol[vehicleid][1] = color2;

	SetVehicleHealth(vehicleid, DEFAULT_VEHICLE_HEALTH);

	if (modelid == 548) {
		cargobobobleft[vehicleid] = CreateObject(19848, x + (floatsin(-(rotation - 90.0), degrees) * CARGOBOB_OB_X_OFFSET), y + (floatcos(-(rotation - 90.0), degrees) * CARGOBOB_OB_Y_OFFSET), z + CARGOBOB_OB_Z_OFFSET, 0.0, 0.0, rotation);
		AttachObjectToVehicle(cargobobobleft[vehicleid], vehicleid, -CARGOBOB_OB_X_OFFSET, CARGOBOB_OB_Y_OFFSET, -CARGOBOB_OB_Z_OFFSET, 0.0, 0.0, 0.0);
		cargobobobright[vehicleid] = CreateObject(19848, x + (floatsin(-(rotation + 90.0), degrees) * CARGOBOB_OB_X_OFFSET), y + (floatcos(-(rotation + 90.0), degrees) * CARGOBOB_OB_Y_OFFSET), z + CARGOBOB_OB_Z_OFFSET, 0.0, 0.0, rotation < 180.0 ? rotation + 180.0 : rotation - 180.0);
		AttachObjectToVehicle(cargobobobright[vehicleid], vehicleid, CARGOBOB_OB_X_OFFSET, CARGOBOB_OB_Y_OFFSET, -CARGOBOB_OB_Z_OFFSET, 0.0, 0.0, 180.0);
	}

//	SetVehicleBeenOccupied(vehicleid, true);
	return vehicleid;
}

stock DestroyVehicle3(vehicleid)
{
	if (cargobobobleft[vehicleid] != 0) {
		DestroyObject(cargobobobleft[vehicleid]);
		cargobobobleft[vehicleid] = 0;
	}
	if (cargobobobright[vehicleid] != 0) {
		DestroyObject(cargobobobright[vehicleid]);
		cargobobobright[vehicleid] = 0;
	}

//	new modelid = GetVehicleModel(vehicleid);

//	vmodelused[modelid-400] --;
//	if (vmodelused[modelid-400] == 0) vehiclemodels --;

	carwindows[vehicleid] = false;

	DestroyVehicle(vehicleid);
}

stock DestroyVehicle4(vehicleid)
{
	if (cargobobobleft[vehicleid] != 0) {
		DestroyObject(cargobobobleft[vehicleid]);
		cargobobobleft[vehicleid] = 0;
	}
	if (cargobobobright[vehicleid] != 0) {
		DestroyObject(cargobobobright[vehicleid]);
		cargobobobright[vehicleid] = 0;
	}

	if (dvucc[vehicleid]) {
		DestroyVehicle2(vehicleid);
	}
	else {
		DestroyVehicle3(vehicleid);
	}
}

stock AddStaticVehicleExByType2(vehicletype, Float:spawn_x, Float:spawn_y, Float:spawn_z, Float:z_angle, respawn_delay)
{
	new modelnew;
	switch (vehicletype)
	{
		case VEHICLE_TYPE_NORMAL:
		{
			modelnew = vtypenormal[MRandom(sizeof(vtypenormal))];
		}
		case VEHICLE_TYPE_INDUSTRIAL:
		{
			modelnew = vtypeindustrial[MRandom(sizeof(vtypeindustrial))];
		}
		case VEHICLE_TYPE_BIKE:
		{
			modelnew = vtypebike[MRandom(sizeof(vtypebike))];
		}
	}
	if (colorused[modelnew-400] < varray[modelnew-400][0][1]) colorused[modelnew-400] ++;
	else colorused[modelnew-400] = 1;

//	vmodelused[modelnew-400] ++;
//	if (vmodelused[modelnew-400] == 1) vehiclemodels ++;

	new vehicleid = AddStaticVehicleEx(modelnew, spawn_x, spawn_y, spawn_z, z_angle, varray[modelnew-400][colorused[modelnew-400]][0], varray[modelnew-400][colorused[modelnew-400]][1], respawn_delay);

	vehcol[vehicleid][0] = varray[modelnew-400][colorused[modelnew-400]][0];
	vehcol[vehicleid][1] = varray[modelnew-400][colorused[modelnew-400]][1];

	SetVehicleHealth(vehicleid, DEFAULT_VEHICLE_HEALTH);

	if (modelnew == 548) {
		cargobobobleft[vehicleid] = CreateObject(19848, spawn_x + (floatsin(-(z_angle - 90.0), degrees) * CARGOBOB_OB_X_OFFSET), spawn_y + (floatcos(-(z_angle - 90.0), degrees) * CARGOBOB_OB_Y_OFFSET), spawn_z + CARGOBOB_OB_Z_OFFSET, 0.0, 0.0, z_angle);
		AttachObjectToVehicle(cargobobobleft[vehicleid], vehicleid, -CARGOBOB_OB_X_OFFSET, CARGOBOB_OB_Y_OFFSET, -CARGOBOB_OB_Z_OFFSET, 0.0, 0.0, 0.0);
		cargobobobright[vehicleid] = CreateObject(19848, spawn_x + (floatsin(-(z_angle + 90.0), degrees) * CARGOBOB_OB_X_OFFSET), spawn_y + (floatcos(-(z_angle + 90.0), degrees) * CARGOBOB_OB_Y_OFFSET), spawn_z + CARGOBOB_OB_Z_OFFSET, 0.0, 0.0, z_angle < 180.0 ? z_angle + 180.0 : z_angle - 180.0);
		AttachObjectToVehicle(cargobobobright[vehicleid], vehicleid, CARGOBOB_OB_X_OFFSET, CARGOBOB_OB_Y_OFFSET, -CARGOBOB_OB_Z_OFFSET, 0.0, 0.0, 180.0);
	}

//	SetVehicleBeenOccupied(vehicleid, true);
	return vehicleid;
}
