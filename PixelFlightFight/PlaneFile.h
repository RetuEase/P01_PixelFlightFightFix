#pragma once
#include "Globals.h"
#include "Instance.h"
#include "Workshop.h"

namespace PlaneFile
{
	void SavePlane(PlaneTemplate pt);		// �ļ������Դ��� PlaneId
	PlaneTemplate LoadPlane(PlaneId id);	// ���ļ����һ�� Instance
}