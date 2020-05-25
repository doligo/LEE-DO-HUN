#include "Std_manager.h"
#include "Std_manager.cpp"

template<typename T>
void main()
{
	Std_manager<T>::GetInstance();

	// 사용할수있는 멤버가 없다고 뜨거나 링크 2019, 1120 오류
}
