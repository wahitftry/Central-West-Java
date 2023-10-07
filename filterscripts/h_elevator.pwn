
#include <a_samp>
#include <streamer>
#include <utils>

#pragma unused gPlayerCheckpointStatus
#pragma unused pilotrespond

#define ELEVATOR_SPEED (5.0)

#define DOORS_SPEED (1.0)

#define ELEVATOR_WAIT_TIME (5000)

#define MAX_ELEVATOR_OBJECTS 10

enum e_info
{
	Float:e_x,
	Float:e_y,
	Float:e_z,
	Float:e_xr,
	Float:e_yr,
	Float:e_zr
}

new Float:elevatorcoords[MAX_ELEVATOR_OBJECTS][e_info] =
{
	{1771.757934, -1355.374877, 1031.061401, 0.000000, 0.000000, 226.309997},
	{1771.757934, -1354.180053, 1031.061401, 0.000000, 0.000000, 226.309997},
	{1769.953002, -1355.976074, 1031.061401, 0.000000, 0.000000, -43.690002},
	{1771.167846, -1355.976806, 1031.061401, 0.000000, 0.000000, 136.309997},
	{1769.952148, -1353.603027, 1031.061401, 0.000000, 0.000000, -43.690002},
	{1771.153808, -1353.604980, 1031.061401, 0.000000, 0.000000, 316.309997},
	{1770.723999, -1355.394897, 1029.699340, -46.400009, -90.000000, 0.410003},
	{1770.722045, -1354.186035, 1029.698364, 313.699920, 270.000000, 180.309997},
	{1770.723999, -1355.389892, 1032.421508, 46.099983, 90.000000, 0.410003},
	{1770.722045, -1354.186035, 1032.424438, 406.100006, 450.000000, 180.309997}
};

#define Y_DOOR_L_CLOSED (-1355.397949)
#define Y_DOOR_R_CLOSED (-1354.180053)
#define Y_DOOR_L_OPENED Y_DOOR_L_CLOSED - 1.125
#define Y_DOOR_R_OPENED Y_DOOR_R_CLOSED + 1.125
#define X_DOOR (1769.647888)
#define GROUND_Z_COORD (1031.061401)

#define E_USE_TEXT_X (1770.70)
#define E_USE_TEXT_Y (-1355.62)
#define E_CALL_TEXT_X (1768.58)
#define E_CALL_TEXT_Y (-1356.38)
#define E_TEXT_Z (1031.061439)

#define ELEVATOR_STATE_IDLE (0)
#define ELEVATOR_STATE_WAITING (1)
#define ELEVATOR_STATE_MOVING (2)

#define MAX_HOSPITALS 4

new hospitalvworlds[MAX_HOSPITALS] = {10095, 10096, 10097, 10098};

#define MAX_FLOORS 2

#define INVALID_FLOOR (-1)

static FloorNames[MAX_FLOORS][] =
{
	"Ground Floor",
	"First Floor"
};

static Float:FloorZOffsets[MAX_FLOORS] =
{
	0.0,
	3.962
};

new Obj_Elevator[MAX_HOSPITALS][MAX_ELEVATOR_OBJECTS], Obj_ElevatorDoors[MAX_HOSPITALS][2];
new Obj_FloorDoor1[MAX_HOSPITALS][MAX_FLOORS], Obj_FloorDoor2[MAX_HOSPITALS][MAX_FLOORS];

new Text3D:Label_Elevator[MAX_HOSPITALS], Text3D:Label_Floors[MAX_HOSPITALS][MAX_FLOORS];

new ElevatorState[MAX_HOSPITALS];

new	ElevatorFloor[MAX_HOSPITALS];

new ElevatorQueue[MAX_HOSPITALS][MAX_FLOORS];

new	FloorRequestedBy[MAX_HOSPITALS][MAX_FLOORS];

new ElevatorBoostTimer[MAX_HOSPITALS] = {-1, ...};
new ElevatorIdleTimer[MAX_HOSPITALS] = {-1, ...};

forward Elevator_Boost(hospitalid, floorid);
forward Elevator_TurnToIdle(hospitalid);

public OnFilterScriptInit()
{

	for (new e = 0; e < MAX_HOSPITALS; e++)
	{
		ResetElevatorQueue(e);

		Elevator_Initialize(e);
	}

	return 1;
}

