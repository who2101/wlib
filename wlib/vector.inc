/*
	Adds vector 1 on vector 2
	
	@param vec Vector 1
	@param add Vector 2
*/
stock void VectorAdd(float vec[3], float add[3])
{
	vec[0] = vec[0] + add[0];
	vec[1] = vec[1] + add[1];
	vec[2] = vec[2] + add[2];
}

/*
	Multiplies vector 1 on vector 2
	
	@param vec Vector 1
	@param mul Vector 2
*/
stock void VectorMul(float vec[3], float mul[3])
{
	vec[0] = vec[0] * mul[0];
	vec[1] = vec[1] * mul[1];
	vec[2] = vec[2] * mul[2];
}

/*
	Compares 2 vectors
	
	@param vec Vector 1
	@param mul Vector 2
*/
stock bool VectorEqual(const float vec[3], const float equal[3])
{
	for(int i = 0; i < 3; i++) if(vec[i] != equal[i])
	{
		return false;
	}
	
	return true;
}