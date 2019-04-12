#include <DxLib.h>
#include <string>
#include <vector>
#include <map>
#include "VECTOR2.h"
#include "ImageMng.h"

struct ActionHeader {
	float version;			// ﾌｧｲﾙのﾊﾞｰｼﾞｮﾝ
	std::string fileName;	// ﾌｧｲﾙ名
	int actCnt;				// ｱｸｼｮﾝの種類数 ←この個数分だけforﾙｰﾌﾟしてｱｸｼｮﾝごとにまとめる
};

struct ActionData {
	bool loop;				// ｱﾆﾒｰｼｮﾝをﾙｰﾌﾟするかどうか
	VECTOR2 rect;			// 分割開始位置
	int width;				// 1ｺﾏの画像の横の長さ
	int height;				// 1ｺﾏの画像の縦の長さ
	VECTOR2 center;			// 1ｺﾏの画像の中心点
	int duration;			// ｱﾆﾒｰｼｮﾝのｺﾏ間隔
		int actRcType;			// 当たり判定用矩形の種類
		VECTOR2 actRect;		// 当たり判定用矩形の開始位置
		int actRcWidth;			// 当たり判定用矩形の横の長さ
		int actRcHeight;		// 当たり判定用矩形の縦の長さ
};

ImageMng::ImageMng()
{
}


ImageMng::~ImageMng()
{
}

//loadGraph用
const VEC_INT& ImageMng::GetID(std::string f_name)
{
	//end(終端)までfind(検索)しても見つからないとき
	if (imageMap.find(f_name) == imageMap.end())
	{
		imageMap[f_name].resize(1);
		//f_nameをﾛｰﾄﾞして保存
		imageMap[f_name][0] = LoadGraph(f_name.c_str(), false);
	}
	return imageMap[f_name];
}

//divGraph用
const VEC_INT & ImageMng::GetID(std::string f_name, VECTOR2 divSize, VECTOR2 divCnt)
{
	if (imageMap.find(f_name) == imageMap.end())
	{
		imageMap[f_name].resize(divCnt.x * divCnt.y);
		LoadDivGraph(
			f_name.c_str(),
			divCnt.x * divCnt.y,
			divCnt.x,
			divCnt.y,
			divSize.x,
			divSize.y,
			&imageMap[f_name][0],
			true
		);
	}
	return imageMap[f_name];
}

void ImageMng::ReadGraph(void)
{
	// ------------------ ﾃﾞｰﾀﾍｯﾀﾞｰ読み込み --------------------------

	ActionHeader header = {};

	std::string actpath = "image/player.act";
	auto f = DxLib::FileRead_open(actpath.c_str());
	FileRead_read(&header.version, sizeof(header.version), f);
	int namesize;
	FileRead_read(&namesize, sizeof(namesize), f);
	header.fileName.resize(namesize);
	FileRead_read(&header.fileName[0], namesize, f);

	auto path = actpath.substr(0, actpath.rfind('/') + 1);
	path += header.fileName;

	FileRead_read(&header.actCnt, sizeof(header.actCnt), f);

	// -------------------- ﾃﾞｰﾀ部読み込み ----------------------------
	
	std::map<std::string, ActionData> data = {};

	for (int actIdx = 0; actIdx < header.actCnt; actIdx++)
	{
		int actNameSize;		// ｱｸｼｮﾝ名のｻｲｽﾞ
		std::string actName;	// ｱｸｼｮﾝ名
		FileRead_read(&actNameSize, sizeof(actNameSize), f);
		actName.resize(actNameSize);
		FileRead_read(&actName[0], actNameSize, f);

		FileRead_read(&data[actName].loop, sizeof(data[actName].loop), f);
		int anim;	// ｺﾏ数 ←この個数分だけforﾙｰﾌﾟして同一ｱｸｼｮﾝ名ごとにまとめる
		FileRead_read(&anim, sizeof(anim), f);

		for (int animIdx = 0; animIdx < anim; animIdx++)
		{
			FileRead_read(&data[actName].rect.x, sizeof(data[actName].rect.x), f);
			FileRead_read(&data[actName].rect.y, sizeof(data[actName].rect.y), f);
			FileRead_read(&data[actName].width, sizeof(data[actName].width), f);
			FileRead_read(&data[actName].height, sizeof(data[actName].height), f);
			FileRead_read(&data[actName].center.x, sizeof(data[actName].center.x), f);
			FileRead_read(&data[actName].center.y, sizeof(data[actName].center.y), f);
			FileRead_read(&data[actName].duration, sizeof(data[actName].duration), f);
			int actRc;	// 当たり判定用矩形の個数 ←この個数分だけforﾙｰﾌﾟして同一当たり判定ﾀｲﾌﾟごとにまとめる
			FileRead_read(&actRc, sizeof(actRc), f);
			for (int actRcIdx = 0; actRcIdx < actRc; actRcIdx++)
			{
				FileRead_read(&data[actName].actRect.x, sizeof(data[actName].actRect.x), f);
				FileRead_read(&data[actName].actRect.y, sizeof(data[actName].actRect.y), f);
				FileRead_read(&data[actName].actRcWidth, sizeof(data[actName].actRcWidth), f);
				FileRead_read(&data[actName].actRcHeight, sizeof(data[actName].actRcHeight), f);
			}
		}
	}

// ------------------------------------------------------------------

	if (imageMap.find(path) == imageMap.end())
	{
		imageMap[path].resize(1);
		imageMap[path][0] = LoadGraph(path.c_str(), false);
	}

}