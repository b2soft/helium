#pragma once

#include "Head.h"

template<typename T> class singleton
{
public:
	static T& get()
	{
		static T theSingleInstance; // � ������ T ���� ����������� �� ���������
		return theSingleInstance;
	}
};