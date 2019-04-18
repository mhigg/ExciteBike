#pragma once
#include <mutex>
#include <vector>
#include <map>

struct ActionHeader {
	float version;			// ﾌｧｲﾙのﾊﾞｰｼﾞｮﾝ
	std::string fileName;	// ﾌｧｲﾙ名
	int actCnt;				// ｱｸｼｮﾝの種類数 ←この個数分だけforﾙｰﾌﾟしてｱｸｼｮﾝごとにまとめる
};

struct ActionData {
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

class VECTOR2;
using VEC_INT = std::vector<int>;
using VEC_ACT = std::vector<ActionData>;

//短縮定義
#define lpImageMng ImageMng::GetInstance()
#define IMAGE_ID(X) (ImageMng::GetInstance().GetID(X))

class ImageMng
{
public:
	static ImageMng &GetInstance(void)
	{
		static ImageMng s_instance;
		return s_instance;
	}

	// LoadGraph用
	const VEC_INT& GetID(std::string f_name);
	// LoadDivGraph対応
	const VEC_INT& GetID(std::string f_name, VECTOR2 divSize, VECTOR2 divCnt);
	// 読み込んだﾃﾞｰﾀから指定したｱｸｼｮﾝ名の画像を呼び出す
	const VEC_INT& GetActID(std::string f_name, std::string actName);
	// ActionDataを読み込み
	const VEC_ACT& GetAct(std::string f_name, std::string actName);

private:
	ImageMng();
	~ImageMng();

	// ﾊﾞｲﾅﾘﾃﾞｰﾀの読み込み 引数はactﾌｧｲﾙ
	void ReadBinary(std::string f_name);

	std::map<std::string, VEC_INT> imageMap;
	std::map<std::string, ActionHeader> header;
	std::map<std::string, VEC_ACT> data;
};