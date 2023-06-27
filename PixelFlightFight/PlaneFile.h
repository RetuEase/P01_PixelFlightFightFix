#pragma once
#include "Globals.h"
#include "Instance.h"
#include "Workshop.h"

namespace PlaneFile
{
	void SavePlane(PlaneTemplate pt);		// 文件名用自带的 PlaneId
	PlaneTemplate LoadPlane(PlaneId id);	// 从文件里读一个 Instance
}