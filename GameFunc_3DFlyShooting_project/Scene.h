#pragma once
class Scene
{
protected:
	bool bLoadingComplete;
public:
	Scene();
	virtual ~Scene();

	virtual void Init()	PURE;
	virtual void Release() PURE;

	virtual void LoadingResource() { bLoadingComplete = true; }
	bool GetLoadingComplete() { return bLoadingComplete; }
	void ResetLoadingComplete() { bLoadingComplete = false; }
};

