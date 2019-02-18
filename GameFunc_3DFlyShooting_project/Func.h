#pragma once


//2 방향벡터의 각도를 구합니다.
Vector3 GetDirectionVector(const Vector3& v1, const Vector3& v2);

void GetBillBoardMatrix(Matrix& mat, const Vector3 & pos, const Vector3 & scale);
void SpaceToClient(Vector3& result, const Vector3& vPos);

//v1 = target ; v2 = start
void GetLookAt(const Vector3& v1, const Vector3& v2, Quaternion& nowQuater, float fS);

//CreateEffect
void CreateEffectA(const Vector3& pos, const Vector3  & scale= Vector3(1.f, 1.f, 1.f), float speed = 0.05f);

template<typename T>
T GetRandomNumber(T mn, T mx);

template< >
float GetRandomNumber < float >(float mn, float mx);

template< >
Vector3 GetRandomNumber < Vector3 >(Vector3 mn, Vector3 mx);

template<typename T>
inline T GetRandomNumber(T mn, T mx)
{
	if (mn >= mx)
		return T();

	std::random_device rn;
	std::mt19937_64 rnd(rn());

	std::uniform_int_distribution<T> range(mn, mx);

	return range(rnd);
}

template<>
inline float GetRandomNumber(float mn, float mx)
{
	if (mn >= mx)
		return 0.f;

	std::random_device rn;
	std::mt19937_64 rnd(rn());

	std::uniform_real_distribution<float> range(mn, mx);

	return range(rnd);
}

template<>
inline Vector3 GetRandomNumber(Vector3 mn, Vector3 mx)
{
	std::random_device rn;
	std::mt19937_64 rnd(rn());
	
	Vector3 result = Vector3(0.f, 0.f, 0.f);
	
	if (mn.x < mx.x)
	{
		std::uniform_real_distribution<float> range(mn.x, mx.x);
	
		result.x = range(rnd);
	}
	if (mn.y < mx.y)
	{
		std::uniform_real_distribution<float> range(mn.y, mx.y);
	
		result.y = range(rnd);
	}
	if (mn.z < mx.z)
	{
		std::uniform_real_distribution<float> range(mn.z, mx.z);
	
		result.z = range(rnd);
	}

	return result;
}