public OnFilterScriptExit()
{
	for (new e = 0; e < MAX_HOSPITALS; e++)
	{
		Elevator_Destroy(e);

		if (ElevatorBoostTimer[e] != -1)
		{
			KillTimer(ElevatorBoostTimer[e]);
			ElevatorBoostTimer[e] = -1;
		}

		if (ElevatorIdleTimer[e] != -1)
		{
			KillTimer(ElevatorIdleTimer[e]);
			ElevatorIdleTimer[e] = -1;
		}
	}
	return 1;
}

public OnDynamicObjectMoved(objectid)
{
	new Float:x, Float:y, Float:z;

	for (new e = 0, temp1 = 0; e < MAX_HOSPITALS; e++)
	{
		if (temp1 == 1) break;
		if (objectid == Obj_Elevator[e][0])
		{
			KillTimer(ElevatorBoostTimer[e]);
			ElevatorBoostTimer[e] = -1;

			FloorRequestedBy[e][ElevatorFloor[e]] = INVALID_PLAYER_ID;

			Elevator_OpenDoors(e);

			Floor_OpenDoors(e, ElevatorFloor[e]);

			GetDynamicObjectPos(Obj_Elevator[e][0], x, y, z);
			Label_Elevator[e] = Create3DTextLabel("{CCCCCC}Press '{FFFFFF}~k~~CONVERSATION_YES~{CCCCCC}' to use elevator", 0xCCCCCCAA, E_USE_TEXT_X, E_USE_TEXT_Y, E_TEXT_Z + FloorZOffsets[ElevatorFloor[e]], 4.0, hospitalvworlds[e], 1);

			ElevatorState[e] = ELEVATOR_STATE_WAITING;
			ElevatorIdleTimer[e] = SetTimerEx("Elevator_TurnToIdle", ELEVATOR_WAIT_TIME, 0, "d", e);

			temp1 = 1;
		}
		else
		{
			for (new i = 0; i < MAX_FLOORS; i++)
			{
				if (objectid == Obj_FloorDoor1[e][i])
				{
					GetDynamicObjectPos(objectid, x, y, z);
					if (y == Y_DOOR_L_CLOSED)
					{
						Elevator_MoveToFloor(e, ElevatorQueue[e][0]);
						RemoveFirstQueueFloor(e);
					}
					temp1 = 1;
					break;
				}
			}
		}
	}

	return 1;
}

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	if (dialogid >= 1000 - MAX_HOSPITALS && dialogid < 1000)
	{
		TogglePlayerControllable(playerid, 1);

		if (!response) return 0;

		new temp1 = GetPVarInt(playerid, "playerhospitalid");
		if (FloorRequestedBy[temp1][listitem] != INVALID_PLAYER_ID || IsFloorInQueue(temp1, listitem))
		{
			GameTextForPlayer(playerid, "~r~This floor is already in the queue", 3500, 4);
		}
		else if (DidPlayerRequestElevator(playerid, temp1))
		{
			GameTextForPlayer(playerid, "~r~You already requested the elevator", 3500, 4);
		}
		else
		{
			CallElevator(playerid, listitem);
		}

		return 1;
	}

	return 0;
}

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if (GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return 1;

	if (newkeys & KEY_YES)
	{
		new Float:x, Float:y, Float:z;
		GetPlayerPos(playerid, x, y, z);
		new Float:temp1 = Y_DOOR_R_CLOSED - ((Y_DOOR_R_CLOSED - Y_DOOR_L_CLOSED) / 2.0);
		if (x > X_DOOR && x < X_DOOR + 2.00 && y < temp1 + 2.0 && y > temp1 - 2.0)
		{
			ShowElevatorDialog(playerid);
		}
		else
		{
			if (x < X_DOOR && x > X_DOOR - 2.00 && y < temp1 + 2.0 && y > temp1 - 2.0)
			{
				new i = 0;
				if (z > GROUND_Z_COORD - 2.0 && z < GROUND_Z_COORD + 2.0)
				{
					i = 0;
				}
				else
				{
					i = 1;
				}
				new temp2 = GetPVarInt(playerid, "playerhospitalid");
				if (ElevatorState[temp2] != ELEVATOR_STATE_MOVING && ElevatorFloor[temp2] == i)
				{
					GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~r~This Elevator~n~~r~Is Already On~n~~r~This Floor!", 3000, 5);
					return 1;
				}
				CallElevator(playerid, i);
				GameTextForPlayer(playerid, "~r~Elevator called", 3500, 4);
			}
		}
	}

	return 1;
}

