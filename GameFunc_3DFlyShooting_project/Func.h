#pragma once


//2 방향벡터의 각도를 구합니다.
Vector3 GetDirectionVector(const Vector3& v1, const Vector3& v2);

void GetBillBoardMatrix(Matrix& mat, const Vector3 & pos, const Vector3 & scale);
void SpaceToClient(Vector3& result, const Vector3& vPos);
//v1 = target ; v2 = start
void GetLookAt(const Vector3& v1, const Vector3& v2, Quaternion& nowQuater, float fS);