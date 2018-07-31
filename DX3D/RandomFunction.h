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
	//0 ~ �����Ѽ���(num) ���̿� ���� �����ϰ� �޾ƿ´�
	inline int GetInt(int num) { return rand() % num; }
	//���� ������ ������ ���� �̾Ƴ��� �Լ�(ex 50, 100) 50���� 100����
	inline int GetFromIntTo(int fromNum, int toNum) { return rand() % (toNum - fromNum + 1) + fromNum; }


	//RAND_MAX��� ���� ������ �߻��� �� �ִ� �ִ� ��
	inline float GetFloat() { return (float)rand() / (float)RAND_MAX; }
	inline float GetFloat(float num) { return ((float)rand() / (float)RAND_MAX) * num; }
	inline float GetFromFloatTo(float fromFloat, float toFloat)
	{
		float rnd = (float)rand() / (float)RAND_MAX;

		return (rnd * (toFloat - fromFloat) + fromFloat);
	}

};