Float:GetDoorsZCoordForFloor(floorid)
{
	return GROUND_Z_COORD + FloorZOffsets[floorid];
}

Elevator_Initialize(hospitalid)
{
	for (new i = 0; i < MAX_ELEVATOR_OBJECTS; i++)
	{
		Obj_Elevator[hospitalid][i] = CreateDynamicObject(3051, elevatorcoords[i][e_x], elevatorcoords[i][e_y], elevatorcoords[i][e_z], elevatorcoords[i][e_xr], elevatorcoords[i][e_yr], elevatorcoords[i][e_zr], hospitalvworlds[hospitalid], 1, -1, 300.0);
	}
	Obj_ElevatorDoors[hospitalid][0] = CreateDynamicObject(3051, X_DOOR, Y_DOOR_L_CLOSED, GROUND_Z_COORD, 0.000000, 0.000000, 46.309997, hospitalvworlds[hospitalid], 1, -1, 300.0);
	Obj_ElevatorDoors[hospitalid][1] = CreateDynamicObject(3051, X_DOOR, Y_DOOR_R_CLOSED, GROUND_Z_COORD, 720.000000, 360.000000, 226.309997, hospitalvworlds[hospitalid], 1, -1, 300.0);

	Label_Elevator[hospitalid] = Create3DTextLabel("{CCCCCC}Press '{FFFFFF}~k~~CONVERSATION_YES~{CCCCCC}' to use elevator", 0xCCCCCCAA, E_USE_TEXT_X, E_USE_TEXT_Y, E_TEXT_Z + FloorZOffsets[ElevatorFloor[hospitalid]], 4.0, hospitalvworlds[hospitalid], 1);

	for (new i = 0, string[128]; i < MAX_FLOORS; i++)
	{
		Obj_FloorDoor1[hospitalid][i] = CreateDynamicObject(3051, X_DOOR - 0.29, Y_DOOR_L_CLOSED, GetDoorsZCoordForFloor(i), 0.000000, 0.000000, 46.309997, hospitalvworlds[hospitalid], 1, -1, 300.0);
		Obj_FloorDoor2[hospitalid][i] = CreateDynamicObject(3051, X_DOOR - 0.29, Y_DOOR_R_CLOSED, GetDoorsZCoordForFloor(i), 0.000000, 0.000000, 226.309997, hospitalvworlds[hospitalid], 1, -1, 300.0);

		format(string, sizeof(string), "{CCCCCC}[%s]\n{CCCCCC}Press '{FFFFFF}~k~~CONVERSATION_YES~{CCCCCC}' to call", FloorNames[i]);

		Label_Floors[hospitalid][i] = Create3DTextLabel(string, 0xCCCCCCAA, E_CALL_TEXT_X, E_CALL_TEXT_Y, E_TEXT_Z + FloorZOffsets[i], 10.5, hospitalvworlds[hospitalid], 1);
	}

	Floor_OpenDoors(hospitalid, 0);
	Elevator_OpenDoors(hospitalid);
}

Elevator_Destroy(hospitalid)
{
	for (new i = 0; i < MAX_ELEVATOR_OBJECTS; i++)
	{
		DestroyDynamicObject(Obj_Elevator[hospitalid][i]);
	}
	DestroyDynamicObject(Obj_ElevatorDoors[hospitalid][0]);
	DestroyDynamicObject(Obj_ElevatorDoors[hospitalid][1]);

	Delete3DTextLabel(Label_Elevator[hospitalid]);

	for (new i = 0; i < MAX_FLOORS; i++)
	{
		DestroyDynamicObject(Obj_FloorDoor1[hospitalid][i]);
		DestroyDynamicObject(Obj_FloorDoor2[hospitalid][i]);
		Delete3DTextLabel(Label_Floors[hospitalid][i]);
	}
}

Elevator_OpenDoors(hospitalid)
{
	new Float:x, Float:y, Float:z;
	GetDynamicObjectPos(Obj_ElevatorDoors[hospitalid][0], x, y, z);

	MoveDynamicObject(Obj_ElevatorDoors[hospitalid][0], x, Y_DOOR_L_OPENED, z, DOORS_SPEED);
	MoveDynamicObject(Obj_ElevatorDoors[hospitalid][1], x, Y_DOOR_R_OPENED, z, DOORS_SPEED);
}

