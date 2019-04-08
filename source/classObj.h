#pragma once
#include <memory>
#include <list>

class Obj;

using sharedObj = std::shared_ptr<Obj>;
using sharedObjList = std::list<sharedObj>;
using sharedListObj = std::shared_ptr<sharedObjList>;
using ObjList_itr = sharedObjList::iterator;
using weakListObj = std::weak_ptr<sharedObjList>;

// ObjList‚É—v‘f‚ð’Ç‰Á‚·‚éŠÖ”µÌÞ¼Þª¸Ä
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