#include <DxLib.h>
#include <string>
#include <vector>
#include <map>
#include "VECTOR2.h"
#include "ImageMng.h"

struct ActionHeader {
	float version;			// ̧�ق��ް�ޮ�
	std::string fileName;	// ̧�ٖ�
	int actCnt;				// ����݂̎�ސ� �����̌�������forٰ�߂��ı���݂��Ƃɂ܂Ƃ߂�
};

struct ActionData {
	bool loop;				// ��Ұ��݂�ٰ�߂��邩�ǂ���
	VECTOR2 rect;			// �����J�n�ʒu
	int width;				// 1�ς̉摜�̉��̒���
	int height;				// 1�ς̉摜�̏c�̒���
	VECTOR2 center;			// 1�ς̉摜�̒��S�_
	int duration;			// ��Ұ��݂̺ϊԊu
		int actRcType;			// �����蔻��p��`�̎��
		VECTOR2 actRect;		// �����蔻��p��`�̊J�n�ʒu
		int actRcWidth;			// �����蔻��p��`�̉��̒���
		int actRcHeight;		// �����蔻��p��`�̏c�̒���
};

ImageMng::ImageMng()
{
}


ImageMng::~ImageMng()
{
}

//loadGraph�p
const VEC_INT& ImageMng::GetID(std::string f_name)
{
	//end(�I�[)�܂�find(����)���Ă�������Ȃ��Ƃ�
	if (imageMap.find(f_name) == imageMap.end())
	{
		imageMap[f_name].resize(1);
		//f_name��۰�ނ��ĕۑ�
		imageMap[f_name][0] = LoadGraph(f_name.c_str(), false);
	}
	return imageMap[f_name];
}

//divGraph�p
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
	// ------------------ �ް�ͯ�ް�ǂݍ��� --------------------------

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

	// -------------------- �ް����ǂݍ��� ----------------------------
	
	std::map<std::string, ActionData> data = {};

	for (int actIdx = 0; actIdx < header.actCnt; actIdx++)
	{
		int actNameSize;		// ����ݖ��̻���
		std::string actName;	// ����ݖ�
		FileRead_read(&actNameSize, sizeof(actNameSize), f);
		actName.resize(actNameSize);
		FileRead_read(&actName[0], actNameSize, f);

		FileRead_read(&data[actName].loop, sizeof(data[actName].loop), f);
		int anim;	// �ϐ� �����̌�������forٰ�߂��ē��걸��ݖ����Ƃɂ܂Ƃ߂�
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
			int actRc;	// �����蔻��p��`�̌� �����̌�������forٰ�߂��ē��ꓖ���蔻�����߂��Ƃɂ܂Ƃ߂�
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