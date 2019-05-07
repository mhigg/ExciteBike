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
				imageHeader[f_name].fileName.c_str(),
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
	
	if (imageHeader.find(f_name) == imageHeader.end())
	{
		ReadBinary(f_name);
	}

	return actData[actName];
}

void ImageMng::ReadBinary(std::string f_name)
{
	// ------------------ �ް�ͯ�ް�ǂݍ��� --------------------------

	imageHeader = {};

	std::string actpath = f_name;	// acţ��
	auto f = DxLib::FileRead_open(actpath.c_str());
	FileRead_read(&imageHeader[actpath].version, sizeof(imageHeader[actpath].version), f);
	int namesize;
	FileRead_read(&namesize, sizeof(namesize), f);
	imageHeader[actpath].fileName.resize(namesize);
	FileRead_read(&imageHeader[actpath].fileName[0], namesize, f);

	auto path = actpath.substr(0, actpath.rfind('/') + 1);
	imageHeader[actpath].fileName = path + imageHeader[actpath].fileName;

	FileRead_read(&imageHeader[actpath].actCnt, sizeof(imageHeader[actpath].actCnt), f);

	// -------------------- �ް����ǂݍ��� ----------------------------

	actData = {};

	for (int actIdx = 0; actIdx < imageHeader[actpath].actCnt; actIdx++)
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
		actData[actName].resize(anim);

		for (int animIdx = 0; animIdx < anim; animIdx++)
		{
			FileRead_read(&actData[actName][animIdx].rect.x, sizeof(actData[actName][animIdx].rect.x), f);
			FileRead_read(&actData[actName][animIdx].rect.y, sizeof(actData[actName][animIdx].rect.y), f);
			FileRead_read(&actData[actName][animIdx].width, sizeof(actData[actName][animIdx].width), f);
			FileRead_read(&actData[actName][animIdx].height, sizeof(actData[actName][animIdx].height), f);
			FileRead_read(&actData[actName][animIdx].center.x, sizeof(actData[actName][animIdx].center.x), f);
			FileRead_read(&actData[actName][animIdx].center.y, sizeof(actData[actName][animIdx].center.y), f);
			FileRead_read(&actData[actName][animIdx].duration, sizeof(actData[actName][animIdx].duration), f);
			int actRc;	// �����蔻��p��`�̌� �����̌�������forٰ�߂��ē��ꓖ���蔻�����߂��Ƃɂ܂Ƃ߂�
			FileRead_read(&actRc, sizeof(actRc), f);
		}
	}
	FileRead_close(f);
}
