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