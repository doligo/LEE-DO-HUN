#include "Computer.h"

#pragma once


void main()
{
	int num = 0;

	Login log;
	Computer com;
	
	while (1)
	{
		com.Menu(); // login��������� �׳�  ���� com���� ����
		if (com.exit == TRUE)
		{
			break;
		}
		com.Change_Login_Status(num); // com���� �������°��� �������� ����־��
		com.Menu2();
	}

}