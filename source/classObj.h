//#pragma once
//#include <list>
//#include <memory>
//
//class Obj;
//
//using sharedObj = std::shared_ptr<Obj>;					// Obj‚Ì¼ª±°ÄÞÎß²ÝÀ
//using sharedObjList = std::list<sharedObj>;				// Obj‚Ì¼ª±°ÄÞÎß²ÝÀ‚ÌØ½Ä
//using sharedListObj = std::shared_ptr<sharedObjList>;	// Obj¼ª±°ÄÞÎß²ÝÀ‚ÌØ½Ä‚Ì¼ª±°ÄÞÎß²ÝÀ
//using ObjList_itr = sharedObjList::iterator;			// sharedObjList‚Ì²ÃÚ°À
//using weakListObj = std::weak_ptr<sharedObjList>;		// Obj¼ª±°ÄÞÎß²ÝÀ‚ÌØ½Ä‚Ì³¨°¸Îß²ÝÀ
//
//
//// ObjList‚É—v‘f‚ð’Ç‰Á‚·‚éŠÖ”µÌÞ¼Þª¸Ä
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

using uniqueObj = std::unique_ptr<Obj>;			//Obj‚ÌÕÆ°¸Îß²ÝÀ
using uniqueObjList = std::list<uniqueObj>;		//ObjÕÆ°¸Îß²ÝÀ‚ÌØ½Ä
using sharedListObj = std::shared_ptr<uniqueObjList>;	//ObjÕÆ°¸Îß²ÝÀ‚ÌØ½Ä‚Ì¼ª±°ÄÞÎß²ÝÀ
using ObjList_itr = uniqueObjList::iterator;	//uniqueObjList‚Ì²ÃÚ°À


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