#include "stdafx.h"

#define g_pRandomFunc RandomFunction::GetInstance()

class RandomFunction 
{
	RandomFunction() 
	{
		srand(GetTickCount());
	}
	~RandomFunction() {}
public:
		static RandomFunction* GetInstance()
	{
		static RandomFunction instance; 
		return &instance; 
	}



public:
	//0 ~ 지정한숫자(num) 사이에 수를 랜덤하게 받아온다
	inline int GetInt(int num) { return rand() % num; }
	//범위 내에서 랜덤한 수를 뽑아내는 함수(ex 50, 100) 50부터 100사이
	inline int GetFromIntTo(int fromNum, int toNum) { return rand() % (toNum - fromNum + 1) + fromNum; }


	//RAND_MAX라는 것은 난수로 발생할 수 있는 최대 수
	inline float GetFloat() { return (float)rand() / (float)RAND_MAX; }
	inline float GetFloat(float num) { return ((float)rand() / (float)RAND_MAX) * num; }
	inline float GetFromFloatTo(float fromFloat, float toFloat)
	{
		float rnd = (float)rand() / (float)RAND_MAX;

		return (rnd * (toFloat - fromFloat) + fromFloat);
	}

};