#pragma once
#include <list>
#include <memory>

class Obj;

using sharedObj = std::shared_ptr<Obj>;					// Obj�̼������߲��
using sharedObjList = std::list<sharedObj>;				// Obj�̼������߲����ؽ�
using sharedListObj = std::shared_ptr<sharedObjList>;	// Obj�������߲����ؽĂ̼������߲��
using ObjList_itr = sharedObjList::iterator;			// sharedObjList�̲�ڰ�
using weakListObj = std::weak_ptr<sharedObjList>;		// Obj�������߲����ؽĂ̳����߲��


// ObjList�ɗv�f��ǉ�����֐���޼ު��
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