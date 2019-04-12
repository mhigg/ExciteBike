#pragma once
#include <DxLib.h>
#include <string>
#include <map>
#include "VECTOR2.h"
#include "classObj.h"

enum ANIM_TBL {
	ANIM_TBL_START_ID,		// ｱﾆﾒｰｼｮﾝの開始
	ANIM_TBL_FRAME,			// ｱﾆﾒｰｼｮﾝのｺﾏ数
	ANIM_TBL_INV,			// ｺﾏごとの間隔
	ANIM_TBL_MAX
};

enum OBJ_TYPE {
	OBJ_PLAYER,			// ﾌﾟﾚｲﾔｰ
	OBJ_BIKE,			// ﾊﾞｲｸ
	OBJ_OBSTACLE,		// 障害物
	OBJ_MAX
};

class GameCtrl;

class Obj
{

public:
	Obj();
	Obj(VECTOR2 drawOffset);	// 受け取ったdrawOffsetを自分の持つdrawOffsetに入れる
	bool init(
		std::string fileName,
		VECTOR2 divSize,
		VECTOR2 divCnt
	);	// 画像のﾌｧｲﾙ名,分割ｻｲｽﾞ,分割数の初期化
	bool init(
		std::string fileName,
		VECTOR2 divSize,
		VECTOR2 divCnt,
		VECTOR pos
	);	// 画像のﾌｧｲﾙ名,分割ｻｲｽﾞ,分割数の初期化,座標
	virtual ~Obj();
	void UpDate(const GameCtrl &controller);	// 情報更新	ｺﾝﾄﾛｰﾗｰ自体のﾎﾟｲﾝﾀを渡す
	virtual void Draw(void);					// 描画
	void Draw(unsigned int id);					// ID指定描画
	const VECTOR &GetPos(void);					// 座標取得関数

	bool AddAnim(
		std::string animName,	// ｱﾆﾒｰｼｮﾝの名前
		int id_x,				// 動き
		int id_y,				// 種別
		int frame,				// ｺﾏ数
		int inv					// 間隔の設定
	);
	bool SetAnim(std::string animName);
	std::string GetAnim(void);
	virtual bool CheckDeath(void) { return false; };	// Player:死亡判定
	virtual bool CheckObjType(OBJ_TYPE type) = 0;

private:
	virtual void SetMove(const GameCtrl &controller) = 0;

	std::string animName;	// 表示するｱﾆﾒｰｼｮﾝ名
	std::map<std::string, int[ANIM_TBL_MAX]> animTable;

protected:
	std::string imageName;	// 表示する画像のﾌｧｲﾙ名
	VECTOR2 divSize;		// 画像の分割ｻｲｽﾞ
	VECTOR2 divCnt;			// 画像の分割数

	unsigned int animCnt;	// ｱﾆﾒｰｼｮﾝのｶｳﾝﾄ

	VECTOR2 drawPos;			// 表示する際の座標 : y座標はﾌﾟﾚｲﾔｰ座標のyとzを足した値
	VECTOR pos;					// ﾌﾟﾚｲﾔｰのｽﾃｰｼﾞ上の座標
	void SetPos(VECTOR pos);

	const VECTOR2 drawOffset;		// 描画ｵﾌｾｯﾄ
};