Elevator_CloseDoors(hospitalid)
{
	if (ElevatorState[hospitalid] == ELEVATOR_STATE_MOVING) return 0;

	new Float:x, Float:y, Float:z;

	GetDynamicObjectPos(Obj_ElevatorDoors[hospitalid][0], x, y, z);
	MoveDynamicObject(Obj_ElevatorDoors[hospitalid][0], x, Y_DOOR_L_CLOSED, z, DOORS_SPEED);
	MoveDynamicObject(Obj_ElevatorDoors[hospitalid][1], x, Y_DOOR_R_CLOSED, z, DOORS_SPEED);

	return 1;
}

PlaySoundForPlayersInRange(soundid, Float:range, Float:x, Float:y, Float:z, virtualworld = 0)
{
	for (new i = 0; i < MAX_PLAYERS; i++)
	{
		if (!IsPlayerConnected(i)) continue;
		if (IsPlayerInRangeOfPoint(i, range, x, y, z) && GetPlayerVirtualWorld(i) == virtualworld)
		{
			PlayerPlaySound(i, soundid, x, y, z);
		}
	}
}

Floor_OpenDoors(hospitalid, floorid)
{
	MoveDynamicObject(Obj_FloorDoor1[hospitalid][floorid], X_DOOR - 0.29, Y_DOOR_L_OPENED, GetDoorsZCoordForFloor(floorid), DOORS_SPEED);
	MoveDynamicObject(Obj_FloorDoor2[hospitalid][floorid], X_DOOR - 0.29, Y_DOOR_R_OPENED, GetDoorsZCoordForFloor(floorid), DOORS_SPEED);

	PlaySoundForPlayersInRange(6401, 50.0, X_DOOR, Y_DOOR_R_CLOSED - ((Y_DOOR_R_CLOSED - Y_DOOR_L_CLOSED) / 2.0), GetDoorsZCoordForFloor(floorid) + 5.0, hospitalvworlds[hospitalid]);
}

Floor_CloseDoors(hospitalid, floorid)
{
	MoveDynamicObject(Obj_FloorDoor1[hospitalid][floorid], X_DOOR - 0.29, Y_DOOR_L_CLOSED, GetDoorsZCoordForFloor(floorid), DOORS_SPEED);
	MoveDynamicObject(Obj_FloorDoor2[hospitalid][floorid], X_DOOR - 0.29, Y_DOOR_R_CLOSED, GetDoorsZCoordForFloor(floorid), DOORS_SPEED);

	PlaySoundForPlayersInRange(6401, 50.0, X_DOOR, Y_DOOR_R_CLOSED - ((Y_DOOR_R_CLOSED - Y_DOOR_L_CLOSED) / 2.0), GetDoorsZCoordForFloor(floorid) + 5.0, hospitalvworlds[hospitalid]);
}

Elevator_MoveToFloor(hospitalid, floorid)
{
	ElevatorState[hospitalid] = ELEVATOR_STATE_MOVING;
	ElevatorFloor[hospitalid] = floorid;

	for (new i = 0; i < MAX_ELEVATOR_OBJECTS; i++)
	{
		MoveDynamicObject(Obj_Elevator[hospitalid][i], elevatorcoords[i][e_x], elevatorcoords[i][e_y], elevatorcoords[i][e_z] + FloorZOffsets[floorid], 0.25);
	}
	MoveDynamicObject(Obj_ElevatorDoors[hospitalid][0], X_DOOR, Y_DOOR_L_CLOSED, GetDoorsZCoordForFloor(floorid), 0.25);
	MoveDynamicObject(Obj_ElevatorDoors[hospitalid][1], X_DOOR, Y_DOOR_R_CLOSED, GetDoorsZCoordForFloor(floorid), 0.25);

	Delete3DTextLabel(Label_Elevator[hospitalid]);

	ElevatorBoostTimer[hospitalid] = SetTimerEx("Elevator_Boost", 2000, 0, "dd", hospitalid, floorid);
}

