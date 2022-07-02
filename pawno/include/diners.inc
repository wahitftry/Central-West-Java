
stock CreateDinerSupports()
{
	// Welcome pump

	CreateObject(16500, 681.559, -448.303, -26.717, 0.0, 90.0, 0.0); // Floor
	CreateDynamicObject(16500, 680.339, -448.303, -24.577, 0.0, 0.0, 180.0, -1, 1, -1, 200.0); // Wall
	CreateDynamicObject(16500, 682.677, -448.303, -24.577, 0.0, 0.0, 0.0, -1, 1, -1, 200.0); // Wall


	// Small diner

	CreateObject(3095, 460.374, -107.655, 997.980, 0.0, 0.0, 0.0); // Floor
	CreateDynamicObject(3095, 451.374, -107.655, 997.980, 0.0, 0.0, 0.0, -1, 5, -1, 200.0); // Floor
	CreateDynamicObject(3095, 442.374, -107.655, 997.980, 0.0, 0.0, 0.0, -1, 5, -1, 200.0); // Floor

	CreateDynamicObject(8659, 460.043, -106.183, 998.594, 0.0, 0.0, 0.0, -1, 5, -1, 200.0); // Counter
	CreateDynamicObject(8659, 460.043, -106.301, 998.594, 0.0, 0.0, 0.0, -1, 5, -1, 200.0); // Counter

	CreateDynamicObject(8673, 451.693, -103.450, 999.740, 0.0, 0.0, 0.0, -1, 5, -1, 200.0); // Long wall
	CreateDynamicObject(8673, 451.693, -103.450, 1000.740, 0.0, 0.0, 0.0, -1, 5, -1, 200.0); // Long wall
	CreateDynamicObject(8673, 451.258, -111.747, 999.740, 0.0, 0.0, 180.0, -1, 5, -1, 200.0); // Long wall
	CreateDynamicObject(8673, 451.258, -111.747, 1000.740, 0.0, 0.0, 180.0, -1, 5, -1, 200.0); // Long wall

	CreateDynamicObject(16500, 441.723, -105.590, 1000.340, 90.0, 0.0, 0.0, -1, 5, -1, 200.0); // Small wall
	CreateDynamicObject(16500, 441.723, -109.590, 1000.340, 90.0, 0.0, 0.0, -1, 5, -1, 200.0); // Small wall
	CreateDynamicObject(16500, 461.235, -105.590, 1000.340, 90.0, 0.0, 180.0, -1, 5, -1, 200.0); // Small wall
	CreateDynamicObject(16500, 461.235, -109.590, 1000.340, 90.0, 0.0, 180.0, -1, 5, -1, 200.0); // Small wall
	
	CreateDynamicObject(8673, 451.258, -106.142, 1002.590, 98.835, 0.0, -180.0, -1, 5, -1, 200.0); // Roof
	CreateDynamicObject(8673, 451.258, -104.843, 1002.390, 98.835, 0.0, -180.0, -1, 5, -1, 200.0); // Roof
	CreateDynamicObject(8673, 451.693, -110.341, 1002.390, 98.835, 0.0, 0.0, -1, 5, -1, 200.0); // Roof
	CreateDynamicObject(8673, 451.693, -109.042, 1002.590, 98.835, 0.0, 0.0, -1, 5, -1, 200.0); // Roof

	
	// Large diner

	CreateDynamicObject(16773, 458.973, -85.620, 1002.405, 90.0, 0.0, 90.0, -1, 4, -1, 200.0); // Roof
	CreateDynamicObject(16773, 450.973, -85.620, 1002.405, 90.0, 0.0, 90.0, -1, 4, -1, 200.0); // Roof
	CreateDynamicObject(16773, 442.973, -85.620, 1002.405, 90.0, 0.0, 90.0, -1, 4, -1, 200.0); // Roof
	CreateDynamicObject(16773, 434.973, -85.620, 1002.405, 90.0, 0.0, 90.0, -1, 4, -1, 200.0); // Roof

}
