#pragma once

template <typename T>
class Single_Ton
{
	static T *m_iam;
public:
	static T *GetInstance()
	{
		if (m_iam == NULL)
			m_iam = new T;

		return m_iam;
	}
};


template <typename T> T *Single_Ton<T>::m_iam = NULL;