public Elevator_Boost(hospitalid, floorid)
{
	for (new i = 0; i < MAX_ELEVATOR_OBJECTS; i++)
	{
		StopDynamicObject(Obj_Elevator[hospitalid][i]);
		MoveDynamicObject(Obj_Elevator[hospitalid][i], elevatorcoords[i][e_x], elevatorcoords[i][e_y], elevatorcoords[i][e_z] + FloorZOffsets[floorid], ELEVATOR_SPEED);
	}
	StopDynamicObject(Obj_ElevatorDoors[hospitalid][0]);
	StopDynamicObject(Obj_ElevatorDoors[hospitalid][1]);
	MoveDynamicObject(Obj_ElevatorDoors[hospitalid][0], X_DOOR, Y_DOOR_L_CLOSED, GetDoorsZCoordForFloor(floorid), ELEVATOR_SPEED);
	MoveDynamicObject(Obj_ElevatorDoors[hospitalid][1], X_DOOR, Y_DOOR_R_CLOSED, GetDoorsZCoordForFloor(floorid), ELEVATOR_SPEED);
}

public Elevator_TurnToIdle(hospitalid)
{
	ElevatorState[hospitalid] = ELEVATOR_STATE_IDLE;
	ReadNextFloorInQueue(hospitalid);

	KillTimer(ElevatorIdleTimer[hospitalid]);
	ElevatorIdleTimer[hospitalid] = -1;
}

RemoveFirstQueueFloor(hospitalid)
{
	for (new i = 0; i < MAX_FLOORS - 1; i++)
	{
		ElevatorQueue[hospitalid][i] = ElevatorQueue[hospitalid][i + 1];
	}
	ElevatorQueue[hospitalid][MAX_FLOORS - 1] = INVALID_FLOOR;
}

AddFloorToQueue(hospitalid, floorid)
{
	new slot = -1;
	for (new i = 0; i < MAX_FLOORS; i++)
	{
		if (ElevatorQueue[hospitalid][i] == INVALID_FLOOR)
		{
			slot = i;
			break;
		}
	}
	if (slot != -1)
	{
		ElevatorQueue[hospitalid][slot] = floorid;
		if (ElevatorState[hospitalid] == ELEVATOR_STATE_IDLE)
		{
			ReadNextFloorInQueue(hospitalid);
		}
	}
}

ResetElevatorQueue(hospitalid)
{
	for (new i = 0; i < MAX_FLOORS; i++)
	{
		ElevatorQueue[hospitalid][i] = INVALID_FLOOR;
		FloorRequestedBy[hospitalid][i] = INVALID_PLAYER_ID;
	}
}

IsFloorInQueue(hospitalid, floorid)
{
	for (new i = 0; i < MAX_FLOORS; i++)
	{
		if (ElevatorQueue[hospitalid][i] == floorid) return 1;
	}
	return 0;
}

ReadNextFloorInQueue(hospitalid)
{
	if (ElevatorState[hospitalid] != ELEVATOR_STATE_IDLE || ElevatorQueue[hospitalid][0] == INVALID_FLOOR) return 0;

	Elevator_CloseDoors(hospitalid);
	Floor_CloseDoors(hospitalid, ElevatorFloor[hospitalid]);

	return 1;
}

DidPlayerRequestElevator(playerid, hospitalid)
{
	for (new i = 0; i < MAX_FLOORS; i++)
	{
		if (FloorRequestedBy[hospitalid][i] == playerid) return 1;
	}
	return 0;
}

ShowElevatorDialog(playerid)
{
	new temp1 = GetPVarInt(playerid, "playerhospitalid");
	new string[512];
	for (new i = 0; i < MAX_FLOORS; i++)
	{
		if (FloorRequestedBy[temp1][i] != INVALID_PLAYER_ID)
		{
			strcat(string, "{FF0000}");
		}
		strcat(string, FloorNames[i]);
		strcat(string, "\n");
	}
	TogglePlayerControllable(playerid, 0);
	ShowPlayerDialog(playerid, 1000 - (temp1 + 1), DIALOG_STYLE_LIST, "Hospital Elevator", string, "Select", "Cancel");
}

CallElevator(playerid, floorid)
{
	new temp1 = GetPVarInt(playerid, "playerhospitalid");

	if (FloorRequestedBy[temp1][floorid] != INVALID_PLAYER_ID || IsFloorInQueue(temp1, floorid)) return 0;

	FloorRequestedBy[temp1][floorid] = playerid;
	AddFloorToQueue(temp1, floorid);

	return 1;
}

