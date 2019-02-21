#pragma once


float GetLengthVector2(const Vector2& v1, const Vector2& v2);
float GetLengthVector3(const Vector3& v1, const Vector3& v2);

void GetBillBoardMatrix(Matrix& mat, const Vector3 & pos, const Vector3 & scale);
void SpaceToClient(Vector3& result, const Vector3& vPos);

//v1 = target ; v2 = start
void GetSLerpLookAt(const Vector3& v1, const Vector3& v2, Quaternion& nowQuater, float fS);
void GetLookAt(Quaternion & q, const Vector3& v1, const Vector3& v2);

//CreateEffect
void CreateEffectA(const Vector3& pos, const Vector3  & scale= Vector3(1.f, 1.f, 1.f), float speed = 0.05f);

#pragma region GetRandomNumber_Template
template<typename T>
T inline GetRandomNumber(T mn, T mx)
{
	if (mn >= mx)
		return T();

	std::random_device rn;
	std::mt19937_64 rnd(rn());

	std::uniform_int_distribution<T> range(mn, mx);

	return range(rnd);
}


template< >
float inline GetRandomNumber < float >(float mn, float mx)
{
	if (mn >= mx)
		return 0.f;

	std::random_device rn;
	std::mt19937_64 rnd(rn());

	std::uniform_real_distribution<float> range(mn, mx);

	return range(rnd);
}

template< >
Vector3 inline GetRandomNumber < Vector3 >(Vector3 mn, Vector3 mx)
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
#pragma endregion GetRandomNumber_Template