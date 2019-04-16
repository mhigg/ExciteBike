#include <DxLib.h>
#include <string>
#include <vector>
#include <map>
#include "VECTOR2.h"
#include "ImageMng.h"


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

const VEC_INT & ImageMng::GetActID(std::string f_name, std::string actName)
{
	if (imageMap.find(actName) == imageMap.end())
	{
		auto actData = GetAct(f_name, actName);
		auto animCnt = actData.size();
		imageMap[actName].resize(animCnt);
		for (int actIdx = 0; actIdx < animCnt; actIdx++)
		{
			LoadDivGraph(
				header[f_name].fileName.c_str(),
				1,
				actData[actIdx].rect.x,
				actData[actIdx].rect.y,
				actData[actIdx].width,
				actData[actIdx].height,
				&imageMap[actName][actIdx],
				true
			);
		}
	}
	return imageMap[actName];
}

const VEC_ACT & ImageMng::GetAct(std::string f_name, std::string actName)
{
	if (header.find(f_name) == header.end())
	{
		ReadBinary(f_name);
	}

	return data[actName];
}

void ImageMng::ReadBinary(std::string f_name)
{
	// ------------------ �ް�ͯ�ް�ǂݍ��� --------------------------

	header = {};

	std::string actpath = f_name;	// acţ��
	auto f = DxLib::FileRead_open(actpath.c_str());
	FileRead_read(&header[actpath].version, sizeof(header[actpath].version), f);
	int namesize;
	FileRead_read(&namesize, sizeof(namesize), f);
	header[actpath].fileName.resize(namesize);
	FileRead_read(&header[actpath].fileName[0], namesize, f);

	auto path = actpath.substr(0, actpath.rfind('/') + 1);
	header[actpath].fileName = path + header[actpath].fileName;

	FileRead_read(&header[actpath].actCnt, sizeof(header[actpath].actCnt), f);

	// -------------------- �ް����ǂݍ��� ----------------------------

	data = {};

	for (int actIdx = 0; actIdx < header[actpath].actCnt; actIdx++)
	{
		int actNameSize;		// ����ݖ��̻���
		std::string actName;	// ����ݖ�
		FileRead_read(&actNameSize, sizeof(actNameSize), f);
		actName.resize(actNameSize);
		FileRead_read(&actName[0], actNameSize, f);

		bool loop;		// ��Ұ��݂�ٰ�߂��邩�ǂ���
		FileRead_read(&loop, sizeof(loop), f);
		int anim;		// �ϐ� �����̌�������forٰ�߂��ē��걸��ݖ����Ƃɂ܂Ƃ߂�
		FileRead_read(&anim, sizeof(anim), f);
		data[actName].resize(anim);

		for (int animIdx = 0; animIdx < anim; animIdx++)
		{
			FileRead_read(&data[actName][animIdx].rect.x, sizeof(data[actName][animIdx].rect.x), f);
			FileRead_read(&data[actName][animIdx].rect.y, sizeof(data[actName][animIdx].rect.y), f);
			FileRead_read(&data[actName][animIdx].width, sizeof(data[actName][animIdx].width), f);
			FileRead_read(&data[actName][animIdx].height, sizeof(data[actName][animIdx].height), f);
			FileRead_read(&data[actName][animIdx].center.x, sizeof(data[actName][animIdx].center.x), f);
			FileRead_read(&data[actName][animIdx].center.y, sizeof(data[actName][animIdx].center.y), f);
			FileRead_read(&data[actName][animIdx].duration, sizeof(data[actName][animIdx].duration), f);
			int actRc;	// �����蔻��p��`�̌� �����̌�������forٰ�߂��ē��ꓖ���蔻�����߂��Ƃɂ܂Ƃ߂�
			FileRead_read(&actRc, sizeof(actRc), f);
			for (int actRcIdx = 0; actRcIdx < actRc; actRcIdx++)
			{
				FileRead_read(&data[actName][animIdx].actRcType, sizeof(data[actName][animIdx].actRcType), f);
				FileRead_read(&data[actName][animIdx].actRect.x, sizeof(data[actName][animIdx].actRect.x), f);
				FileRead_read(&data[actName][animIdx].actRect.y, sizeof(data[actName][animIdx].actRect.y), f);
				FileRead_read(&data[actName][animIdx].actRcWidth, sizeof(data[actName][animIdx].actRcWidth), f);
				FileRead_read(&data[actName][animIdx].actRcHeight, sizeof(data[actName][animIdx].actRcHeight), f);
			}
		}
	}
	FileRead_close(f);
}
