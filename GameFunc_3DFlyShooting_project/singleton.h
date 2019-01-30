#pragma once

template<class T>
class singleton
{
private:
	static T * inst;
public:
	singleton() {}
	virtual ~singleton() {}

	static T & GetInst() {
		if (!inst)
			inst = new T;

		return *inst;
	}

	static void ReleaseInst() {
		if (inst)
			delete inst;

		inst = nullptr;
	}
};

template <class T>
T * singleton<T>::inst = nullptr;

