#include "CLinear_actu.h"

CLinear_actu::CLinear_actu(std::string mot_file)
{
	char* writable = new char[mot_file.size() + 1];
	std::copy(mot_file.begin(), mot_file.end(), writable);
	writable[mot_file.size()] = '\0';
	DWORD Code = AxlOpen(7);
	if (Code == AXT_RT_SUCCESS)
	{
		printf("라이브러리가 초기화되었습니다.\n");
		//모션 모듈이 있는지 검사
		DWORD uStatus;
		Code = AxmInfoIsMotionModule(&uStatus);
		if (Code == AXT_RT_SUCCESS)
		{
			printf("라이브러리가 초기화되었습니다.\n");
			if (uStatus == STATUS_EXIST)
			{
				printf("라이브러리가 초기화되었습니다.\n");

				AxmMotLoadParaAll(writable);

				AxmStatusSetActPos(0, 0.0);
				AxmStatusSetCmdPos(0, 0.0);

				AxmSignalServoOn(0, ENABLE);

				AxmMotSetAbsRelMode(0, 0); //0->abs, 1->Rel
				AxmMotSetProfileMode(0, 3);	//0->symetric trapezode, 1->unsymetric trapezode, 2->reserved, 3->symetric S Curve, 4->unsymetric S Cuve
			}
		}
	}
}

CLinear_actu::~CLinear_actu()
{
	AxmSignalServoOn(0, 0);
	AxlClose();
}


void CLinear_actu::move_actu(int pos, int vel_cmd, int accel_cmd)
{
	AxmMovePos(0, pos, vel_cmd, accel_cmd, accel_cmd);
	DWORD uStatus;
	AxmStatusReadInMotion(0, &uStatus);
	while (uStatus)
	{
		AxmStatusReadInMotion(0, &uStatus);
	}
}
