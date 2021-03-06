#pragma once
#include <list>
#include <memory>
#include "Obj.h"

class Obj;

using uniqueObj = std::unique_ptr<Obj>;			//Objのﾕﾆｰｸﾎﾟｲﾝﾀ
using uniqueObjList = std::list<uniqueObj>;		//Objﾕﾆｰｸﾎﾟｲﾝﾀのﾘｽﾄ
using sharedListObj = std::shared_ptr<uniqueObjList>;	//Objﾕﾆｰｸﾎﾟｲﾝﾀのﾘｽﾄのｼｪｱｰﾄﾞﾎﾟｲﾝﾀ
using ObjList_itr = uniqueObjList::iterator;	//uniqueObjListのｲﾃﾚｰﾀ


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