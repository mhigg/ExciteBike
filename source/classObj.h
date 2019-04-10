//#pragma once
//#include <list>
//#include <memory>
//
//class Obj;
//
//using sharedObj = std::shared_ptr<Obj>;					// Obj�̼������߲��
//using sharedObjList = std::list<sharedObj>;				// Obj�̼������߲����ؽ�
//using sharedListObj = std::shared_ptr<sharedObjList>;	// Obj�������߲����ؽĂ̼������߲��
//using ObjList_itr = sharedObjList::iterator;			// sharedObjList�̲�ڰ�
//using weakListObj = std::weak_ptr<sharedObjList>;		// Obj�������߲����ؽĂ̳����߲��
//
//
//// ObjList�ɗv�f��ǉ�����֐���޼ު��
//struct AddObjList
//{
//	//public:
//	ObjList_itr operator()(weakListObj objList, sharedObj objPtr)
//	{
//		//objList.expired();
//		objList.lock()->push_back(std::move(objPtr));
//		ObjList_itr itr = objList.lock()->end();
//		itr--;
//		return itr;
//	}
//};

#pragma once
#include <list>
#include <memory>
#include "Obj.h"

class Obj;

using uniqueObj = std::unique_ptr<Obj>;			//Obj���ư��߲��
using uniqueObjList = std::list<uniqueObj>;		//Obj�ư��߲����ؽ�
using sharedListObj = std::shared_ptr<uniqueObjList>;	//Obj�ư��߲����ؽĂ̼������߲��
using ObjList_itr = uniqueObjList::iterator;	//uniqueObjList�̲�ڰ�


struct AddObjList
{

	ObjList_itr operator()(sharedListObj objList, uniqueObj objPtr)
	{
		objList->push_back(std::move(objPtr));
		ObjList_itr itr = objList->end();
		itr--;
		return itr;
	}
};