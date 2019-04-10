//#pragma once
//#include <list>
//#include <memory>
//
//class Obj;
//
//using sharedObj = std::shared_ptr<Obj>;					// Objのｼｪｱｰﾄﾞﾎﾟｲﾝﾀ
//using sharedObjList = std::list<sharedObj>;				// Objのｼｪｱｰﾄﾞﾎﾟｲﾝﾀのﾘｽﾄ
//using sharedListObj = std::shared_ptr<sharedObjList>;	// Objｼｪｱｰﾄﾞﾎﾟｲﾝﾀのﾘｽﾄのｼｪｱｰﾄﾞﾎﾟｲﾝﾀ
//using ObjList_itr = sharedObjList::iterator;			// sharedObjListのｲﾃﾚｰﾀ
//using weakListObj = std::weak_ptr<sharedObjList>;		// Objｼｪｱｰﾄﾞﾎﾟｲﾝﾀのﾘｽﾄのｳｨｰｸﾎﾟｲﾝﾀ
//
//
//// ObjListに要素を追加する関数ｵﾌﾞｼﾞｪｸﾄ
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