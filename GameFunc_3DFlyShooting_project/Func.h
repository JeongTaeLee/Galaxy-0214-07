#pragma once


//2 ���⺤���� ������ ���մϴ�.
Vector3 GetDirectionVector(const Vector3& v1, const Vector3& v2);

void GetBillBoardMatrix(Matrix& mat, const Vector3 & pos, const Vector3 & scale);
void SpaceToClient(Vector3& result, const Vector3& vPos);
//v1 = target ; v2 = start
void GetLookAt(const Vector3& v1, const Vector3& v2, Quaternion& nowQuater, float fS);