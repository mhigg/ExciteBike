#pragma once
#include <memory>
#include <list>

class Obj;

using sharedObj = std::shared_ptr<Obj>;
using sharedObjList = std::list<sharedObj>;
using sharedListObj = std::shared_ptr<sharedObjList>;
using ObjList_itr = sharedObjList::iterator;
using weakListObj = std::weak_ptr<sharedObjList>;

// ObjListに要素を追加する関数ｵﾌﾞｼﾞｪｸﾄ
struct AddObjList
{
	//public:
	ObjList_itr operator()(weakListObj objList, sharedObj objPtr)
	{
		//objList.expired();
		objList.lock()->push_back(std::move(objPtr));
		ObjList_itr itr = objList.lock()->end();
		itr--;
		return itr;
	}
};